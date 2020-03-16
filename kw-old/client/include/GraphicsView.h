/*
 *
 * Created on: 23.03.12
 *
 * GraphicsView.h
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Ivan Penkin, MIPT
 * grek.penkin@gmail.com
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

#ifndef GRAPHICSVIEW_H_
#define GRAPHICSVIEW_H_

#include <QtGui>
#include <QGraphicsScene>
#include <GameScene.h>
#include <QApplication>
#include <QtOpenGL>
#include <MainMenu.h>
#include <HUD.h>

using namespace GameWorld;

class GraphicsView: public QGraphicsView
{
  Q_OBJECT

  public:
    GraphicsView ( QApplication * pApp, QWidget * parent = 0 );

    virtual
    ~GraphicsView ();

    QRectF viewRect() const;

  public slots:
    void onPause         ();
    void onResume        ();
    void onError         ( int, QString );
    void onConnect       ( const Net::ServerAbout & connectionInfo );
    void deleteGameScene ();

  protected:
    virtual void wheelEvent ( QWheelEvent * );

  private:
    GraphicsView ();
    GraphicsView ( const GraphicsView &rhs );
    GraphicsView& operator= ( const GraphicsView &rhs );

    enum Scene{ Menu, Game };
    Scene curentScene;

    void SignalsSwitchTo( Scene direction );

    MainMenuScene           * menuScene;
    GameWorld::GameScene    * gameScene;
    QApplication            * parentApp;
};

#endif /* GRAPHICSVIEW_H_ */
