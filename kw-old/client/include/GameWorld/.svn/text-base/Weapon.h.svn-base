/*
 *
 * Created on: 22.04.2012
 *
 * Weapon.h
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

#ifndef WEAPON_H_
#define WEAPON_H_

#include <QPoint>
#include <QByteArray>
#include <Versions.h>

namespace GameWorld
{

namespace consts
{
  static const int weaponDamage = 10;
}

class Weapon
{
  public:
    enum Type  { Blaster, RocketGun };
    enum State { Fire, NoFire };

    Weapon(){};
    ~Weapon()
    {
      //qDebug() << "~Weapon";
      //qDebug() << (void*) this;
    }

    Weapon(
            Type  type,
            State state,
            const QPointF & target,
            quint16 masterId
           ):
      type( type ),
      state( state ),
      target( target ),
      masterId( masterId )
    {};

    QByteArray serialize() const
    {
      QByteArray  bufer;
      QDataStream buferStream( &bufer, QIODevice::WriteOnly );
      buferStream.setVersion( Net::DataStreamVersion );

      qint32 type  = qint32( Weapon::type );
      qint32 state = qint32( Weapon::state );

      buferStream << type;
      buferStream << state;
      buferStream << target;
      buferStream << masterId;

      buferStream.device() -> seek( 0 );
      return bufer;
    };

    void deserialize( const QByteArray & array )
    {
      QDataStream arrayStream(
                               const_cast<QByteArray *>( &array ),
                               QIODevice::ReadOnly
                              );
      arrayStream.setVersion( Net::DataStreamVersion );

      qint32 type  = 0;
      qint32 state = 0;

      arrayStream >> type;
      arrayStream >> state;
      arrayStream >> target;
      arrayStream >> masterId;

      Weapon::type  = Type( type );
      Weapon::state = State( state );
    };

    Type        type;
    State       state;
    QPointF     target;
    quint16     masterId;
};


} /* namespace GameWorld */

#endif /* WEAPON_H_ */
