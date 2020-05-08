#ifndef AIBOT_H
#define AIBOT_H

#include "Player.h"
#include "Datagramms.h"
#include "sharedtypes.h"



class AIBot: public MovingEntity {
public:
    enum State {Attack, Pursuit, Patrol, Escape};
    // TODO: enum Role {Assault, Guardian};

    AIBot(MovingObjectProperties props);

    // void setHead (QVector2D &);
    // const QVector2D & getHead ();
    void fire (QPointF target, int type); //не реализован

    // void setTimeStep (qint32);
    // qint32 getTimeStep ();
    void switchState(Shared & sharedData);
    MovingObjectProperties action(Shared & sharedData, MovingObjectProperties currentProps);

private:
    AIBot (const AIBot & rhs);
    AIBot & operator= (const Player & rhs);
    bool isVisible(QPointF playerPos);

    State state;
    MovingObjectProperties::Team team;
    QString name;
    quint8 hp;
    QVector2D head;
    Weapon weapon;
    qint32 timeStep;

    QList<Bullet*> firedBullets;
};

#endif // AIBOT_H
