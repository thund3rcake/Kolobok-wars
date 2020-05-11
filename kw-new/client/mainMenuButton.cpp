#include <MainMenuButton.h>


MainMenuButton::MainMenuButton( const QString & text, QWidget * p ):
  QLabel( p )
{
  setText( text );
  setStyleSheet( MainMenuStyle::Label );
  activate();
}



void  MainMenuButton::mousePressEvent( QMouseEvent * )
{
  if ( active ) emit clicked();
}

bool MainMenuButton::isActive() const
{
  return active;
}

void MainMenuButton::deactivate()
{
  active = false;
}

void MainMenuButton::activate()
{
  active = true;
}