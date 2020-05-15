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
    qDebug() << "udp";
    mutex.lock();
    toQuit = true;
    mutex.unlock();
//    qDebug() << "udpquit";
    wait();
//    qDebug() << "udpwait";
    if(socket) {
        delete socket;
//        qDebug() << "udpdelete";
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
//    if (!toQuit) {
        while (!toQuit) {
            mutex.unlock();;
            send();
            receive();
        }
//    } else {
//        return;
//    }
}





void UdpClient::send() {

    static QByteArray block;
    MovingObjectProperties sendProperty;
    sendProperty.setEmptyProperty();
    QDataStream request(&block, QIODevice::OpenModeFlag::WriteOnly);

    request.setVersion( Net::DataStreamVersion );

    QMutexLocker locker (&mutex);

    for (int i = 0; i < outgoing.size(); ++i) {
        sendProperty.setTimestamp(prevTimestamp);

        block.clear();
        sendProperty = outgoing.dequeue();

        request << (quint32)0;
        request << sendProperty;
        request.device() -> seek(0);
        request << (quint32)(block.size() - sizeof(quint32));

        socket -> writeDatagram( block.data(), block.size(), server, port );

    }
}


void UdpClient::receive() {


    static QByteArray block;
    QDataStream response(&block, QIODevice::OpenModeFlag::ReadOnly);
    response.setVersion(Net::DataStreamVersion);

    static QHostAddress address;
    static quint16 port;



    if (socket -> hasPendingDatagrams()) {
        block.clear();
        block.resize(socket -> pendingDatagramSize());
        socket ->readDatagram(
                                                            block.data(),
                                                            block.size(),
                                                            &address,
                                                            &port
                                                            );
        if (address != this -> server || port != this -> port) {
            return;
        }

        NetDataContainer<MovingObjectProperties> * container = new NetDataContainer<MovingObjectProperties>;
        quint32 size;

        response >> size;
        response >> container -> getOption();
        MovingObjectProperties::Type pckgType = container -> getOption().getType();

        if (!packegeQuality(container -> getOption().getTimestamp(), (pckgType == MovingObjectProperties::Timestamp)? false: true)) {
          qDebug() << "!packegeQuality";
          return;
        }

        prevTimestamp = container -> getOption().getTimestamp();

        if(pckgType == MovingObjectProperties::Timestamp) {
            sendNewObjectProperties( container -> getOption() );
            delete container;
            return;
        }
        emit newObjectProperties( container );
      }
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

    if (laggingFrom100 > 1000) {
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