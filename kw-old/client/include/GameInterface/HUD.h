/*
 *  Created on: 29.04.2012
 *
 * HUD.h
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

#ifndef HUD_H_
#define HUD_H_

#include <QObject>
#include <QLabel>
#include <QtGui>

#include <Player.h>
#include <GamePanel.h>
#include <Console.h>
#include <Statistics.h>

class HUD: public QWidget
{
  Q_OBJECT

  public:
    HUD ();

    virtual
    ~HUD();

    void updateConsole ( Player*,
                         const QPointF &,
                         bool );
    void updConsFireTargt (const QPointF & trgt);

    virtual void  keyPressEvent ( QKeyEvent * event );
    virtual void  keyReleaseEvent ( QKeyEvent * event );

  private:
    HUD( const HUD & rhs );
    HUD & operator=( const HUD & rhs );

    GamePanel   * bottomPanel;
    Console     * console;
    Statistics  * statistics;
    QVBoxLayout * vLayout;
    QHBoxLayout * topHLayout;
};


#endif /* HUD_H_ */
