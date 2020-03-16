/*
 *  Created on: 25.03.2012
 *
 * abstractMap.h
 *
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
#ifndef MAP_CLASS_H_
#define MAP_CLASS_H_

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QTreeWidget>

#include <Entity.h>
#include <commonLibs.h>

class abstractMap: public QObject
{
  friend class XmlHandler;
  public:
    abstractMap() {};
    const QString & getName ();
    QPoint  getSize ();
    int     getPlayerAmount ();

  protected:
    uint    m_sizeH;  //prefix 'm' means that this value belongs to map coordinates
    uint    m_sizeW;  //prefix 'm' means that this value belongs to map coordinates
    int     playersAmount;
    QString name;

    void    setSize         ( uint height, uint width );
    void    setName         ( const QString & str );
    void    setPlayerAmount ( int amnt );

  private:
    abstractMap (const abstractMap& rhs);
    abstractMap& operator= (const abstractMap& rhs);
};


#ifndef KOLOBOK_BOT /* #IFDEF CLIENT || SERVER */

class abstractNoAIMap: public abstractMap
{
  Q_OBJECT
  friend class XmlHandler;
  public:
    abstractNoAIMap (QString);

    bool    isDotAvailable  ( QPoint dot );

    bool    isThereSDotFile ();
    bool    load_sDOT_file  ();
    bool    write_sDOT_file ();

    QString getBackgroundPath ();
    const   QList<PolygonEntity*> &  getPolygons ();

  protected:
    void    findAvailblDots ();
    bool    addPolygon     ( PolygonEntity* );

  private:

    abstractNoAIMap ( const abstractNoAIMap &rhs );
    abstractNoAIMap& operator= ( const abstractNoAIMap &rhs );

    QString backgroundPath;

    QList<PolygonEntity*>     polygons;
    QVector<QVector<quint8> > availableDots;
    QVector<QPoint>           m_respawnPlaces;

  signals:
    void error (int, QString);
};

inline bool isDotInAnyRect (
                            QPointF dot,
                            QList<PolygonEntity*> & polygons,
                            QList<PolygonEntity*> & suspiciousPols
                           );
void markTheNearest (
                     int x,    int y,
                     int srcX, int srcY,
                     QVector<QVector<quint8> > & availableDots
                    );

#endif

#ifdef KOLOBOK_BOT

class Map: public abstractMap
{
  private:
    Map ( const Map &rhs );
    Map& operator= ( const Map &rhs );
};

#endif

#ifdef KOLOBOK_CLIENT

class Map : public abstractNoAIMap /* client map */
{
  public:
    explicit
    Map(QString);

  private:
    Map ();
    Map ( const Map &rhs );
    Map& operator= ( const Map &rhs );
};

#endif

#ifdef KOLOBOK_SERVER

class Map : public abstractNoAIMap /* server map */
{
  public:
    explicit
    Map(QString);

  private:
    Map ( const Map &rhs );
    Map& operator= ( const Map &rhs );
};

#endif

#endif /* MAP_CLASS_H_ */
