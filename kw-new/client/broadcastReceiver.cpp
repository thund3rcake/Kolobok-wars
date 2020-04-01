#include <QtNetwork/QtNetwork>
#include<QtNetwork/QTcpSocket>

#include <BroadcastReceiver.h>
#include<Serializable.h>


BroadcastReceiver::BroadcastReceiver
    (
      QVector<ServerAbout> & srvs,
      QWidget * parent
    ):
    QUdpSocket( (QObject *)parent ),
    servers( srvs )
{
  if ( !(bind( 27030, QUdpSocket::ShareAddress )) )
  {
    throw Exception( error(), errorString() );
  }

  QObject::connect( this, SIGNAL( readyRead()),
                    this, SLOT( processPendingDatagrams()) );
}


void BroadcastReceiver::processPendingDatagrams() {

  while(hasPendingDatagrams()) {
    QByteArray block;
    ServerAbout info;
    quint32 size = 0;


    block.clear();
    block.resize( pendingDatagramSize() );

    readDatagram(
                  block.data(),
                  block.size(),
                  &(info.address),
                  &(info.port)
                 );

    info.data.deserialize( block );
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