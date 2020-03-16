/*
 *
 * Created on: 12.04.2012
 *
 * LanTab.h
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

#ifndef FINDTAB_H_
#define FINDTAB_H_

#include <QtGui>
#include <QTreeWidget>

#include <ActivatableButton.h>
#include <Datagrams.h>

namespace Net
{
  class BroadcastReceiver;
}

class LanTab : public QWidget
{
    Q_OBJECT

  public:
    explicit
    LanTab( QWidget * parent = 0 );

    ~LanTab();

  private:
    LanTab();
    LanTab( const LanTab & rhs );
    LanTab & operator=( const LanTab & rhs );

    inline
    void tableInitialization();

    ActivatableButton       * lanRefresh;
    ActivatableButton       * lanConnect;
    QTreeWidget             * table;
    Net::BroadcastReceiver  * receiver;

    QVector<Net::ServerAbout> servers;
    QTimer                    timer;
    int                       curSelectedIndex;

  private slots:
    void refreshStart();
    void refreshStop();
    void addNewItem( int );
    void onServerSelection( QTreeWidgetItem *, int );
    void onConnectClicked();

  signals:
    void error( int errno, QString message );
    void startGame( const Net::ServerAbout & connectionInfo );
};



#endif /* FINDTAB_H_ */
