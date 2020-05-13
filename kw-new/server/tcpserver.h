#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

#include "udpserver.h"
#include "sharedtypes.h"
#include "playerthread.h"

class TcpServer : public QTcpServer {
    Q_OBJECT

public:
    TcpServer(quint16 port, quint8 maxPlayers, UdpServer & udpServer,
              Shared & sharedData, const bool & quit, QObject *parent = 0);

    class Exception {
    public:
        explicit
        Exception(int no):
           erNno(no) {}

        Exception(int no, const QString & msg):
            erNno(no),
            message(msg) {}

        int     erNno;
        QString message;
    };

protected slots:
    virtual
    void incomingConnection(qintptr socketDescriptor);
    void onDeletePlayer(quint16);

private:
    quint16 port;
    quint8 maxPlayers;
    UdpServer & udpServer;
    Shared & sharedData;
    const bool & quit;

};

#endif // TCPSERVER_H
