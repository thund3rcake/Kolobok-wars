/*
 *  Created on: 30.03.2012
 *
 * GameWorld.h
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Krepak Vitaly, MIPT
 * krepakvitaliy@gmail.com
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
#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include <QGraphicsView>
#include <QtGui>
#include <QtNetwork>
#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <Entity.h>
#include <GameWorldConsts.h>
#include <QWidget>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <Player.h>
#include <AIBot.h>
#include <Bullet.h>
#include <HUD.h>
#include <Map.h>
#include <TCPClient.h>
#include <UDPClient.h>

namespace GameWorld
{

class GameScene: public QGraphicsScene
{
  Q_OBJECT

  public:
    GameScene (
                QApplication * pApp,
                QGraphicsView * pView,
                const QHostAddress & address,
                quint16 port,
                const QString & mapName
                );

    virtual
    ~GameScene();

    virtual void keyPressEvent   ( QKeyEvent * event );
    virtual void keyReleaseEvent ( QKeyEvent * event );
    virtual void mousePressEvent       ( QGraphicsSceneMouseEvent * );
    virtual void mouseMoveEvent        ( QGraphicsSceneMouseEvent * );
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * );

    HUD & getHUD () { return *hud; };
    void setCharacterHeading ( QVector2D & );

    QPointF getSize ();
    quint16 getUdpPort(){ return udpClient -> getPort(); };

  private:
    GameScene ();
    GameScene ( const GameScene &rhs );
    GameScene& operator= ( const GameScene &rhs );

    void characterFire    ( QPointF );
    void updateHUD        ();

    struct KeysState
    {
      KeysState()
      {
        up   = false; down  = false;
        left = false; right = false;
      }

      bool up;
      bool down;
      bool left;
      bool right;
    };

    QApplication         * parentApp;
    QGraphicsView        * parentView;
    QTimer               * timer;
    QTimer               * sendTimer;
    QTime                * time;
    HUD                  * hud;
    QGraphicsProxyWidget * proxy;

    Net::TcpClient       * tcpClient;
    Net::UdpClient       * udpClient;

    Map *      map;
    QPointF    s_size; //prefix 's' means that this value belongs to scene coordinates
    Player     mainCharacter;
    QPointF    topLeft;
    QSizeF     desktopSize;
    KeysState  keyState;

    QLinkedList<Player*> players;
    QLinkedList<AIBot*> bots;
    QLinkedList<Bullet*> bullets;

    QHostAddress   server;
    quint16        port;

  public slots:
    void updatePlayerPos  ( NetDataContainer<Net::MovingObjectProperties> *);
    void updateBulletsPos ( NetDataContainer<Net::MovingObjectProperties> *);
    void catchError ( int, QString );
    void repaint();
    void characterSteer ();
    void setOwnId( quint16 id ){ mainCharacter.setId( id ); };

  signals:
    void pause ();
    void error ( int, QString );
    void keyPressed ();
};

} /* namespace GameWorld */

#endif /* GAME_SCENE_H_ */

