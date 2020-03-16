/*
 *
 * Created on: 12.04.2012
 *
 * FavoriteTab.cpp
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



#ifndef FAVORITETAB_CPP_
#define FAVORITETAB_CPP_

#include <FavoriteTab.h>
#include <QtGui>
#include <WindowStyle.h>


FavoriteTab::FavoriteTab( QWidget * parent ):
  QWidget( parent )
{
  QVBoxLayout * favVLayout = new QVBoxLayout;
  QHBoxLayout * favHLayout = new QHBoxLayout;

  favSrv = new QTreeWidget( this );
  favVLayout -> addWidget( favSrv );

  favVLayout -> addStretch();
  favHLayout -> addStretch();

  favVLayout -> addLayout( favHLayout );

  favConnect = new QPushButton( "Connect", this );
  favAddFav  = new QPushButton( "Add favorite", this );

  favConnect -> setEnabled( false );

  favConnect -> setStyleSheet( WindowStyle::PushButton );
  favAddFav -> setStyleSheet( WindowStyle::PushButton );

  favHLayout -> addWidget( favAddFav );
  favHLayout -> addWidget( favConnect );

  setLayout( favVLayout );
}


FavoriteTab::~FavoriteTab()
{
  delete favAddFav;
  delete favConnect;
  delete favSrv;
}


#endif /* FAVORITETAB_CPP_ */
