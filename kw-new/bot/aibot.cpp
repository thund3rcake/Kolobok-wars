#include "aibot.h"
#include "Datagramms.h"
#include "GameWorldConsts.h"
#include "sharedtypes.h"
#include "playerthread.h"
#include "sharedobject.h"
#include <QLinkedList>
#include "aibot.h"
#include "Entity.h"

bool AIBot::isVisible(QPointF playerPos) {
    // TODO
    return false;
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
            if(isVisible(nearestPlayerProps.getPosition()))
                state = Attack;
            // TODO: player is dead ==> patrol
            break;
        case Patrol:
            if(isVisible(nearestPlayerProps.getPosition()) && hp <= consts::hpEscape)
                state = Escape;
            if(isVisible(nearestPlayerProps.getPosition()) && hp > consts::hpEscape)
                state = Attack;
            break;
        case Escape:
            if(!isVisible(nearestPlayerProps.getPosition()))
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
            // TODO: need to implement fire()
            fire(nearestPlayerProps.getPosition(), 0);
            break;
        case Pursuit:
            // pursuit
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
    return newProps;
}


