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

    static QVector2D getMoveIntent(QPointF source, QPointF destination, Shared & sharedData, quint8 stride, QLinkedList<QPointF> * path);
    static QPointF selectAvailableDot(Shared & sharedData);
    static QVector<QPointF> selectPolygon(Shared & sharedData, quint8 minEdgeLength);
    static bool arePointsClose(QPointF p1, QPointF p2, quint8 thresohld);
    static QLinkedList<QPointF> breadthFirstSearch(QPointF source, QPointF destination, Shared & sharedData, quint8 stride = 1);


};

#endif // UTILITYALGORITHMS_H
