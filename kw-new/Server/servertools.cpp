#include "servertools.h"

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
    console(console)
{
    console->clear();
    curTime.start();
    data.nextPlayerId.get() = 1;

    broadcastSender = new BroadcastSender(serverName, mapName, 27030,
                                          port, maxPlayers, this);
    udpServer = new UdpServer(port, this);
    connect(udpServer, SIGNAL(newPacket()),
            this, SLOT(setNewUdpPacket()));
    udpServer->start();

    try {
        console->insertHtml("Starting TCP-server... &nbsp");
        TcpServer * tcpServer = new TcpServer(port, *udpServer, data, this);
    } catch (TcpServer::Exception exception) {
        console->insertHtml("[Fail]<br />");
        console->insertHtml(exception.message + "<br />");
        tcpServer = NULL;
    }

    if (tcpServer) {
        console->insertHtml("[Done]<br />");
    }

    try {
        data.gameMap.get() = new Map("./maps/" + map + ".xml");
    } catch (Exception excp) {
        qDebug() << "ServerTools::ServerTools: Map has crashad" << excp.message;
    }
}

ServerTools::~ServerTools()
{
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

void ServerTools::setNewUdpPacket() {
    bool gotten = false;
    UdpServer::Packet newPacket = udpServer->getPacket(gotten);

    if (gotten)
        switch(newPacket.properties.getType()) {

        break; case MovingObjectProperties::Player: {
            qDebug() << "player";
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
            qDebug() << "timestamp";
            qint32 newLatency = getCurentTime() - newPacket.properties.getTimestamp();
            qDebug() << newLatency;

            data.playerLatencyById.writeLock();
            QMap<qint32, qint32>::iterator latency =
                data.playerLatencyById.get().find( newPacket.properties.getId());

            if  (latency != data.playerLatencyById.get().end()) {
                latency.value() = newLatency;
            }
            data.playerLatencyById.writeUnlock();
        }

        break; case MovingObjectProperties::Bullet:
            qDebug() << "bullet";
            data.bulletById.readLock();
            BulletsMap::iterator bulletIt =
                    data.bulletById.get().find(newPacket.properties.getId());
            bool newBullet = (bulletIt != data.bulletById.get().end());
            data.bulletById.readUnlock();
            if (newBullet) {
               data.nextBulletId.writeLock();
               quint16 id = data.nextBulletId.read();
               data.nextBulletId.get()++;
               data.nextBulletId.writeUnlock();
            }

            break;
        }
}
