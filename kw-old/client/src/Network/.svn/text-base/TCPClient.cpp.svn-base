/*
 *
 * Created on: 20.04.2012
 *
 * TCPClient.cpp
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

#include <TCPClient.h>
#include <GameScene.h>

using namespace Net;


/*
 *
 *  TCPClient
 *
 *
 */

TcpClient::TcpClient(
                            const QHostAddress & server,
                            quint16 port,
                            QObject * parent,
                            qint32 timeout
                           ):
    QThread( parent ),
    host( server ),
    port( port ),
    timeout( timeout ),
    socket( NULL ),
    mode( None )
{}


TcpClient::~TcpClient()
{
  setMode( Exit );
  wait();
  if ( socket )
    delete socket;
}


void TcpClient::setMode( Mode newMode )
{
  QMutexLocker locker( &mutex );
  mode = newMode;

  if ( !isRunning() ) start();
      else condition.wakeOne();
}

void TcpClient::pushGamePropertie( const GameProperties & option )
{
  QMutexLocker locker( &mutex );

  sendBufer.enqueue( option );
}

void TcpClient::run()
{
  Mode mode = getMode();
  bool waitCond;

  while( true )
  {
    waitCond = true;

    switch ( mode )
    {
      case Exit:        return;
      case None:        break;
      case Connect:     connect();
                        waitCond = false;
                        break;
      case Send:        send();
                        waitCond = false;
                        break;
      case Listen:      listen();
    }
    mode = getMode( waitCond );
  }
}

void TcpClient::postErrorHandler( int errno, const QString & message )
{
  emit error( errno, message );
  mutex.lock();
  mode = None;
  mutex.unlock();
}


bool TcpClient::waitForBytesAvailable(
                                       qint64 size,
                                       qint32 maxTime,
                                       bool noBytesIsError
                                      )
{
  while ( socket -> bytesAvailable() < size )
  {
    if ( !(socket -> waitForReadyRead( maxTime )) )
    {
      if ( noBytesIsError )
      {
        postErrorHandler( socket -> error(), socket -> errorString() );
        socket -> disconnectFromHost();
      }
      return false;
    }
  }
  return true;
}

bool TcpClient::checkConnectionInfo()
{
  static QByteArray block;
  block.clear();
  quint64 blockSize = 0;
  QDataStream blockStream( &block, QIODevice::ReadOnly );
  blockStream.setVersion( Net::DataStreamVersion );
  QDataStream in( socket );
  in.setVersion( Net::DataStreamVersion );

  if ( !waitForBytesAvailable( sizeof(quint64), timeout ) )
  {
    return false;
  }

  in >> blockSize;

  if ( !waitForBytesAvailable( blockSize, timeout ) )
  {
    return false;
  }
  block.resize( blockSize );
  in >> block;

  QString signature;
  qint16  version = 0;
  qint16  subversion = 0;
  quint16 id = 0;

  blockStream >> signature;
  blockStream >> version;
  blockStream >> subversion;
  blockStream >> id;

  emit idGoten( id );

  if ( signature != QStringSignature )
  {
    postErrorHandler( socket -> error(), socket -> errorString() );
    socket -> disconnectFromHost();
    return false;
  }
  else
  {
    if ( version > ProtVersion || subversion > ProtSubversion )
    {
      postErrorHandler
                  (
                    -1,
                    "Server version is " +
                    QString().number( version, 10 ) +
                    "." +
                    QString().number( subversion, 10 )
                   );
      socket -> disconnectFromHost();
      return false;
    }
  }

  GameProperties udpPortOption;

  QDataStream out( socket );
  out.setVersion( Net::DataStreamVersion );

  udpPortOption.type = GameProperties::UdpPort;

  udpPortOption.firstQInt = 0;
  while ( !udpPortOption.firstQInt )
  {
    udpPortOption.firstQInt =
      static_cast<GameWorld::GameScene*>( parent() ) -> getUdpPort();
    usleep( 3 );
  }

  block.clear();
  block = udpPortOption.serialize();

  out << (quint64)block.size();
  out << block;

  socket -> waitForBytesWritten( 10 );

  return true;
}


