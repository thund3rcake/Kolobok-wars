  /*
 *
 * Created on: 23.03.12
 *
 * kolobok-wars-client.cpp
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Ivan Penkin, MIPT
 * grek.penkin@gmail.com
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

#include<kolobok-wars-client.h>

#include <QtGui>
#include <QApplication>
#include <GraphicsView.h>


int main(int argc, char *argv[])
{
  QApplication app( argc, argv );

  qsrand( QTime( 0,0,0 ).secsTo( QTime::currentTime() ));
  GraphicsView view( &app );
  view.show();

  return app.exec();
}
