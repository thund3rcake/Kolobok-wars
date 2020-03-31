#include "BroadcastReceiver.h"
#include <QtNetwork/QtNetwork>
#include <BroadcastReceiver.h>


using namespace Net;

BroadcastReceiver::BroadcastReceiver
    (
      QVector<ServerAbout> & servers,
      QWidget * parent
    ):
    QUdpSocket( (QObject *)parent ),
    servers( servers )
{
  if ( !(bind( 27030, QUdpSocket::ShareAddress )) )
  {
    throw Exception( error(), errorString() );
  }

    QObject::connect( this, SIGNAL( readyRead()), this, SLOT(processWaitingDatagramms()) );
}


void BroadcastReceiver::processWaitingDatagramms()
{
  while ( hasPendingDatagrams() )
  {
    static QByteArray  block;
    static ServerAbout info;

    block.clear();
    block.resize( pendingDatagramSize() );

    readDatagram(
                  block.data(),
                  block.size(),
                  &(info.address),
                  &(info.port)
                 );

    info.data << block;
    info.port = info.data.tcpPort;


    if (
          info.data.signature  != Net::QStringSignature ||
          info.data.version    != Net::ProtVersion ||
          info.data.subversion != Net::ProtSubversion
        ) continue;

    bool newSrv = true;
    foreach ( ServerAbout about, servers )
    {
      if (
           info.data.serverName == about.data.serverName &&
           info.address == about.address
          )
      {
        newSrv = false;
        break;
      }
    }

    if ( newSrv )
    {
      servers.push_back( info );
      emit newServer( servers.count() - 1 );
    }
  }
}