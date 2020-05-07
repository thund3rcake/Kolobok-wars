/*
 *  Created on: 28.04.2012
 *
 * Player.h
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Krepak Vitaly, MIPT
 * krepakvitaliy@gmail.com
 *
 * kolobok-wars-client is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kolobok-wars-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kolobok-wars-client if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 */

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

    QVector2D dfs(QVector2D current, QVector2D target);

    enum Team { Red, Blue };

    Player ();
    Player (QString name, int team);

    virtual
    void paint (
                QPainter * painter,
                const QStyleOptionGraphicsItem * option,
                QWidget * widget = 0
               );

    void         setHead     ( QVector2D & );
    const QVector2D &  getHead ();
    void fire ( QPointF target, int type );

    void setTimeStep (qint32);
    qint32 getTimeStep ();

  private:
    Player (const Player& rhs);
    Player& operator= (const Player& rhs);

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
