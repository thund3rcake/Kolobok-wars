/*
 *
 * Created on: 23.03.12
 *
 * MainMenuCanvas.h
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

#ifndef MAINMENUCANVAS_H_
#define MAINMENUCANVAS_H_


#include <QtGui>
#include <MainMenuStyle.h>

class MainMenuCanvas: public QWidget
{
  Q_OBJECT

  public:
    explicit
    MainMenuCanvas( QApplication * parent, int width = 0, int height = 0 );

    virtual
    ~MainMenuCanvas();

    virtual void addWidget( QWidget * widget );
  private:
    MainMenuCanvas();
    MainMenuCanvas( const MainMenuCanvas & rhs );
    MainMenuCanvas & operator=( const MainMenuCanvas & rhs );



    QVBoxLayout  * VLayout;
    QApplication * parentApp;

  private slots:
      void exit();
};


#endif /* MAINMENUCANVAS_H_ */
