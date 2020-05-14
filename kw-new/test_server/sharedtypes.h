#ifndef SHAREDTYPES_H
#define SHAREDTYPES_H

#include "sharedobject.h"
#include "Datagramms.h"
#include "Bullet.h"
#include "Map.h"

typedef QQueue<MovingObjectProperties> UdpQueue;
typedef SharedObject<UdpQueue>         SharedUdpQueue;

typedef QMap<qint32, qint32>      LatencysMap;
typedef SharedObject<LatencysMap> SharedLatencysMap;

typedef QMap<qint32, Bullet *>    BulletsMap;
typedef SharedObject<BulletsMap>  SharedBulletsMap;

class PlayerThread;
typedef QMap<qint32, PlayerThread *> PlayersMap;
typedef SharedObject<PlayersMap>     SharedPlayersMap;

class Shared
{
  public:
    SharedObject<Map*>    gameMap;

    SharedObject<quint16> nextPlayerId;
    SharedPlayersMap      playerById;
    SharedLatencysMap     playerLatencyById;

    SharedObject<qint32>  nextBulletId;
    SharedBulletsMap      bulletById;
};

#endif // SHAREDTYPES_H
