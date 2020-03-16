/*
 *
 * Created on: 10.05.2012
 *
 * PlayerThread.h
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

#ifndef PLAYERTHREAD_H_
#define PLAYERTHREAD_H_

#include <QThread>
#include <QTcpSocket>

#include <UDPServer.h>
#include <ServerTools.h>
#include <Weapon.h>

class PlayerThread: public QThread
{
    Q_OBJECT
  public:
    PlayerThread(
                  quint16 id,
                  int socketDescriptor,
                  Net::UDPServer & udpServer,
                  ServerTools::Shared & sharedData,
                  QObject * parent
                 );

    quint16  getId() { return id; };
    Net::MovingObjectProperties getProperties();
    SharedUdpQueue * getUdpQueue() { return incomingUdpQueue; };
    QHostAddress * getPeerAdress() { return peerAddress; };

  protected:
    virtual
    void run();

  private:
    quint16      id;
    int          socketDescriptor;
    QTcpSocket * tcpSocket;
    QByteArray   packetBufer;

    QMutex  mutex;
    QTime   timer;

    ServerTools::Shared  & sharedData;

    Net::UDPServer &       udpServerOnlyForSend;
    SharedUdpQueue *       incomingUdpQueue;
    QHostAddress *         peerAddress;
    quint16                peerPort;

    qint32   latency;
    QTimer * timestampSendTimer;

    QMutex  propertiesMutex;
    Net::MovingObjectProperties playerProperties;

    /* UDP */
    inline
    Net::MovingObjectProperties getProperty( bool & goten );
    inline
    void sendProperty ( const Net::MovingObjectProperties & );
    /* UDP */

    /* TCP */
    inline
    void connect();
    inline
    void sendGameProperty( const Net::GameProperties & );
    inline
    Net::GameProperties receiveGameProperty(
                                             bool & goten,
                                             quint32 timeout = 1500
                                            );

    inline
    void byteArrayToSocket( const QByteArray & array );
    inline
    bool waitForBytesAvailable(
                                qint64 size,
                                qint32 maxTime,
                                bool noBytesIsError = true
                               );
    /* TCP */

    bool isThereCollisionsWithTheOthers ( const PlayerThread * );
    void updateCoordinates ( Net::MovingObjectProperties & );
    inline
    bool isThereHits ( const GameWorld::Bullet * bullet );

  private slots:
    void sendTimestamp();

  signals:
    void error( int errno, const QString & msg );
};









#endif /* PLAYERTHREAD_H_ */
