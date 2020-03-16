/*
 *  Created on: 28.04.2012
 *
 * Bullet.h
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

#ifndef BULLET_H_
#define BULLET_H_

#include <Entity.h>
#include <Weapon.h>
#include <QVector2D>

namespace GameWorld
{

class Bullet: public MovingEntity, public QGraphicsRectItem
{
  public:
    Bullet (int, const QPointF&, QPointF&, Weapon::Type );

    virtual
    void paint (
                QPainter * painter,
                const QStyleOptionGraphicsItem * option,
                QWidget * widget = 0
               );
    bool isTargetReach ();

  private:
    Bullet ();
    Bullet (const Bullet& rhs);
    Bullet& operator= (const Bullet& rhs);

    Weapon weapon;
    bool  reached; //temporary flag, this flag needs until bullets don't removed
};

} /* namespace GameWorld */

#endif /* BULLET_H_ */
