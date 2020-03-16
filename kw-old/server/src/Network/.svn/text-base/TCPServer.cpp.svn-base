/*
 *
 * Created on: 10.05.2012
 *
 * TCPServer.cpp
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

#include <TCPServer.h>
#include <UDPServer.h>
#include <ServerTools.h>

using namespace Net;


TCPServer::TCPServer(
                      quint16 port,
                      UDPServer & udpServer,
                      QObject *parent
                     ):
  QTcpServer( parent ),
  port( port ),
  udpServer( udpServer )
{
  if ( !listen( QHostAddress::Any, port ) )
  {
    qDebug() << "TCPServer: listen failed";
    throw Exception( -1 , errorString() );
  }

  qDebug() << "TCPServer: listen OK";
};

void TCPServer::incomingConnection( int socketDescriptor )
{
  qDebug() << "TCPServer::incomingConnection";

  ServerTools::Shared & sharedData =
      static_cast<ServerTools *>( parent() ) -> getShared();

  quint16 id = 0;

  sharedData.nextPlayerId.writeLock();
  id = sharedData.nextPlayerId.read();
  sharedData.nextPlayerId.get()++;
  sharedData.nextPlayerId.writeUnlock();

  PlayerThread * thread = new PlayerThread(
                                            id, socketDescriptor,
                                            udpServer, sharedData,
                                            this
                                           );

 sharedData.playerById.writeLock();
 sharedData.playerById.get().insert( id, thread );
 sharedData.playerById.writeUnlock();

  /*
  connect( thread, SIGNAL( finished() ),
           this,   SLOT( deletePlayer()) );
  connect( thread, SIGNAL( finished() ),
           thread, SLOT( deleteLater()) );
  */

 thread->start();
}
