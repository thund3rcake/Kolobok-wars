#include "testreceiver.h"

testReceiver::testReceiver(
            QVector<ServerAbout> & servers,
            QWidget * parent
            ):
    BroadcastReceiver(servers, parent), servers(servers) {}

bool testReceiver::serversIsEmpty() {
    if (servers.size() == 0)
        return true;
    return false;
}

BroadcastData & testReceiver::getLastServerAboutInfo() {
    return servers[servers.size() - 1].data;
}

void testReceiver::makeItToRead() {
    emit this->QUdpSocket::readyRead();
}
