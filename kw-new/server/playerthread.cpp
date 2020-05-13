#include <playerthread.h>
#include <GameWorldConsts.h>

PlayerThread::PlayerThread(quint16 id, qintptr socketDescriptor,
             UdpServer & udpServer, Shared & sharedData, const bool & quit,
             QObject * parent):
    QThread(parent),
    id(id),
    socketDescriptor(socketDescriptor),
    sharedData(sharedData),
    udpServerOnlyForSend(udpServer),
    incomingUdpQueue(new SharedUdpQueue),
    peerAddress(NULL),
    peerPort(0),
    gameEventsTimer(new QTimer(this)),
    timestampCounter(0),
    noPacketsCounter(0),
    stopped(false),
    allowFire(true),
    quit(quit) {

    playerMovProperties = getEmptyProperty();

    sharedData.playerLatencyById.writeLock();
    sharedData.playerLatencyById.get().insert(id, 1);
    sharedData.playerLatencyById.writeUnlock();

    gameEventsTimer->setInterval(100);
    QObject::connect(gameEventsTimer, SIGNAL(timeout()),
                     this, SLOT(regularGameEvents()));
    gameEventsTimer->start();
    timer.start();
}

PlayerThread::~PlayerThread() {
    if (tcpSocket) {
        delete tcpSocket;
    }

    if (incomingUdpQueue) {
        delete incomingUdpQueue;
    }
}

quint16 PlayerThread::getId() {
    return id;
}

const MovingObjectProperties & PlayerThread::getMovProperties() {
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
    MovingObjectProperties prop = getEmptyProperty();
    prop.setType(MovingObjectProperties::Timestamp);
    sendMovProperties(prop);
}

bool PlayerThread::waitForBytesAvailable(qint64 size, qint32 maxTime,
                                         bool noBytesIsError) {
    while (tcpSocket->bytesAvailable() < size) {
        if (!(tcpSocket->waitForReadyRead(maxTime))) {
            if (noBytesIsError) {
                emit error(tcpSocket->error(), tcpSocket->errorString());
                tcpSocket->disconnectFromHost();
            }
            return false;
        }
    }
    return true;
}

