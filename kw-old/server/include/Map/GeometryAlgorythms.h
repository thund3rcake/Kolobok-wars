/*
 *  Created on: 01.05.2012
 *
 * GeometryAlgorythms.h
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

#ifndef GEOMETRYALGORYTHMS_H_
#define GEOMETRYALGORYTHMS_H_

#include <QPoint>
#include <Entity.h>
#include <QList>

enum { Inside, Outside, Boundary };         // dot's position
//     ВНУТРИ, ВНЕ,     НА ГРАНИЦЕ
enum { Touching,    Crossing,     Inessential };   // edge's position
//     КАСАТЕЛbНОЕ, ПЕРЕСЕКАЮЩЕЕ, НЕСУЩЕСТВЕННОЕ

enum {Left,  Right,  Beyond,  Behind, Between, Origin, Destination};
//    СЛЕВА, СПРАВА, ВПЕРЕДИ, ПОЗАДИ, МЕЖДУ,   НАЧАЛО, КОНЕЦ

bool isDotInAnyPolygon ( QPointF &tested, QList<PolygonEntity*> suspicious);
bool isDotInPolygon ( QPointF &tested, PolygonEntity* polygon );

int classifyPoint (QPointF tested, QPointF p0, QPointF p1);

int analyseEdge (QPointF tested, QPointF p0, QPointF p1);

#endif /* GEOMETRYALGORYTHMS_H_ */
