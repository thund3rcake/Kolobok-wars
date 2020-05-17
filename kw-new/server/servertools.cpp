#include "servertools.h"
#include "botthread.h"

ServerTools::ServerTools(
                         const QString & server,
                         const QString & map,
                         quint16 port,
                         quint8 mPlayers,
                         quint8 bots,
                         quint16 portForSending,
                         QTextEdit * console,
                         QObject * parent
                         ):
    QObject(parent),
    serverName(server),
    mapName(map),
    port(port),
    maxPlayers(mPlayers),
    bots(bots),
    console(console),
    broadcastSender(NULL),
    udpServer(NULL),
    tcpServer(NULL) {

    console->clear();
    curTime.start();

    data.nextPlayerId.get() = 1;
    data.nextBulletId.get() = 1;
    data.quit.get() = false;

    broadcastSender = new BroadcastSender(serverName, mapName, data, portForSending,
                                          port, maxPlayers, bots, this);

    udpServer = new UdpServer(port, this);
    connect(udpServer, SIGNAL(newPacket()),
            this, SLOT(setNewUdpPacket()));

    udpServer->start();

    try {
        console->insertHtml("Starting TCP-server... &nbsp");
        TcpServer * tcpServer = new TcpServer(port, maxPlayers, *udpServer, data, this);
        QObject::connect(tcpServer, &TcpServer::newIP, this, &ServerTools::IPtoConsole);
    } catch (TcpServer::Exception exception) {
        console->insertHtml("[Fail]<br />");
        console->insertHtml(exception.message + "<br />");
        tcpServer = NULL;
    }

    if (tcpServer) {
        console->insertHtml("[Done]<br />");

    }

    try {
        data.gameMap.get() = new Map("./maps/" + map + "/" + map + ".xml");
    } catch (Exception excp) {
        qDebug() << "ServerTools::ServerTools: Map has crashed" << excp.message;
    }

    for (int i = 0; i < bots; i++) {

        quint16 id = 0;

        data.nextPlayerId.writeLock();
        BotThread * bot = new BotThread(data.nextPlayerId.get(), data, this);
        id = data.nextPlayerId.get();
        data.nextPlayerId.get()++;
        data.nextPlayerId.writeUnlock();

        data.botById.writeLock();
        data.botById.get().insert(id, bot);
        data.botById.writeUnlock();

        bot->start();
    }
}

ServerTools::~ServerTools() {
    qDebug() << "~ServTools";

    data.quit.writeLock();
    data.quit.get() = true;
    data.quit.writeUnlock();

    delete broadcastSender;

    for (PlayersMap::iterator player = data.playerById.get().begin();
        player != data.playerById.get().end(); ++player) {
        player.value()->wait();
    }

    for (BotsMap::iterator bot = data.botById.get().begin();
        bot != data.botById.get().end(); ++bot) {
        bot.value()->wait();
    }

    for (BulletsMap::iterator blt = data.bulletById.get().begin();
        blt != data.bulletById.get().end(); ++blt) {
        delete blt.value();
    }

    disconnect( udpServer, SIGNAL( newPacket() ),
                this,      SLOT( setNewUdpPacket() ));

    delete udpServer;
    delete tcpServer;
}

BroadcastSender & ServerTools::getBroadcastSender() {
    return * broadcastSender;
}

UdpServer & ServerTools::getUdpServer() {
    return * udpServer;
}

Shared & ServerTools::getShared() {
    return data;
}

qint32 ServerTools::getCurentTime() {
    return curTime.elapsed();
}

void ServerTools::IPtoConsole(QString ipStr) {
    qDebug() << "ST: " << ipStr;
    emit newPlayer(ipStr);
}

void ServerTools::setNewUdpPacket() {
    bool gotten = false;
    UdpServer::Packet newPacket = udpServer->getPacket(gotten);

    if (gotten)
        switch(newPacket.properties.getType()) {

        break; case MovingObjectProperties::Player: {
            data.playerById.readLock();
            QMap<qint32, PlayerThread*>::iterator playerIt = data.playerById.get().find((newPacket.properties.getId()));
            if (playerIt != data.playerById.get().end()
                && !playerIt.value()->getPeerAddr()->isNull()
                && *(playerIt.value()->getPeerAddr()) == newPacket.address) {

                PlayerThread * player = playerIt.value();

                player->getUdpQueue()->writeLock();
                player->getUdpQueue()->get().enqueue(newPacket.properties);
                player->getUdpQueue()->writeUnlock();
            }
            data.playerById.readUnlock();
        }

        break; case MovingObjectProperties::Timestamp: {
            qint32 newLatency = getCurentTime() - newPacket.properties.getTimestamp();
            //qDebug() << newLatency;

            data.playerLatencyById.writeLock();
            QMap<qint32, qint32>::iterator latency =
                data.playerLatencyById.get().find( newPacket.properties.getId());

            if  (latency != data.playerLatencyById.get().end()) {
                latency.value() = newLatency;
            }
            data.playerLatencyById.writeUnlock();
        }

        break; case MovingObjectProperties::Bullet: {
//            qDebug() << "bullet";
//            data.bulletById.readLock();
//            BulletsMap::iterator bulletIt =
//                    data.bulletById.get().find(newPacket.properties.getId());
//            bool newBullet = (bulletIt != data.bulletById.get().end());
//            data.bulletById.readUnlock();
//            if (newBullet) {
//               data.nextBulletId.writeLock();
//               quint16 id = data.nextBulletId.read();
//               data.nextBulletId.get()++;
//               data.nextBulletId.writeUnlock();
            }
        }
}
