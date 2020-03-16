/*
 *
 * Created on: 16.04.2012
 *
 * Datagrams.h
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

#ifndef DATAGRAMS_H_
#define DATAGRAMS_H_

#include <QtNetwork>
#include <QVector2D>
#include <Versions.h>
#include <Weapon.h>

namespace Net
{

static const int MaxSignatureLength = 16;
static const int MaxMapNameLength = 16;

static const QString QStringSignature = "kOlObOk";

/*
 *
 *  UDP broadcast
 *
 */

class BroadcastDatagram
{
  public:
    BroadcastDatagram(){};
    BroadcastDatagram(
                       const QString & signature,
                       const QString & serverName,
                       const QString & mapName,
                       quint16  tcpPort,
                       quint8   version,
                       quint8   subversion,
                       quint8   bots,
                       quint8   players,
                       quint8   maxPlayers
                      );

    QByteArray serialize() const;

    void deserialize( const QByteArray & array );


    QString  signature;
    QString  serverName;
    QString  mapName;
    quint16  tcpPort;
    quint8   version;
    quint8   subversion;
    quint8   bots;
    quint8   players;
    quint8   maxPlayers;
};

struct ServerAbout
{
  QHostAddress      address;
  quint16           port;
  BroadcastDatagram data;
  quint8            latency;
};


static const QStringList tableHeadLabels =
             QList<QString>() << "Servers"
                              << "Players (B/P/M)"
                              << "Map"
                              << "Latency";

/* UDP broadcast */


/*
 *
 * UDP client
 *
 */

static const qint32 MaxPackegeDelay = 200 /* ms */;

class MovingObjectProperties
{
  public:
    enum Type { Player, Bullet, Timestamp };
    enum Team { Red, Blue };

    MovingObjectProperties(){};
    ~MovingObjectProperties();

    MovingObjectProperties(
                            quint32   timestamp,
                            Type      type,
                            Team      team,
                            quint16   id,
                            const QPoint    & position,
                            const QVector2D & intent,
                            const QVector2D & head,
                            quint8    hp,
                            const GameWorld::Weapon & weapon
                           );

    QByteArray serialize() const;
    void deserialize( const QByteArray & arr );

    void setTimestamp( qint32 time );

    qint32            timestamp;
    Type              type;
    Team              team;
    quint16           id;
    QPointF           position;
    QVector2D         intent;
    QVector2D         head;
    quint8            hp;
    GameWorld::Weapon weapon;
};


/* UDP client */



/*
 *
 * TCP - options
 *
 */

const static QString InitRequest   = "Kolobok-war client:";

class GameProperties
{
  public:
    enum Type { UdpPort };

    GameProperties(){};
    GameProperties(
                    Type type,
                    const QString & firstQString
                   ):
      type( type ),
      firstQString( firstQString )
    {};
    GameProperties(
                    Type type,
                    qint64 firstQInt
                   ):
      type( type ),
      firstQInt( firstQInt )
    {};
    GameProperties(
                    Type type,
                    qreal firstQReal
                   ):
      type( type ),
      firstQReal( firstQReal )
    {};
    GameProperties(
                      Type type,
                      const QString & firstQString,
                      qint64 firstQInt
                     ):
      type( type ),
      firstQString( firstQString ),
      firstQInt( firstQInt )
    {};
    GameProperties(
                      Type type,
                      const QString & firstQString,
                      qreal firstQReal
                     ):
      type( type ),
      firstQString( firstQString ),
      firstQReal( firstQReal )
    {};
    GameProperties(
                     Type type,
                     const QString & firstQString,
                     qint64 firstQInt,
                     qreal  firstQReal
                    ):
      type( type ),
      firstQString( firstQString ),
      firstQInt( firstQInt ),
      firstQReal( firstQReal )
    {};
    GameProperties(
                     Type type,
                     const QString & firstQString,
                     const QString & secondQString,
                     qint64 firstQInt,
                     qint64 secondQInt,
                     qreal  firstQReal,
                     qreal  secondQReal
                    ):
      type( type ),
      firstQString( firstQString ),
      secondQString( secondQString ),
      firstQInt( firstQInt ),
      secondQInt( secondQInt ),
      firstQReal( firstQReal ),
      secondQReal( secondQReal )
    {};

    QByteArray serialize() const
    {
      QByteArray  bufer;
      QDataStream buferStream( &bufer, QIODevice::WriteOnly );
      buferStream.setVersion( Net::DataStreamVersion );

      buferStream << (qint32) type;
      buferStream << firstQString;
      buferStream << secondQString;
      buferStream << firstQInt;
      buferStream << secondQInt;
      buferStream << firstQReal;
      buferStream << secondQReal;

      buferStream.device() -> seek( 0 );

      return bufer;
    }

    void deserialize( const QByteArray & array )
    {
      QDataStream arrayStream(
                               const_cast<QByteArray *>( &array ),
                               QIODevice::ReadOnly
                              );
      arrayStream.setVersion( Net::DataStreamVersion );

      arrayStream >> reinterpret_cast<qint32 &>( type );
      arrayStream >> firstQString;
      arrayStream >> secondQString;
      arrayStream >> firstQInt;
      arrayStream >> secondQInt;
      arrayStream >> firstQReal;
      arrayStream >> secondQReal;
    }

    Type             type;
    QString          firstQString;
    QString          secondQString;
    qint64           firstQInt;
    qint64           secondQInt;
    qreal            firstQReal;
    qreal            secondQReal;
};

/* TCP - options */

} /* namespace Net */

#endif /* DATAGRAMS_H_ */
