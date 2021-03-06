/*
 *
 * Created on: 10.05.2012
 *
 * PlayerThread.cpp
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

#include <QDataStream>
#include <Bullet.h>

#include <PlayerThread.h>
#include <Versions.h>
#include <ServerTools.h>
#include <Datagrams.h>


PlayerThread::PlayerThread(
                            quint16 id,
                            int socketDescriptor,
                            Net::UDPServer & udpServer,
                            ServerTools::Shared & sharedData,
                            QObject * parent
                           ):
  QThread( parent ),
  id( id ),
  socketDescriptor( socketDescriptor ),
  sharedData( sharedData ),
  udpServerOnlyForSend( udpServer ),
  incomingUdpQueue( new SharedUdpQueue ),
  peerAddress( NULL ),
  peerPort( 0 ),
  timestampSendTimer( new QTimer( this ) )
{
  sharedData.playerLatencyById.writeLock();
  sharedData.playerLatencyById.get().insert( id, 1 );
  sharedData.playerLatencyById.writeUnlock();

  timestampSendTimer -> setInterval( 5000 );
  QObject::connect( timestampSendTimer, SIGNAL( timeout() ),
                    this,               SLOT( sendTimestamp() ));
  timestampSendTimer -> start();
  timer.start();
}



void PlayerThread::run()
{
  tcpSocket = new QTcpSocket;
  if ( !(tcpSocket -> setSocketDescriptor( socketDescriptor )) )
  {
    qDebug() << "PlayerThread::run(): setSocketDescriptor error" << tcpSocket -> errorString();
    emit error( tcpSocket -> error(), tcpSocket -> errorString() );
    return;
  }

  /* connection */
  connect();
  /* connection */

  peerAddress = new QHostAddress( tcpSocket -> peerAddress() );

  bool goten = false;

  QMap<qint32, qint32>::iterator latencyIter;
  /* main loop */
  while(1)
  {
    playerProperties = getProperty ( goten );
    if ( goten == false )
    {
      usleep(100); //TODO: accurate constant
      continue;    //TODO: ?? what about the others players
    }

    latencyIter = sharedData.playerLatencyById.get().find(id);
    if ( latencyIter != sharedData.playerLatencyById.get().end() )
      latency = latencyIter.value();

    updateCoordinates (playerProperties);
    this -> sendProperty(playerProperties);

    foreach ( PlayerThread * player, sharedData.playerById.get() )
    {
      if ( player -> getId() != this -> id )
      {
        this -> sendProperty ( player -> getProperties() );
      }
    }
    usleep(100);
  }
  /* main loop */
}

bool PlayerThread::isThereHits ( const GameWorld::Bullet * /* bullet */ )
{
  return false;
}

void PlayerThread::updateCoordinates ( Net::MovingObjectProperties & prop )
{
  if ( prop.timestamp > consts::sendTimerInterval*1.25 )
    return;

  QPointF increment = prop.intent.toPointF()*prop.timestamp/25;

  QPointF intentedDot = prop.position;

  for ( int i = 0; i < 5; i++ )
  {
    intentedDot += increment;
    if ( sharedData.gameMap.get() -> isDotAvailable(intentedDot.toPoint()) )
    {
      propertiesMutex.lock();
      prop.position = intentedDot;
      propertiesMutex.unlock();
    }
//    else
//    {
//      if ( sharedData.gameMap.get() -> isDotAvailable( QPoint(intentedDot.x(), prop.position.y()) ) )
//      {
//        propertiesMutex.lock();
//        prop.position.setX( intentedDot.x() );
//        propertiesMutex.unlock();
//      }
//      if ( sharedData.gameMap.get() -> isDotAvailable( QPoint(prop.position.x(), intentedDot.y()) ) )
//      {
//        propertiesMutex.lock();
//        prop.position.setY( intentedDot.y() );
//        propertiesMutex.unlock();
//      }
//    }
  }

  return;
}


