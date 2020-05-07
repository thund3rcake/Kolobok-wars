#include "aiprocessor.h"
#include "sharedobject.h"
#include "playerthread.h"
#include <QLinkedList>
#include "aibot.h"
#include "Entity.h"

AIProcessor::AIProcessor() {

}


void AIProcessor::updateMovingProperties(Shared & sharedData, MovingObjectProperties * props) {    
    quint16 id = props->getId();
    AIBot * currentBot = nullptr;

    foreach(AIBot * aiBot, aiBots) { // find our bot
        if(aiBot->getId() == id)
            currentBot = aiBot;
    }
    if (currentBot == nullptr) // create if not found
        currentBot = new AIBot(props);

    MovingObjectProperties nearestPlayerProps;
    foreach (PlayerThread * player, sharedData.playerById.get())
        if (!(player->isFinished()) && player->getId() != id) {
            // find the nearest player
            nearestPlayerProps = player->getMovProperties();
        }
    // change
    //processState(nearestPlayer);
    // acation according to the state
    //action(state);
}
