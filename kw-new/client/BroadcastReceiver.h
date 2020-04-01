#ifndef BROADCASTRECEIVER_H
#define BROADCASTRECEIVER_H

#include <QtNetwork/QUdpSocket>
#include<Versions.h>
#include<Datagramms.h>

class ServersTable;


class BroadcastReceiver:  public QUdpSocket{
    Q_OBJECT
public:
    BroadcastReceiver(
            QVector<ServerAbout> & servers,
            QWidget * parent = 0
            );

    class Exception
        {
          public:
            explicit
            Exception( int no ):
              errNo( no )
            {};

            Exception( int no, const QString & msg ):
              errNo( no ),
              message( msg )
            {};

            int errNo;
            QString message;
        };

private:
    BroadcastReceiver();
    BroadcastReceiver(const BroadcastReceiver & rhs);
    BroadcastReceiver & operator =(const BroadcastReceiver & rhs) const;
    QVector<ServerAbout> & servers;

private slots:
    void processPendingDatagramms();

signals:
    void newServer(int vectorIndex);
};

#endif // BROADCASTRECEIVER_H