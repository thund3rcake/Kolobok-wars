#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include<QMutex>
#include<QWaitCondition>
#include<QObject>
#include<QThread>
#include<QtCore>
#include<QtNetwork/QTcpSocket>

#include<NetDataContainer.h>
#include<Datagramms.h>
#include<Versions.h>
#include<Utils.h>


class TcpClient : public QThread {
    Q_OBJECT

    enum Mode {
        None,
        Exit,
        Connect,
        Send,
        Listen
                            };

public:
    TcpClient(
                        const QHostAddress & server,
                        quint16 port,
                        quint32 timeout = 1000,
                        QObject * parent = 0
                        );
    virtual ~TcpClient();

private:
    TcpClient();
    TcpClient(const TcpClient & rhs);
    TcpClient & operator = (const TcpClient & rhs);

    Mode getMode (bool waitCondition = false);

    inline bool checkConnectionInfo();
    inline void connect();
    inline void errorHandler(int error, const QString & message);
    inline bool waitForDataAvailable(quint64 size, quint32 maxTime, bool noBytesIsError = true);
    inline void send();
    inline void waitResponse();

    QHostAddress host;
    quint16 port;
    quint32 timeout;

    QTcpSocket * socket;
    Mode mode;
    QMutex mutex;
    QWaitCondition condition;

    QQueue<GameProperties> sendBuffer;

public slots:
    void setMode(Mode mode);
    void pushGameProperties(const GameProperties & option);
    
private slots:
    virtual void start();
protected:
    virtual void run();

signals:
    void connected();
    void idGoten(quint16);
    void newProperty(NetDataContainer<GameProperties> * option);
    void error(int error, QString message);
};


#endif // TCPCLIENT_H