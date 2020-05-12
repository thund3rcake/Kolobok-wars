#include <MainMenuCanvas.h>

MainMenuCanvas::MainMenuCanvas( QCoreApplication * pApp, int w, int h )
{
  parentApp = pApp;

  if ( w && h )
  {
    setMinimumWidth( w );
    setMinimumHeight( h );
  }

  VLayout = new QVBoxLayout;
  QHBoxLayout * HLayout = new QHBoxLayout;

  HLayout -> addLayout( VLayout );
  HLayout -> addStretch();
  VLayout -> addStretch();

  setLayout( HLayout );
  setStyleSheet( MainMenuStyle::CanvasBg );
}

MainMenuCanvas::~MainMenuCanvas()
{
  delete VLayout;
}


void MainMenuCanvas::addWidget( QWidget * widget )
{
  VLayout -> addWidget( widget );
}

void MainMenuCanvas::exit()
{
  parentApp -> exit(0);
}
