/*
 *
 * Created on: 07.05.2012
 *
 * UDPClient.cpp
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

#include <UDPServer.h>
#include <ServerTools.h>

using namespace Net;


UDPServer::UDPServer( quint16 port, QObject * parent ):
  QThread( parent ),
  port( port ),
  socket( NULL ),
  toQuit( false )
{}


UDPServer::~UDPServer()
{
  incomingMutex.lock();
  outgoingMutex.lock();
  toQuit = true;
  outgoingMutex.unlock();
  incomingMutex.unlock();

  wait();
  if( socket )
    delete socket;
}


void UDPServer::run()
{
  if ( !socket )
  {
    socket = new QUdpSocket;
  }
  if ( !( socket -> bind( port, QUdpSocket::ShareAddress )) )
  {
    emit error( socket -> error(), socket -> errorString() );
    qDebug() << socket -> errorString();
    return;
  }

  quitMutex.lock();
  while ( !toQuit )
  {
    quitMutex.unlock();

    static QByteArray block;
    static Packet     packetBufer;

    /* sending */
    outgoingMutex.lock();
    if ( !outgoing.empty() )
    {
      packetBufer = outgoing.dequeue();
      outgoingMutex.unlock();

      if ( packetBufer.port == 0 )
      {
        quitMutex.lock();
        continue;
      }

      /* timestamp */
      packetBufer.properties.timestamp =
              static_cast<ServerTools *>( parent() ) -> getCurentTime();
      /* timestamp */

      /* only sending */
      block.clear();
      block = packetBufer.properties.serialize();
      socket -> writeDatagram(
                               block.data(), block.size(),
                               packetBufer.address, packetBufer.port
                              );
      /* only sending */
    }
    else
    {
      outgoingMutex.unlock();
    };
    /* sending */

    /* receiving */
    if ( socket -> hasPendingDatagrams() )
    {
      static quint16 clientPort;

      /* only receiving */
      block.clear();
      block.resize( socket -> pendingDatagramSize() );
      socket -> readDatagram(
                              block.data(),
                              block.size(),
                              &(packetBufer.address),
                              &clientPort
                             );
      packetBufer.properties.deserialize( block );
      /* only receiving */

      incomingMutex.lock();
      incoming.enqueue( packetBufer );
      incomingMutex.unlock();

      emit newPacket();
    }/* receiving */

    usleep( 5 ); //TODO: correct this value

    quitMutex.lock();
  }
  quitMutex.unlock();
}


void UDPServer::sendPacket( const Packet & packet )
{
  outgoingMutex.lock();
  outgoing.enqueue( packet );
  outgoingMutex.unlock();
}

const UDPServer::Packet UDPServer::getPacket( bool & result )
{
  if ( incoming.isEmpty() )
  {
    result = false;
    return UDPServer::Packet();
  }

  QMutexLocker locker( &incomingMutex );
  result = true;
  return incoming.dequeue();
}







