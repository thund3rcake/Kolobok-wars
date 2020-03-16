/*
 *
 * Created on: 23.03.12
 *
 * MainMenuButton.h
 * This file is part of kolobok-wars-client
 *
 * Copyright (C) 2012 - Ivan Penkin, MIPT
 * grek.penkin@gmail.com
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


#ifndef MAINMENUBUTTUN_H_
#define MAINMENUBUTTUN_H_


#include <QtGui>
#include <QPalette>
#include <MainMenuStyle.h>

class MainMenuButton: public QLabel
{
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




#endif /* MAINMENUBUTTUN_H_ */
