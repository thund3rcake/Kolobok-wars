#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include<QtCore>
#include<QThread>
#include<QtNetwork>
#include<QQueue>
#include<QMutex>
#include<QLinkedList>

#include<NetDataContainer.h>
#include<Datagramms.h>
#include<Versions.h>

static const qint32 MaxPackegeDelay = 200;

class UdpClient: public QThread {
    Q_OBJECT

public:
    typedef NetDataContainer<MovingObjectProperties> MObjPrptContainer;

    UdpClient(
            const QHostAddress & server,
            quint16 port,
            QObject * parent
            );

    virtual ~UdpClient();

    class Exception {
    public:
        explicit Exception (int no):
            errNo(no) {};

        Exception (int no, const QString & msg) :
            errNo(no),
            message(msg) {};

        int errNo;
        QString message;
    };

public slots:
    void sendNewObjectProperties(MovingObjectProperties & prpt);
    quint16 getPort() {
        return ownPort;
    }

private:
    UdpClient();
    UdpClient(const UdpClient & rhs);
    UdpClient & operator = (const UdpClient & rhs);

    inline void send();
    inline void receive();
    inline bool packegeQuality(quint32 timestamp, bool incrementBadPckg = true);

    QHostAddress server;
    quint16 port;
    quint16 ownPort;

    quint32 prevTimestamp;
    quint32 laggingFrom100;
    quint32 receivedFrom100;
    QUdpSocket * socket;

    QQueue<MovingObjectProperties> outgoing;
    bool toQuit;
    QMutex mutex;

private slots:
    void checkError (QAbstractSocket::SocketError);

protected:
    virtual void run();

signals:
    void newObjectProperties(NetDataContainer<MovingObjectProperties> * prpt);
    void error (int error, QString message);
};

#endif // UDPCLIENT_H
