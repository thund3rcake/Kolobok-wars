/*
 *
 * Created on: 10.05.2012
 *
 * TCPServer.h
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

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <QTcpServer>

#include <UDPServer.h>
#include <PlayerThread.h>

namespace Net
{

class TCPServer: public QTcpServer
{
    Q_OBJECT

  public:
    TCPServer(
               quint16 port,
               UDPServer & udpServer,
               QObject *parent = 0
              );

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

  protected:
    virtual
    void incomingConnection( int socketDescriptor );


  private:
    quint16 port;

    UDPServer & udpServer;
};


} /* namespace Net */


#endif /* TCPSERVER_H_ */
