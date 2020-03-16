/*
 *
 * Created on: 12.04.2012
 *
 * LanTab.cpp
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




#include <LanTab.h>
#include <QtGui>
#include <WindowStyle.h>
//#include <ServersTable.h>
#include <BroadcastReceiver.h>

LanTab::LanTab( QWidget * parent ):
  QWidget( parent ),
  curSelectedIndex( -1 )
{
  QVBoxLayout * lanVLayout = new QVBoxLayout;
  QHBoxLayout * lanHLayout = new QHBoxLayout;

  table = new QTreeWidget( this );
  lanVLayout -> addWidget( table );

  tableInitialization();

  lanVLayout -> addStretch();
  lanHLayout -> addStretch();

  lanVLayout -> addLayout( lanHLayout );

  lanConnect = new ActivatableButton( "Connect", this );
  lanRefresh = new ActivatableButton( "Refresh", this );

  lanConnect -> setEnabled( false );

  lanConnect -> setStyleSheet( WindowStyle::PushButton );
  lanRefresh -> setStyleSheet( WindowStyle::PushButton );

  lanHLayout -> addWidget( lanRefresh );
  lanHLayout -> addWidget( lanConnect );

  setLayout( lanVLayout );
  lanConnect -> deactivate();

  QWidget::connect( lanRefresh, SIGNAL( clicked()),
                    this,       SLOT( refreshStart()) );
  QWidget::connect( &timer,     SIGNAL( timeout()),
                    this,       SLOT( refreshStop()) );

  QWidget::connect( lanConnect, SIGNAL( clicked()),
                    this,       SLOT( onConnectClicked()) );

  /*
  QWidget::connect( lanSrv, SIGNAL( readyToConnect() ),
                    lanConnect, SLOT( activate()) );
  QWidget::connect( this, SIGNAL( itemClicked( QTreeWidgetItem *, int )),
                    this, SLOT( setCurrentServer( QTreeWidgetItem *, int )) );


  QWidget::connect( lanSrv, SIGNAL( error( int, QString )),
                    this, SLOT( catchError ( int, QString )) );

  */
}

void LanTab::tableInitialization()
{
  table -> setStyleSheet( WindowStyle::SrvTableHeight );

  table -> verticalScrollBar() -> setStyleSheet( WindowStyle::SrvTableScrolVertical );
  table -> verticalScrollBar() -> setContextMenuPolicy( Qt::NoContextMenu );

  table -> setVerticalScrollBarPolicy(   Qt::ScrollBarAlwaysOn  );
  table -> setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

  table -> header() -> setStyleSheet( WindowStyle::SrvTableHeader );
  table -> header() -> setResizeMode( QHeaderView::Fixed );
  table -> header() -> setMaximumSize( 551, 16 );

  table -> setColumnCount ( Net::tableHeadLabels.count() );
  table -> setHeaderLabels( Net::tableHeadLabels );

  table -> header() -> resizeSection( 0, 540/Net::tableHeadLabels.count() ); //240
  table -> header() -> resizeSection( 1, 540/Net::tableHeadLabels.count() ); //95
  table -> header() -> resizeSection( 2, 540/Net::tableHeadLabels.count() ); //155
  table -> header() -> resizeSection( 3, 540/Net::tableHeadLabels.count() ); //60
}


LanTab::~LanTab()
{
  delete lanRefresh;
  delete lanConnect;
  delete table;
}

void LanTab::refreshStart()
{
  lanRefresh -> deactivate();
  lanConnect -> deactivate();
  curSelectedIndex = -1;

  disconnect( table, SIGNAL( itemClicked( QTreeWidgetItem *, int )),
              this,  SLOT( onServerSelection( QTreeWidgetItem *, int )) );


  timer.start( 4000 );

  table -> clear();
  servers.clear();

  try
  {
    receiver = new Net::BroadcastReceiver( servers, this );
  }
  catch( Net::BroadcastReceiver::Exception exc )
  {
    emit error( exc.errno, exc.message );
    timer.stop();
    lanRefresh -> activate();
    return;
  }
  QWidget::connect( receiver, SIGNAL( newServer( int )),
                    this,     SLOT( addNewItem( int )), Qt::DirectConnection );

}

void LanTab::refreshStop()
{
  timer.stop();

  QWidget::disconnect( receiver,   SIGNAL( newServer( int )),
                       this,       SLOT( addNewItem( int )) );
  delete receiver;

  connect( table,      SIGNAL( itemClicked( QTreeWidgetItem *, int )),
           this,       SLOT( onServerSelection( QTreeWidgetItem *, int )) );

  lanConnect -> deactivate();
  lanRefresh -> activate();
}

void LanTab::addNewItem( int vectorIndex )
{
  using namespace Net;

  QTreeWidgetItem * item = new QTreeWidgetItem( table );

  item -> setText(
                   0,
                   servers[vectorIndex].data.serverName +
                   ":" +
                   QString().number( servers[vectorIndex].port, 10 )
                  );

  item -> setText( 1, QString().number( servers[vectorIndex].data.bots, 10 ) + "/" +
                      QString().number( servers[vectorIndex].data.players, 10 ) + "/" +
                      QString().number( servers[vectorIndex].data.maxPlayers, 10 ));
  item -> setText( 2, servers[vectorIndex].data.mapName );
  item -> setText( 3, QString( servers[vectorIndex].latency, 10 ));

  table -> insertTopLevelItem( vectorIndex, item );
}


void LanTab::onServerSelection( QTreeWidgetItem * item, int )
{
  lanConnect -> activate();
  lanRefresh -> deactivate();

  int index = table -> indexOfTopLevelItem( item );
  if ( index > -1 && index < servers.count() )
  {
    curSelectedIndex = index;
  };

  lanRefresh -> activate();
};

void LanTab::onConnectClicked()
{
  if ( curSelectedIndex > -1 )
  {
    emit startGame( servers[curSelectedIndex] );
  }
}


