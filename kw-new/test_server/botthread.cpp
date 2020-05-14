#include "botthread.h"
#include "sharedobject.h"
#include "playerthread.h"
#include <QLinkedList>
#include "aibot.h"
#include "Entity.h"
#include <iostream>

BotThread::BotThread(quint16 id, Shared & sharedData, QObject * parent):
    QThread(parent),
    sharedData(sharedData),
    id(id) {
    botProps = MovingObjectProperties(parent);
    botProps.setEmptyProperty();
    botProps.setPosition(getRespawnPlace());
    sharedData.playerLatencyById.writeLock();
    sharedData.playerLatencyById.get().insert(id, 1);
    sharedData.playerLatencyById.writeUnlock();
    qDebug() << "bot thread initialized; respawn place = " << botProps.getPosition();
}


QPointF BotThread::getRespawnPlace() {
    quint16 x = rand() % consts::mapSizeX, y = rand() % consts::mapSizeY;
    srand (time(NULL));
    while(!(sharedData.gameMap.get()->isDotAvailable(QPoint(x, y)))) {
        x = rand() % rand() % consts::mapSizeX;
        y = rand() % rand() % consts::mapSizeY;
    }
    return QPointF(x, y);
}

void BotThread::run() {
    int count = 0;
    while(1) {
        //qDebug() << "botthread::run start" << botProps.getId();
        updateMovingProperties(sharedData);
        //qDebug() << "botthread::run mprops updated" << botProps.getPosition();
        MovingObjectProperties property = botProps;
        //if(count % int(1e10) == 0)
        //    qDebug() << "botthread::run mprops updated" << botProps.getPosition();
        /* std::cout << "SEND PACKET: " << property.getTimestamp() << " " << property.getType() << " " <<
                    property.getTeam() << " " << property.getId() << " " << property.getPosition() <<
                    " " << property.getIntent() << " " << " " <<
                    property.getHead() << " " << property.getHp() << " " <<
                    property.getWeapon().getType() << " " << property.getWeapon().getState() << " " << property.getWeapon().getTarget() << " " <<
                    property.getWeapon().getMasterId(); */
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
        currentBot = new AIBot(sharedData, botProps);
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

