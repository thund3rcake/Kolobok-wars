#ifndef MAINMENU_H
#define MAINMENU_H

#include <QtGui>
#include <QWidget>
#include<QGraphicsView>
#include <QGraphicsProxyWidget>

#include <MainMenuButton.h>
#include <MainMenuCanvas.h>
#include <DerivedWindows.h>
#include <Utils.h>


class MainMenuScene: public QGraphicsScene
{
  Q_OBJECT

  public:
    MainMenuScene( QApplication * pApp, QGraphicsView * pView );

    virtual
    ~MainMenuScene();

    virtual
    void keyPressEvent(QKeyEvent * event);
  public slots:
    void pause();
    void catchError( int, const QString & );

  protected:

  private:
    MainMenuScene();
    MainMenuScene( const MainMenuScene & rhs );
    MainMenuScene & operator=( const MainMenuScene & rhs );


    QApplication *           parentApp;
    QGraphicsView *          parentView;
    QGraphicsProxyWidget *   proxy;
    MainMenuCanvas *         canvas;

    QPoint *                 size;

    MainMenuButton *         resume;
    MainMenuButton *         disconnect;
    MainMenuButton *         startServer;
    MainMenuButton *         findBtn;
    MainMenuButton *         optionsBtn;
    MainMenuButton *         quitBtn;

    FindWindow *    findW;
    OptionsWindow * optionsW;
    QuitWindow *    quitW;
    ErrorWindow *   errorW;

  private slots:
    void     onDisconnect();
    void     onQuit();
    void     cancelQuit();

  signals:
    void escaped();
    void startGame( const ServerAbout & connectionInfo );
};


#endif // MAINMENU_H
