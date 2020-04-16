#ifndef TESTRECEIVER_H
#define TESTRECEIVER_H

#include "BroadcastReceiver.h"

class testReceiver : public BroadcastReceiver {
public:

    testReceiver(
            QVector<ServerAbout> & servers,
            QWidget * parent = 0
            );

    bool serversIsEmpty();
    BroadcastData & getLastServerAboutInfo();
    void makeItToRead();

private:
    QVector<ServerAbout> &servers;
};

#endif // TESTRECEIVER_H
