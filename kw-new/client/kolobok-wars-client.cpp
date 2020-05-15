#include <QtGui>
#include <QApplication>
#include <GraphicsView.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
  QApplication app( argc, argv );

  qsrand( QTime( 0,0,0 ).secsTo( QTime::currentTime() ));
  GraphicsView view( &app );
  view.show();

  return app.exec();
}