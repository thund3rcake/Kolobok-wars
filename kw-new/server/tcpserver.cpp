#include "tcpserver.h"
#include "udpserver.h"
#include "servertools.h"
#include "playerthread.h"

TcpServer::TcpServer(quint16 port,
                     quint8 maxPlayers,
                     UdpServer & udpServer,
                     Shared & shared,
                     const bool & quit,
                     QObject * parent) :
    QTcpServer(parent),
    port(port),
    maxPlayers(maxPlayers),
    udpServer(udpServer),
    sharedData(shared),
    quit(quit) {
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "TCP Server: listen failed";
    } else {
        qDebug() << "TCP Serve r: listen OK";
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "TcpServer::incomingConnection";

    quint8 curPlayers = 0;

    sharedData.playerById.readLock();
    curPlayers = sharedData.playerById.get().size();
    sharedData.playerById.readUnlock();

    if (curPlayers < maxPlayers) {

        quint16 id = 0;

        sharedData.nextPlayerId.writeLock();
        id = sharedData.nextPlayerId.read();
        sharedData.nextPlayerId.get()++;
        sharedData.nextPlayerId.writeUnlock();

        PlayerThread * thread = new PlayerThread(id, socketDescriptor,
                                    udpServer, sharedData, quit, this);

        QObject::connect(thread, &PlayerThread::finished, thread, &PlayerThread::deleteLater);
        QObject::connect(thread, &PlayerThread::deletePlayer, this, &TcpServer::onDeletePlayer);

        sharedData.playerById.writeLock();
        sharedData.playerById.get().insert(id, thread);
        sharedData.playerById.writeUnlock();

        thread->start();
    }
}

void TcpServer::onDeletePlayer(quint16 id) {
    sharedData.playerById.writeLock();
    sharedData.playerById.get().remove(id);
    qDebug() << "deleted from dic new way";
    sharedData.playerById.writeUnlock();
}
