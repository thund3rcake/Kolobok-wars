#include "aibot.h"
#include "Datagramms.h"
#include "GameWorldConsts.h"



bool AIBot::isVisible(QPointF playerPos) {
    // TODO
    return false;
}

AIBot::AIBot(MovingObjectProperties *props) {
   state = Patrol;
   team = props->getTeam();
   hp = props->getHp();
   head = props->getHead();
   weapon = props->getWeapon();
   position = props->getPosition();
   id = props->getId();
}

void AIBot::processState(const MovingObjectProperties & playerProps) {
    switch (state) {
        case Attack:
            if(hp <= consts::hpEscape)
                state = Escape;
            // TODO: if no visible enemies ==> patrol
            break;
        case Pursuit:
            if(isVisible(playerProps.getPosition()))
                state = Attack;
            // TODO: player is dead ==> patrol
            break;
        case Patrol:
            if(isVisible(playerProps.getPosition()) && hp <= consts::hpEscape)
                state = Escape;
            if(isVisible(playerProps.getPosition()) && hp > consts::hpEscape)
                state = Attack;
            break;
        case Escape:
            if(!isVisible(playerProps.getPosition()))
                state = Patrol;
            break;
        default:
            break;
    }
}
