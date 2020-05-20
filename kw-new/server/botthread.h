#ifndef BOTTHREAD_H
#define BOTTHREAD_H

//#include "thread.h"
#include "sharedtypes.h"
#include "Datagramms.h"
#include "aibot.h"
#include <QLinkedList>

class BotThread: public QThread
{
public:
    BotThread(quint16 id, Shared & sharedData, QObject * parent);

    ~BotThread();
    void run();
    void getProperty();
    quint16 getId();
    const MovingObjectProperties & getBotProperties();
    void getDamage();

private:
    QPointF getRespawnPlace();
    void updateCoordinates ();
    qreal distanceToTheClosestPlayer (const QPointF position );
    qreal getLength(QPointF a, QPointF b);
    void updateMovingProperties(Shared & sharedData);
    QLinkedList<AIBot *> aiBots;
    MovingObjectProperties botProps;
    Shared & sharedData;
    QTime timer;
    QMutex propertiesMutex;;
    quint16 id;
};

#endif // BOTTHREAD_H
