#ifndef AIBOT_H
#define AIBOT_H

#include <QVector>
#include "Datagramms.h"
#include "sharedtypes.h"



class AIBot: public MovingEntity {
public:
    enum State {Attack, Pursuit, Patrol, Escape};
    // TODO: enum Role {Assault, Guardian};

    AIBot(Shared & sharedData, MovingObjectProperties props);

    // void setHead (QVector2D &);
    // const QVector2D & getHead ();
    void fire (QPointF target, int type); //не реализован

    // void setTimeStep (qint32);
    // qint32 getTimeStep ();
    void switchState(Shared & sharedData);
    MovingObjectProperties action(Shared & sharedData, MovingObjectProperties currentProps);
    void setProperties(MovingObjectProperties props);

private:
    AIBot (const AIBot & rhs);
    AIBot & operator= (const AIBot & rhs);
    bool isVisible(QPointF playerPos, Shared & sharedData);

    // attack the specified player
    void attack(MovingObjectProperties playerProps);

    // escape from the specified player
    void escape(MovingObjectProperties playerProps, Shared & sharedData);

    // pursuit specified player
    void pursuit(MovingObjectProperties playerProps, Shared & sharedData);

    // patrol the map
    void patrol(Shared &sharedData);

    QRandomGenerator random;
    State state;
    QVector<QPointF> patrolPoints;
    qint8 currentPatrolIndex;
    MovingObjectProperties::Team team;
    QString name;
    quint8 hp;
    QVector2D head;
    Weapon weapon;
    qint32 timeStep;

    QList<Bullet*> firedBullets;
};

#endif // AIBOT_H
