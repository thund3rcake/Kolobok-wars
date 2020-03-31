//#include "TcpClient.h"

///*
// *
// * TcpClient
// *
// */

//TcpClient::TcpClient(
//                                            const QHostAddress & server,
//                                            quint16 port,
//                                            quint32 timeout,
//                                            QObject * parent
//                                            ):
//    QThread(parent),
//    host(server),
//    port(port),
//    timeout(timeout),
//    socket(nullptr)
///*    mode(TcpClient::None)*/ {}

//TcpClient::~TcpClient() {
//    setMode(Exit);
////    QWaitCondition::wait();
//    if (socket) {
//        delete socket;
//    }
//}

//void TcpClient::setMode (Mode newMode) {
//    QMutexLocker locker (& mutex);
//    mode = newMode;
    
////    if (!isRunning()) {
////        start();
////    } else {
//        condition.wakeOne();
////    }
//}

//void TcpClient::pushGameProperties(const GameProperties &option) {
//    QMutexLocker locker ( &mutex);
//    sendBuffer.enqueue(option);
//}

//void TcpClient::run() {
//    Mode mode = getMode();
//    bool waitCond;
    
//    while (true) {
//        waitCond = true;
//        switch (mode) {
//        case Exit: return;
//        case None: break;
//        case Connect: connect();
//                                      waitCond = false;
//                                      break;
//        case Send: send();
//                               waitCond = false;
//                               break;
//        case Listen: listen();
//        default:
//            break;
//        }
//        mode = getMode(waitCond);
//    }
//}

//void TcpClient::errorHandler(int errNo, const QString &message) {
//    emit error(errNo, message);
    
//}
