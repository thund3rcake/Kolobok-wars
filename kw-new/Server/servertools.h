#ifndef SERVERTOOLS_H
#define SERVERTOOLS_H


#include <QtCore>
#include <QtGui>
#include <QTime>
#include <QTextEdit>

#include <sharedtypes.h>
#include <BroadcastSender.h>
#include <udpserver.h>
#include <Bullet.h>
#include <Map.h>

class PlayerThread;

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

    BroadcastSender & getBroadcastSender() { return * broadcastSender; }
    UdpServer       & getUdpServer      () { return * udpServer; }
//    TCPServer       & getTcpServer      () { return * tcpServer; }
    Shared               & getShared         () { return data; }
    qint32                 getCurentTime     () { return curTime.elapsed(); }

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
//    TCPServer *       tcpServer;

    Shared data;

private slots:
    void setNewUdpPacket();
};

#endif // SERVERTOOLS_H
