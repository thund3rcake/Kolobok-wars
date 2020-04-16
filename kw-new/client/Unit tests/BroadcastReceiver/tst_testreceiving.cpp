#include <QtTest>
#include "testreceiver.h"
// add necessary includes here

//Run BroadcastSender before testing
//Nothing happens: BroadcastReceiver don't receive information
//2 passed, 1 failed: BroadcastReceiver read wrong
//3 passed: success

class testReceiving : public QObject
{
    Q_OBJECT

public:

private slots:
    void test_case1();

};

void testReceiving::test_case1()
{
    BroadcastData dataToReceive(
                    QStringSignature, //signature
                    "myServer",       //serverName
                    "myMap",          //mapName
                    111,              //tcpPort
                    NET_VERSION,      //version
                    NET_SUBVERSION,   //subversion
                    0,                //bots
                    0,                //players
                    12                //maxplayers
            );
    QVector<ServerAbout> servers;
    testReceiver rec(servers);
    while (rec.serversIsEmpty()) {
        rec.makeItToRead();
    }
    qDebug() << "Size " << servers.size();
    QCOMPARE(rec.getLastServerAboutInfo().getSignature() , dataToReceive.getSignature());
    QCOMPARE(rec.getLastServerAboutInfo().getServerName(), dataToReceive.getServerName());
    QCOMPARE(rec.getLastServerAboutInfo().getMapName(), dataToReceive.getMapName());
    QCOMPARE(rec.getLastServerAboutInfo().getTcpPort(), dataToReceive.getTcpPort());
    QCOMPARE(rec.getLastServerAboutInfo().getVersion(), dataToReceive.getVersion());
    QCOMPARE(rec.getLastServerAboutInfo().getSubversion(), dataToReceive.getSubversion());
    QCOMPARE(rec.getLastServerAboutInfo().getBots(), dataToReceive.getBots());
    QCOMPARE(rec.getLastServerAboutInfo().getPlayers(), dataToReceive.getPlayers());
    QCOMPARE(rec.getLastServerAboutInfo().getMaxPlayers(), dataToReceive.getMaxPlayers());

}

QTEST_APPLESS_MAIN(testReceiving)
#include "tst_testreceiving.moc"