bool PlayerThread::isThereCollisionsWithTheOthers ( const PlayerThread *  )
{
  return false;
}

Net::MovingObjectProperties PlayerThread::getProperty ( bool & goten )
{
  Net::MovingObjectProperties property;

  incomingUdpQueue -> writeLock();

  if ( !(incomingUdpQueue -> get().isEmpty()) )
  {
    goten = true;
    property = incomingUdpQueue -> get().dequeue();
  }
  else
  {
    goten = false;
  }
  incomingUdpQueue -> writeUnlock();

  if ( goten ) return property;
  return playerProperties;
}

void PlayerThread::sendProperty( const Net::MovingObjectProperties & property )
{
  Net::UDPServer::Packet packet;
  packet.port       = peerPort;
  packet.address    = *peerAddress;
  packet.properties = property;

  udpServerOnlyForSend.sendPacket( packet );
}

void PlayerThread::connect()
{
  QDataStream blockStream( &packetBufer, QIODevice::WriteOnly );
  blockStream.setVersion( Net::DataStreamVersion );

  blockStream << Net::QStringSignature;
  blockStream << Net::ProtVersion;
  blockStream << Net::ProtSubversion;
  blockStream << id;

  blockStream.device() -> seek( 0 );

  byteArrayToSocket( packetBufer );

  packetBufer.clear();
  quint64 blockSize;
  QDataStream in( tcpSocket );
  in.setVersion( Net::DataStreamVersion );

  if ( !waitForBytesAvailable( sizeof(quint64), 1500 ) )
  {
      qDebug() << "TcpServer::Connect: tcp error" << tcpSocket -> errorString();
      //TODO: emit error()
      return;
  }

  in >> blockSize;
  qDebug() << blockSize;

  if ( !waitForBytesAvailable( blockSize, 500 ) )
  {
      qDebug() << "TcpServer::Connect: tcp error" << tcpSocket -> errorString();
      //TODO: emit error()
      return;
  }

  packetBufer.resize( blockSize );
  in >> packetBufer;

  Net::GameProperties property;
  property.deserialize( packetBufer );

  if ( property.type != Net::GameProperties::UdpPort )
  {
    emit error( -1, "Wrong client" );
    tcpSocket -> disconnectFromHost();
  }

  peerPort = (quint16) property.firstQInt;
}

bool PlayerThread::waitForBytesAvailable(
                                          qint64 size, qint32 maxTime,
                                          bool noBytesIsError
                                         )
{
  while ( tcpSocket -> bytesAvailable() < size )
  {
    if ( !(tcpSocket -> waitForReadyRead( maxTime )) )
    {
      if ( noBytesIsError )
      {
        emit error( tcpSocket -> error(), tcpSocket -> errorString() );
        tcpSocket -> disconnectFromHost();
      }
      return false;
    }
  }
  return true;
}

void PlayerThread::sendGameProperty( const Net::GameProperties & property )
{
  packetBufer = property.serialize();
  byteArrayToSocket( packetBufer );
}

void PlayerThread::byteArrayToSocket( const QByteArray & array )
{
  QDataStream sockStream( tcpSocket );
  sockStream.setVersion( Net::DataStreamVersion );

  if ( !(tcpSocket -> isWritable()) )
        emit error( -1, "Client closes the connection" ); // TODO: delete the thread, not error

  sockStream << (quint64)array.size();
  sockStream << array;

  tcpSocket -> waitForBytesWritten( 10 );
}

Net::GameProperties PlayerThread::receiveGameProperty(
                                                       bool & ,
                                                       quint32
                                                      )
{
  return Net::GameProperties();
}

void PlayerThread::sendTimestamp()
{
  Net::MovingObjectProperties property;

  property.type = Net::MovingObjectProperties::Timestamp;
  sendProperty( property );
}

Net::MovingObjectProperties PlayerThread::getProperties()
{
  QMutexLocker locker(&propertiesMutex);
  return playerProperties;
}
