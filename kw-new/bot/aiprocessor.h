#ifndef AIPROCESSOR_H
#define AIPROCESSOR_H

#include "sharedtypes.h"
#include "Datagramms.h"
#include "aibot.h"

#include<QLinkedList>

class AIProcessor
{
public:
    AIProcessor();
    MovingObjectProperties updateMovingProperties(Shared & sharedData, MovingObjectProperties currentProps);
private:
    MovingObjectProperties botProps;
    QLinkedList<AIBot *> aiBots;
};

#endif // AIPROCESSOR_H
