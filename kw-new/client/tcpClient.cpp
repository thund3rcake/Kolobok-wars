#include "TcpClient.h"
#include<GameScene.h>

/*
 *
 * TcpClient
 *
 */

TcpClient::TcpClient(
                                            const QHostAddress & server,
                                            quint16 port,
                                            QObject * parent,
                                            quint32 timeout
                                            ):
    QThread(parent),
    host(server),
    port(port),
    timeout(timeout),
    socket(nullptr),
    mode(TcpClient::None) {}

TcpClient::~TcpClient() {
    setMode(Exit);
    wait();
    if (socket) {
        delete socket;
    }
}


void TcpClient::setMode (Mode newMode) {
    QMutexLocker locker (& mutex);
    mode = newMode;
    
    if (!isRunning()) {
        start();
    } else {
        condition.wakeOne();
    }
}


void TcpClient::pushGameProperties(const GameProperties &option) {
    QMutexLocker locker ( &mutex);
    sendBuffer.enqueue(option);
}


void TcpClient::run() {
    Mode mode = getMode();
    bool waitCond;
    
    while (true) {
        waitCond = true;
        switch (mode) {
        case Exit: return;
        case None: break;
        case Connect: connect();
                                      waitCond = false;
                                      break;
        case Send: send();
                               waitCond = false;
                               break;
        case Listen: waitResponse();
        default:
            break;
        }
        mode = getMode(waitCond);
    }
}


void TcpClient::errorHandler(int errNo, const QString &message) {
    emit error(errNo, message);
    mutex.lock();
    mode = None;
    mutex.unlock();
}


void TcpClient::connect() {
    socket = new QTcpSocket();
    socket -> connectToHost(host, port);

    if (!(socket -> waitForConnected(timeout))) {
        errorHandler(socket -> error(), socket -> errorString());
        return;
    }

    if (!checkConnectionInfo()) {
        return;
    }

    mutex.lock();
    mode = Listen;
    mutex.unlock();

    emit connected();
}


bool TcpClient::waitForDataAvailable(
                                                                            quint64 size,
                                                                            quint32 maxTime,
                                                                            bool noBytesIsError
                                                                            ) {
    while ((quint64)socket -> bytesAvailable() < size) {
        if (!(socket -> waitForReadyRead(maxTime))) {
            if (noBytesIsError) {
                errorHandler(socket -> error(), socket -> errorString());
                socket -> disconnectFromHost();
            }
            return false;
        }
    }
    return true;
}


bool TcpClient::checkConnectionInfo() {
    static QByteArray block;
    block.clear();
    quint64 blockSize = 0;
    QDataStream blockStream(&block, QIODevice::ReadOnly);
    blockStream.setVersion(Net::DataStreamVersion);
    QDataStream in(socket);
    in.setVersion(Net::DataStreamVersion);

    if(!waitForDataAvailable(sizeof(quint64), timeout)) {
        return false;
    }
    in >> blockSize;

    if(!waitForDataAvailable(blockSize, timeout)) {
        return false;
    }

    block.resize(blockSize);
    in >> block;

    QString signature;
    quint16 version = 0;
    quint16 subversion = 0;
    quint16 id = 0;

    blockStream >> signature;
    blockStream >> version;
    blockStream >> subversion;
    blockStream >> id;

    emit idGoten (id);

    if (signature != QStringSignature ) {
        errorHandler(socket -> error(), socket -> errorString());
        socket -> disconnectFromHost();
        return false;
    } else {
        if (version > Net::ProtVersion || subversion > Net::ProtSubversion) {
            errorHandler(-1, "Server version is " + QString().number(version, 10) + "." + QString().number(subversion, 10));
            socket -> disconnectFromHost();
            return false;
        }
    }

    GameProperties udpPortOption;

    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(Net::DataStreamVersion);

    udpPortOption.setQuintType(GameProperties::UdpPort);

    udpPortOption.setFirstQInt(0);

    while ( !udpPortOption.getFirstQInt()) {
        udpPortOption.setFirstQInt(static_cast<GameScene*>(parent()) -> getUdpPort());
        usleep(3);
    }

    block.clear();
    out << (quint32) 0;
    out << udpPortOption;
    out.device() -> seek(0);
    out << (quint32) (block.size() - sizeof(quint32));

    socket -> write(block);
    socket -> waitForBytesWritten(10);

    return true;
}


void TcpClient::send() {
    if (socket -> state() != QAbstractSocket::ConnectedState) {
        emit error(-1, "Disconnected from the server");
        return;
    }

    QByteArray block;
    static GameProperties dataForSend;

    QDataStream request(&block, QIODevice::WriteOnly);
    request.setVersion(Net::DataStreamVersion);

    mutex.lock();
    for (int i = 0; i < sendBuffer.size(); ++i) {
        block.clear();

        dataForSend = sendBuffer.dequeue();
        request << (quint32) 0;
        request << dataForSend;
        request.device() -> seek(0);
        request << (quint32) (block.size() - sizeof(quint32));

        socket -> write(block);
        socket -> waitForBytesWritten(10);
    }
    mutex.unlock();

    if(!(socket -> waitForBytesWritten(timeout))) {
        errorHandler( socket -> error(), socket -> errorString());
        socket -> disconnectFromHost();
        return;
    }
    mutex.lock();
    mode = Listen;
    mutex.unlock();
}


void TcpClient::waitResponse() {
    QDataStream response (socket);
    response.setVersion(Net::DataStreamVersion);

    quint32 size = 0;
    while ((quint64) (socket -> bytesAvailable()) < sizeof(size)) {
        socket -> waitForReadyRead(50);
        if (QTcpSocket::ConnectedState != socket -> state()) {
            emit error (socket -> error(), "Disconnected from the server");
            return;
        }
    }

    response >> size;

    while (socket -> bytesAvailable() < size) {
        socket -> waitForReadyRead(50);
        if (QTcpSocket::ConnectedState != socket -> state()) {
            emit error (socket -> error(), "Disconnected from the server");
            return;
        }
    }

    NetDataContainer<GameProperties> * container = new NetDataContainer<GameProperties>();

    GameProperties responseData;
    response >> responseData;

    container -> setOption(responseData);
    emit newProperty(container);
}


TcpClient::Mode TcpClient::getMode(bool waitCondition) {
    QMutexLocker locker (&mutex);
    if (waitCondition) condition.wait(&mutex, timeout);
    return mode;
}


void TcpClient::start() {
    QThread::start();
}