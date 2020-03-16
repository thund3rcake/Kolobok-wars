/*
 *
 * Created on: 25.03.2012
 *
 * DerivedWindows.h
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
 * along with kolobok-wars-client; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *  
 */


#ifndef DERIVEDWINDOWS_H_
#define DERIVEDWINDOWS_H_

#include <BaseWindow.h>
#include <LanTab.h>
#include <FavoriteTab.h>
#include <WindowStyle.h>

class FindWindow : public Window
{
    Q_OBJECT

  public:
    explicit
    FindWindow( QWidget * parent = 0 );

    virtual
    ~FindWindow();

  private:
    FindWindow();
    FindWindow( const FindWindow & rhs );
    FindWindow & operator=( const FindWindow & rhs );


    QTabWidget  * findType;

    LanTab      * lan;
    FavoriteTab * fav;

  private slots:
    void onStartGame( const Net::ServerAbout & connectionInfo );
    void catchError( int, QString );

  signals:
    void startGame( const Net::ServerAbout & connectionInfo );
};

class OptionsWindow : public Window
{
    Q_OBJECT

  public:
    explicit
    OptionsWindow( QWidget * parent = 0 );

  private:
    OptionsWindow();
    OptionsWindow( const OptionsWindow & rhs );
    OptionsWindow & operator=( const OptionsWindow & rhs );
};


class QuitWindow : public Window
{
    Q_OBJECT

  public:
    explicit
    QuitWindow( QWidget * parent = 0 );

  private:
    QuitWindow();
    QuitWindow( const QuitWindow & rhs );
    QuitWindow & operator=( const QuitWindow & rhs );
};

class ErrorWindow: public Window
{
    Q_OBJECT

  public:
    explicit
    ErrorWindow( QWidget * parent = 0 );

    void setMessage( const QString & msg );

  private:
    ErrorWindow();
    ErrorWindow( const QuitWindow & rhs );
    ErrorWindow & operator=( const QuitWindow & rhs );

    QLabel * message;
};


#endif /* DERIVEDWINDOWS_H_ */
