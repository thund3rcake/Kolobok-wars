/*
 *  Created on: 25.03.2012
 *
 * Entity.h
 *
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

#ifndef ENTITY_CLASS_H_
#define ENTITY_CLASS_H_

#include <GameWorldConsts.h>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QVector2D>
#include <QPixmap>
#include <QString>
#include <QBrush>
#include <Weapon.h>
#include <QTime>

using namespace GameWorld;

const int NOT_VALID = -1;

class Entity: public QObject
{
  Q_OBJECT
  friend class XmlHandler;
  public:
    Entity ();
    Entity (int id): id(id) {};

    bool  isValid ();
    int   getId ();
    bool  setId (int ID);

  protected:
    int     id;

  private:
    Entity (const Entity& rhs);
    Entity& operator= (const Entity& rhs);

  signals:
    void error (int, QString);
};


class PolygonEntity: public Entity, public QGraphicsPolygonItem
{
    friend class XmlHandler;
  public:
    PolygonEntity ();

    virtual
    void paint (
                QPainter * painter,
                const QStyleOptionGraphicsItem * option,
                QWidget * widget = 0
               );
    QString getTexturePath ();
    bool    makeImage ();

    enum OverlayModes { Tiled, Extended, Native };
  private:
    PolygonEntity (const PolygonEntity& rhs);
    PolygonEntity& operator= (const PolygonEntity& rhs);

    void setTexturePath (QString path);

    QPixmap*     pixmap;

    QRect        boundRect;
    QString      texturePath;
    bool         animated;
    OverlayModes overlay;
};

class MovingEntity: public Entity
{
  public:
    MovingEntity () {};
    MovingEntity ( int, QPointF, QVector2D );

    void    setIntent   ( const QVector2D& );
    void    setPosition ( const QPointF& );

    const QPointF&    getPosition  ();
    const QVector2D& getIntention ();

  protected:
    QPointF     position;
    QVector2D   intent;

  private:
    MovingEntity (const MovingEntity& rhs);
    MovingEntity& operator= (const MovingEntity& rhs);
};

#endif /* ENTITY_CLASS_H_ */
