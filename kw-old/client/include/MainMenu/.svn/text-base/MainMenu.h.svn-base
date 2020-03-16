/*
 *
 * Created on: 23.03.12
 *
 * MainMenu.h
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
 *
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_


#include <QtGui>
#include <QWidget>
#include <QGraphicsProxyWidget>

#include <MainMenuButton.h>
#include <MainMenuCanvas.h>
#include <DerivedWindows.h>
#include <commonLibs.h>


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
    void startGame( const Net::ServerAbout & connectionInfo );
};


#endif /* MAINMENU_H_ */
