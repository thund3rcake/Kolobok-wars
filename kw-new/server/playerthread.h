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
    PlayerThread(quint16 id, qintptr socketDescriptor,
                 UdpServer & udpServer, Shared & sharedData,
                 QObject * parent);

    quint16 getId();
    const MovingObjectProperties & getMovProperties();
    SharedUdpQueue * getUdpQueue();
    QHostAddress * getPeerAddr();

    void run();

private:
    quint16 id;
    qintptr socketDescriptor;
    QTcpSocket * tcpSocket;
    QByteArray packetBufer;

    QMutex mutex;
    QTime timer;

    Shared & sharedData;

    UdpServer & udpServerOnlyForSend;
    SharedUdpQueue * incomingUdpQueue;
    QHostAddress * peerAddress;
    quint16 peerPort;

    qint32 latency;
    QTimer * gameEventsTimer;

    qint32 timestampCounter;
    qint32 noPacketsCounter;

    bool stopped;
    bool allowFire;

    QMutex propertiesMutex;
    MovingObjectProperties playerMovProperties;

    inline MovingObjectProperties getProperty(bool &gotten);
    inline MovingObjectProperties getEmptyProperty();
    inline void sendMovProperties(const MovingObjectProperties &);

    quint16 receivePeerPort();
    void setPeerPort(quint16);
    void sendTimestamp();

    inline void sendGameProperty(const GameProperties &);
    inline void byteArrayToSocket(const QByteArray & array);
    inline bool waitForBytesAvailable(qint64 size, qint32 maxTime, bool noBytesIsError = true);

    qreal distanceToTheClosestPlayer (const QPointF position);
    qreal getLength(const QPointF, const QPointF);

    QPointF getRespawnPlace();

    void updateCoordinates(MovingObjectProperties &);
    bool isThereHits(Bullet *bullet);

private slots:
    void regularGameEvents();
    void stop();

signals:
    void error(int errNo, const QString & msg);
};

#endif // PLAYERTHREAD_H
