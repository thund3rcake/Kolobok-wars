/*
 *  Created on: 05.05.2012
 *
 * Bullet.cpp
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

#include <Bullet.h>
#include <Entity.h>
#include <QPainter>
#include <commonLibs.h>
#include <math.h>

Bullet::Bullet ( int id, const QPointF& position, QPointF& targAbs, Weapon::Type typ ):
  MovingEntity(id, position, QVector2D(-position+targAbs).normalized()),
  reached(false)
{
  setPosition (position);
  weapon.type = typ;
  weapon.target = targAbs;
  setRect( position.x(),         position.y(),
           consts::playerSize/4, consts::playerSize/4);
}

void Bullet::paint (
                    QPainter * painter,
                    const QStyleOptionGraphicsItem *,
                    QWidget *
                   )
{
  setRect( getPosition().x()-consts::playerSize/8, getPosition().y()-consts::playerSize/8,
           consts::playerSize/4, consts::playerSize/4);

  painter->drawRect( getPosition().x()-consts::playerSize/8, getPosition().y()-consts::playerSize/8,
                    consts::playerSize/4, consts::playerSize/4);
}

bool Bullet::isTargetReach ()
{
  if ( reached == true ) return true;

  double dx = abs ( getPosition().x() - weapon.target.rx() );
  double dy = abs ( getPosition().y() - weapon.target.ry() );

  if ( dx < consts::bulletVelocity &&
       dy < consts::bulletVelocity )
  {
    setPosition ( weapon.target );
    reached = true;
    return true;
  }
  return false;
}
