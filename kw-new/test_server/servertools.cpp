#include "servertools.h"
#include "botthread.h"

ServerTools::ServerTools(
                         const QString & server,
                         const QString & map,
                         quint16 port,
                         quint8 mPlayers,
                         QTextEdit * console,
                         QObject * parent
                         ):
    QObject(parent),
    serverName(server),
    mapName(map),
    port(port),
    maxPlayers(mPlayers),
    console(console),
    broadcastSender(NULL),
    udpServer(NULL),
    tcpServer(NULL),
    quit(false) {

    console->clear();
    curTime.start();
    data.nextPlayerId.get() = 1;
    data.nextBulletId.get() = 1;

    broadcastSender = new BroadcastSender(serverName, mapName, data, 27030,
                                          port, maxPlayers, this);

    udpServer = new UdpServer(port, this);
    connect(udpServer, SIGNAL(newPacket()),
            this, SLOT(setNewUdpPacket()));

    udpServer->start();

    try {
        console->insertHtml("Starting TCP-server... &nbsp");
        TcpServer * tcpServer = new TcpServer(port, maxPlayers, *udpServer, data, quit, this);
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
}

ServerTools::~ServerTools()
{
    qDebug() << "~ServTools";
    quit = true;
    delete broadcastSender;
    disconnect( udpServer, SIGNAL( newPacket() ),
                this,      SLOT( setNewUdpPacket() ));
    delete udpServer;
    for (PlayersMap::iterator it = data.playerById.get().begin();
         it != data.playerById.get().end(); ++it) {
        it.value()->wait();
        delete it.value();
        qDebug() << "player deleted";
    }
    delete tcpServer;
    qDebug() << "~~ServTools";
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

void ServerTools::setNewUdpPacket() {
    bool gotten = false;
    UdpServer::Packet newPacket = udpServer->getPacket(gotten);

    if (gotten)
        switch(newPacket.properties.getType()) {

        break; case MovingObjectProperties::Player: {
            data.playerById.readLock();
            //qDebug() << "ServerTools Readlock";
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
            //qDebug() << "ServerTools ReadUnlock";
        }

        break; case MovingObjectProperties::Timestamp: {
            //qDebug() << "timestamp";
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
