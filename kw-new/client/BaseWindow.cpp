#include <QtGui>
#include <BaseWindow.h>
#include <WindowStyle.h>

Window::Window(
                 QWidget * parent,
                 Qt::WindowFlags flags
              ):
  QWidget( parent, flags )
{
    setStyleSheet( WindowStyle::Window );

    closeButton = new QToolButton;
    closeButton -> setToolButtonStyle( Qt::ToolButtonIconOnly );
    closeButton -> setIconSize( QSize( 9, 9 ));
    closeButton -> setIcon( QIcon::fromTheme( "window-close" ) );
    closeButton -> setStyleSheet( WindowStyle::ToolButtonHover );
    closeButton -> setAutoRaise( true );

    QWidget::connect( closeButton, SIGNAL( clicked() ),
                      this,        SLOT( close() ));

    title = new QLabel;
    title -> setStyleSheet( WindowStyle::WindowTitle );


    layout = new QVBoxLayout();
    layout -> setMargin( 0 );

    QBoxLayout * hLayout = new QHBoxLayout();
    QBoxLayout * vLayout = new QVBoxLayout();

    hLayout -> setMargin( 2 );
    vLayout -> setMargin( 1 );

    vLayout -> addLayout( hLayout );
    vLayout -> addLayout( layout );
    vLayout -> addStretch();

    hLayout -> addWidget( title );
    hLayout -> addStretch();
    hLayout -> addWidget( closeButton );

    setLayout( vLayout );

    QPoint wPos = pos();

    if ( wPos.x() < 0 ) wPos.setX( 0 );
    if ( wPos.y() < 0 ) wPos.setY( 0 );

    wPos.setX( wPos.x() + qrand() %200 + 100 );
    wPos.setY( wPos.y() + qrand() %100 + 50 );

    move( wPos );
    setMinimumSize( 600, 400 );


    lastPos.setX( 0 );
    lastPos.setY( 0 );
    moving = false;
}

Window::~Window()
{
  delete closeButton;
  delete title;

  delete layout;
}

void Window::catchError( int errNo, QString message )
{
  emit error( errNo, message );
}


void Window::mousePressEvent( QMouseEvent * event )
{
  if ( event -> button() == Qt::LeftButton )
  {
    if (
          (event -> globalX() < pos().x() + width() - 22) &&
          (event -> globalY() < pos().y() + 22)
        )
    {
      lastPos = event -> pos();
      moving  = true;
    }
  }
}

void Window::mouseMoveEvent( QMouseEvent * event )
{
  if( (event -> buttons() & Qt::LeftButton) && moving )
  {
    move(
           event -> globalX() - lastPos.x(),
           event -> globalY() - lastPos.y()
         );
  }
}

void Window::mouseReleaseEvent( QMouseEvent *event )
{
  if ( event -> button() == Qt::LeftButton && moving )
  {
    moving = false;
  }
}

void Window::close()
{
  hide();
  emit closed();
}

void Window::addLayout( QLayout * lt )
{
  layout -> addLayout( lt );
}

void Window::setWindowTitle( const QString & ttl )
{
  title -> setText( ttl );
}

void Window::paintEvent( QPaintEvent * e )
{
  QWidget::paintEvent( e );

  QPainter painter( this );

  QPoint topLeft( 0, 0 );
  QPoint topRight( width(), 0 );
  QPoint bottomLeft( 0, height() );
  QPoint bottomRight( width(), height() );

  QPen pen( QColor( 140, 146, 132 ));
  pen.setWidth( 1 );
  painter.setPen( pen );
  painter.drawLine( bottomLeft, topLeft );
  painter.drawLine( topLeft, topRight );

  pen.setColor( QColor( 41, 44, 33 ));
  pen.setWidth( 1 );
  painter.setPen( pen );
  painter.drawLine( topRight, bottomRight );
  painter.drawLine( bottomLeft, bottomRight );

  topLeft     += QPoint( 1, 1 );
  topRight    += QPoint( -1, 1 );
  bottomLeft  += QPoint( 1, -1 );
  bottomRight += QPoint( -1, -1 );

  pen.setColor( QColor( 140, 146, 132, 127 ));
  pen.setWidth( 1.5 );
  painter.setPen( pen );
  painter.drawLine( bottomLeft, topLeft );
  painter.drawLine( topLeft, topRight );

  pen.setColor( QColor( 41, 44, 33, 127 ));
  pen.setWidth( 1.5 );
  painter.setPen( pen );
  painter.drawLine( topRight, bottomRight );
  painter.drawLine( bottomLeft, bottomRight );
}

