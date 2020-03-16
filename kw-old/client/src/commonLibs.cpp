/*
 *  Created on: 15.04.2012
 *
 * commonLibs.cpp
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


#include <commonLibs.h>
#include <GameWorldConsts.h>

QPoint getDesktopSize()
{
  static OnceCreated<QPoint> size;

  if ( size.isNull() )
  {
    QDesktopWidget desktop;
    size = QPoint( desktop.width(), desktop.height() );
  }

  return size.getdData();
}

double  scale_x_100 ()
{
  static OnceCreated<double> scale;

  if ( scale.isNull() )
  {
    scale = 100 * double ( getDesktopSize().ry() )/
                  double ( GameWorld::consts::heightOfVisibleArea );
  }

  return scale.getdData();
}

double scaledPlayerSize()
{
  static OnceCreated<double> size;

  if ( size.isNull() )
  {
    size = GameWorld::consts::playerSize*(scale_x_100()/100);
  }

  return size.getdData();
}
