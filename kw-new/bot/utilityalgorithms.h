#ifndef UTILITYALGORITHMS_H
#define UTILITYALGORITHMS_H

#include <QLinkedList>
#include <QPointF>
#include "Map.h"
#include "sharedtypes.h"


class UtilityAlgorithms
{
public:
    UtilityAlgorithms();
    static QLinkedList<QPointF> breadthFirstSearch(QPointF source, QPointF destination, Shared & sharedData, quint32 timestamp);

    // TODO: BFS, A-star
};

#endif // UTILITYALGORITHMS_H
