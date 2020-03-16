/*
 *
 * Created on: 25.03.2012
 *
 * DerivedWindows.h
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
 * along with kolobok-wars-client; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *  
 */



#include <DerivedWindows.h>
#include <commonLibs.h>


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

  QWidget::connect( lan, SIGNAL( startGame( const Net::ServerAbout & )),
                    this, SLOT( onStartGame( const Net::ServerAbout & )) );
}

FindWindow::~FindWindow()
{
  delete findType;

  delete lan;
  delete fav;
}


void FindWindow::onStartGame( const Net::ServerAbout & connectionInfo )
{
  emit startGame( connectionInfo );
};

void FindWindow::catchError( int errno, QString msg )
{
  emit error( errno, msg );
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
                    parent, SLOT( exit() ));
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
                    parent, SLOT( exit() ));

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



