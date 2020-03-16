/*
 *
 * Created on: 29.04.2012
 *
 * ServerUi.h
 * This file is part of kolobok-wars-server
 * 
 * Copyright (C) 2012 - Ivan Penkin, MIPT
 * grek.penkin@gmail.com
 *
 * kolobok-wars-server is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * kolobok-wars-server is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with kolobok-wars-server; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *  
 */

#ifndef SERVERUI_H_
#define SERVERUI_H_

#include <QtCore>
#include <QtGui>

#include <ServerTools.h>



class ServerUi: public QWidget
{
  Q_OBJECT

  public:
    ServerUi();

    virtual
    ~ServerUi();

  private:
    ServerUi( const ServerUi & rhs );
    ServerUi & operator=( const ServerUi & rhs );

    void findMaps();
    void setupTools( const QString & srvName );

    QLineEdit * serverName;
    QComboBox * port;
    QComboBox * mapName;
    QSpinBox  * maxPlayers;
    QTextEdit * console;

    QPushButton * startBtn;
    QPushButton * stopBtn;

    ServerTools * tools;

  private slots:
    void onStart();
    void onStop();
};








#endif /* SERVERUI_H_ */
