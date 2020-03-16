/*
 *
 * Created on: 03.05.2012
 *
 * BroadcastSender.cpp
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

#include <BroadcastSender.h>

using namespace Net;

BroadcastSender::BroadcastSender(
                                  const QString & serverName,
                                  const QString & mapName,
                                  quint16 p,
                                  quint16 tcpPort,
                                  quint8  maxPlayers,
                                  QObject * parent
                                 ):
  QThread( parent ),
  quit( false ),
  socket( NULL ),
  serverName( serverName ),
  mapName( mapName ),
  port( p ),
  tcpPort( tcpPort ),
  maxPlayers( maxPlayers ),
  players( 0 ),
  bots( 0 )
{
  generateDatagram();
}


BroadcastSender::~BroadcastSender()
{
  quit = true;
  wait();
  if ( socket )
    delete socket;
}

void BroadcastSender::generateDatagram()
{
  QMutexLocker locker( &mutex );

  datagram.clear();

  datagram = BroadcastDatagram(
                                Net::QStringSignature,
                                serverName,
                                mapName,
                                tcpPort,
                                quint8( Net::ProtVersion ),
                                quint8( Net::ProtSubversion ),
                                bots,
                                players,
                                maxPlayers
                               ).serialize();
}

void BroadcastSender::setMapName( const QString & name )
{
  QMutexLocker locker( &mutex );
  mapName = name;
}

void BroadcastSender::setBotCount( quint8 count )
{
  QMutexLocker locker( &mutex );
  bots = count;
}

void BroadcastSender::setPlayerCount( quint8 count )
{
  QMutexLocker locker( &mutex );
  players = count;
}

void BroadcastSender::run()
{
  generateDatagram();

  mutex.lock();
  if ( !socket )
  {
    socket = new QUdpSocket;

    if ( !(socket -> bind( port, QUdpSocket::ShareAddress )) )
      emit error( socket -> error(), socket -> errorString() );
  }

  while ( !quit )
  {
    if ( socket -> writeDatagram( datagram, QHostAddress::Broadcast, 27030 ) < 0)
      emit error( socket -> error(), socket -> errorString() );

    mutex.unlock();
    sleep( 4 );
    mutex.lock();
  }
  mutex.unlock();
}





