/*
 *  Created on: 15.04.2012
 *
 * GameWorld.cpp
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Ivan Penkin, Krepak Vitaly, MIPT
 * grek.penkin@gmail.com, krepakvitaliy@gmail.com
 *
 * kolobok-wars-client is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kolobok-wars-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kolobok-wars-client if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 */

#include <GraphicsView.h>
#include <GameScene.h>
#include <commonLibs.h>
#include <QDebug>
#include <AIBot.h>
#include <QtGlobal>

using namespace GameWorld;

GameScene::GameScene (
                       QApplication * pApp,
                       QGraphicsView * pView,
                       const QHostAddress & address,
                       quint16 srvPort,
                       const QString & mapName
                      ):
  parentApp (pApp),
  parentView (pView),
  hud(new HUD),
  proxy( addWidget( hud )),
  topLeft( QPointF( 0, 0 )),
  desktopSize( QSizeF( getDesktopSize().x(), getDesktopSize().y() )),
  server( address ),
  port( srvPort )
{
  map = new Map("./maps/" + mapName + "/" + mapName + ".xml");

  proxy -> setZValue( 100 );

  /* error slots connection */
  QObject::connect ( map,   SIGNAL (error(int, QString)),
                     this,  SLOT (catchError(int, QString)) );
  /* error slots connection */

  udpClient = new Net::UdpClient( server, port, this );

  QObject::connect ( udpClient, SIGNAL (error(int, QString)),
                     this,      SLOT (catchError(int, QString)) );
  QObject::connect ( udpClient, SIGNAL(newObjectProperties(NetDataContainer<Net::MovingObjectProperties> *)),
                     this,      SLOT  (updatePlayerPos(NetDataContainer<Net::MovingObjectProperties> *)) );

  /* AIBot connection: */
  //QObject::connect ( udpClient, SIGNAL(newObjectProperties(NetDataContainer<Net::MovingObjectProperties> *)),
  //                   this,      SLOT  (MoveAIBot(NetDataContainer<Net::MovingObjectProperties> *)) );

  udpClient -> start();

  tcpClient = new Net::TcpClient( server, port, this );

  QObject::connect ( tcpClient, SIGNAL (error(int, QString)),
                     this,      SLOT (catchError(int, QString)) );

  QObject::connect ( tcpClient,      SIGNAL( idGoten( quint16 )),
                     this, SLOT( setOwnId( quint16 )) );

  tcpClient -> setMode( Net::TcpClient::Connect );

  qDebug() << port;

  /* Setup GameScene's settings */
  s_size = map -> getSize();

  s_size = ( s_size * scale_x_100() ) / 100;

  setSceneRect (
                -desktopSize.rwidth()/2,
                -desktopSize.rheight()/2,
                s_size.x() + desktopSize.rwidth(),
                s_size.y() + desktopSize.rheight()
               );

  setItemIndexMethod( QGraphicsScene::NoIndex );

  setBackgroundBrush ( QColor(80,80,80) );
  /* Setup GameScene's settings */

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
  connect (sendTimer, SIGNAL( timeout() ),
            this,      SLOT  ( characterSteer() ), Qt::DirectConnection );
  /* AIBot movement */
  connect (sendTimer, SIGNAL( timeout() ),
            this,      SLOT  ( botSteer() ), Qt::DirectConnection );
  sendTimer -> setInterval( consts::sendTimerInterval );
  sendTimer -> start();
  /* Motion and Animation */
  time = new QTime();
  time -> start();
}

GameScene::~GameScene()
{
  delete timer;
  delete hud;
  qDebug() << "GameScene::~GameScene(): deleted";
}

QPointF GameScene::getSize ()
{
  return s_size;
}

void GameScene::repaint()
{
//  static int elapsed = 0;

  /* Update Player's position and centering */
  mainCharacter.setPos (mainCharacter.getPosition());
  parentView -> centerOn( &mainCharacter );
  foreach ( Player * player, players )
  {
    player -> setPos ( player -> getPosition() );
  }
  /* Update bots */
  foreach (AIBot  * bot, bots)
  {
    bot -> setPos ( bot -> getPosition() );
  }
  /* Update Player's position and centering */

  /* Update HUD */
  updateHUD();
  /* Update HUD */
}

/* AIBot MOVEMENT */
//void GameScene::moveAIBot(NetDataContainer<Net::MovingObjectProperties> *) {}

void GameScene::botSteer() {}


/* World's behavior */
void GameScene::characterSteer()
{
  static int elapsed = 0;
//  qDebug() << "Elapsed" << time -> elapsed() - elapsed;
  QVector2D v( 0, 0 );

  if ( keyState.up != keyState.down )
  {
    if ( keyState.up   ) v.setY( -1 );
    if ( keyState.down ) v.setY(  1 );
  }

  if ( keyState.left != keyState.right )
  {
    if ( keyState.left  ) v.setX( -1 );
    if ( keyState.right ) v.setX(  1 );
  }

  v.normalize();

  mainCharacter.setIntent ( v );

  Net::MovingObjectProperties playerProp;
  playerProp.hp        = 100;                              //TODO: implement getHP
  playerProp.id        = mainCharacter.getId();
  playerProp.head      = mainCharacter.getHead();
  playerProp.team      = Net::MovingObjectProperties::Red; //TODO: implement method getTeam
  playerProp.type      = Net::MovingObjectProperties::Player;
  playerProp.intent    = mainCharacter.getIntention();
  playerProp.position  = ( mainCharacter.getPosition()*100/scale_x_100() );
  playerProp.timestamp = time -> elapsed() - elapsed;
  playerProp.weapon.type     = Weapon::Blaster;
  playerProp.weapon.state    = Weapon::NoFire;
  playerProp.weapon.target   = QPointF(0,0);
  playerProp.weapon.masterId = mainCharacter.getId();

  udpClient->sendNewObjectPropertie(playerProp);
  elapsed = time -> elapsed();
}

