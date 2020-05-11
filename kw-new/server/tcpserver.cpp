#include "tcpserver.h"
#include "udpserver.h"
#include "servertools.h"
#include "playerthread.h"

TcpServer::TcpServer(quint16 port,
                     UdpServer & udpServer,
                     Shared & shared,
                     QObject * parent) :
    QTcpServer(parent),
    port(port),
    udpServer(udpServer),
    sharedData(shared)
{
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "TCP Server: listen failed";
    } else {
        qDebug() << "TCP Server: listen OK";
    }
}

void TcpServer::incomingConnection(int socketDescriptor) {
    qDebug() << "TcpServer::incomingConnection";

    quint16 id = 0;

    sharedData.nextPlayerId.writeLock();
    id = sharedData.nextPlayerId.read();
    sharedData.nextPlayerId.get()++;
    sharedData.nextPlayerId.writeUnlock();

    PlayerThread * thread = new PlayerThread(id, socketDescriptor,
                                             udpServer, sharedData, this);

    QObject::connect(thread, SIGNAL(finished()),
                this, SLOT(deletePlayer));
    QObject::connect(thread, SIGNAL(finished()),
                thread, SLOT(deletePlayer));


    sharedData.playerById.writeLock();
    sharedData.playerById.get().insert(id, thread);
    sharedData.playerById.writeUnlock();

    thread->start();
}

void TcpServer::deletePlayer() {
    PlayersMap::iterator it = sharedData.playerById.get().begin();
    for (;it != sharedData.playerById.get().end() && it.value()->isFinished(); ++it);
    if (it != sharedData.playerById.get().end()) {
        delete it.value();
        sharedData.playerById.get().remove(it.key());
    }
}
