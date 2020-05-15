#include <GraphicsView.h>
#include <Utils.h>
#include <QGLFormat>
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


void GraphicsView::onError( int errNo, QString msg )
{
  menuScene -> catchError( errNo, msg );

  setScene( menuScene );
  curentScene = Menu;

  SignalsSwitchTo( Menu );
  qDebug() << "no gameScene on error";
  deleteGameScene();
}


void GraphicsView::onConnect( const ServerAbout & connectionInfo )
{
  if ( gameScene != NULL )
  {
    deleteGameScene();
  };

  try
  {
  gameScene = new GameScene(
                                        parentApp,
                                        this,
                                        connectionInfo.address,
                                        connectionInfo.port,
                                        connectionInfo.data.getMapName()
                                       );
  }
  catch (Exception excp)
  {
    onError ( -1, excp.message );
    return;
  }
  catch (UdpClient::Exception excp)
  {
    onError( excp.errNo, excp.message );
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

