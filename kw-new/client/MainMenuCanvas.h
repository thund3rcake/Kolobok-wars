#ifndef MAINMENUCANVAS_H_
#define MAINMENUCANVAS_H_


#include<QtGui>
#include<MainMenuStyle.h>
#include<QBoxLayout>
#include<QWidget>

class MainMenuCanvas: public QWidget {
  Q_OBJECT

  public:
    explicit
    MainMenuCanvas(QApplication * parent, int width = 0, int height = 0);

    virtual
    ~MainMenuCanvas();

    virtual void addWidget(QWidget * widget);
  private:
    MainMenuCanvas();
    MainMenuCanvas(const MainMenuCanvas & rhs);
    MainMenuCanvas & operator=(const MainMenuCanvas & rhs);



    QVBoxLayout  * VLayout;
    QApplication * parentApp;

  private slots:
      void exit();
};


#endif /* MAINMENUCANVAS_H_ */