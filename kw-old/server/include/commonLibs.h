/*
 *  Created on: 15.04.2012
 *
 * commonLibs.h
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

#ifndef COMMONLIBS_H_
#define COMMONLIBS_H_

#include <QtGui>
#include <GameWorldConsts.h>

class Exception
{
  public:
    explicit
    Exception( int no ):
     errno( no )
    {};

    Exception( int no, const QString & msg ):
     errno( no ),
     message( msg )
    {};

    int     errno;
    QString message;
};


template <class T>
class OnceCreated
{
  public:
    OnceCreated():
      isNULL( true )
    {};

    explicit
    OnceCreated( const T & data ):
      isNULL( false ),
      data( data )
    {};

    OnceCreated & operator= ( const T & rhs )
    {
      isNULL = false;
      data = rhs;
      return *this;
    };

    inline bool isNull()   { return isNULL; };
    inline T    getdData() { return data; };

  private:
    bool isNULL;
    T    data;

};


#ifdef KOLOBOK_CLIENT
QPoint  getDesktopSize();
double scale_x_100 ();
#endif

double scaledPlayerSize();


#endif /* COMMONLIBS_H_ */
