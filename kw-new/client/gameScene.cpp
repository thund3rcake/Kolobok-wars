#include <GameScene.h>
#include<Utils.h>
#include<QDebug>
#include<GraphicsView.h>

GameScene::GameScene(
                                                        QApplication *pApp,
                                                        QGraphicsView *pView,
                                                        const QHostAddress &address,
                                                        quint16 port,
                                                        const QString &mapName
                                                        ):
    parentApp(pApp),
    parentView(pView),
    hud(new HUD),
    proxy(addWidget(hud)),
    topLeft(QPointF(0, 0)),
    desktopSize(QSizeF (getDesktopSize().x(), getDesktopSize().y())),
    server(address),
    port(port) {

    map = new Map("./maps/" + mapName + "/" + mapName + ".xml");

    proxy -> setZValue(100);

    QObject::connect(map, SIGNAL(error(int,QString)), this, SLOT(catchError(int,QString)));

    udpClient = new UdpClient(server, port, this);

    QObject::connect(udpClient, SIGNAL(error(int,QString)), this, SLOT(catchError(int, QString)));
    QObject::connect(udpClient, SIGNAL(newObjectProperties(NetDataContainer<MovingObjectProperties>*)),
                     this, SLOT(updatePlayersPos(NetDataContainer<MovingObjectProperties>*)));
    udpClient -> start();


    tcpClient = new TcpClient(server, port, this);

    QObject::connect(tcpClient, SIGNAL(error(int,QString)), this, SLOT(catchError(int,QString)));
    QObject::connect(tcpClient, SIGNAL(idGoten(quint16)), this, SLOT(setOwnId(quint16)));

    tcpClient -> setMode(TcpClient::Connect);

    qDebug() << port;

    s_size = map -> getSize();
    s_size = (s_size * scale_x_100()) / 100;

    setSceneRect(
                                -desktopSize.rwidth() / 2,
                                -desktopSize.rheight() / 2,
                                s_size.x() + desktopSize.rwidth(),
                                s_size.y() + desktopSize.rheight()
                                );

    setItemIndexMethod(QGraphicsScene::NoIndex);

    setBackgroundBrush(QColor(80, 80, 80));

/* Draw the Map */
  QPolygonF * backPol = new QPolygonF;
  *backPol << QPointF(0,0) << QPointF (0,s_size.y())
           << s_size       << QPointF (s_size.x(),0);
  QGraphicsPolygonItem * back = new QGraphicsPolygonItem(*backPol);
  back->setBrush
            (
             QPixmap( "./maps/" + mapName + "/" + map->getBackgroundPath () )
            );
  back->setPen ( Qt::NoPen );
  addItem(back);
  foreach ( PolygonEntity* entity, map->getPolygons() )
  {
    addItem ( entity );
  }
  /* Draw the Map */

  /* Draw the Player */ //TODO: respawn place
    mainCharacter.setPosition (
                          QPoint( desktopSize.rwidth()/2,
                                  desktopSize.rheight()/2 )
                         );
    mainCharacter.setIntent ( QVector2D(0,0) );
    mainCharacter.blockSignals(true);
    addItem(&mainCharacter);
    /* Draw the Player */

    /* Motion and Animation */
    timer = new QTimer( this );
    connect ( timer, SIGNAL( timeout() ),
              this,  SLOT  ( repaint() ) );
    timer -> setInterval( consts::sceneUpdateInterval );
    timer -> start();

    sendTimer = new QTimer( this );
    connect ( sendTimer, SIGNAL( timeout() ),
              this,      SLOT  ( characterSteer() ), Qt::DirectConnection );
    sendTimer -> setInterval( consts::sendTimerInterval );
    sendTimer -> start();
    /* Motion and Animation */
    time = new QTime();
    time -> start();
}

GameScene::~GameScene() {
    delete timer;
    delete hud;
    qDebug() << "GameScene::~GameScene(): Deleted";
}

QPointF GameScene::getSize() {
    return s_size;
}

void GameScene::repaint() {
    /* Update Player's position and centering */
      mainCharacter.setPos (mainCharacter.getPosition());
      parentView -> centerOn( &mainCharacter );
      foreach ( Player * player, players )
      {
        player -> setPos ( player -> getPosition() );
      }
      /* Update Player's position and centering */

      /* Update HUD */
      updateHUD();
      /* Update HUD */
}

/* World's behavior */

