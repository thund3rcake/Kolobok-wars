#ifndef GEOMETRYALGORITHMS_H
#define GEOMETRYALGORITHMS_H


#include <QPoint>
#include <Entity.h>
#include <QList>

enum { Inside, Outside, Boundary }; // dot position

enum { Touching,    Crossing,     Inessential }; // edge position

enum {Left,  Right,  Beyond,  Behind, Between, Origin, Destination};

bool isDotInAnyPolygon (QPointF &tested, QList<PolygonEntity*> suspicious);
bool isDotInPolygon (QPointF &tested, PolygonEntity* polygon );

int classifyPoint (QPointF tested, QPointF p0, QPointF p1);

int analyseEdge (QPointF tested, QPointF p0, QPointF p1);


#endif // GEOMETRYALGORITHMS_H