/*
 * Connects to the server TcpServer::host and
 * TcpServer::port, checks the signature and
 * protocol version. Emits void TcpServer::connected()
 * signal. Sets TcpServer::mode in TcpServer::None
 * on return. When error is occurred emits
 * void TcpServer::error( int errno, QString message )
 * signal and sets mode in TcpServer::None.
 */
void TcpClient::connect()
{
  socket = new QTcpSocket();
  socket -> connectToHost( host, port );

  if ( !(socket -> waitForConnected( timeout )) )
  {
    postErrorHandler( socket -> error(), socket -> errorString() );
    return;
  };

  if ( !checkConnectionInfo() ) return;

  mutex.lock();
  mode = Listen;
  mutex.unlock();

  emit connected();
}


/*
 * Sends data from TcpServer::sendBufer to the server
 * Sets TcpServer::mode in TcpServer::Listen
 * on return. When error is occurred emits
 * void TcpServer::error( int errno, QString message )
 * signal and sets mode in TcpServer::None.
 */
void TcpClient::send()
{
  if( socket -> state() != QAbstractSocket::ConnectedState )
  {
    emit error( -1, "Disconnected from the server" );
    return;
  }

  QByteArray block;
  static GameProperties optionForSend;

  QDataStream out( socket );
  out.setVersion( Net::DataStreamVersion );

  mutex.lock();
  for ( int i = 0; i < sendBufer.size(); ++i )
  {
    block.clear();

    optionForSend = sendBufer.dequeue();

    QByteArray block = optionForSend.serialize();

    out << block.size();
    out << block;

    socket -> waitForBytesWritten( 10 );
  }
  mutex.unlock();

  if ( !(socket -> waitForBytesWritten( timeout )) )
  {
    postErrorHandler( socket -> error(), socket -> errorString() );
    socket -> disconnectFromHost();
    return;
  }
  mutex.lock();
  mode = Listen;
  mutex.unlock();
}


/*
 * Waits data on the TcpServer::socket for about
 * 2 * TcpServer::timeout seconds. If data is available
 * reads it and emits
 * TcpServer::newOption( OptionsContainer * option ),
 * else returns, in all of the variants it doesn't
 * change the TcpServer::mode. When error is occurred emits
 * void TcpServer::error( int errno, QString message )
 * signal and sets mode in TcpServer::None.
 * WARNING!!! You must delete OptionsContainer after
 * use.
 */
void TcpClient::listen()
{
  //////qDebug() << "TcpClient::Listen: started";
  if( socket -> state() != QAbstractSocket::ConnectedState )
  {
    //////qDebug() << "TcpClient::Listen: the socket is disconnected. Returned";
    emit error( socket -> error(), "Disconnected from the server" );
    return;
  }

  static QByteArray block;
  block.clear();
  quint64 blockSize = 0;
  QDataStream blockStream( &block, QIODevice::ReadOnly );
  blockStream.setVersion( Net::DataStreamVersion );
  QDataStream in( socket );
  in.setVersion( Net::DataStreamVersion );

  //////qDebug() << "TcpClient::Listen: preparing to read size";

  if ( !waitForBytesAvailable( sizeof(quint64), timeout, false ) )
  {

    return;
  }
  in >> blockSize;

  //////qDebug() << "TcpClient::Listen: + received size: " <<
               QString().number( blockSize, 10 );


  //////qDebug() << "TcpClient::Listen: preparing to read option";

  if ( !waitForBytesAvailable( blockSize, timeout ) ) return;
  block.resize( blockSize );
  in >> block;

  //////qDebug() << "TcpClient::Listen:  + received pckg: " <<
              QString().number( blockSize, 10 );

  NetDataContainer<GameProperties> * container =
      new NetDataContainer<GameProperties>();

  GameProperties option;
  option.deserialize( block );

  //////qDebug() << "TcpClient::Listen: the option:"
  //         << QString().number( option.type, 10 );

  container -> setOption( option );
  emit newProperty( container );
  ////qDebug() << "TcpClient::Listen: emited \"newOption\"";
}


TcpClient::Mode TcpClient::getMode( bool waitCondition )
{
  QMutexLocker locker( &mutex );
  if ( waitCondition ) condition.wait( &mutex, timeout );
  return mode;
}


void TcpClient::start()
{
  QThread::start();
}


/* TCPClient */
