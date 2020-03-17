#ifndef PLAYER_H_
#define PLAYER_H_

#include <Entity.h>
#include <Bullet.h>
#include <Weapon.h>
#include <GameWorldConsts.h>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>

using namespace GameWorld;

class Player: public MovingEntity, public QGraphicsRectItem
{

public:
    enum Team { Red, Blue };

    Player ();
    Player (QString name, int team);

    virtual
    void paint (
               QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget = 0
               );

    void setHead (QVector2D &);
    const QVector2D & getHead ();
    void fire (QPointF target, int type); //не реализован

    void setTimeStep (qint32);
    qint32 getTimeStep ();

private:
    Player (const Player& rhs);
    Player & operator= (const Player& rhs);

    int       team;
    QString   name;
    quint8    hp;
    QVector2D head;
    Weapon    weapon;
    qint32    timeStep;

    QString   modelId;
    QBrush    playerBrush;

    QList<Bullet*> firedBullets;
};


#endif /* PLAYER_H_ */