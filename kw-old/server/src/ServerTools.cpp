/*
 *
 * Created on: 29.04.2012
 *
 * ServerTools.cpp
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

#include <ServerTools.h>
#include <TCPServer.h>
#include <Map.h>
#include <commonLibs.h>


ServerTools::ServerTools(
                           const QString & server,
                           const QString & map,
                           quint16 port,
                           quint8 mPlayers,
                           QTextEdit * console,
                           QObject * parent
                          ):
  QObject( parent ),
  serverName( server ),
  mapName( map ),
  port( port ),
  maxPlayers( mPlayers ),
  console( console )
{
  console -> clear();

  curTime.start();

  data.nextPlayerId.get() = 1;

  broadcastSender = new Net::BroadcastSender(
                                              serverName, mapName,
                                              27030, port,
                                              maxPlayers, this
                                             );

  udpServer = new Net::UDPServer( port, this );
  connect( udpServer, SIGNAL( newPacket() ),
           this,      SLOT( setNewUdpPacket() ));

  udpServer -> start();

  try
  {
    console -> insertHtml( "Starting TCP server... &nbsp" );
    tcpServer = new Net::TCPServer( port, *udpServer, this );
  }
  catch ( Net::TCPServer::Exception exception )
  {
    console -> insertHtml( "[FAIL]<br />" );
    console -> insertHtml( exception.message + "<br />" );
    tcpServer = NULL;
  }
  if ( tcpServer )
  {
    console -> insertHtml( "[DONE]<br />" );
  }

  try
  {
    data.gameMap.get() = new Map("./maps/" + map + "/" + map + ".xml");
  }
  catch (Exception excp)
  {
    qDebug() << "ServerTools::ServerTools: Map has crashed: " << excp.message;
  }
}


ServerTools::~ServerTools()
{
  delete broadcastSender;

  disconnect( udpServer, SIGNAL( newPacket() ),
              this,      SLOT( setNewUdpPacket() ));
  delete udpServer;

  delete tcpServer;
}

void ServerTools::setNewUdpPacket()
{
  bool goten = false;
  Net::UDPServer::Packet newPacket = udpServer -> getPacket( goten );
  if ( goten )
  {
    if ( newPacket.properties.type == Net::MovingObjectProperties::Player )
    {
      data.playerById.readLock();
      QMap<qint32, PlayerThread*>::iterator playerIterator =
          data.playerById.get().find( newPacket.properties.id );

      if (
           playerIterator != data.playerById.get().end() &&
           !playerIterator.value() -> getPeerAdress() -> isNull() &&
           *(playerIterator.value() -> getPeerAdress()) == newPacket.address
          )
      {
        PlayerThread * player = playerIterator.value();

        player -> getUdpQueue() -> writeLock();
        player -> getUdpQueue() -> get().enqueue( newPacket.properties );
        player -> getUdpQueue() -> writeUnlock();
      }
      data.playerById.readLock();
    };

    if ( newPacket.properties.type == Net::MovingObjectProperties::Timestamp )
    {
      qDebug() << "timestamp";
      qint32 newLatency = getCurentTime() - newPacket.properties.timestamp;
      qDebug() << newLatency;

      data.playerLatencyById.writeLock();
      QMap<qint32, qint32>::iterator latency =
          data.playerLatencyById.get().find( newPacket.properties.id );

      if ( latency != data.playerLatencyById.get().end() )
      {
        latency.value() = newLatency;
      }
      data.playerLatencyById.writeUnlock();
    }
  }
}



