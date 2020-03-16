/*
 *  Created on: 01.05.2012
 *
 * GamePanel.h
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Krepak Vitaly, MIPT
 * krepakvitaliy@gmail.com
 *
 * kolobok-wars-client is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kolobok-wars-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kolobok-wars-client if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 */

#ifndef GAMEPANEL_H_
#define GAMEPANEL_H_

#include <QObject>
#include <QLabel>
#include <QtGui>
#include <HUDStyleSheets.h>

class GamePanel: public QHBoxLayout
{
  Q_OBJECT
  public:
    GamePanel();

    virtual
    ~GamePanel ();

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
    GamePanel( const GamePanel & rhs );
    GamePanel & operator=( const GamePanel & rhs );

    QFont * font;

    uint    hpVal;
    QLabel* hpValLabel;
    uint    ammoVal;
    QLabel* ammoValLabel;
    uint    secsVal;
    uint    minsVal;
    QLabel* timerValLabel;
};

#endif /* GAMEPANEL_H_ */
