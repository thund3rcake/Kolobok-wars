
#include <QPoint>
#include <GeometryAlgorithms.h>
#include <CommonGlobal.h>



bool isDotInAnyPolygon(QPointF &tested, QList<PolygonEntity*> suspicious) {
    foreach (PolygonEntity* entity, suspicious) {
        if (isDotInPolygon (tested, entity) == Inside) {
            return true;
        }
    }
    return false;
}

bool isDotInPolygon(QPointF &tested, PolygonEntity* polygon) {
    int parity = 0;
    QList<QPointF> points = polygon->polygon().toList();

    #ifdef KOLOBOK_CLIENT

    for ( QList<QPointF>::iterator i = points.begin(); i != points.end(); ++i ) {
        i->operator *=(100/scale_x_100());
    }

    #endif

    QPointF first = points.first();
    QPointF prev  = first;

    for(QList<QPointF>::iterator i = ++points.begin(); i != points.end(); ++i) {
        switch (analyseEdge(tested, prev, *i)) {
            case Touching:
                return Boundary;
            case Crossing:
                parity = 1 - parity;
        }
        prev = *i;
    }
    switch(analyseEdge( tested, prev, first)) {
        case Touching:
            return Boundary;
        case Crossing:
            parity = 1 - parity;
    }
    return (parity ? Inside : Outside);
}

int analyseEdge(QPointF tested, QPointF p0, QPointF p1) {
    switch (classifyPoint (tested, p0, p1)) {
        case Left:
            return ((p0.y() < tested.y()) && (tested.y() <= p1.y())) ? Crossing : Inessential;
        case Right:
            return ((p1.y() < tested.y()) && (tested.y() <= p0.y())) ? Crossing : Inessential;
        case Between:
        case Origin:
        case Destination:
            return Touching;
        default:
            return Inessential;
  }
}

int classifyPoint (QPointF tested, QPointF p0, QPointF p1) {
    QPointF p2  = tested;
    QVector2D a = QVector2D ((p1 - p0).x(), (p1 - p0).y());
    QVector2D b = QVector2D ((p2 - p0).x(), (p2 - p0).y());
    double sa = a.x() * b.y() - b.x() * a.y();

    if(sa > 0.0)
        return Left;

    if(sa < 0.0)
        return Right;

    if ((a.x()*b.x() < 0.0) || (a.y()*b.y() < 0.0))
        return Behind;

    if (a.length() < b.length())
        return Beyond;

    if (p0 == p2)
        return Origin;

    if (p1 == p2)
        return Destination;

    return Between;
}