#ifndef ACTIVATABLEBUTTON_H
#define ACTIVATABLEBUTTON_H


#include <QtGui>
#include<QPushButton>

class ActivatableButton: public QPushButton
{
  Q_OBJECT

  public:
    explicit
    ActivatableButton( const QString & text, QWidget * parent = 0):
      QPushButton( text, parent )
    {};

  private:
    ActivatableButton();
    ActivatableButton( const ActivatableButton & rhs );
    ActivatableButton & operator=( const ActivatableButton & rhs );


  public slots:
    void activate()
    {
      setEnabled( true );
    };
    void deactivate()
    {
      setEnabled( false );
    };
};


#endif // ACTIVATABLEBUTTON_H