#include <playerthread.h>
#include <botthread.h>
#include <GameWorldConsts.h>

PlayerThread::PlayerThread(quint16 id, qintptr socketDescriptor,
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
    gameEventsTimer(new QTimer(this)),
    timestampCounter(0),
    noPacketsCounter(0),
    stopped(false),
    allowFire(true) {

    playerMovProperties.setEmptyProperty();

    sharedData.playerLatencyById.writeLock();
    sharedData.playerLatencyById.get().insert(id, 1);
    sharedData.playerLatencyById.writeUnlock();

    gameEventsTimer->setInterval(100);
    QObject::connect(gameEventsTimer, SIGNAL(timeout()),
                     this, SLOT(regularGameEvents()));
    gameEventsTimer->start();
    timer.start();
}

quint16 PlayerThread::getId() {
    return id;
}

const MovingObjectProperties & PlayerThread::getMovProperties() {
    QMutexLocker locker(&propertiesMutex);
    return playerMovProperties;
}

void PlayerThread::sendDamage(quint16 id) {
    sharedData.playerById.readLock();
    PlayersMap::iterator player = sharedData.playerById.get().find(id);
    if (player != sharedData.playerById.get().end()) {
        player.value()->getDamage();
    } else {
        sharedData.botById.readLock();
        BotsMap::iterator bot = sharedData.botById.get().find(id);
        if (bot != sharedData.botById.get().end()) {
            bot.value()->getDamage();
        }
        sharedData.botById.readUnlock();
    }
    sharedData.playerById.readUnlock();
}

void PlayerThread::getDamage() {
    QMutexLocker locker(&propertiesMutex);
    quint8 hp = playerMovProperties.getHp();
    if (playerMovProperties.getHp() > consts::bulletDamage) {
        playerMovProperties.setHp(hp - consts::bulletDamage);
    } else {
        playerMovProperties.setHp(0);
    }
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
    prop.setEmptyProperty();
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
        emit error(-1, "Client closes the connection");
        stopped = true;
        return 0;
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
        stopped = true;
        return 0;
    }

    in >> blockSize;
    qDebug() << blockSize;

    if (!waitForBytesAvailable(blockSize, 500)) {
        qDebug() << "PlayerThread::startCommutication() : TCP error 2"
                 << tcpSocket->errorString();
        stopped = true;
        return 0;
    }

    packetBufer.resize(blockSize);

    GameProperties prop;
    in >> prop;

    if (prop.getType() != GameProperties::UdpPort) {
        stopped = true;
    }

    qDebug() << (quint16)prop.getFirstQInt();
    return (quint16)prop.getFirstQInt();
}

void PlayerThread::sendMovProperties(const MovingObjectProperties & prop) {
    UdpServer::Packet packet;

    if (peerAddress) {
        packet.port       = peerPort;
        packet.address    = *peerAddress;
        packet.properties = prop;
        udpServerOnlyForSend.sendPacket(packet);
    }
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
    foreach ( BotThread * bot, sharedData.botById.get() ) {
        if (bot->getId() != this->id) {
            qreal lgth = getLength(position, bot->getBotProperties().getPosition() );
            if (lgth < consts::playerSize*2) {
                return lgth;
            }
            minLength = minLength < lgth ? minLength : lgth;
        }
    }
  return minLength;
}

