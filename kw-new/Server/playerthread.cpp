#include <playerthread.h>
#include <GameWorldConsts.h>

PlayerThread::PlayerThread(quint16 id, int socketDescriptor,
             UdpServer & udpServer, Shared & sharedData,
             QObject * parent):
    QThread(parent),
    id(id),
    socketDescriptor(socketDescriptor),
    sharedData(sharedData),
    udpServerOnlyForSend(udpServer),
    incomingUdpQueue(new SharedUdpQueue),
    peerAddress(NULL),
    peerPort(0),
    timestampSendTimer(new QTimer(this)) {

    sharedData.playerLatencyById.writeLock();
    sharedData.playerLatencyById.get().insert(id, 1);
    sharedData.playerLatencyById.writeUnlock();

    timestampSendTimer->setInterval(5000);
    QObject::connect(timestampSendTimer, SIGNAL(timeout()),
                     this, SLOT(sendTimestamp()));
    timestampSendTimer->start();
    timer.start();
}

quint16 PlayerThread::getId() {
    return id;
}

MovingObjectProperties PlayerThread::getMovProperties() {
    QMutexLocker locker(&propertiesMutex);
    return playerMovProperties;
}

SharedUdpQueue * PlayerThread::getUdpQueue() {
    return incomingUdpQueue;
}

QHostAddress * PlayerThread::getPeerAddr() {
    return peerAddress;
}

void PlayerThread::setPeerPort(quint16 port) {
    peerPort = port;
}

void PlayerThread::sendTimestamp() {
    MovingObjectProperties prop;
    prop.setType(MovingObjectProperties::Timestamp);
    sendMovProperties(prop);
}

void PlayerThread::sendGameProperty(const GameProperties & prop)
{
  QDataStream request(tcpSocket);
  request.setVersion(Net::DataStreamVersion);

  if (!(tcpSocket->isWritable())) {
      //delete the thread
  }

  request << (quint32)0;
  request << prop;
  request.device() -> seek(0);
  request << (quint32)(packetBufer.size() - sizeof(quint32));

  tcpSocket -> waitForBytesWritten(10);
}

bool PlayerThread::waitForBytesAvailable(qint64 size, qint32 maxTime,
                                         bool noBytesIsError) {
    while (tcpSocket->bytesAvailable() < size) {
        if (!(tcpSocket->waitForReadyRead(maxTime)) && noBytesIsError) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            tcpSocket->disconnectFromHost();
        }
    }
    return false;
}

quint16 PlayerThread::receivePeerPort() {
    QDataStream blockStream(&packetBufer, QIODevice::WriteOnly);
    blockStream.setVersion(Net::DataStreamVersion);

    // ! blockStream << (quint32)0;
    blockStream << QStringSignature;
    blockStream << Net::ProtVersion;
    blockStream << Net::ProtSubversion;
    blockStream << id;

    // blockStream.device()->seek(0);
    // ! blockStream << (quint32)(packetBufer.size() - sizeof(quint32));

    if (!waitForBytesAvailable(sizeof(quint64), 1500)) {
        qDebug() << "PlayerThread::startCommutication() : TCP error "
                 << tcpSocket->errorString();
        return 0;
    }

    quint64 blockSize;
    QDataStream in(tcpSocket);
    in.setVersion(Net::DataStreamVersion);

    in >> blockSize;
    //qDebug() << blockSize;

    if (!waitForBytesAvailable(blockSize, 500)) {
        qDebug() << "PlayerThread::startCommutication() : TCP error "
                 << tcpSocket->errorString();
        return 0;
    }

    packetBufer.resize(blockSize);

    GameProperties prop;
    in >> prop;

    if (prop.getType() != GameProperties::UdpPort) {
        //delete the thread
    }

    return (quint16)prop.getFirstQInt();
}

void PlayerThread::sendMovProperties(const MovingObjectProperties & prop) {
    UdpServer::Packet packet;

    packet.port       = peerPort;
    packet.address    = *peerAddress;
    packet.properties = prop;

    udpServerOnlyForSend.sendPacket(packet);
}

MovingObjectProperties PlayerThread::getProperty(bool & gotten) {
    MovingObjectProperties prop;

    incomingUdpQueue->writeLock();
    if (!(incomingUdpQueue->get().isEmpty())) {
        gotten = true;
        prop = incomingUdpQueue->get().dequeue();
    } else {
        gotten = false;
    }
    incomingUdpQueue->writeUnlock();

    return gotten ? prop : playerMovProperties;
}

qreal PlayerThread::getLength(QPointF a, QPointF b) {
    return sqrt( (a.rx() - b.rx())*(a.rx() - b.rx()) + (a.ry() - b.ry())*(a.ry() - b.ry()) );
}

//TODO: rename func; l-value ref
qreal PlayerThread::isThereCollisionsWithTheOthers ( QPointF position ) {
    foreach ( PlayerThread * player, sharedData.playerById.get() ) {
        if (player->getId() != this->id) {
            qreal lgth = getLength(position, player -> getMovProperties().getPosition() );
            if (lgth < consts::playerSize*2) {
                return lgth;
            }
        }
    }
  return consts::playerSize*2;
}

void PlayerThread::updateCoordinates (MovingObjectProperties & prop) {
    if ( prop.getTimestamp() <= consts::sendTimerInterval*1.25 ) {
        QPointF increment = prop.getIntent().toPointF()*prop.getTimestamp()/25;
        QPointF intentedDot = prop.getPosition();

        for (int i = 0; i < 5; i++) {
            intentedDot += increment;
            if ( isThereCollisionsWithTheOthers(intentedDot) >= isThereCollisionsWithTheOthers(getMovProperties().getPosition())
            && sharedData.gameMap.get() -> isDotAvailable(intentedDot.toPoint()) ) {
                propertiesMutex.lock();
                prop.setPosition(intentedDot);
                propertiesMutex.unlock();
            }
        }
    }
    return;
}

void PlayerThread::run() {
    tcpSocket = new QTcpSocket;
    if (!(tcpSocket->setSocketDescriptor(socketDescriptor))) {
        qDebug() << "PlayerThread::run(): " << tcpSocket->errorString();
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return;
    }

    setPeerPort(receivePeerPort());
    peerAddress = new QHostAddress(tcpSocket->peerAddress());

    bool gotten = false;
    QMap<qint32, qint32>::iterator latencyIter;

    while(1) { //change
        playerMovProperties = getProperty(gotten);
        //if (timeout > ...) { emit finished(); return; }
        if (gotten == false) {
            usleep(100);
            continue;
        }

        latencyIter = sharedData.playerLatencyById.get().find(id);
        if (latencyIter != sharedData.playerLatencyById.get().end())  {
            latency = latencyIter.value();
        }

        updateCoordinates(playerMovProperties);
        sendMovProperties(playerMovProperties);

        sharedData.nextPlayerId.readLock();
        foreach (PlayerThread * player, sharedData.playerById.get()) {
            if (!(player->isFinished()) && player->getId() != id) {
                sendMovProperties(player->getMovProperties());
            }
        }
        sharedData.nextPlayerId.readUnlock();
        usleep(100);
    }
}
