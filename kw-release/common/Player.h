﻿#ifndef PLAYER_H_
#define PLAYER_H_

#include <Entity.h>
#include <Bullet.h>
#include <Weapon.h>
#include <GameWorldConsts.h>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <CommonGlobal.h>
#include <Datagramms.h>

class KW_COMMON_EXPORT Player: public MovingEntity, public QGraphicsRectItem {

public:

    QVector2D dfs(QVector2D current, QVector2D target);

    enum Team { Red, Blue };

    Player ();
    Player (QString name, Player::Team team);

    virtual
    void paint (
               QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget = 0
               );

    void setHead (QVector2D );
    const QVector2D & getHead ();
    void fire (QPointF target, int type); //не реализован

    void setTimeStep (qint32);
    qint32 getTimeStep ();

protected:
    Player (const Player& rhs);
    Player & operator= (const Player& rhs);

    Player::Team team;
    QString name;
    quint8 hp;
    QVector2D head;
    Weapon weapon;
    qint32 timeStep;

    QString modelId;
    QBrush playerBrush;

    QList<Bullet*> firedBullets;
};


#endif /* PLAYER_H_ */
