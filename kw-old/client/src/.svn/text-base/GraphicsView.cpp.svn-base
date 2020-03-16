/*
 *
 * Created on: 23.03.12
 *
 * GraphicsView.cpp
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Krepak Vitaly, Ivan Penkin MIPT
 * krepakvitaliy@gmail.com, grek.penkin@gmail.com
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
#include <commonLibs.h>
#include <qgraphicseffect.h>

GraphicsView::GraphicsView( QApplication * pApp, QWidget * parent ):
  QGraphicsView( parent ),
  parentApp( pApp )
{
  setWindowIcon(QIcon("./images/kolobok-wars.ico"));
  setWindowTitle ( tr( "Kolobok Wars" ) );

  setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAlwaysOff );


  QGLFormat * glFormat = new QGLFormat(QGL::DoubleBuffer | QGL::SampleBuffers );
  //glFormat -> setSwapInterval(0);
  QGLWidget * viewport = new QGLWidget( *glFormat );

  setViewport( viewport );
  setViewportUpdateMode ( QGraphicsView::FullViewportUpdate );

  setWindowState ( Qt::WindowActive | Qt::WindowFullScreen );
  setOptimizationFlags( QGraphicsView::DontAdjustForAntialiasing );
  setRenderHints ( QPainter::SmoothPixmapTransform );

  menuScene = new MainMenuScene ( parentApp, this );
  gameScene = NULL;
  setScene ( menuScene );
  curentScene = Menu;

  parentApp->setOverrideCursor
           (
            QCursor(QPixmap("./images/cursorMenu.png",0,0), 0, 0 )
           );
}

GraphicsView::~GraphicsView()
{
  delete menuScene;
  delete gameScene;
}


void GraphicsView::SignalsSwitchTo( Scene direction )
{
  if ( direction == Menu )
  {
    if ( gameScene != NULL )
    {
      disconnect( gameScene, SIGNAL( pause()), this, SLOT ( onPause() ));
      disconnect( gameScene, SIGNAL( error( int, QString )),
                  this,      SLOT ( onError( int, QString )) );
    }
    parentApp -> restoreOverrideCursor ();
  }
  else
  {
    connect( gameScene, SIGNAL( pause()), this, SLOT ( onPause()) );
    connect( gameScene, SIGNAL( error( int, QString )),
             this, SLOT ( onError( int, QString ) ));
    parentApp -> setOverrideCursor
                    (
                      QCursor(QPixmap("./images/cursorGame.png",0,0))
                     );
  }
};


void GraphicsView::onPause()
{
  menuScene -> pause();

  setScene( menuScene );
  curentScene = Menu;

  SignalsSwitchTo( Menu );
}

void GraphicsView::onResume()
{
  setScene( gameScene );
  curentScene = Game;

  SignalsSwitchTo( Game );
}


void GraphicsView::onError( int errno, QString msg )
{
  menuScene -> catchError( errno, msg );

  setScene( menuScene );
  curentScene = Menu;

  SignalsSwitchTo( Menu );
  deleteGameScene();
}


void GraphicsView::onConnect( const Net::ServerAbout & connectionInfo )
{
  if ( gameScene != NULL )
  {
    deleteGameScene();
  };

  try
  {
  gameScene = new GameWorld::GameScene(
                                        parentApp,
                                        this,
                                        connectionInfo.address,
                                        connectionInfo.port,
                                        connectionInfo.data.mapName
                                       );
  }
  catch (Exception excp)
  {
    onError ( -1, excp.message );
    return;
  }
  catch (Net::UdpClient::Exception excp)
  {
    onError( excp.errno, excp.message );
    return;
  }

  setScene( gameScene );
  curentScene = Game;

  SignalsSwitchTo( Game );
}


void GraphicsView::deleteGameScene()
{
  delete gameScene;
  gameScene = NULL;
}

void GraphicsView::wheelEvent( QWheelEvent * e )
{
  if ( curentScene == Menu )
  {
    QGraphicsView::wheelEvent( e );
  }
}

