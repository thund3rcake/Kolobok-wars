#include <Datagramms.h>
#include<Weapon.h>
#include <QtCore>
#include<assert.h>
#include<iostream>


int main (){

    //    GameProperties::Type type = GameProperties::UdpPort;
    //    const QString firstQString = QString("first");
    //    const QString secondQString = QString("second");
    //    qint64 firstQInt = 1;
    //    qint64 secondQInt = 2;
    //    qreal firstQReal = 3.0;
    //    qreal secondQReal = 4.0;

    //    GameProperties data1 (
    //                type,
    //                firstQString,
    //                secondQString,
    //                firstQInt,
    //                secondQInt,
    //                firstQReal,
    //                secondQReal
    //                );

    Weapon::Type type = Weapon::Blaster;
    Weapon::State state = Weapon::NoFire;
    const QPointF target = QPointF(1.0, 0.0);
    quint16 masterId = 1;

//    const GameWorld::Weapon data1(
//                type,
//                state,
//                target,
//                masterId
//                );

    quint32 timestamp = 1;
    MovingObjectProperties::Type type1 = MovingObjectProperties::Player;
    MovingObjectProperties::Team team = MovingObjectProperties::Red;
    quint16 id = 2;
    const QPointF position = QPointF(1.0, 0.0);
    const QVector2D intent = QVector2D(2.0, 0.0);
    const QVector2D head = QVector2D(3.0, 0.0);
    quint8 hp = 3;
    const Weapon weapon = Weapon(
                                                                                                                                type,
                                                                                                                                state,
                                                                                                                                target,
                                                                                                                                masterId
                                                                                                                                );

    const MovingObjectProperties data1(
                timestamp,
                type1,
                team,
                id,
                position,
                intent,
                head,
                hp,
                weapon
    );


//    const QString & signature = QString("sign");
//    const QString & servername = QString("Sname");
//    const QString & mapName = QString("Mname");
//    quint16 tcpPort = 1;
//    quint8 version = 2;
//    quint8 subversion = 3;
//    quint8 bots = 4;
//    quint8 players = 5;
//    quint8 maxPlayers = 6;

//    BroadcastData data1(
//                signature,
//                servername,
//                mapName,
//                tcpPort,
//                version,
//                subversion,
//                bots,
//                players,
//                maxPlayers
//                );


    QByteArray buffer = QByteArray();
    QDataStream wStream(&buffer, QIODevice::OpenModeFlag::WriteOnly);

    wStream << data1;

    QDataStream rStream(buffer);

//    GameProperties data2;
//    GameWorld::Weapon data2;
    MovingObjectProperties data2;
//    BroadcastData data2;

    rStream >> data2;

    assert(data1 == data2);

    return 0;
}