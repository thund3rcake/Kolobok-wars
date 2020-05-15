#ifndef HUD_H
#define HUD_H

#include<QObject>
#include<QLabel>
#include<QtGui>

#include<Player.h>
#include<GamePanel.h>
#include<Console.h>
#include<Statistics.h>

class HUD: public QWidget {
    Q_OBJECT

public:
    HUD();

    virtual ~HUD();

    void updateConsole(
            Player *,
            const QPointF &,
            bool);
    void updConstFireTarget(const QPointF & target);

    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    HUD(const HUD & rhs);
    HUD & operator =(const HUD & rhs);

    GamePanel * bottomPanel;
    Console * console;
    Statistics * statistics;
    QVBoxLayout * vLayout;
    QHBoxLayout * topHLayout;
};

#endif // HUD_H
