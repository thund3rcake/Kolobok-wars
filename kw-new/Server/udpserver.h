#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QtCore>
#include <QTime>
#include <QThread>
#include <QtNetwork>

#include "Datagramms.h"
//#include "servertools.h"

class ServerTools;

class UdpServer : public QThread {
    Q_OBJECT

public:

    explicit
    UdpServer(quint16 port,
              QObject *parent = 0
              );

    virtual
    ~UdpServer();

    struct Packet {
        MovingObjectProperties properties;
        quint16                port;
        QHostAddress           address;
    };

    const Packet getPacket(bool &result);
    void         sendPacket(const Packet &packet);

protected:

    virtual
    void run();

private:
    UdpServer();
    UdpServer(const UdpServer &rhs);
    UdpServer& operator=(const UdpServer &rhs);

    quint16     port;
    QUdpSocket *socket;

    QMutex      quitMutex;
    bool        toQuit;

    QMutex         outgoingMutex;
    QMutex         incomingMutex;
    QQueue<Packet> outgoing;
    QQueue<Packet> incoming;

signals:
    void error(int, QString);
    void newPacket();
};


#endif // UDPSERVER_H
