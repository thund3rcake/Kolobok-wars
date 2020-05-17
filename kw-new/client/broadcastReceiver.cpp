#include <BroadcastReceiver.h>
#include<Serializable.h>


BroadcastReceiver::BroadcastReceiver(
                                                                                    QVector<ServerAbout> & srvs,
                                                                                    QWidget * parent,
                                                                                    int port
                                                                                    ):
    QUdpSocket((QObject * ) parent),
    servers(srvs) {
    if (!bind(port, QUdpSocket::ShareAddress)) {
        throw Exception(error(), errorString());
    }

    connect(this, &QUdpSocket::readyRead,
            this, &BroadcastReceiver::processPendingDatagramms);

}


void BroadcastReceiver::processPendingDatagramms() {

    while (hasPendingDatagrams()) {
        QByteArray data1;
        QDataStream response(&data1, QIODevice::OpenModeFlag::ReadOnly); //BroadcastSender and BroadcastReceiver must call the same constructor
        ServerAbout info;
        quint32 size;

        //When DataStream versions in BroadcastSender and BroadcastReceiver are different
        //it doesn't work
        response.setVersion( Net::DataStreamVersion );

        data1.clear();

        data1.resize(int(pendingDatagramSize()));

        readDatagram(data1.data(), data1.size(), &(info.address), &(info.port));

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
            servers.push_back( info ); //Copy constructor for BroadcastData must be implemented
            emit newServer( servers.count() - 1 );
        }
    }
}
