#ifndef GEOMETRYALGORITHMS_H
#define GEOMETRYALGORITHMS_H


#include <QPoint>
#include <Entity.h>
#include <QList>
#include <CommonGlobal.h>

enum KW_COMMON_EXPORT { Inside, Outside, Boundary }; // dot position

enum KW_COMMON_EXPORT { Touching,    Crossing,     Inessential }; // edge position

enum KW_COMMON_EXPORT {Left,  Right,  Beyond,  Behind, Between, Origin, Destination};

bool KW_COMMON_EXPORT isDotInAnyPolygon (QPointF &tested, QList<PolygonEntity*> suspicious);
bool KW_COMMON_EXPORT isDotInPolygon (QPointF &tested, PolygonEntity* polygon );

int KW_COMMON_EXPORT classifyPoint (QPointF tested, QPointF p0, QPointF p1);

int KW_COMMON_EXPORT analyseEdge (QPointF tested, QPointF p0, QPointF p1);


#endif // GEOMETRYALGORITHMS_H
