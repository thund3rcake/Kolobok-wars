﻿#include <MainMenuCanvas.h>

MainMenuCanvas::MainMenuCanvas( QApplication * pApp, int w, int h )
{
    qDebug() << "MMCanvas";
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
    qDebug() << "~MMCanvas";
  delete VLayout;
}


void MainMenuCanvas::addWidget( QWidget * widget )
{
  VLayout -> addWidget( widget );
}

void MainMenuCanvas::exit()
{
    qDebug() << "~MMCanvasExit";
  parentApp -> closeAllWindows ();
}
