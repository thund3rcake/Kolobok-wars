#include <Utils.h>
#include <GameWorldConsts.h>
#include <QtWidgets/QDesktopWidget>

QPoint getDesktopSize() // Проблемы с QDescrtopWidget
{
  static OnceCreated<QPoint> size;

//  if ( size.isNull() ) //isNull() вернёт false, если вектор не пуст, иначе true.
//  {
//    QDesktopWidget desktop;
//    size = QPoint( desktop.width(), desktop.height() );
//  }

  return size.getdData(); //
}



double  scale_x_100 ()
{
  static OnceCreated<double> scale;

  if ( scale.isNull() )
  {
    scale = 100 * double ( getDesktopSize().ry() )/
                  double (consts::heightOfVisibleArea ); //.ry  это ссылка на координату y.
  }

  return scale.getdData();
}

double scaledPlayerSize()
{
  static OnceCreated<double> size;

  if ( size.isNull() )
  {
    size = consts::playerSize*(scale_x_100()/100);
  }

  return size.getdData();
}
