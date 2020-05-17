#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H


#include <QtGui>
#include <QGraphicsScene>
#include <GameScene.h>
#include <QApplication>
#include <QtOpenGL>
#include <MainMenu.h>
#include <HUD.h>

class GraphicsView: public QGraphicsView
{
  Q_OBJECT

  public:
    GraphicsView ( QApplication * pApp, QWidget * parent = 0 );

    virtual
    ~GraphicsView ();

    QRectF viewRect() const;

  public slots:
    void onPause         ();
    void onResume        ();
    void onError         ( int, QString );
    void onConnect       ( const ServerAbout & connectionInfo );
    void deleteGameScene ();

  protected:
    virtual void wheelEvent ( QWheelEvent * );

  private:
    GraphicsView ();
    GraphicsView ( const GraphicsView &rhs );
    GraphicsView& operator= ( const GraphicsView &rhs );

    enum Scene{ Menu, Game };
    Scene curentScene;

    void SignalsSwitchTo( Scene direction );

    QGLFormat * glFormat;
    QGLWidget * viewport;
    MainMenuScene           * menuScene;
    GameScene    * gameScene;
    QApplication            * parentApp;
};


#endif // GRAPHICSVIEW_H