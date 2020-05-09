#include "botthread.h"
#include "sharedobject.h"
#include "playerthread.h"
#include <QLinkedList>
#include "aibot.h"
#include "Entity.h"

BotThread::BotThread() {}

void BotThread::run() {
   while(1) {
       playerMovProperties = updateMovingProperties(sharedData, playerMovProperties);
       usleep(100);
    }
}

void BotThread::getProperty()
{

}

MovingObjectProperties BotThread::updateMovingProperties(Shared & sharedData, MovingObjectProperties currentProps) {
    quint16 id = currentProps.getId();
    AIBot * currentBot = nullptr;
    MovingObjectProperties newProps = MovingObjectProperties();

    foreach(AIBot * aiBot, aiBots) { // find our bot
        if(aiBot->getId() == id)
            currentBot = aiBot;
    }

    if (currentBot == nullptr) { // create if not found
        currentBot = new AIBot(currentProps);
        aiBots.append(currentBot);
    }

    currentBot->switchState(sharedData); // change the bot state
    newProps = currentBot->action(sharedData, currentProps);
    return newProps;
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
