#ifndef BOTTHREAD_H
#define BOTTHREAD_H

//#include "thread.h"
#include "sharedtypes.h"
#include "Datagramms.h"
#include "aibot.h"
#include <QLinkedList>

class BotThread: public QThread
{
public:
    BotThread(quint16 id, Shared & sharedData, QObject * parent);

    void run();
    void getProperty();
    quint16 getId();

private:
    void updateCoordinates (MovingObjectProperties & prop);
    qreal isThereCollisionsWithTheOthers ( QPointF position );
    qreal getLength(QPointF a, QPointF b);
    void updateMovingProperties(Shared & sharedData);
    QLinkedList<AIBot *> aiBots;
    MovingObjectProperties botProps;
    Shared & sharedData;
    QTime timer;
//    QTimer * timestampSendTimer;
    quint16 id;
};

//class botThread: public Thread {
//    ...
//};

//void botThread::run() {
//    ...

//    while (1) {
//        foreach (Thread * player, sharedData.playerById.get()) {    // <-- players and bots
//            if (!(player->isFinished()) && player->getId() != id) {
//                teamAnalyse(prop.getTeam());
//                positionAnalyse(prop.getPosition());
//                hpAnalyse(prop.getHp());
//                ...
//            }
//            playerMovProperties = WhatTheBotMustDo(...);
//            usleep(100);
//        }
//    }
//}

#endif // BOTTHREAD_H
