#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<QGraphicsView>
#include<QtGui>
#include<QtNetwork>
#include<QWidget>
#include<QGraphicsProxyWidget>
#include<QGraphicsScene>
#include<QGraphicsItemAnimation>
#include<QTimeLine>
#include<Entity.h>
#include<Bullet.h>
#include<HUD.h>
#include<GameWorldConsts.h>
#include<Player.h>
#include<Map.h>
#include<TcpClient.h>
#include<UdpClient.h>


class GameScene: public QGraphicsScene {
    Q_OBJECT

public :
    GameScene(
            QApplication * pApp,
            QGraphicsView * pView,
            const QHostAddress & address,
            quint16 port,
            const QString & mapName
            );

    virtual ~GameScene();

    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * );
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * );
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * );

    HUD & getHUD() {
        return * hud;
    }

    void setCharacterHeading (QVector2D & );

    QPointF getSize();
    quint16 getUdpPort() {
        return udpClient -> getPort();
    }

private:
    GameScene ();
    GameScene(const GameScene & rhs);
    GameScene & operator = (const GameScene & rhs);

    void characterFire(QPointF);
    void updateHUD();

    struct KeysState {
        KeysState() {
            up = false;
            down = false;
            left = false;
            right = false;
        }
        bool up;
        bool down;
        bool left;
        bool right;
    };

    struct MouseState {
        MouseState() {
            mousePress = false;
        }
        bool mousePress;
    };

    QApplication * parentApp;
    QGraphicsView * parentView;
    QTimer * timer;
    QTimer * sendTimer;
    QTime * time;
    HUD * hud;
    QGraphicsProxyWidget * proxy;

    TcpClient * tcpClient;
    UdpClient * udpClient;

    Map * map;
    QPointF s_size;

    Player mainCharacter;
    QPointF topLeft;
    QSizeF desktopSize;
    KeysState keyState;
    MouseState mouse;

    QLinkedList<Player *> players;
    QLinkedList<Bullet *> bullets;

    QHostAddress server;
    quint16 port;

public slots:
    void updatePlayersPos (NetDataContainer<MovingObjectProperties> *);
    void updateBulletsPos (NetDataContainer<MovingObjectProperties> *);
    void catchError (int, QString);
    void repaint();
    void characterStreet();
    void setOwnId(quint16 id) {
        mainCharacter.setId(id);
    }

signals:
    void pause();
    void error(int, QString);
    void keyPressed();
};

#endif // GAMESCENE_H
