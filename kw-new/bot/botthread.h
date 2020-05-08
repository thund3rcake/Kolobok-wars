#ifndef BOTTHREAD_H
#define BOTTHREAD_H

#include "thread.h"
#include "aiprocessor.h"

class BotThread: public Thread
{
public:
    BotThread();

    void run() override;
    void getProperty() override;

private:
    AIProcessor aiProcessor;

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
