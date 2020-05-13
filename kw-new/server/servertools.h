#ifndef SERVERTOOLS_H
#define SERVERTOOLS_H

#include <QtCore>
#include <QtGui>
#include <QTime>
#include <QTextEdit>

#include "sharedtypes.h"
#include "broadcastsender.h"
#include "udpserver.h"
#include "tcpserver.h"
#include "playerthread.h"
#include "Bullet.h"
#include "Map.h"

class PlayerThread;
class UdpServer;

class ServerTools: public QObject {
    Q_OBJECT

public:
    ServerTools(
                  const QString & serverName,
                  const QString & mapName,
                  quint16 port,
                  quint8  maxPlayers,
                  QTextEdit * console,
                  QObject * parent
                 );

    virtual
    ~ServerTools();

    BroadcastSender & getBroadcastSender();
    UdpServer       & getUdpServer();
    TcpServer       & getTcpServer();
    Shared          & getShared();
    qint32          getCurentTime();

private:
    ServerTools();
    ServerTools( const ServerTools & rhs );
    ServerTools & operator=( const ServerTools & rhs );

    QString     serverName;
    QString     mapName;
    quint16     port;
    quint8      maxPlayers;
    quint8      bots;
    quint8      players;
    QTextEdit * console;

    QTime       curTime;

    BroadcastSender * broadcastSender;
    UdpServer *       udpServer;
    TcpServer *       tcpServer;

    Shared data;
    bool quit;

private slots:
    void setNewUdpPacket();
};

#endif // SERVERTOOLS_H
