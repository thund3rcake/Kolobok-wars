#ifndef TESTSENDER_H
#define TESTSENDER_H

#include "BroadcastSender.h"

class testSender : BroadcastSender {
public:
    testSender(
            const QString & serverName,
            const QString & mapName,
            quint16 port,
            quint16 tcpPort,
            quint8  maxPlayers,
            QObject * parent = 0
           );
    void testRun();
};

#endif // TESTSENDER_H
