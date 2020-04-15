#include <BroadcastReceiver.h>
#include <Serializable.h>
#include <Datagramms.h>


BroadcastReceiver::BroadcastReceiver(
                                                                                    QVector<ServerAbout> & srvs,
                                                                                    QWidget * parent
                                                                                    ):
    QUdpSocket((QObject * ) parent),
    servers(srvs) {
    if (!(bind(27030, QUdpSocket::ShareAddress))) {
        throw Exception(error(), errorString());
    }

    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}


void BroadcastReceiver::processPendingDatagramms() {

    while(hasPendingDatagrams()) {
        QByteArray data1;
        QDataStream response(data1);
        ServerAbout info;
        quint32 size;

        response.setVersion( Net::DataStreamVersion );

        data1.clear();
        data1.resize( pendingDatagramSize() );

        readDatagram(
                                      data1.data(),
                                      data1.size(),
                                      &(info.address),
                                      &(info.port)
                                    );

        response >> size;
        response >> info.data;
        info.port = info.data.getTcpPort();


        if(info.data.getSignature() != QStringSignature ||
              info.data.getVersion() != Net::ProtVersion ||
              info.data.getSubversion() != Net::ProtSubversion)
        {
            continue;
        }

        bool newSrv = true;
        foreach (ServerAbout about, servers) {
            if(info.data.getServerName() == about.data.getServerName() && info.address == about.address) {
                newSrv = false;
                break;
            }
        }

        if ( newSrv ) {
            servers.push_back( info );
            emit newServer( servers.count() - 1 );
        }
    }
}

bool BroadcastReceiver::serversIsEmpty() {
    if (servers.size() == 0)
        return true;
    return false;
}

BroadcastData BroadcastReceiver::getLastServerAboutInfo() {
    return servers[servers.size() - 1].data;
}

void BroadcastReceiver::makeItToRead() {
    emit readyRead();
}
