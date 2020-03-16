/*
 *
 * Created on: 10.05.2012
 *
 * SharedObjects.h
 * This file is part of kolobok-wars-server
 * 
 * Copyright (C) 2012 - Ivan Penkin, MIPT
 * grek.penkin@gmail.com
 *
 * kolobok-wars-server is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kolobok-wars-server is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kolobok-wars-server; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *  
 */

#ifndef SHAREDOBJECTS_H_
#define SHAREDOBJECTS_H_

#include <QtCore>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

template <class T>
class SharedObject
{
  public:
    SharedObject():
      readersCount( 0 ),
      preparingToWrite( false )
    {};

    T & get()
    {
      return data;
    };

    void writeLock()
    {
      mutex.lock();
      preparingToWrite = true;
      while( readersCount != 0 )
      {
        mutexUnlocked.wait( &mutex );
      }
    };

    void      writeUnlock()
    {
      preparingToWrite = false;
      mutex.unlock();
      mutexUnlocked.wakeOne();
    };

    void      readLock()
    {
      mutex.lock();
      while ( preparingToWrite )
      {
        mutexUnlocked.wait( &mutex );
      }
      readersCount++;
      mutex.unlock();
    };

    void      readUnlock()
    {
      mutex.lock();
      readersCount--;
      mutex.unlock();
      mutexUnlocked.wakeOne();
    };

    const T & read()
    {
      return data;
    };

  private:
    SharedObject( const SharedObject & );
    SharedObject & operator= ( const SharedObject & );

    T      data;

    qint32         readersCount;
    bool           preparingToWrite;
    QMutex         mutex;
    QWaitCondition mutexUnlocked;
};


#include <Datagrams.h>
#include <Bullet.h>

typedef QQueue<Net::MovingObjectProperties> UdpQueue;
typedef SharedObject<UdpQueue>              SharedUdpQueue;

class PlayerThread;
typedef QMap<qint32, PlayerThread *> PlayersMap;
typedef SharedObject<PlayersMap>     SharedPlayersMap;

typedef QMap<qint32, qint32>     LatencysMap;
typedef SharedObject<LatencysMap> SharedLatencysMap;

typedef QMap<qint32, GameWorld::Bullet *> BulletsMap;
typedef SharedObject<BulletsMap>          SharedBulletsMap;


#endif /* SHAREDOBJECTS_H_ */
