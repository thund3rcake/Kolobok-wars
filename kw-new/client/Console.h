#ifndef CONSOLE_H
#define CONSOLE_H

#include<QObject>
#include<QLabel>
#include<QWidget>
#include<QtGui>
#include<QHBoxLayout>

#include<HUDStyleSheets.h>

class Console: public QWidget {
    Q_OBJECT
public:
    Console (QWidget * parent = 0);

    void setPlayerPos (const QPoint & pos);
    void setTopLeft (const QPointF & topLeft);
    void setAvailable (bool avail);
    void setHeading (const QVector2D & head);
    void setIntention (const QVector2D & intn);
    void setFireTarget (const QPointF & trgt);

private:
    Console();
    Console(const Console & rhs);
    Console & operator = (const Console & rhs);

    QLabel playerPos;
    QLabel topLeft;
    QLabel available;
    QLabel heading;
    QLabel fireTargt;
    QLabel intention;
};

#endif // CONSOLE_H
