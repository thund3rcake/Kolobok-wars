/*
 *  Created on: 01.05.2012
 *
 * GeometryAlgorythms.cpp
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Krepak Vitaly, Ivan Penkin MIPT
 * krepakvitaliy@gmail.com, grek.penkin@gmail.com
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

#include <QPoint>
#include <GeometryAlgorythms.h>
#include <commonLibs.h>



bool isDotInAnyPolygon ( QPointF &tested, QList<PolygonEntity*> suspicious )
{
  foreach ( PolygonEntity* entity, suspicious )
  {
    if ( isDotInPolygon (tested, entity) == Inside )
    {
      return true;
    }
  }
  return false;
}

bool isDotInPolygon ( QPointF &tested, PolygonEntity* polygon )
{
  int parity = 0;
  QList<QPointF> points = polygon->polygon().toList();

#ifdef KOLOBOK_CLIENT

  for ( QList<QPointF>::iterator i = points.begin();
        i != points.end(); ++i )
  {
    i->operator *=(100/scale_x_100());
  }

#endif

  QPointF first = points.first();
  QPointF prev  = first;

  for ( QList<QPointF>::iterator i = ++points.begin();
        i != points.end(); ++i)
  {
    switch ( analyseEdge( tested, prev, *i ) )
    {
      case Touching:
        return Boundary;
      case Crossing:
        parity = 1 - parity;
    }
    prev = *i;
  }
  switch ( analyseEdge( tested, prev, first ) )
  {
    case Touching:
      return Boundary;
    case Crossing:
      parity = 1 - parity;
  }
  return (parity ? Inside : Outside);
}

int analyseEdge (QPointF tested, QPointF p0, QPointF p1)
{
  switch ( classifyPoint (tested, p0, p1) )
  {
    case Left:
      return ( (p0.y() < tested.y()) && (tested.y() <= p1.y()) ) ? Crossing : Inessential;
    case Right:
      return ( (p1.y() < tested.y()) && (tested.y() <= p0.y()) ) ? Crossing : Inessential;
    case Between:
    case Origin:
    case Destination:
      return Touching;
    default:
      return Inessential;
  }
}

int classifyPoint (QPointF tested, QPointF p0, QPointF p1)
{
  QPointF p2  = tested;
  QVector2D a = QVector2D ( (p1 - p0).x(), (p1 - p0).y() );
  QVector2D b = QVector2D ( (p2 - p0).x(), (p2 - p0).y() );
  double sa = a.x()*b.y() - b.x()*a.y();

  if ( sa > 0.0 )
    return Left;

  if ( sa < 0.0 )
    return Right;

  if ( (a.x()*b.x() < 0.0) ||
       (a.y()*b.y() < 0.0) )
    return Behind;

  if ( a.length() < b.length() )
    return Beyond;

  if ( p0 == p2 )
    return Origin;

  if ( p1 == p2 )
    return Destination;

  return Between;
}

