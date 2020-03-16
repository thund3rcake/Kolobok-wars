/*
 *
 * Created on: 20.04.2012
 *
 * TCPClient.cpp
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

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include <QtCore>
#include <QThread>
#include <QtNetwork>
#include <QMutex>
#include <QWaitCondition>

#include <NetDataContainer.h>
#include <Datagrams.h>
#include <Versions.h>

namespace Net
{

class TcpClient: public QThread
{
    Q_OBJECT

  public:
    TcpClient(
                  const QHostAddress & server,
                  quint16 port,
                  QObject * parent,
                  qint32 timeout = 1500/* ms */
                 );
    virtual
    ~TcpClient();

    enum Mode { None, Exit, Connect, Send, Listen };
  public slots:
    void setMode( Mode mode );
    void pushGamePropertie( const GameProperties & option );


  private:
    TcpClient();
    TcpClient( const TcpClient & rhs );
    TcpClient & operator=( const TcpClient & rhs );

    Mode getMode( bool waitCondition = false );

    inline
    bool checkConnectionInfo();
    inline
    void connect();

    inline
    void postErrorHandler( int error, const QString & message );

    inline
    bool waitForBytesAvailable(
                                qint64 size,
                                qint32 maxTime,
                                bool noBytesIsError = true
                               );
    inline
    void send();

    inline
    void listen();

    QHostAddress    host;
    quint16         port;
    qint32          timeout;


    QTcpSocket *   socket;
    Mode           mode;
    QMutex         mutex;
    QWaitCondition condition;

    QQueue<GameProperties> sendBufer;

  private slots:
    virtual
    void start();

  protected:
    virtual
    void run();

  signals:
    void connected();
    void idGoten( quint16 );
    void newProperty( NetDataContainer<GameProperties> * option );
    void error( int error, QString message );
};

} /* namespace Net */


#endif /* TCPCLIENT_H_ */
