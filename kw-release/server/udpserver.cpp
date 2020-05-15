#include "udpserver.h"
#include "servertools.h"
#include "Versions.h"

UdpServer::UdpServer(quint16 port, QObject *parent):
    QThread(parent),
    port(port),
    socket(NULL),
    toQuit(false) {}

UdpServer::~UdpServer() {
    incomingMutex.lock();
    outgoingMutex.lock();
    toQuit = true;
    outgoingMutex.unlock();
    incomingMutex.unlock();

    wait();
    if (socket)
        delete socket;
}


//run() gets from outgoing queue, puts in incoming queue
void UdpServer::run() {

    if (!socket) {
        socket = new QUdpSocket;
    }

    if (!(socket->bind(port, QUdpSocket::ShareAddress))) {
        emit error(socket->error(), socket->errorString());
        return;
    }

    quitMutex.lock();

    while (!toQuit) {

        quitMutex.unlock();

        static QByteArray block;
        static Packet     packetBufer;

        /* sending */
        outgoingMutex.lock();


        if (!outgoing.empty()) {
            packetBufer = outgoing.dequeue();
            outgoingMutex.unlock();

            if (packetBufer.port == 0) {
                quitMutex.lock();
                continue;
            }

            /* timestamp */
            packetBufer.properties.setTimestamp(
                        static_cast<ServerTools *>( parent() ) -> getCurentTime()
                        );
            /* timestamp */

            block.clear();

            QDataStream request(&block, QIODevice::OpenModeFlag::WriteOnly);
            //Use the same QDataStream constructor in client

            request.setVersion( Net::DataStreamVersion );
            //Use the same version in client

            request << (quint32)0;
            request << packetBufer.properties;
            request.device() -> seek(0);
            request << (quint32)(block.size() - sizeof(quint32));

            socket->writeDatagram(block.data(), block.size(), packetBufer.address, packetBufer.port);
        } else {
            outgoingMutex.unlock();
        }
        /* sending */

        /* receiving */
        if (socket->hasPendingDatagrams()) {

            static quint16 clientPort;
            static quint32 size;

            QDataStream response(&block, QIODevice::OpenModeFlag::ReadOnly);
            //Use the same QDataStream constructor in client

            response.setVersion( Net::DataStreamVersion );
            //Use the same version in client

            block.clear();
            block.resize(socket->pendingDatagramSize());

            socket->readDatagram(block.data(), block.size(), &(packetBufer).address, &clientPort);

            response >> size;
            response >> packetBufer.properties;

            incomingMutex.lock();
            incoming.enqueue(packetBufer);
            incomingMutex.unlock();

            emit newPacket();
        }
        /* receiving */

        usleep(5); // ??
        quitMutex.lock();
    }
    quitMutex.unlock();
}

//puts in outgoing queue
void UdpServer::sendPacket(const Packet &packet) {
  outgoingMutex.lock();
  outgoing.enqueue(packet);
  outgoingMutex.unlock();
}

//gets from incoming queue
const UdpServer::Packet UdpServer::getPacket(bool &result) {
  if (incoming.isEmpty()) {
    result = false;
    return Packet();
  }

  QMutexLocker locker( &incomingMutex );
  result = true;
  return incoming.dequeue();
}
