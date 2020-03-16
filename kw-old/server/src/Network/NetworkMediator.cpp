/*
 *
 * Created on: 20.05.2012
 *
 * networkMediator.cpp
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

#include <NetworkMediator.h>

using namespace Net;

NetworkMediator::NetworkMediator(
                                  quint16 id,
                                  QTcpSocket * tcpSocket,
                                  Net::UDPServer & udpServer,
                                  ServerTools::Shared & sharedData,
                                  QObject * parent
                                 ):
  QObject( parent ),
  id( id ),
  peerPort( 0 ),
  tcpSocket( tcpSocket ),
  udpServerOnlyForSend( udpServer ),
  sharedData( sharedData )
{
  timestampSendTimer.setInterval ( 1000 );
  connect( &timestampSendTimer, SIGNAL( timeout() ),
                     this,               SLOT( sendTimestamp() ));
  timestampSendTimer.start();
}

SharedUdpQueue & NetworkMediator::getUdpQueue()
{
  return incomingUdpQueue;
}

QHostAddress & NetworkMediator::getPeerAddress()
{
  return peerAddress;
}


void NetworkMediator::connectt()
{
//  if ( !(tcpSocket -> setSocketDescriptor( socketDescriptor )) )
//  {
//    qDebug() << "NetworkMediator::run(): setSocketDescriptor error" << tcpSocket -> errorString();
//    emit error( tcpSocket -> error(), tcpSocket -> errorString() );
//    return;
//  }

  peerAddress = tcpSocket -> peerAddress();

  standardGreeting();
  setPeerUdpPort();
}

void NetworkMediator::standardGreeting()
{
  QByteArray packetBufer;
  packetBufer.clear();

  QDataStream blockStream( &packetBufer, QIODevice::WriteOnly );
  blockStream.setVersion( Net::DataStreamVersion );

  blockStream << Net::QStringSignature;
  blockStream << Net::ProtVersion;
  blockStream << Net::ProtSubversion;
  blockStream << id;

  blockStream.device() -> seek( 0 );

  tcpSendArray( packetBufer );
}

void NetworkMediator::setPeerUdpPort()
{
  GameProperties property;
  property.deserialize( tcpReceiveArray() );

  if ( property.type != Net::GameProperties::UdpPort )
  {
    emit error( -1, "Wrong client" );
    tcpSocket -> disconnectFromHost();
    return;
  }

  peerPort = (quint16) property.firstQInt;
}

void NetworkMediator::sendGameProperty( const GameProperties & property )
{
  static QByteArray block;
  block.clear();

  block = property.serialize();
  tcpSendArray( block );
}

GameProperties NetworkMediator::receiveGameProperty()
{
  GameProperties property;

  property.deserialize( tcpReceiveArray() );
  return property;
}


void NetworkMediator::tcpSendArray( const QByteArray & array )
{
  QDataStream sockStream( tcpSocket );
  sockStream.setVersion( Net::DataStreamVersion );

  if ( !(tcpSocket -> isWritable()) )
  {
    emit error( -1, "Client closes the connection" ); // TODO: delete the thread, not error
    return;
  }

  sockStream << (quint64)array.size();
  sockStream << array;

  tcpSocket -> waitForBytesWritten( 3 );
}

QByteArray NetworkMediator::tcpReceiveArray()
{
  static QByteArray block;
  block.clear();

  static quint64 blockSize;

  QDataStream in( tcpSocket );
  in.setVersion( Net::DataStreamVersion );

  if ( !waitForBytesAvailable( sizeof(quint64), 1500 ) )
  {
    emit error( tcpSocket -> error(), tcpSocket -> errorString() );
    return block;
  }

  in >> blockSize;
  qDebug() << blockSize;

  if ( !waitForBytesAvailable( blockSize, 500 ) )
  {
    emit error( tcpSocket -> error(), tcpSocket -> errorString() );
    return block;
  }

  block.resize( blockSize );
  in >> block;

  return block;
}

bool NetworkMediator::waitForBytesAvailable( qint64 size, qint32 maxTime )
{
  while ( tcpSocket -> bytesAvailable() < size )
  {
    if ( !(tcpSocket -> waitForReadyRead( maxTime )) )
    {
      emit error( tcpSocket -> error(), tcpSocket -> errorString() );
      tcpSocket -> disconnectFromHost();
      return false;
    }
  }
  return true;
}


MovingObjectProperties NetworkMediator::getProperty ( bool & goten )
{
  MovingObjectProperties property;
  goten = false;

  incomingUdpQueue.writeLock();
  if ( !incomingUdpQueue.read().isEmpty() )
  {
    goten = true;
    property = incomingUdpQueue.get().dequeue();
  }
  incomingUdpQueue.writeLock();

  return property;
}


void NetworkMediator::sendProperty ( const Net::MovingObjectProperties & property )
{
  UDPServer::Packet packet;
  packet.port       = peerPort;
  packet.address    = peerAddress;
  packet.properties = property;

  qDebug() << packet.port << packet.address;

  udpServerOnlyForSend.sendPacket( packet );
}

void NetworkMediator::sendTimestamp()
{
  qDebug() << "Timestamp";

  MovingObjectProperties property;

  property.type = MovingObjectProperties::Timestamp;
  sendProperty( property );
}

