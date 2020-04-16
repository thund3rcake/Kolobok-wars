#include "testsender.h"


testSender::testSender(
            const QString & serverName,
            const QString & mapName,
            quint16 port,
            quint16 tcpPort,
            quint8  maxPlayers,
            QObject * parent
           ) :
    BroadcastSender(serverName, mapName, port, tcpPort, maxPlayers, parent) {}

void testSender::testRun() {
    run();
}
