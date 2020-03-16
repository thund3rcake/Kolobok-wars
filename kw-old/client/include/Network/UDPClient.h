/*
 *
 * Created on: 22.04.2012
 *
 * UDPClient.h
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

#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

#include <QtCore>
#include <QThread>
#include <QtNetwork>
#include <QQueue>
#include <QMutex>
#include <QLinkedList>

#include <NetDataContainer.h>
#include <Datagrams.h>
#include <Versions.h>



namespace Net
{

class UdpClient: public QThread
{
    Q_OBJECT

  public:
    typedef NetDataContainer<MovingObjectProperties> MObjPrptContainer;


    UdpClient(
               const QHostAddress & server,
               quint16 port,
               QObject * parent
              );

    virtual
    ~UdpClient();

    class Exception
    {
      public:
        explicit
        Exception( int no ):
          errno( no )
        {};

        Exception( int no, const QString & msg ):
          errno( no ),
          message( msg )
        {};

        int     errno;
        QString message;
    };

  public slots:
    void sendNewObjectPropertie( MovingObjectProperties & prpt );
    quint16 getPort(){ return ownPort; };


  private:
    UdpClient();
    UdpClient( const UdpClient & rhs );
    UdpClient & operator=( const UdpClient & rhs );

    inline
    void send();
    inline
    void receive();
    inline
    bool packegeQuality( qint32 timestamp, bool incrementBadPckg = true );

    QHostAddress server;
    quint16      port;
    quint16      ownPort;

    qint32  prevTimestamp;
    quint32 laggingFrom100;
    quint32 receivedFrom100;

    QUdpSocket * socket;

    QQueue<MovingObjectProperties> outgoing;
    bool   toQuit;
    QMutex mutex;

  private slots:
    void checkError( QAbstractSocket::SocketError );

  protected:
    virtual
    void run();


  signals:
    void newObjectProperties( NetDataContainer<Net::MovingObjectProperties> * prpt );
    void error( int error, QString message );
};





} /* namespace Net */
#endif /* UDPCLIENT_H_ */
