/*
 *
 * Created on: 15.04.2012
 *
 * BroadcastReceiver.cpp
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



#include <QtNetwork>
#include <BroadcastReceiver.h>


using namespace Net;

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


void BroadcastReceiver::processPendingDatagrams()
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
