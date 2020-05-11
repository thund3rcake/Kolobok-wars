#ifndef FINDWINDOW_H_
#define FINDWINDOW_H_

#include <QtGui>
#include<QBoxLayout>
#include<QToolButton>
#include<QLabel>

class Window : public QWidget
{
  Q_OBJECT

  public:
    Window(
             QWidget *parent = 0,
             Qt::WindowFlags flags = Qt::ToolTip
          );

    virtual
    ~Window();

    virtual void setWindowTitle( const QString & tittle );
    virtual void addLayout( QLayout * layout );

  public slots:
    void catchError( int errNo, QString message );

  protected:
    virtual void mousePressEvent( QMouseEvent *event );
    virtual void mouseMoveEvent( QMouseEvent * event );
    virtual void mouseReleaseEvent( QMouseEvent *event );
    virtual void paintEvent( QPaintEvent * event );

  private:
    Window();
    Window( const Window & rhs );
    Window & operator=( const Window & rhs );


    QPoint        lastPos;
    bool          moving;

    QToolButton * closeButton;
    QLabel *      title;

    QBoxLayout * layout;

  signals:
    void closed();
    void error( int errNo, QString message );

  private slots:
    void close();
};

#endif /* FINDWINDOW_H_ */
