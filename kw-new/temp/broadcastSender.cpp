#include <BroadcastSender.h>

//using namespace Net;

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

  BroadcastData data(
                                Net::QStringSignature,
                                serverName,
                                mapName,
                                tcpPort,
                                quint8( Net::ProtVersion ),
                                quint8( Net::ProtSubversion ),
                                bots,
                                players,
                                maxPlayers,
                                parent
                               );
  datagram = QByteArray();
  QDataStream wStream( &buffer, QIODevice::OpenModeFlag::WriteOnly );

  wStream << data;
}

void BroadcastSender::setMapName( const QString & name )
{
  QMutexLocker locker( &mutex );
  //Constructs a QMutexLocker and locks mutex. The mutex will be unlocked when the QMutexLocker is destroyed. (c)
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