void GameScene::updateBulletsPos ( NetDataContainer<Net::MovingObjectProperties> * prop )
{
  if ( prop -> getOption().type == Net::MovingObjectProperties::Bullet )
  {
    qDebug() << "GameScene::updateBulletsPos:" << "Bullet was received";
    return;
  }
}

void GameScene::updatePlayerPos ( NetDataContainer<Net::MovingObjectProperties> * container )
{
  quint16 inpId = container -> getOption().id;

  if ( inpId == mainCharacter.getId() )
  {
    mainCharacter.setPosition ( container -> getOption().position*scale_x_100()/100 );
    topLeft = QPointF(mainCharacter.getPosition().x() - desktopSize.rwidth() /2 + scaledPlayerSize()/2,
                      mainCharacter.getPosition().y() - desktopSize.rheight()/2 + scaledPlayerSize()/2);
  }
  else
  {
    foreach ( Player * player, players )
    {
      if ( player -> getId() == inpId )
      {
        player -> setPosition  ( container -> getOption().position*scale_x_100()/100 );
        player -> setHead      ( container -> getOption().head );
//        player -> setTimeStep  ( container -> getOption().timestamp );
        inpId = 0;
        break;
      }
    }

    if ( inpId != 0 )
    {
      // DETERMINE IF BOT OR PLAYER
      if(container->getOption().type == Net::MovingObjectProperties::AIBot) {
          AIBot * bot = new AIBot;
          bot -> setPosition ( container -> getOption().position*scale_x_100()/100 );
          bot -> setHead ( container -> getOption().head );
          bot -> setId( inpId );
          bots.append(bot);
          addItem (bot);
          qDebug() << "Bot" << bot -> getId() << " Added;";
      } else if (container->getOption().type == Net::MovingObjectProperties::Player) {
          Player * player = new Player;
          player -> setPosition ( container -> getOption().position*scale_x_100()/100 );
          player -> setHead ( container -> getOption().head );
          player -> setId( inpId );
          players.append(player);
          addItem ( player );
          qDebug() << "Player" << player -> getId() << " Added;";
      }

    }
  }

  container -> setReaden();
  delete container;
}
/* World's behavior */

void GameScene::updateHUD ()
{
  hud->move( topLeft.rx(), topLeft.ry() );
}

void GameScene::catchError ( int errno, QString errorMessage )
{
  emit error ( errno, errorMessage );
}

void GameScene::setCharacterHeading ( QVector2D & vector )
{
  mainCharacter.setHead(vector);
}
void GameScene::characterFire ( QPointF targAbs )
{
  hud->updConsFireTargt(targAbs);
  hud->updateConsole (
                       &mainCharacter,
                       topLeft,
                       map->isDotAvailable ( mainCharacter.getPosition().toPoint() )
                     );

  QVector2D targ ( targAbs - mainCharacter.getPosition() );
  QPointF position (mainCharacter.getPosition() + scaledPlayerSize()*mainCharacter.getHead().toPointF());

  Net::MovingObjectProperties bulletProp;
  bulletProp.hp        = 0;
  bulletProp.id        = 0;
  bulletProp.head      = QVector2D(0,0);
  bulletProp.team      = Net::MovingObjectProperties::Red; //TODO: implement method getTeam
  bulletProp.type      = Net::MovingObjectProperties::Bullet;
  bulletProp.intent    = QVector2D(0,0);;
  bulletProp.position  = ( position*100/scale_x_100() ).toPoint();
  bulletProp.timestamp = 0;
  bulletProp.weapon.type     = Weapon::Blaster;
  bulletProp.weapon.state    = Weapon::Fire;
  bulletProp.weapon.target   = targAbs*100/scale_x_100();
  bulletProp.weapon.masterId = mainCharacter.getId();

  udpClient->sendNewObjectPropertie(bulletProp);
}

void GameScene::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
  if ( event->button() == Qt::LeftButton )
    characterFire( event->scenePos() );
}

void GameScene::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )
{
  if ( event->button() == Qt::LeftButton )
    characterFire( event->scenePos() );
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
  switch (event->key())
  {
    case Qt::Key_Escape:  emit pause(); break;

    case Qt::Key_W:       keyState.up    = true; break;

    case Qt::Key_S:       keyState.down  = true; break;

    case Qt::Key_A:       keyState.left  = true; break;

    case Qt::Key_D:       keyState.right = true; break;
  }
  hud->keyPressEvent(event);
}

void GameScene::keyReleaseEvent ( QKeyEvent * event )
{
  switch (event->key())
  {
    case Qt::Key_W:       keyState.up    = false; break;

    case Qt::Key_S:       keyState.down  = false; break;

    case Qt::Key_A:       keyState.left  = false; break;

    case Qt::Key_D:       keyState.right = false; break;
  }
  hud->keyReleaseEvent(event);
}