quint16 PlayerThread::receivePeerPort() {
    QDataStream blockStream(&packetBufer, QIODevice::WriteOnly);
    blockStream.setVersion(Net::DataStreamVersion);

    blockStream << QStringSignature;
    blockStream << Net::ProtVersion;
    blockStream << Net::ProtSubversion;
    blockStream << id;

    QDataStream sockStream(tcpSocket);
    sockStream.setVersion(Net::DataStreamVersion);

    if (!(tcpSocket->isWritable())) {
        qDebug() << "notWritable";
        emit error(-1, "Client closes the connection");
    }

    sockStream << (quint32)packetBufer.size();
    sockStream << packetBufer;

    tcpSocket->waitForBytesWritten(10);

    packetBufer.clear();
    quint32 blockSize;
    QDataStream in(tcpSocket);
    in.setVersion(Net::DataStreamVersion);

    if (!waitForBytesAvailable(sizeof(quint32), 1500)) {
        qDebug() << "PlayerThread::startCommutication() : TCP error 1"
                 << tcpSocket->errorString();
        return 0;
    }

    in >> blockSize;

    if (!waitForBytesAvailable(blockSize, 500)) {
        qDebug() << "PlayerThread::startCommutication() : TCP error 2"
                 << tcpSocket->errorString();
        return 0;
    }

    packetBufer.resize(blockSize);

    GameProperties prop;
    in >> prop;

    if (prop.getType() != GameProperties::UdpPort) {
        //delete the thread
    }

    qDebug() << (quint16)prop.getFirstQInt();
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

qreal PlayerThread::getLength(const QPointF a, const QPointF b) {
    return sqrt( (a.x() - b.x())*(a.x() - b.x()) + (a.y() - b.y())*(a.y() - b.y()) );
}

qreal PlayerThread::distanceToTheClosestPlayer (const QPointF position ) {
    qreal minLength = 1000;
    foreach ( PlayerThread * player, sharedData.playerById.get() ) {
        if (player->getId() != this->id) {
            qreal lgth = getLength(position, player -> getMovProperties().getPosition() );
            if (lgth < consts::playerSize*2) {
                return lgth;
            }
            minLength = minLength < lgth ? minLength : lgth;
        }
    }
  return minLength;
}

void PlayerThread::updateCoordinates (MovingObjectProperties & prop) {
    if ( prop.getTimestamp() <= consts::sendTimerInterval*1.25 ) {
        QPointF increment = prop.getIntent().toPointF()*prop.getTimestamp()/25;
        QPointF intentedDot = prop.getPosition();

        for (int i = 0; i < 5; i++) {
            intentedDot += increment;
            qreal thenTheClosest = distanceToTheClosestPlayer(intentedDot);
            if (sharedData.gameMap.get() -> isDotAvailable(intentedDot.toPoint())
                && (thenTheClosest >= 2*consts::playerSize
                    || thenTheClosest > distanceToTheClosestPlayer(prop.getPosition()))) {
                propertiesMutex.lock();
                prop.setPosition(intentedDot);
                propertiesMutex.unlock();
            }
        }
    }
}


void PlayerThread::regularGameEvents() {

    if (noPacketsCounter >= 20000) {
        stopped = true;
    }

    if (timestampCounter >= 50) {
        sendTimestamp();
        timestampCounter = 0;
    }

    allowFire = true;

    timestampCounter++;
}

MovingObjectProperties PlayerThread::getEmptyProperty() {
    MovingObjectProperties prop;
    Weapon wep;
    prop.setTimestamp(0);
    prop.setType(MovingObjectProperties::Timestamp);
    prop.setTeam(MovingObjectProperties::Red);
    prop.setId(0);
    prop.setPosition(QPoint(0, 0));
    prop.setIntent(QVector2D(0, 0));
    prop.setHead(QVector2D(0, 0));
    prop.setHp(0);
    wep.setType(Weapon::Blaster);
    wep.setState(Weapon::NoFire);
    wep.setTarget(QPointF(0, 0));
    wep.setMasterId(0);
    prop.setWeapon(wep);
    return prop;
}

QPointF PlayerThread::getRespawnPlace() {
    quint16 x = 0, y = 0;
    srand (time(NULL));
    while(!(sharedData.gameMap.get()->isDotAvailable(QPoint(x, y)))) {
        x = rand() % 950;
        y = rand() % 700;
    }
    return QPointF(x, y);
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

    playerMovProperties.setPosition(getRespawnPlace());

    while(!stopped && !quit) {
        playerMovProperties <<= getProperty(gotten);

        if (gotten == false) {
            noPacketsCounter++;
            usleep(100);
            continue;
        }

        noPacketsCounter = 0;

        latencyIter = sharedData.playerLatencyById.get().find(id);
        if (latencyIter != sharedData.playerLatencyById.get().end())  {
            latency = latencyIter.value();
        }

        updateCoordinates(playerMovProperties);
        sendMovProperties(playerMovProperties);

        sharedData.playerById.readLock();
        foreach (PlayerThread * player, sharedData.playerById.get()) {
            if (!(player->isFinished()) && player->getId() != id) {
                sendMovProperties(player->getMovProperties());
            }
        }
        sharedData.playerById.readUnlock();
        usleep(100);
    }

    QObject::disconnect(gameEventsTimer, SIGNAL(timeout()),
                         this, SLOT(regularGameEvents()));

    if (!quit) {
        playerMovProperties.setPosition(QPointF(0, 0));
        usleep(100000);
        emit PlayerThread::deletePlayer(id);
    }

//    sharedData.playerById.writeLock();
//    sharedData.playerById.get().remove(id);
//    sharedData.playerById.writeUnlock();
}
