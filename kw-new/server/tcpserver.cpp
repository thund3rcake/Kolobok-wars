#include "tcpserver.h"
#include "udpserver.h"
#include "servertools.h"
#include "playerthread.h"

TcpServer::TcpServer(quint16 port,
                     quint8 maxPlayers,
                     UdpServer & udpServer,
                     Shared & shared,
                     QObject * parent) :
    QTcpServer(parent),
    port(port),
    maxPlayers(maxPlayers),
    udpServer(udpServer),
    sharedData(shared)
{
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
                                             udpServer, sharedData, this);

        QObject::connect(thread, &PlayerThread::getIP, this, &TcpServer::sendIP);

//        QObject::connect(thread, SIGNAL(finished()),
//                this, SLOT(deletePlayer));
        QObject::connect(thread, SIGNAL(finished()),
                thread, SLOT(deleteLater()));


        sharedData.playerById.writeLock();
        sharedData.playerById.get().insert(id, thread);
        sharedData.playerById.writeUnlock();

        thread->start();
    }
}

void TcpServer::sendIP(QString ipStr) {
    qDebug() << "tcp: " << ipStr;
    emit newIP(ipStr);
}

//void TcpServer::deletePlayer() {
//    PlayersMap::iterator it = sharedData.playerById.get().begin();
//    for (;it != sharedData.playerById.get().end() && it.value()->isFinished(); ++it);
//    if (it != sharedData.playerById.get().end()) {
//        delete it.value();
//        sharedData.playerById.get().remove(it.key());
//    }
//}