qint32 PlayerThread::playerIdToBeHit(const QPointF position) {
    sharedData.playerById.readLock();
    foreach (PlayerThread * player, sharedData.playerById.get()) {
        if (player->getId() != id) {
            qreal lgth = getLength(position, player->getMovProperties().getPosition());
            if (lgth < consts::playerSize) {
                sharedData.playerById.readUnlock();
                return player->getId();
            }
        }
    }
    sharedData.playerById.readUnlock();

    sharedData.botById.readLock();
    foreach (BotThread * bot, sharedData.botById.get()) {
        if (bot->getId() != id) {
            qreal lgth = getLength(position, bot->getBotProperties().getPosition());
            if (lgth < consts::playerSize) {
                sharedData.botById.readUnlock();
                return bot->getId();
            }
        }
    }
    sharedData.botById.readUnlock();
    return 0;
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

void PlayerThread::updateBulletCoordinates() {
    sharedData.bulletById.writeLock();
    foreach(Bullet* blt, sharedData.bulletById.get()) {
        if (id == blt->getBulletWeapon().getMasterId()) {
            QPointF intentedDot = blt->getPosition() + 7*blt->getBulletWeapon().getTarget();
            quint16 victimId = playerIdToBeHit(intentedDot);
            if (victimId) {
                sharedData.bulletById.get().remove(blt->getId());
                sendDamage(victimId);
                delete blt;
            } else if (!sharedData.gameMap.get()->isDotAvailable(intentedDot.toPoint())) {
                sharedData.bulletById.get().remove(blt->getId());
                delete blt;
            } else {
                blt->setPosition(intentedDot);
            }
        }
    }
    sharedData.bulletById.writeUnlock();
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

QPointF PlayerThread::getRespawnPlace() {
    quint16 x = 0, y = 0;
    srand (time(NULL));
    while(!(sharedData.gameMap.get()->isDotAvailable(QPoint(x, y)))) {
        x = rand() % consts::mapSizeX;
        y = rand() % consts::mapSizeY;
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
    QHostAddress ip4Address(peerAddress->toIPv4Address());
    //qDebug() << "Player " << id << "has IP " << ip4Address.toString();
    emit getIP(ip4Address.toString());

    bool gotten = false;
    bool toQuit = false;

    QMap<qint32, qint32>::iterator latencyIter;

    playerMovProperties.setPosition(getRespawnPlace());

    while(!stopped && !toQuit) {
        sharedData.quit.readLock();
        toQuit = sharedData.quit.get();
        sharedData.quit.readUnlock();

        if (!playerMovProperties.getHp()) {
            playerMovProperties.setPosition(getRespawnPlace());
            playerMovProperties.setHp(100);
        }

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
        updateBulletCoordinates();
        sendMovProperties(playerMovProperties);

        sharedData.playerById.readLock();
        foreach (PlayerThread * player, sharedData.playerById.get()) {
            if (!(player->isFinished()) && player->getId() != id) {
                sendMovProperties(player->getMovProperties());
            }
        }
        sharedData.playerById.readUnlock();

        sharedData.botById.readLock();
        foreach (BotThread * bot, sharedData.botById.get()) {
            if (!(bot->isFinished())) {
                    sendMovProperties(bot->getBotProperties());
            }
        }
        sharedData.botById.readUnlock();


        if (playerMovProperties.getWeapon().getState() == Weapon::Fire
                && allowFire) {
            qint32 bltId = 0;
            sharedData.nextBulletId.readLock();
            bltId = sharedData.nextBulletId.get();
            sharedData.nextBulletId.get()++;
            sharedData.nextBulletId.readUnlock();
            Bullet * blt = new Bullet(bltId,
                                      playerMovProperties.getPosition() +
                                      consts::playerSize*playerMovProperties.getHead().toPointF(),
                                      playerMovProperties.getHead().toPointF(),
                                      id, Weapon::Blaster);

            sharedData.bulletById.readLock();
            sharedData.bulletById.get().insert(bltId, blt);
            sharedData.bulletById.readUnlock();

            allowFire = false;
        }

        usleep(100);
    }

    QObject::disconnect(gameEventsTimer, SIGNAL(timeout()),
                         this, SLOT(regularGameEvents()));

    if (tcpSocket) {
        delete tcpSocket;
    }

    if (incomingUdpQueue) {
        delete incomingUdpQueue;
    }

    if (peerAddress) {
        delete peerAddress;
    }

    if (!toQuit) {
        playerMovProperties.setPosition(QPointF(0, 0));
        usleep(100000);
        sharedData.playerById.writeLock();
        sharedData.playerById.get().remove(id);
        qDebug() << "Player removed from the map: " << id;
        sharedData.playerById.writeUnlock();
    } else {
        QObject::disconnect(this, SIGNAL(finished()),
                this, SLOT(deleteLater()));
    }
}
