/*
 *
 * Created on: 22.04.2012
 *
 * UDPClient.cpp
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
 * along with kolobok-wars-client; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *  
 */


#include <UDPClient.h>
#include <NetDataContainer.h>

using namespace Net;


UdpClient::UdpClient(
                      const QHostAddress & server,
                      quint16 port,
                      QObject * parent
                     ):
    QThread( parent ),
    server( server ),
    port( port ),
    ownPort( 0 ),
    prevTimestamp( 0 ),
    laggingFrom100( 0 ),
    receivedFrom100( 0 ),
    socket( NULL ),
    toQuit( false )
{}


UdpClient::~UdpClient()
{
  mutex.lock();
  toQuit = true;
  mutex.unlock();

  wait();
  if ( socket )
    delete socket;
}


void UdpClient::sendNewObjectPropertie( MovingObjectProperties & prpt )
{
  QMutexLocker locker( &mutex );
  outgoing.enqueue( prpt );
}

void UdpClient::run()
{
  socket = new QUdpSocket;

  connect( socket, SIGNAL( error( QAbstractSocket::SocketError ) ),
           this,   SLOT( checkError( QAbstractSocket::SocketError ) ));

  if ( !( socket -> bind( 0, QUdpSocket::DontShareAddress )) )
  {
    emit error( socket -> error(), socket -> errorString()  );
  }
  ownPort =  socket -> localPort();

  mutex.lock();
  while ( !toQuit )
  {
    mutex.unlock();
    send();
    receive();
    mutex.lock();
  }
  mutex.unlock();
}

void UdpClient::send()
{
  static QByteArray block;

  static MovingObjectProperties propertyBufer;

  QMutexLocker locker( &mutex );
  for ( int i = 0; i < outgoing.size(); ++i )
  {
    propertyBufer.timestamp = prevTimestamp;

    block.clear();
    propertyBufer = outgoing.dequeue();
    block = propertyBufer.serialize();

    socket -> writeDatagram( block.data(), block.size(), server, port );
  }
}

void UdpClient::receive()
{
  if ( socket -> hasPendingDatagrams() )
  {
    static QByteArray   block;
    static QHostAddress address;
    static quint16      port;

    block.clear();
    block.resize( socket -> pendingDatagramSize() );
    socket -> readDatagram(
                            block.data(),
                            block.size(),
                            &address,
                            &port
                           );

    if ( address != this -> server || port != this -> port ) return;

    NetDataContainer<MovingObjectProperties> * container
      = new NetDataContainer<MovingObjectProperties>;

    container -> getOption().deserialize( block );

    MovingObjectProperties::Type pckgType = container -> getOption().type;

    if (
         !packegeQuality
              (
                container -> getOption().timestamp,
                ( pckgType == MovingObjectProperties::Timestamp )? false: true
               )
        )
    {
      qDebug() << "!packegeQuality";
      return;
    }

    prevTimestamp = container -> getOption().timestamp;

    if ( pckgType == MovingObjectProperties::Timestamp )
    {
      sendNewObjectPropertie( container -> getOption() );
      delete container;
      return;
    }
    emit newObjectProperties( container );  // TODO: connect this UDP emit with update coordinates and other actions
  }
}

bool UdpClient::packegeQuality( qint32 timestamp, bool incrementBadPckg )
{
  if ( prevTimestamp > timestamp ) return false;

  if ( incrementBadPckg )
  {
    if ( prevTimestamp - timestamp > MaxPackegeDelay ) laggingFrom100++;
  }

  if ( laggingFrom100 > 50 )
    emit error( QUdpSocket::UnknownSocketError, "Bad connection... :(" );

  if ( receivedFrom100 >= 100 )
  {
     laggingFrom100  = 0;
     receivedFrom100 = 0;
  }
  else
  {
     receivedFrom100++;
  }

  return true;
}

void UdpClient::checkError( QAbstractSocket::SocketError )
{
  emit error( socket -> error(), socket -> errorString() );
}