void GameScene::characterStreet() {
    static int elapsed = 0;
    QVector2D v(0, 0);
    
    if (keyState.up != keyState.down) {
        if (keyState.up) {
            v.setY(-1);
        }
        if(keyState.down) {
            v.setY(1);
        }
    }
    
    if(keyState.left != keyState.right) {
        if(keyState.left) {
            v.setX(-1);
        }
        if(keyState.right) {
            v.setX(1);
        }
    }
    
    v.normalize();
    
    mainCharacter.setIntent(v);
    
    MovingObjectProperties playerProp;
    playerProp.setHp(100);
    playerProp.setId(mainCharacter.getId());
    playerProp.setHead(mainCharacter.getHead());
    playerProp.setTeam(MovingObjectProperties::Red);
    playerProp.setType(MovingObjectProperties::Player);
//    playerProp.setIntent(mainCharacter.getIntention());
    playerProp.setPosition(mainCharacter.getPosition() * 100 / scale_x_100());
    playerProp.setTimestamp(time -> elapsed() - elapsed);
    playerProp.getWeapon().setType(Weapon::Blaster);
    if (mouse.mousePress == true) {
        playerProp.getWeapon().setState(Weapon::Fire);
    } else {
        playerProp.getWeapon().setState(Weapon::NoFire);
    }
    playerProp.getWeapon().setTarget(QPointF(0, 0));
    playerProp.getWeapon().setMasterId(mainCharacter.getId());
    
    udpClient -> sendNewObjectProperties(playerProp);
    elapsed = time -> elapsed();
    mouse.mousePress = false;
}

void GameScene::updatePlayersPos(NetDataContainer<MovingObjectProperties> * container) {
    quint16 inpId = container -> getOption().getId();
    
    if(inpId == mainCharacter.getId()) {
        mainCharacter.setPosition(container ->getOption().getPosition() * scale_x_100() / 100);
        topLeft = QPointF(mainCharacter.getPosition().x() - desktopSize.rwidth() / 2 + scaledPlayerSize() / 2,
                                                mainCharacter.getPosition().y() - desktopSize.rheight() / 2 + scaledPlayerSize() / 2);
    } else {
        foreach (Player * player, players) {
            if (player -> getId() == inpId) {
                player -> setPosition(container -> getOption().getPosition() * scale_x_100() / 100);
                player -> setHead(container -> getOption().getHead());
                inpId = 0;
                break;
            }
        }
        
        if (inpId != 0) {
            Player * player = new Player;
            player -> setPosition(container -> getOption().getPosition() * scale_x_100() / 100);
            player -> setHead(container -> getOption().getHead());
            player -> setId (inpId);
            players.append(player);
            addItem(player);
            qDebug() << "Player" << player -> getId() << "Added";
        }
    }
    
    container -> setReaden();
    delete container;
}

void GameScene::updateBulletsPos ( NetDataContainer<MovingObjectProperties> * prop )
{
    if ( prop -> getOption().getType() == MovingObjectProperties::Bullet ) {
        qDebug() << "GameScene::updateBulletsPos:" << "Bullet was received";
    return;
    }
}

void GameScene::characterFire ( QPointF targAbs )
{
  hud->updConstFireTarget(targAbs);
  hud->updateConsole (
                       &mainCharacter,
                       topLeft,
                       map->isDotAvailable ( mainCharacter.getPosition().toPoint() )
                     );

  QVector2D targ ( targAbs - mainCharacter.getPosition() );
  QPointF position (mainCharacter.getPosition() + scaledPlayerSize()*mainCharacter.getHead().toPointF());
}

void GameScene::updateHUD ()
{
  hud->move( topLeft.rx(), topLeft.ry() );
}

void GameScene::catchError ( int errNo, QString errorMessage )
{
  emit error ( errNo, errorMessage );
}

void GameScene::setCharacterHeading ( QVector2D & vector )
{
  mainCharacter.setHead(vector);
}
void GameScene::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {
    if ( event->button() == Qt::LeftButton ) {
//        characterFire( event->scenePos() );
        mouse.mousePress = true;
    }
}

void GameScene::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event ) {
    if ( event->button() == Qt::LeftButton ) {}
//    characterFire( event->scenePos() );
}

void GameScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
  QVector2D vector;
  vector.setX( event->scenePos().rx() - mainCharacter.getPosition().x() );
  vector.setY( event->scenePos().ry() - mainCharacter.getPosition().y() );
  mainCharacter.setHead (vector);
  mainCharacter.update(mainCharacter.rect());
}

void GameScene::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
        case Qt::Key_Escape: emit pause(); break;

        case Qt::Key_W: keyState.up = true; break;

        case Qt::Key_Up: keyState.up = true; break;

        case Qt::Key_S: keyState.down = true; break;

        case Qt::Key_Down: keyState.down = true; break;

        case Qt::Key_A: keyState.left  = true; break;

        case Qt::Key_Left: keyState.left  = true; break;

        case Qt::Key_D: keyState.right = true; break;

        case Qt::Key_Right: keyState.right = true; break;
    }
    hud->keyPressEvent(event);
}

void GameScene::keyReleaseEvent ( QKeyEvent * event )
{
    switch (event->key()) {
        case Qt::Key_Escape: emit pause(); break;

        case Qt::Key_W: keyState.up = false; break;

        case Qt::Key_Up: keyState.up = false; break;

        case Qt::Key_S: keyState.down = false; break;

        case Qt::Key_Down: keyState.down = false; break;

        case Qt::Key_A: keyState.left  = false; break;

        case Qt::Key_Left: keyState.left  = false; break;

        case Qt::Key_D: keyState.right = false; break;

        case Qt::Key_Right: keyState.right = false; break;
    }
    hud->keyPressEvent(event);
}