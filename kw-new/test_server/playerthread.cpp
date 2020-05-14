#include <playerthread.h>
#include <GameWorldConsts.h>
#include "Bullet.h"

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

void PlayerThread::sendDamage(quint16 id) {
    sharedData.playerById.readLock();
    PlayersMap::iterator player = sharedData.playerById.get().find(id);
    if (player != sharedData.playerById.get().end()) {
        player.value()->getDamage();
    }
    sharedData.playerById.readUnlock();
}

void PlayerThread::getDamage() {
    QMutexLocker locker(&propertiesMutex);
    quint8 hp = playerMovProperties.getHp();
    playerMovProperties.setHp(hp - 15);
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

qreal PlayerThread::distanceToTheClosestPlayer (const QPointF position, const qreal critical) {
    qreal minLength = 1000;
    sharedData.playerById.readLock();
    foreach ( PlayerThread * player, sharedData.playerById.get() ) {
        if (player->getId() != id) {
            qreal lgth = getLength(position, player -> getMovProperties().getPosition() );
            if (lgth < critical) {
                return lgth;
            }
            minLength = minLength < lgth ? minLength : lgth;
        }
    }
    sharedData.playerById.readUnlock();
  return minLength;
}

qint32 PlayerThread::playerIdToBeHit(const QPointF position) {
    sharedData.playerById.readLock();
    foreach (PlayerThread * player, sharedData.playerById.get()) {
        if (player->getId() != id) {
            qreal lgth = getLength(position, player->getMovProperties().getPosition());
            if (lgth < consts::playerSize) {
                return player->getId();
            }
        }
    }
    sharedData.playerById.readUnlock();
    return 0;
}

void PlayerThread::updateCoordinates (MovingObjectProperties & prop) {
    if ( prop.getTimestamp() <= consts::sendTimerInterval*1.25 ) {
        QPointF increment = prop.getIntent().toPointF()*prop.getTimestamp()/25;
        QPointF intentedDot = prop.getPosition();

        for (int i = 0; i < 5; i++) {
            intentedDot += increment;
            qreal thenTheClosest = distanceToTheClosestPlayer(intentedDot, consts::playerSize*2);
            if (sharedData.gameMap.get() -> isDotAvailable(intentedDot.toPoint())
                && (thenTheClosest >= 2*consts::playerSize
                    || thenTheClosest > distanceToTheClosestPlayer(prop.getPosition(), consts::playerSize*2))) {
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
                MovingObjectProperties prop = sharedData.playerById.get().find(victimId).value()->getMovProperties();
                delete blt;
            } else if (!sharedData.gameMap.get()->isDotAvailable(intentedDot.toPoint())) {
                sharedData.bulletById.get().remove(blt->getId());
            } else {
                blt->setPosition(intentedDot);
                //sendProperty...
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
        updateBulletCoordinates();

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

        if (playerMovProperties.getWeapon().getState() == Weapon::Fire
                && allowFire) {
            qint32 bltId = 0;
            sharedData.nextBulletId.readLock();
            bltId = sharedData.nextBulletId.get();
            sharedData.nextBulletId.get()++;
            sharedData.nextBulletId.readUnlock();
            Bullet * blt = new Bullet(bltId, playerMovProperties.getPosition(),
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

    if (!quit) {
        playerMovProperties.setPosition(QPointF(0, 0));
        usleep(100000);
        emit PlayerThread::deletePlayer(id);
    }
}
