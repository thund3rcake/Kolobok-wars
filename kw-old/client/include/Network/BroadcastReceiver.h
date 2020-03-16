/*
 *
 * Created on: 15.04.2012
 *
 * BroadcastReceiver.h
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

#ifndef BROADCASTRECEIVER_H_
#define BROADCASTRECEIVER_H_

#include <QtNetwork>
#include <Versions.h>
#include <Datagrams.h>

class LanServersTable;

namespace Net
{

class BroadcastReceiver: public QUdpSocket
{
  Q_OBJECT

  public:
    explicit
    BroadcastReceiver
       (
         QVector<ServerAbout> & srvs,
         QWidget * parent = 0
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

  private:
    BroadcastReceiver();
    BroadcastReceiver( const BroadcastReceiver & rhs );
    BroadcastReceiver & operator=( const BroadcastReceiver & rhs );


    QVector<ServerAbout> & servers;

  private slots:
    void processPendingDatagrams();

  signals:
    void newServer( int vectorIndex );
};

} /* namespace Net */

#endif /* BROADCASTRECEIVER_H_ */
