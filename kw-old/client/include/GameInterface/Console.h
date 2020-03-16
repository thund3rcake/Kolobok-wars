/*
 *  Created on: 01.05.2012
 *
 * Console.h
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

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <QObject>
#include <QLabel>
#include <QtGui>
#include <HUDStyleSheets.h>

class Console: public QWidget
{
  Q_OBJECT
  public:
    Console ( QWidget * parent = 0 );

    void setPlayerPos ( const QPoint & pos );
    void setTopLeft   ( const QPointF & topLeft );
    void setAvailable ( bool avail );
    void setHeading   ( const QVector2D & head );
    void setIntention ( const QVector2D & intn );
    void setFireTargt ( const QPointF & trgt );

  private:
    Console();
    Console( const Console & rhs );
    Console & operator=( const Console & rhs );

    QLabel playerPos;
    QLabel topLeft;
    QLabel availbl;
    QLabel heading;
    QLabel fireTargt;
    QLabel intention;
};


#endif /* CONSOLE_H_ */
