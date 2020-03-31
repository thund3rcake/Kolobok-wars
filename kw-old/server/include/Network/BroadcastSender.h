/*
 *
 * Created on: 03.05.2012
 *
 * BroadcastSender.h
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

#ifndef BROADCASTSENDER_H_
#define BROADCASTSENDER_H_


#include <QtCore>
#include <QtNetwork>
#include <QDataStream>
#include <QThread>

#include <Datagrams.h>
#include <Versions.h>

namespace Net
{

class BroadcastSender: public QThread
{
  Q_OBJECT

  public:
    BroadcastSender(
                     const QString & serverName,
                     const QString & mapName,
                     quint16 port,
                     quint16 tcpPort,
                     quint8  maxPlayers,
                     QObject * parent = 0
                    );

    virtual
    ~BroadcastSender();

  public slots:
    void generateDatagram();
    void setMapName( const QString & mapName );
    void setBotCount( quint8 count );
    void setPlayerCount( quint8 );

  private:
    BroadcastSender();
    BroadcastSender( const BroadcastSender & rhs );
    BroadcastSender & operator= ( const BroadcastSender & rhs );

    bool         quit;
    QUdpSocket * socket;

    QMutex     mutex;
    QString    serverName;
    QString    mapName;
    quint16    port;
    quint16    tcpPort;
    quint8     maxPlayers;
    quint8     players;
    quint8     bots;
    QByteArray datagram;

  protected:
    virtual
    void run();

  signals:
    void error( int errno, QString message );
};

} /* namespace Net */


#endif /* BROADCASTSENDER_H_ */
