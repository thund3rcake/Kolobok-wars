#ifndef MAINMENUBUTTON_H
#define MAINMENUBUTTON_H

#include <QtGui>
#include <QPalette>
#include <MainMenuStyle.h>
#include<QLabel>

class MainMenuButton: public QLabel{
  Q_OBJECT

  public:
    explicit
    MainMenuButton( const QString & label, QWidget * parent = 0 );

    virtual
    bool isActive() const;

  protected:
    virtual
    void mousePressEvent( QMouseEvent * event );

  private:
    MainMenuButton();
    MainMenuButton( const MainMenuButton & rhs );
    MainMenuButton & operator=( const MainMenuButton & rhs );

    bool active;

  signals:
    void clicked();

  public slots:
    void deactivate();
    void   activate();
};


#endif // MAINMENUBUTTON_H
