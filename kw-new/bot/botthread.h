#ifndef BOTTHREAD_H
#define BOTTHREAD_H

#include "thread.h"
#include "sharedtypes.h"
#include "Datagramms.h"
#include "aibot.h"
#include <QLinkedList>

class BotThread: public Thread
{
public:
    BotThread();

    void run() override;
    void getProperty() override;

private:
    MovingObjectProperties updateMovingProperties(Shared & sharedData, MovingObjectProperties currentProps);
    QLinkedList<AIBot *> aiBots;
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
