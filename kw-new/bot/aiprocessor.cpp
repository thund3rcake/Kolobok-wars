#include "aiprocessor.h"
#include "sharedobject.h"
#include "playerthread.h"
#include <QLinkedList>
#include "aibot.h"
#include "Entity.h"

AIProcessor::AIProcessor() {

}


MovingObjectProperties AIProcessor::updateMovingProperties(Shared & sharedData, MovingObjectProperties currentProps) {
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
