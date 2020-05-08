#include "botthread.h"
#include "aiprocessor.h"

BotThread::BotThread()
{
    aiProcessor = AIProcessor();
}

void BotThread::run() {
   while(1) {
       playerMovProperties = aiProcessor.updateMovingProperties(sharedData, playerMovProperties);
       usleep(100);
    }
}

void BotThread::getProperty()
{

}

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
