#include "botthread.h"
#include "sharedobject.h"
#include "playerthread.h"
#include <QLinkedList>
#include "aibot.h"
#include "Entity.h"

BotThread::BotThread(quint16 id, Shared & sharedData, QObject * parent):
    QThread(parent),
    sharedData(sharedData),
    id(id) {
    sharedData.playerLatencyById.writeLock();
    sharedData.playerLatencyById.get().insert(id, 1);
    sharedData.playerLatencyById.writeUnlock();

    timestampSendTimer->setInterval(5000);
    QObject::connect(timestampSendTimer, SIGNAL(timeout()),
                     this, SLOT(sendTimestamp()));
    timestampSendTimer->start();
    timer.start();
}

void BotThread::run() {
   while(1) {
        updateMovingProperties(sharedData);
       usleep(100);
    }
}

void BotThread::getProperty()
{

}

quint16 BotThread::getId()
{
    return id;
}

void BotThread::updateMovingProperties(Shared & sharedData) {
    quint16 id = botProps.getId();
    AIBot * currentBot = nullptr;
    MovingObjectProperties newProps = MovingObjectProperties();

    foreach(AIBot * aiBot, aiBots) { // find our bot
        if(aiBot->getId() == id) {
            currentBot = aiBot;
            currentBot->setProperties(botProps);
        }
    }

    if (currentBot == nullptr) { // create if not found
        currentBot = new AIBot(botProps);
        aiBots.append(currentBot);
    }


    currentBot->switchState(sharedData); // change the bot state
    newProps = currentBot->action(sharedData, botProps);
    updateCoordinates(botProps);
}


void BotThread::updateCoordinates (MovingObjectProperties & prop) {
    if ( prop.getTimestamp() <= consts::sendTimerInterval * 1.25 ) {
        QPointF increment = prop.getIntent().toPointF()*prop.getTimestamp()/25;
        QPointF intentedDot = prop.getPosition();

        for (int i = 0; i < 5; i++) {
            intentedDot += increment;
            if ( isThereCollisionsWithTheOthers(intentedDot) >= isThereCollisionsWithTheOthers(botProps.getPosition())
            && sharedData.gameMap.get() -> isDotAvailable(intentedDot.toPoint()) ) {
                prop.setPosition(intentedDot);
            }
        }
    }
    return;
}

qreal BotThread::isThereCollisionsWithTheOthers ( QPointF position ) {
    foreach ( PlayerThread * player, sharedData.playerById.get() ) {
        if (player->getId() != this->id) {
            qreal lgth = getLength(position, player -> getMovProperties().getPosition() );
            if (lgth < consts::playerSize*2) {
                return lgth;
            }
        }
    }
  return consts::playerSize*2;
}


qreal BotThread::getLength(QPointF a, QPointF b) {
    return sqrt( (a.rx() - b.rx())*(a.rx() - b.rx()) + (a.ry() - b.ry())*(a.ry() - b.ry()) );
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
