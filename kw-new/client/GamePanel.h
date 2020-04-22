#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include<QObject>
#include<QLabel>
#include<QtGui>
#include<HUDStyleSheets.h>
#include<QHBoxLayout>

class GamePanel: public QHBoxLayout {
    Q_OBJECT
public:
    GamePanel();
    virtual ~GamePanel();

    uint getAmmo() const;
    uint getHp() const;
    uint getMins() const;
    uint getSecs() const;

public slots:
    void setAmmo(uint ammo);
    void setHp(uint hp);
    void setMins(uint mins);
    void setSecs(uint secs);

private:
    GamePanel(const GamePanel & rhs);
    GamePanel & operator = (const GamePanel & rhs);

    QFont * font;

    uint hpVal;
    QLabel * hpValLabel;
    uint ammoVal;
    QLabel * ammoValLabel;
    uint secsVal;
    uint minsVal;
    QLabel * timerValLabel;
};

#endif // GAMEPANEL_H
