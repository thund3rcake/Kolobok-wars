/*
 *
 * Created on: 07.05.2012
 *
 * UDPCLient.h
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

#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

#include <QtCore>
#include <QTime>
#include <QThread>
#include <QtNetwork>

#include <Datagrams.h>

namespace Net
{

class UDPServer: public QThread
{
  Q_OBJECT

  public:
    explicit
    UDPServer( quint16 port, QObject * parent = 0 );

    virtual
    ~UDPServer();


    struct Packet
    {
      Net::MovingObjectProperties properties;
      quint16                     port;
      QHostAddress                address;
    };

    const Packet getPacket( bool & result );
    void         sendPacket( const Packet & packet );

  protected:
    virtual
    void run();

  private:
    UDPServer();
    UDPServer( const UDPServer & rhs );
    UDPServer & operator= ( const UDPServer & rhs );

    quint16      port;
    QUdpSocket * socket;

    QMutex       quitMutex;
    bool         toQuit;

    QMutex         outgoingMutex;
    QQueue<Packet> outgoing;

    QMutex         incomingMutex;
    QQueue<Packet> incoming;

  signals:
    void error( int, QString );
    void newPacket();
};

} /* namespace Net */


#endif /* UDPCLIENT_H_ */
