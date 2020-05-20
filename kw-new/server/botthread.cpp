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
    botProps.setId(id);
    botProps.setType(MovingObjectProperties::Player);
    botProps.setPosition(getRespawnPlace());
    botProps.setTimestamp(25);
    sharedData.playerLatencyById.writeLock();
    sharedData.playerLatencyById.get().insert(id, 1);
    sharedData.playerLatencyById.writeUnlock();
    qDebug() << "bot thread initialized; respawn place = " << botProps.getPosition();
}

BotThread::~BotThread()
{
    aiBots.clear();
}

const MovingObjectProperties & BotThread::getBotProperties() {
    QMutexLocker locker(&propertiesMutex);
    return botProps;
}

void BotThread::getDamage() {
    QMutexLocker locker(&propertiesMutex);
    quint8 hp = botProps.getHp();
    if (botProps.getHp() > consts::bulletDamage) {
        botProps.setHp(hp - consts::bulletDamage);
    } else {
        botProps.setHp(0);
    }
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
    bool toQuit = false;

    while(!toQuit) {
        toQuit = sharedData.quit.get();

        if (!botProps.getHp()) {
            botProps.setHp(100);
            botProps.setPosition(getRespawnPlace());
        }

        //qDebug() << "botthread::run start" << botProps.getId();
        updateMovingProperties(sharedData);
        //qDebug() << "botthread::run mprops updated" << botProps.getPosition();
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
    botProps.setIntent(newProps.getIntent());
    updateCoordinates();
}


void BotThread::updateCoordinates () {
    if ( botProps.getTimestamp() <= consts::sendTimerInterval*1.25 ) {
        QPointF increment = botProps.getIntent().toPointF()*botProps.getTimestamp()/25;
        QPointF intentedDot = botProps.getPosition();

        for (int i = 0; i < 5; i++) {
            intentedDot += increment;
            qreal thenTheClosest = distanceToTheClosestPlayer(intentedDot);
            if (sharedData.gameMap.get() -> isDotAvailable(intentedDot.toPoint())
                && (thenTheClosest >= 2*consts::playerSize
                    || thenTheClosest > distanceToTheClosestPlayer(botProps.getPosition()))) {
                propertiesMutex.lock();
                botProps.setPosition(intentedDot);
                propertiesMutex.unlock();
            }
        }
    }
}

qreal BotThread::distanceToTheClosestPlayer (const QPointF position ) {
    qreal minLength = 1000;
    foreach ( PlayerThread * player, sharedData.playerById.get() ) {
        if (player->getId() != this->id) {
            qreal lgth = getLength(position, player -> getMovProperties().getPosition() );
            if (lgth < consts::playerSize*2) {
                return lgth;
            }
            minLength = minLength < lgth ? minLength : lgth;
        }
    }
    foreach ( BotThread * bot, sharedData.botById.get() ) {
        if (bot->getId() != this->id) {
            qreal lgth = getLength(position, bot->getBotProperties().getPosition() );
            if (lgth < consts::playerSize*2) {
                return lgth;
            }
            minLength = minLength < lgth ? minLength : lgth;
        }
    }
  return minLength;
}

qreal BotThread::getLength(QPointF a, QPointF b) {
    return sqrt( (a.rx() - b.rx())*(a.rx() - b.rx()) + (a.ry() - b.ry())*(a.ry() - b.ry()) );
}

