/*
 *
 * Created on: 29.04.2012
 *
 * ServerTools.h
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

#ifndef SERVERTOOLS_H_
#define SERVERTOOLS_H_

#include <QtCore>
#include <QtGui>
#include <QTime>

#include <SharedObject.h>
#include <BroadcastSender.h>
#include <UDPServer.h>
#include <Bullet.h>
#include <Map.h>

namespace Net{ class TCPServer; };
class PlayerThread;

class ServerTools: public QObject
{
    Q_OBJECT

  public:
    ServerTools(
                  const QString & serverName,
                  const QString & mapName,
                  quint16 port,
                  quint8  maxPlayers,
                  QTextEdit * console,
                  QObject * parent
                 );

    virtual
    ~ServerTools();

    class Shared
    {
      public:
        SharedObject<Map*>    gameMap;

        SharedObject<quint16> nextPlayerId;
        SharedPlayersMap      playerById;
        SharedLatencysMap     playerLatencyById;

        SharedObject<qint32>  nextBulletId;
        SharedBulletsMap      bulletById;
    };

    Net::BroadcastSender & getBroadcastSender() { return * broadcastSender; };
    Net::UDPServer       & getUdpServer      () { return * udpServer; };
    Net::TCPServer       & getTcpServer      () { return * tcpServer; };
    Shared               & getShared         () { return data; };
    qint32                 getCurentTime     () { return curTime.elapsed(); };

  private:
    ServerTools();
    ServerTools( const ServerTools & rhs );
    ServerTools & operator=( const ServerTools & rhs );

    QString     serverName;
    QString     mapName;
    quint16     port;
    quint8      maxPlayers;
    quint8      bots;
    quint8      players;
    QTextEdit * console;

    QTime       curTime;

    Net::BroadcastSender * broadcastSender;
    Net::UDPServer *       udpServer;
    Net::TCPServer *       tcpServer;

    Shared data;

  private slots:
    void setNewUdpPacket();
};



#endif /* SERVERTOOLS_H_ */
