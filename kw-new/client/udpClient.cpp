#include <UdpClient.h>
#include<NetDataContainer.h>

UdpClient::UdpClient(
                                                const QHostAddress &server,
                                                quint16 port,
                                                QObject *parent
                                                ) :
    QThread (parent),
    server(server),
    port(port),
    ownPort(0),
    prevTimestamp(0),
    laggingFrom100(0),
    receivedFrom100(0),
    socket (NULL),
    toQuit(false) {}


UdpClient::~UdpClient() {
    mutex.lock();
    toQuit = true;
    mutex.unlock();

    wait();
    if(socket) {
        delete socket;
    }
}


void UdpClient::sendNewObjectProperties(MovingObjectProperties &prpt) {
    QMutexLocker locker (&mutex);
    outgoing.enqueue(prpt);
}


void UdpClient::run() {
    socket = new QUdpSocket;

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(checkError(QAbstractSocket::SocketError)));

    if( !(socket -> bind(0, QUdpSocket::DontShareAddress))) {
        emit error(socket -> error(), socket -> errorString());
    }
    ownPort = socket -> localPort();

    mutex.lock();
    while (!toQuit) {
        mutex.unlock();;
        send();
        receive();
        mutex.lock();
    }
    mutex.unlock();
}





void UdpClient::send() {

}


void UdpClient::receive() {

}


bool UdpClient::packegeQuality(quint32 timestamp, bool incrementBadPckg) {
    if (prevTimestamp > timestamp) {
        return false;
    }
    if (incrementBadPckg) {
        if (prevTimestamp - timestamp > MaxPackegeDelay) {
            laggingFrom100++;
        }
    }

    if (laggingFrom100 > 50) {
        emit error(QUdpSocket::UnknownSocketError, "Bad connection.. : (");
    }
    if (receivedFrom100 >= 100) {
        laggingFrom100 = 0;
        receivedFrom100 = 0;
    } else {
        receivedFrom100++;
    }
    return true;
}


void UdpClient::checkError(QAbstractSocket::SocketError) {
    emit error(socket -> error(), socket -> errorString());
}