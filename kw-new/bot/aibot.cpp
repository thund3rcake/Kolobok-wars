#include "aibot.h"
#include "Datagramms.h"
#include "GameWorldConsts.h"
#include "sharedtypes.h"
#include "playerthread.h"
#include "sharedobject.h"
#include <QLinkedList>
#include "aibot.h"
#include "utilityalgorithms.h"
#include "Entity.h"

bool AIBot::isVisible(QPointF playerPos, Shared & sharedData) {
    quint32 velocity = 32;
    QVector2D move = QVector2D(playerPos.x() - position.x(), playerPos.y() - position.y());
    quint16 distance = move.length();
    qfloat16 moveTime = distance / velocity;
    QPointF unitIncrement = (move / moveTime).toPointF();

    // split the vector into unit moves; if any of the moves is irrelevant ==> dot is not visible
    for(int i = 0; i < qCeil(moveTime); i++)
        if(!sharedData.gameMap.get()->isDotAvailable((position + unitIncrement).toPoint()))
            return false;
    return true;
}

void AIBot::attack(MovingObjectProperties playerProps)
{
    fire(playerProps.getPosition(), 0);
}

void AIBot::pursuit(MovingObjectProperties playerProps, Shared & sharedData)
{
    QVector2D intent = UtilityAlgorithms::getMoveIntent(
                position, playerProps.getPosition(), sharedData, consts::stride
                );
    this->intent = intent;
}



AIBot::AIBot(MovingObjectProperties props) {
   state = Patrol;
   team = props.getTeam();
   hp = props.getHp();
   // head = props->getHead();
   weapon = props.getWeapon();
   position = props.getPosition();
   id = props.getId();
}

void AIBot::fire(QPointF target, int type) {
    // TODO: implement
}

void AIBot::switchState(Shared & sharedData) {
    // for now, the logic is: bot's movement is dependent on the nearest player to it.
    // TODO: smarter system
    MovingObjectProperties nearestPlayerProps;
    foreach (PlayerThread * player, sharedData.playerById.get())
        if (!(player->isFinished()) && player->getId() != id) {
            // find the nearest player
            nearestPlayerProps = player->getMovProperties();
        }

    switch (state) {
        case Attack:
            if(hp <= consts::hpEscape)
                state = Escape;
            // TODO: if no visible enemies ==> patrol
            break;
        case Pursuit:
            if(isVisible(nearestPlayerProps.getPosition(), sharedData))
                state = Attack;
            // TODO: player is dead ==> patrol
            break;
        case Patrol:
            if(isVisible(nearestPlayerProps.getPosition(), sharedData) && hp <= consts::hpEscape)
                state = Escape;
            if(isVisible(nearestPlayerProps.getPosition(), sharedData) && hp > consts::hpEscape)
                state = Attack;
            break;
        case Escape:
            if(!isVisible(nearestPlayerProps.getPosition(), sharedData))
                state = Patrol;
            break;
        default:
            break;
    }
}

MovingObjectProperties AIBot::action(Shared & sharedData, MovingObjectProperties currentProps) {
    // for now, the logic is: bot's movement is dependent on the nearest player to it.
    // TODO: smarter system
    MovingObjectProperties nearestPlayerProps;
    MovingObjectProperties newProps = MovingObjectProperties();
    foreach (PlayerThread * player, sharedData.playerById.get())
        if (!(player->isFinished()) && player->getId() != id) {
            // find the nearest player
            nearestPlayerProps = player->getMovProperties();
        }

    switch (state) {
        case Attack:
            attack(nearestPlayerProps);
            break;
        case Pursuit:
            pursuit(nearestPlayerProps, sharedData);
            break;
        case Patrol:
            // patrol
            break;
        case Escape:
            // escape
            break;
        default:
            break;
    }
    newProps.setIntent(intent);
    newProps.setHp(hp);
    newProps.setWeapon(weapon);
    return newProps;
}

void AIBot::setProperties(MovingObjectProperties props)
{
    position = props.getPosition();
    hp = props.getHp();
    head = props.getHead();
}


