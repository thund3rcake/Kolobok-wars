#include <DerivedWindows.h>
#include <Utils.h>


FindWindow::FindWindow( QWidget * parent ):
  Window( parent )
{
  setWindowTitle( "Find server" );

  QVBoxLayout * mainLayout = new QVBoxLayout;
  addLayout( mainLayout );

  findType = new QTabWidget( this );
  findType -> setStyleSheet( WindowStyle::TabBar );

  mainLayout -> addWidget( findType );
  mainLayout -> setMargin( 5 );

  lan = new LanTab( this );
  fav = new FavoriteTab( this );

  findType -> addTab( lan, "Lan" );
  findType -> addTab( fav, "Favorites" );

  QWidget::connect( lan, SIGNAL( error( int, QString)),
                    this, SLOT( catchError( int, QString )) );

  QWidget::connect( lan, SIGNAL( startGame( const ServerAbout & )),
                    this, SLOT( onStartGame( const ServerAbout & )) );
}

FindWindow::~FindWindow()
{
  delete findType;

  delete lan;
  delete fav;
}


void FindWindow::onStartGame( const ServerAbout & connectionInfo )
{
  emit startGame( connectionInfo );
};

void FindWindow::catchError( int errNo, QString msg )
{
  emit error( errNo, msg );
};


OptionsWindow::OptionsWindow( QWidget * parent ):
  Window( parent )
{
  setWindowTitle( "Options" );
}



QuitWindow::QuitWindow( QWidget * parent ):
  Window( parent )
{
  setWindowTitle( "Quit game" );

  setMinimumSize( 300, 100 );
  setMaximumSize( 300, 100 );

  QPoint wPosition = getDesktopSize();
  wPosition += QPoint( -300, -100 );
  wPosition /= 2;

  move( wPosition );

  QLabel * question = new QLabel ( "Are you shure?" );
  question -> setStyleSheet( WindowStyle::DialogWindowFontColor );

  QPushButton * Yes = new QPushButton( "Yes" );
  QPushButton * No  = new QPushButton( "No" );

  Yes -> setStyleSheet( WindowStyle::PushButton );
  No  -> setStyleSheet( WindowStyle::PushButton );

  QWidget::connect( Yes,    SIGNAL( clicked() ),
                    parent, SLOT(exit() ));
  QWidget::connect( No,     SIGNAL( clicked() ),
                    this,   SLOT( close() ));

  QVBoxLayout * VLayout = new QVBoxLayout;
  QHBoxLayout * H1Layout = new QHBoxLayout;
  QHBoxLayout * H2Layout = new QHBoxLayout;

  H1Layout -> addStretch();
  H1Layout -> addWidget( question );
  H1Layout -> addStretch();

  H2Layout -> addStretch();
  H2Layout -> addWidget( Yes );
  H2Layout -> addWidget( No );
  H2Layout -> addStretch();

  VLayout -> addStretch();
  VLayout -> addLayout( H1Layout );
  VLayout -> addLayout( H2Layout );
  VLayout -> addStretch();

  addLayout( VLayout );
}

ErrorWindow::ErrorWindow( QWidget * parent ):
  Window( parent )
{
  setWindowTitle( "Error" );

  setMinimumSize( 300, 100 );
  setMaximumSize( 300, 100 );

  QPoint wPosition = getDesktopSize();
  wPosition += QPoint( -300, -100 );
  wPosition /= 2;

  move( wPosition );

  message = new QLabel;
  message -> setStyleSheet( WindowStyle::DialogWindowFontColor );

  QPushButton * Ok = new QPushButton( "Ok" );

  Ok -> setStyleSheet( WindowStyle::PushButton );

  QWidget::connect( Ok,     SIGNAL( clicked() ),
                    parent, SLOT( exit() ));
  QWidget::connect( this,   SIGNAL( closed() ),
                    parent, SLOT( close() ));

  QVBoxLayout * VLayout = new QVBoxLayout;
  QHBoxLayout * H1Layout = new QHBoxLayout;
  QHBoxLayout * H2Layout = new QHBoxLayout;

  H1Layout -> addStretch();
  H1Layout -> addWidget( message );
  H1Layout -> addStretch();

  H2Layout -> addStretch();
  H2Layout -> addWidget( Ok );
  H2Layout -> addStretch();

  VLayout -> addStretch();
  VLayout -> addLayout( H1Layout );
  VLayout -> addLayout( H2Layout );
  VLayout -> addStretch();

  addLayout( VLayout );
}


void ErrorWindow::setMessage( const QString & msg )
{
  message -> setText( msg );
}



