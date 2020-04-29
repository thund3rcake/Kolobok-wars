#include "servertools.h"

ServerTools::ServerTools()
{

}

ServerTools::~ServerTools()
{

}

void ServerTools::setNewUdpPacket() {
    bool gotten = false;
    UdpServer::Packet newPacket = udpServer->getPacket(gotten);

    if (gotten)
        switch(newPacket.properties.getType()) {

        case MovingObjectProperties::Player:
            qDebug() << "player";
            //TODO
            break;

        case MovingObjectProperties::Timestamp: {
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

            break;
        }

        case MovingObjectProperties::Bullet:
            qDebug() << "bullet";
            //TODO
            break;
        }

}
