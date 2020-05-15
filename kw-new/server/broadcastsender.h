#ifndef BROADCASTSENDER_H_
#define BROADCASTSENDER_H_

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QDataStream>
#include <QThread>

#include <Datagramms.h>
#include <Versions.h>
#include <sharedtypes.h>

namespace Net {}

class BroadcastSender: public QThread
{
  Q_OBJECT

  public:
    BroadcastSender(
                     const QString & serverName,
                     const QString & mapName,
                     Shared & sharedData,
                     quint16 port,
                     quint16 tcpPort,
                     quint8  maxPlayers,
                     quint8  bots,
                     QObject * parent = 0
                    );

    virtual
    ~BroadcastSender();

  public slots:
    void generateDatagram();
    void setMapName(const QString & mapName);
    void setBotCount(quint8 count);

  private:
    BroadcastSender();
    BroadcastSender(const BroadcastSender & rhs);
    BroadcastSender & operator= (const BroadcastSender & rhs);

    bool         quit;
    QUdpSocket * socket;
    Shared & sharedData;

    QMutex     mutex;
    QString    serverName;
    QString    mapName;
    quint16    port;
    quint16    tcpPort;
    quint8     maxPlayers;
    quint8     players;
    quint8     bots;
    QByteArray datagram;

  protected:
    virtual
    void run();

  signals:
    void error (int errNo, QString message);
};


#endif /* BROADCASTSENDER_H_ */
