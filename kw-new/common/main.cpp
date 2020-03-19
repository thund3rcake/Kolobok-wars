#include <Datagramms.h>
#include <QtCore>
#include<assert.h>
#include<iostream>

int main (){
//    MetaRegistrator<BroadcastData> broadcastDataRegistrator (MetaRegistrator<BroadcastData>("BroadcastData"));
//    const QString signature = QString("sign");
//    const QString serverName = QString("server");
//    const QString mapName = QString("map");
//    const quint16 tcpPort = 1;
//    const quint8 version = 2;
//    const quint8 subversion = 3;
//    const quint8 bots = 4;
//    const quint8 players = 5;
//    const quint8 maxPlayers = 6;

//    BroadcastData data1(
//                broadcastDataRegistrator,
//                signature,
//                serverName,
//                mapName,
//                tcpPort,
//                version,
//                subversion,
//                bots,
//                players,
//                maxPlayers
//    );

//    QByteArray buffer = QByteArray();
//    QDataStream wStream(&buffer, QIODevice::OpenModeFlag::WriteOnly);

//    wStream << data1;

//    QDataStream rStream(buffer);

//    BroadcastData data2;

//    rStream >> data2;

//    std::cout << data1.getSignature().toStdString() << std::endl;
//    std::cout << data2.getSignature().toStdString() << std::endl;


//    assert(data1.getSignature() == data2.getSignature());

    return 0;
}