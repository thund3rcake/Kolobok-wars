/*
 *  Created on: 29.03.2012
 *
 * Entity.cpp
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

#include <Entity.h>
#include <QPixmap>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsEffect>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// this functions were implemented for Entity

Entity::Entity ()
{
  this->id = NOT_VALID;
}

bool Entity::setId (int ID)
{
  if ( this->isValid() ) return false;
  id = ID;
  return true;
}

bool Entity::isValid ()
{
  if ( id >= 0 )
    return true;
  else
    return false;
}

int   Entity::getId ()
{
  return id;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// this functions were implemented for PolygonEntity


PolygonEntity::PolygonEntity () :
  Entity(),              // TODO: cut it down
  QGraphicsPolygonItem() //
{}

void PolygonEntity::setTexturePath (QString path)
{
  texturePath = path;
}

bool PolygonEntity::makeImage() //warning! this function must be used only in client!
{
  boundRect = boundingRect().toRect();
  QImage * image;
  if ( overlay == Native )
  {
    image = new QImage(texturePath);
    if ( image -> isNull() )
    {
      qDebug() << "EntityID: " << id << "Texture wasn't found";
      return false;
    }
  }
  if ( overlay == Tiled )
  {
    image = new QImage(boundRect.size(), QImage::Format_ARGB32);
    image->fill(125);

    QPainter  imagePainter(image);
    QPolygonF tmpPoligon;
    QPointF   tmpPoint;

    foreach( QPointF point, this->polygon().toList() )
    {
      tmpPoint.rx() = point.x() - boundRect.topLeft().x();
      tmpPoint.ry() = point.y() - boundRect.topLeft().y();

      tmpPoligon << tmpPoint;
    }

    QImage * brushImg = new QImage( texturePath );
    if ( brushImg -> isNull() ) return false;

    imagePainter.setBrush( QBrush( *brushImg ));
    imagePainter.setPen( Qt::NoPen );

    imagePainter.drawPolygon( tmpPoligon );
    imagePainter.end();
  }
  pixmap = new QPixmap;
  *pixmap = ( pixmap -> fromImage(*image) );

  delete image;

  return true;
}

QString PolygonEntity::getTexturePath ()
{
  return texturePath;
}

void PolygonEntity::paint (
                           QPainter * painter,
                           const QStyleOptionGraphicsItem *,
                           QWidget *
                          )
{
  painter -> drawPixmap( boundRect, *pixmap );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// this functions were implemented for PolygonEntity

MovingEntity::MovingEntity ( int id, QPointF pos, QVector2D intention ):
  Entity(id),
  position(pos),
  intent(intention)
{}


void MovingEntity::setIntent   ( const QVector2D & intention )
{
  intent = intention;
}

const QVector2D& MovingEntity::getIntention ()
{
  return intent;
}

void MovingEntity::setPosition ( const QPointF& pos )
{
  position = pos;
}

const QPointF & MovingEntity::getPosition()
{
  return position;
}
