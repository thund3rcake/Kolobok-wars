#include "utilityalgorithms.h"
#include "GameWorldConsts.h"
#include <QLinkedList>
#include <QPointF>
#include <QQueue>
#include <QStack>
#include <QDebug>
#include <QLinkedList>

UtilityAlgorithms::UtilityAlgorithms()
{}

struct Node {
    QPointF point;
    struct Node * prev;
    Node(QPointF point, Node * prev): point(point), prev(prev) {}
    Node() {};
};

QLinkedList<QPointF> UtilityAlgorithms::breadthFirstSearch(
        QPointF source, QPointF destination, Shared & sharedData, quint8 stride)
{
    QLinkedList<QPointF> visited = QLinkedList<QPointF>();
    QLinkedList<QPointF> path = QLinkedList<QPointF>();
    QQueue<Node *> queue = QQueue<Node *>();

    Node * start = new Node(source, nullptr);
    Node * current;

    queue.enqueue(start); // create queue

    while (!queue.isEmpty()) {
        // BFS iteration
        current = queue.dequeue();

        if(current->point == destination)
            break;

        Node * left = new Node(current->point + QPointF(-stride, 0), nullptr);
        Node * right = new Node(current->point + QPointF(stride, 0), nullptr);
        Node * top = new Node(current->point + QPointF(0, stride), nullptr);
        Node * bottom = new Node(current->point + QPointF(0, -stride), nullptr);

        // append adjacent vertices
        if(sharedData.gameMap.get()->isDotAvailable(left->point.toPoint()) && !visited.contains(left->point)) {
            left->prev = current;
            queue.enqueue(left);
            visited.append(left->point);
        }

        if(sharedData.gameMap.get()->isDotAvailable(right->point.toPoint()) && !visited.contains(right->point)) {
            right->prev = current;
            queue.enqueue(right);
            visited.append(right->point);
        }

        if(sharedData.gameMap.get()->isDotAvailable(top->point.toPoint()) && !visited.contains(top->point)) {
            top->prev = current;
            queue.enqueue(top);
            visited.append(top->point);
        }

        if(sharedData.gameMap.get()->isDotAvailable(bottom->point.toPoint()) && !visited.contains(bottom->point)) {
            bottom->prev = current;
            queue.enqueue(bottom);
            visited.append(bottom->point);
        }
    }

    // do backtrace to get the path
    while(current->prev != nullptr) {
        path.push_back(current->point);
        Node * tmp = current;
        current = current->prev;
        delete tmp;
    }

    //qDebug() << "path (" << path.first() << " , " << path.last() << " )";

    return path;
}

QVector2D UtilityAlgorithms::getMoveIntent(
        QPointF source, QPointF destination, Shared & sharedData, quint8 stride)
{
    QLinkedList<QPointF> path = breadthFirstSearch(source, destination, sharedData, stride);
    QPointF next_point = path.takeLast();
    QVector2D intent = QVector2D(next_point - source);
    intent.normalize();
    return intent;
}

QPointF UtilityAlgorithms::selectAvailableDot(Shared &sharedData)
{
    QPointF target;
    do {
        float x = qrand() % consts::mapSizeX;
        float y = qrand() % consts::mapSizeY;
        target = QPointF(x, y);
    } while(!sharedData.gameMap.get()->isDotAvailable(target.toPoint()));
    return target;
}

QVector<QPointF> UtilityAlgorithms::selectPolygon(Shared &sharedData, quint8 minEdgeLength)
{
    QVector<QPointF> polygon = QVector<QPointF>();
    QPointF target = selectAvailableDot(sharedData);
    polygon.push_back(target);
    for(quint8 i = 1; i < consts::patrolPointsCount; i++) {
        bool flag = false;
        while (!flag) {
            flag = true;
            qDebug() << "select: " << target;
            target = selectAvailableDot(sharedData);
            for(auto it = polygon.begin(); it != polygon.end(); ++it)
                if(QVector2D(*it - target).length() < minEdgeLength)
                    flag = false;
        }
        polygon.push_back(target);
    }
    return polygon;
}

//QVector2D intent = QVector2D(destination.x() - source.x(), destination.y() - source.y());
//intent.normalize();
//
//QPointF increment = intent.toPointF() * timestamp / 25;
//if(sharedData.gameMap.get() -> isDotAvailable((source + increment).toPoint())) { // if we can


