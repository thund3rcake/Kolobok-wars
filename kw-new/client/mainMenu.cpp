#include <MainMenu.h>
#include <GraphicsView.h>

MainMenuScene::MainMenuScene( QApplication * pApp, QGraphicsView * pView ):
  parentApp( pApp ),
  parentView( pView )
{
  setParent( pView );

  size = new QPoint( getDesktopSize() );

  setSceneRect( 0, 0, (size -> x()) - 2, (size -> y()) - 2 );
  QPixmap bg;

  if (
        (double)(size -> x())/(size -> y()) > 1.6 &&
        (double)(size -> x())/(size -> y()) < 2
      )
    bg.load( "./images/bg-16:9.png" );
  else
    bg.load( "./images/bg-4:3.png" );

  setBackgroundBrush( bg.scaled( (size -> x()) - 2, (size -> y()) - 2 ));

  resume         = new MainMenuButton( "Resume" );
  disconnect     = new MainMenuButton( "Disconnect" );
  startServer    = new MainMenuButton( "" );
  findBtn        = new MainMenuButton( "Find server" );
  optionsBtn     = new MainMenuButton( "Options" );
  quitBtn        = new MainMenuButton( "Quit" );

  canvas = new MainMenuCanvas( pApp, (size -> x()) - 2, (size -> y()) - 2 );
  proxy  = addWidget( canvas );
  proxy -> setZValue( 1000 );

  canvas -> addWidget( resume );
  canvas -> addWidget( disconnect );
  canvas -> addWidget( startServer );
  canvas -> addWidget( findBtn );
  canvas -> addWidget( optionsBtn );
  canvas -> addWidget( quitBtn );

  resume       -> hide();
  disconnect   -> hide();
  //startServer  -> hide();

  findW    = new FindWindow( canvas );
  optionsW = new OptionsWindow( canvas );
  quitW    = new QuitWindow( canvas );
  errorW   = new ErrorWindow( canvas );

  QWidget::connect( resume,     SIGNAL( clicked() ),
                    parentView, SLOT( onResume() ));
  QWidget::connect( disconnect, SIGNAL( clicked() ),
                    this,       SLOT( onDisconnect() ));

  QWidget::connect( findBtn,    SIGNAL( clicked() ),
                    findW,      SLOT( show() ));
  QWidget::connect( optionsBtn, SIGNAL( clicked() ),
                    optionsW,   SLOT( show() ));
  QWidget::connect( quitBtn,    SIGNAL( clicked() ),
                    this,       SLOT( onQuit() ));
  QWidget::connect( this,       SIGNAL( escaped() ),
                    this,       SLOT( onQuit() ));

  QWidget::connect( quitW,      SIGNAL( closed() ),
                    this,       SLOT( cancelQuit() ));

  QWidget::connect( findW,      SIGNAL( error( int, QString )),
                    this,       SLOT( catchError( int, QString )) );
  QWidget::connect( findW,      SIGNAL( startGame( const ServerAbout & )),
                    parentView, SLOT( onConnect( const ServerAbout & )) );
}

MainMenuScene::~MainMenuScene()
{



    delete disconnect;
  delete resume;
  delete findBtn;
  delete optionsBtn;
  delete quitBtn;

  delete findW;
  delete optionsW;
  delete quitW;
    delete errorW;

    delete canvas;

    delete size;

}

void MainMenuScene::keyPressEvent ( QKeyEvent * event )
{
  if ( event->key() == Qt::Key_Escape )
  {
    emit escaped();
  }
}


void MainMenuScene::onQuit()
{
  findW    -> hide();
  optionsW -> hide();

  quitW    -> show();

  resume     -> deactivate();
  disconnect -> deactivate();
  findBtn    -> deactivate();
  optionsBtn -> deactivate();
  quitBtn    -> deactivate();
}

void MainMenuScene::cancelQuit()
{
  resume     -> activate();
  disconnect -> activate();
  findBtn    -> activate();
  optionsBtn -> activate();
  quitBtn    -> activate();
}

void MainMenuScene::pause()
{
  resume     -> show();
  disconnect -> show();
}

void MainMenuScene::catchError( int, const QString & msg )
{
  findW    -> hide();
  optionsW -> hide();

  errorW -> setMessage( msg );
  errorW -> show();

  resume     -> deactivate();
  disconnect -> deactivate();
//  findBtn    -> deactivate();
//  optionsBtn -> deactivate();
//  quitBtn    -> deactivate();
}

void MainMenuScene::onDisconnect()
{
  resume     -> hide();
  disconnect -> hide();

  static_cast<GraphicsView*>( parentView ) -> deleteGameScene();
}