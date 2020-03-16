/*
 *
 * Created on: 23.03.12
 *
 * BaseWindow.h
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


#ifndef FINDWINDOW_H_
#define FINDWINDOW_H_

#include <QtGui>

class Window : public QWidget
{
  Q_OBJECT

  public:
    Window(
             QWidget *parent = 0,
             Qt::WindowFlags flags = Qt::ToolTip
          );

    virtual
    ~Window();

    virtual void setWindowTitle( const QString & tittle );
    virtual void addLayout( QLayout * layout );

  public slots:
    void catchError( int errno, QString message );

  protected:
    virtual void mousePressEvent( QMouseEvent *event );
    virtual void mouseMoveEvent( QMouseEvent * event );
    virtual void mouseReleaseEvent( QMouseEvent *event );
    virtual void paintEvent( QPaintEvent * event );

  private:
    Window();
    Window( const Window & rhs );
    Window & operator=( const Window & rhs );


    QPoint        lastPos;
    bool          moving;

    QToolButton * closeButton;
    QLabel *      title;

    QBoxLayout * layout;

  signals:
    void closed();
    void error( int errno, QString message );

  private slots:
    void close();
};

#endif /* FINDWINDOW_H_ */
