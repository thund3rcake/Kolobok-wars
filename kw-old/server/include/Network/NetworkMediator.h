/*
 *
 * Created on: 20.05.2012
 *
 * networkMediator.h
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

#ifndef NETWORKMEDIATOR_H_
#define NETWORKMEDIATOR_H_

#include <QtCore>
#include <QTimer>
#include <UDPServer.h>
#include <ServerTools.h>

namespace Net
{

class NetworkMediator: public QObject
{
    Q_OBJECT

  public:
    NetworkMediator(
                     quint16 id,
                     QTcpSocket * tcpSocket,
                     Net::UDPServer & udpServer,
                     ServerTools::Shared & sharedData,
                     QObject * parent = 0
                    );

    SharedUdpQueue & getUdpQueue();
    QHostAddress   & getPeerAddress();

    void connectt();
    void sendGameProperty( const GameProperties & );
    GameProperties receiveGameProperty();

    /* UDP */
    Net::MovingObjectProperties getProperty( bool & goten );
    void sendProperty ( const Net::MovingObjectProperties & );
    /* UDP */

  private:
    NetworkMediator();
    NetworkMediator( const NetworkMediator & );
    NetworkMediator & operator=( const NetworkMediator & );

    quint16          id;
    int              socketDescriptor;
    QHostAddress     peerAddress;
    quint16          peerPort;
    QTcpSocket *     tcpSocket;

    Net::UDPServer &      udpServerOnlyForSend;
    ServerTools::Shared & sharedData;
    SharedUdpQueue        incomingUdpQueue;
    QTimer                timestampSendTimer;

    /* TCP */
    inline
    void standardGreeting();
    inline
    void setPeerUdpPort();

    inline
    bool waitForBytesAvailable( qint64 size, qint32 maxTime );
    inline
    void tcpSendArray( const QByteArray & array );
    inline
    QByteArray tcpReceiveArray();
    /* TCP */

  public slots:
    void sendTimestamp();

  signals:
    void error( int, QString );
};


} /* namespace Net */

#endif /* NETWORKMEDIATOR_H_ */
