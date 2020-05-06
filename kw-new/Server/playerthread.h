#ifndef PLAYERTHREAD_H
#define PLAYERTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "udpserver.h"
#include "sharedtypes.h"
#include "Weapon.h"



class PlayerThread : public QThread {
    Q_OBJECT

public:
    PlayerThread(quint16 id, int socketDescriptor,
                 UdpServer & udpServer, Shared & sharedData,
                 QObject * parent);

    quint16 getId();
    MovingObjectProperties getMovProperties();
    SharedUdpQueue * getUdpQueue();
    QHostAddress * getPeerAddr();

    void run();
    void stop();

private:
    quint16 id;
    int socketDescriptor;
    QTcpSocket * tcpSocket;
    QByteArray packetBufer;

    QMutex mutex;
    QTime timer;
    bool stopped;

    Shared & sharedData;

    UdpServer & udpServerOnlyForSend;
    SharedUdpQueue * incomingUdpQueue;
    QHostAddress * peerAddress;
    quint16 peerPort;

    qint32 latency;
    QTimer * timestampSendTimer;

    QMutex propertiesMutex;
    MovingObjectProperties playerMovProperties;

    inline MovingObjectProperties getProperty(bool &gotten);
    inline void sendMovProperties(const MovingObjectProperties &);

    quint16 receivePeerPort();
    void setPeerPort(quint16);

    inline void sendGameProperty(const GameProperties &);
    inline void byteArrayToSocket(const QByteArray & array);
    inline bool waitForBytesAvailable(qint64 size, qint32 maxTime, bool noBytesIsError = true);

    qreal isThereCollisionsWithTheOthers (QPointF position); //rename
    qreal getLength(QPointF, QPointF);

    void updateCoordinates(MovingObjectProperties &);
    bool isThereHits(Bullet *bullet);

private slots:
    void sendTimestamp();

signals:
    void error(int errNo, const QString & msg);
};

#endif // PLAYERTHREAD_H
