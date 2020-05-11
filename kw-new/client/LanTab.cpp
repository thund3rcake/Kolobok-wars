#include <LanTab.h>
#include <QtGui>
#include <WindowStyle.h>
//#include <ServersTable.h>
#include<QBoxLayout>
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

//  table -> verticalScrollBar() -> setStyleSheet( WindowStyle::SrvTableScrolVertical );
//  table -> verticalScrollBar() -> setContextMenuPolicy( Qt::NoContextMenu );

  table -> setVerticalScrollBarPolicy(   Qt::ScrollBarAlwaysOn  );
  table -> setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

//  table -> header() -> setStyleSheet( WindowStyle::SrvTableHeader );
//  table -> header() -> setResizeMode( QHeaderView::Fixed );
//  table -> header() -> setMaximumSize( 551, 16 );

//  table -> setColumnCount ( Net::tableHeadLabels.count() );
//  table -> setHeaderLabels( Net::tableHeadLabels );

//  table -> header() -> resizeSection( 0, 540/Net::tableHeadLabels.count() ); //240
//  table -> header() -> resizeSection( 1, 540/Net::tableHeadLabels.count() ); //95
//  table -> header() -> resizeSection( 2, 540/Net::tableHeadLabels.count() ); //155
//  table -> header() -> resizeSection( 3, 540/Net::tableHeadLabels.count() ); //60
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
    receiver = new BroadcastReceiver( servers, this );
  }
  catch( BroadcastReceiver::Exception exc )
  {
    emit error( exc.errNo, exc.message );
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
                   servers[vectorIndex].data.getServerName() +
                   ":" +
                   QString().number( servers[vectorIndex].port, 10 )
                  );

  item -> setText( 1, QString().number( servers[vectorIndex].data.getBots(), 10 ) + "/" +
                      QString().number( servers[vectorIndex].data.getPlayers(), 10 ) + "/" +
                      QString().number( servers[vectorIndex].data.getMaxPlayers(), 10 ));
  item -> setText( 2, servers[vectorIndex].data.getMapName() );
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


