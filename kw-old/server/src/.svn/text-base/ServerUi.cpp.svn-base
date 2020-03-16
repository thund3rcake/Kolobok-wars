/*
 *
 * Created on: 29.04.2012
 *
 * ServerUi.cpp
 * This file is part of kolobok-wars-server
 * 
 * Copyright (C) 2012 - Ivan Penkin, MIPT
 * grek.penkin@gmail.com
 *
 * kolobok-wars-server is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kolobok-wars-server is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kolobok-wars-server; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *  
 */

#include <QtGui>
#include <ServerUi.h>

ServerUi::ServerUi()
{
  setFixedWidth( 500 );

  tools = NULL;

  serverName = new QLineEdit( this );
  port       = new QComboBox( this );
  mapName    = new QComboBox( this );
  maxPlayers = new QSpinBox( this );
  console    = new QTextEdit( this );

  startBtn = new QPushButton( "Start" );
  stopBtn  = new QPushButton( "Stop" );

  serverName -> setFixedWidth( 200 );
  serverName -> setMaxLength( 14 );

  port -> addItem( QString( "27031" ));
  port -> addItem( QString( "27032" ));
  port -> addItem( QString( "27033" ));
  port -> addItem( QString( "27034" ));
  port -> addItem( QString( "27035" ));
  port -> setFixedWidth( 100 );

  mapName -> setFixedWidth( 200 );
  findMaps();

  maxPlayers -> setFixedWidth( 50 );
  maxPlayers -> setMinimum( 2  );
  maxPlayers -> setMaximum( 32 );

  console -> setFixedSize( 480, 200 );
  console -> setReadOnly( true );

  QVBoxLayout * vLayout           = new QVBoxLayout;
  QHBoxLayout * hGridLayout       = new QHBoxLayout;
  QHBoxLayout * hButtonLayout     = new QHBoxLayout;

  QGridLayout * gridLayout        = new QGridLayout;

  setLayout( vLayout );

  vLayout -> addLayout( hGridLayout );
  vLayout -> addLayout( hButtonLayout );
  vLayout -> addWidget( console );

  hGridLayout -> addLayout( gridLayout );

  QLabel * serverNameLbl = new QLabel( "Server name", this );
  QLabel * portLbl       = new QLabel( "Port",        this );
  QLabel * mapNameLbl    = new QLabel( "Map name",    this );
  QLabel * maxPlayersLbl = new QLabel( "Max players", this );

  gridLayout -> addWidget( serverNameLbl, 0, 0 );
  gridLayout -> addWidget( portLbl,       1, 0 );
  gridLayout -> addWidget( mapNameLbl,    2, 0 );
  gridLayout -> addWidget( maxPlayersLbl, 3, 0 );

  gridLayout -> addWidget( serverName, 0, 1 );
  gridLayout -> addWidget( port,       1, 1 );
  gridLayout -> addWidget( mapName,    2, 1 );
  gridLayout -> addWidget( maxPlayers, 3, 1 );

  hButtonLayout -> addStretch();
  hButtonLayout -> addWidget( startBtn );
  hButtonLayout -> addWidget( stopBtn );
  hButtonLayout -> addStretch();

  QWidget::connect( startBtn, SIGNAL( clicked()),
                    this,     SLOT( onStart()) );
  QWidget::connect( stopBtn,  SIGNAL( clicked()),
                    this,     SLOT( onStop()) );
}

ServerUi::~ServerUi()
{
  delete serverName;
  delete mapName;
  delete maxPlayers;
  delete console;

  delete startBtn;
  delete stopBtn;
}

void ServerUi::findMaps()
{
  QDir mapDirectory( "./maps/" );
  QStringList maps = mapDirectory.entryList( QDir::Dirs, QDir::Name );

  foreach( QString name, maps )
  {
    if ( name == "." ||  name == ".."  ) continue;

    mapDirectory.cd( name );
    if ( mapDirectory.exists( name + ".xml" ) )
      mapName -> addItem( name );
    mapDirectory.cdUp();
  }
}

void ServerUi::setupTools( const QString & srvName )
{
  if ( tools == NULL )
  {
    bool ok;
    tools = new ServerTools(
                             srvName,
                             mapName -> currentText(),
                             port -> currentText().toInt( &ok, 10 ),
                             (quint8)(maxPlayers -> value()),
                             console,
                             this
                            );

    console -> insertHtml( "Starting broadcast... &nbsp" );
    tools -> getBroadcastSender().start();
    console -> insertHtml( "[DONE]<br />" );

    console -> insertHtml( "Starting udp server... &nbsp" );
    tools -> getUdpServer().start();
    console -> insertHtml( "[DONE]<br />" );

    console -> insertHtml( "====================================<br />" );
    console -> insertHtml( "<b>Kolobok Wars Server " +
                           QString().number( Net::ProtVersion, 10 ) +
                           "." +
                           QString().number( Net::ProtSubversion, 10 ) +
                           "</b><br />"
                          );
    console -> insertHtml( "port: \"" +
                           port -> currentText() +
                           "\"<br />"
                          );
    console -> insertHtml( "name: \"" + srvName + "\"<br />" );
    console -> insertHtml( "map: \"" + mapName -> currentText() + "\"<br />" );
    console -> insertHtml(
                           "max. players: \"" +
                           QString().number( maxPlayers -> value(), 10 ) +
                           "\"<br />"
                          );
    console -> insertHtml( "====================================<br />" );

  }
  else
  {
    console -> insertHtml( "<b>Server already has been started</b><br />" );
  }
};

void ServerUi::onStart()
{
  QString srvName = serverName -> text().simplified();
  int j = 0;
  while ( (j = srvName.indexOf( " ", j )) != -1 )  srvName.replace( j, 1, "_" );

  if ( srvName.length() == 0 )
  {
    console -> insertHtml( "You should set \"Server Name\"<br />" );
    return;
  }

  setupTools( srvName );
}

void ServerUi::onStop()
{
  delete tools;
  tools = NULL;

  console -> clear();
  console -> insertHtml( "Server stopped.<br />" );
}

