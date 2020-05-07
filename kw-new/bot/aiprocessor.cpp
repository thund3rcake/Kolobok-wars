#include "aiprocessor.h"
#include "sharedobject.h"
#include "playerthread.h"
#include <QLinkedList>
#include "aibot.h"
#include "Entity.h"

AIProcessor::AIProcessor() {

}


void AIProcessor::updateMovingProperties(Shared & sharedData, MovingObjectProperties * props) {
    // find our bot
    quint16 id = props->getId();
    AIBot * currentBot;
    foreach(AIBot * aiBot, aiBots) {
        if(aiBot->getId() == id)
            currentBot = aiBot;
    }

    MovingObjectProperties nearestPlayer;
    foreach (PlayerThread * player, sharedData.playerById.get())
        if (!(player->isFinished()) && player->getId() != id) {
            // find the nearest player
            nearestPlayer = player->getMovProperties();
        }
    // change
    //processState(nearestPlayer);
    // acation according to the state
    //action(state);
}
