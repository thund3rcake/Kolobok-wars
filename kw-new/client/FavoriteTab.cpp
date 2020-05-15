#ifndef FAVORITETAB_CPP_
#define FAVORITETAB_CPP_

#include <FavoriteTab.h>
#include <QtGui>
#include <WindowStyle.h>
#include<QVBoxLayout>


FavoriteTab::FavoriteTab( QWidget * parent ):
  QWidget( parent )
{
    qDebug() << "FavoriteTab";
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
    qDebug() << "~FavoriteTab";
  delete favAddFav;
  delete favConnect;
  delete favSrv;
}


#endif /* FAVORITETAB_CPP_ */
