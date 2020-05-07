/*
 *  Created on: 28.04.2012
 *
 * Player.cpp
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

#include <Player.h>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPixmap>
#include <commonLibs.h>

Player::Player()
{
  this->setRect( 0, 0, scaledPlayerSize(), scaledPlayerSize() );
}

Player::Player (QString name, int team):
  team (team),
  name (name)
{
  this->setRect( 0, 0, scaledPlayerSize(), scaledPlayerSize() );
}

void  Player::setHead ( QVector2D & vector )
{
  head = vector.normalized();
}

const QVector2D & Player::getHead ()
{
  return head;
}

void Player::paint (
                    QPainter * painter,
                    const QStyleOptionGraphicsItem *,
                    QWidget *
                   )
{
//  qDebug() << "Repaint Player" << id;
  if ( position != pos() )
    setPos(pos() + intent.toPointF()*consts::sendTimerInterval/5/consts::sceneUpdateInterval);
  painter->setRenderHint( QPainter::Antialiasing, true );
  painter->drawEllipse ( QPointF(0,0), scaledPlayerSize(), scaledPlayerSize() );
  painter->drawLine    ( QPointF(0,0), head.toPointF()*scaledPlayerSize() );
}

void Player::setTimeStep (qint32 step)
{
  timeStep = step;
}

QVector2D Player::dfs(QVector2D current, QVector2D target) {

}

qint32 Player::getTimeStep ()
{
  return timeStep;
}
