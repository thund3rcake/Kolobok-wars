/*
 *  Created on: 18.05.2012
 *
 * Datagrams.cpp
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

#include <Datagrams.h>

using namespace Net;

/* Broadcast Datagram */
BroadcastDatagram::BroadcastDatagram(
                                     const QString & signature,
                                     const QString & serverName,
                                     const QString & mapName,
                                     quint16  tcpPort,
                                     quint8   version,
                                     quint8   subversion,
                                     quint8   bots,
                                     quint8   players,
                                     quint8   maxPlayers
                                    ):
signature( signature ),
serverName( serverName ),
mapName( mapName ),
tcpPort( tcpPort ),
version( version ),
subversion( subversion ),
bots( bots ),
players( players ),
maxPlayers( maxPlayers )
{};

QByteArray BroadcastDatagram::serialize() const
{
  QByteArray  bufer;
  QDataStream buferStream( &bufer, QIODevice::WriteOnly );
  buferStream.setVersion( Net::DataStreamVersion );

  buferStream << signature;
  buferStream << serverName;
  buferStream << mapName;
  buferStream << tcpPort;
  buferStream << version;
  buferStream << subversion;
  buferStream << bots;
  buferStream << players;
  buferStream << maxPlayers;

  buferStream.device() -> seek( 0 );

  return bufer;
}

void BroadcastDatagram::deserialize( const QByteArray & array )
{
  QDataStream arrayStream(
                           const_cast<QByteArray *>( &array ),
                           QIODevice::ReadOnly
                          );
  arrayStream.setVersion( Net::DataStreamVersion );

  arrayStream >> signature;
  arrayStream >> serverName;
  arrayStream >> mapName;
  arrayStream >> tcpPort;
  arrayStream >> version;
  arrayStream >> subversion;
  arrayStream >> bots;
  arrayStream >> players;
  arrayStream >> maxPlayers;
}

/* Broadcast Datagram */

/* MovingObjectProperties */

MovingObjectProperties::MovingObjectProperties(
                                               quint32   timestamp,
                                               Type      type,
                                               Team      team,
                                               quint16   id,
                                               const QPoint    & position,
                                               const QVector2D & intent,
                                               const QVector2D & head,
                                               quint8    hp,
                                               const GameWorld::Weapon & weapon
                                              ):
 timestamp( timestamp ),
 type( type ),
 team( team ),
 id( id ),
 position( position ),
 intent( intent ),
 head( head ),
 hp( hp ),
 weapon( weapon )
{
};

MovingObjectProperties::~MovingObjectProperties()
{
  //qDebug() << "~MovingObjectProperties";
  //qDebug() << (void*) this;
}


QByteArray MovingObjectProperties::serialize() const
{
  QByteArray  bufer;
  QDataStream buferStream( &bufer, QIODevice::WriteOnly );
  buferStream.setVersion( Net::DataStreamVersion );

  qint32 type = qint32( MovingObjectProperties::type );
  qint32 team = qint32( MovingObjectProperties::team );

  buferStream << timestamp;
  buferStream << type;
  buferStream << team;
  buferStream << id;
  buferStream << position;
  buferStream << intent;
  buferStream << head;
  buferStream << hp;
  buferStream << weapon.serialize();

  buferStream.device() -> seek( 0 );

  return bufer;
}

void MovingObjectProperties::deserialize( const QByteArray & arr )
{
  QByteArray array = arr;

  QDataStream arrayStream(
                           &array,
                           QIODevice::ReadOnly
                          );
  arrayStream.setVersion( Net::DataStreamVersion );

  qint32 type = 0;
  qint32 team = 0;

  arrayStream >> timestamp;
  arrayStream >> type;
  arrayStream >> team;
  arrayStream >> id;
  arrayStream >> position;
  arrayStream >> intent;
  arrayStream >> head;
  arrayStream >> hp;
  QByteArray weaponBufer;
  arrayStream >> weaponBufer; weapon.deserialize( weaponBufer );

  MovingObjectProperties::type = Type( type );
  MovingObjectProperties::team = Team( team );
}

void MovingObjectProperties::setTimestamp( qint32 time )
{
  timestamp = time;
};

/* MovingObjectProperties */





