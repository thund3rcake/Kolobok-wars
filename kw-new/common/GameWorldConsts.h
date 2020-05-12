#ifndef GAMESCENECONSTS_H_
#define GAMESCENECONSTS_H_

#include <QtCore>
#include <CommonGlobal.h>

namespace consts
{
  static const int heightOfVisibleArea = 200; //TODO: what do we need to do with the 4:3 monitors
  static const int widthOfVisibleArea  = 90;  // or 16:10?



  static const int fps                   =   100;
  static const int sendTimerInterval     =   1000 / 25;      //ms
  static const int sceneUpdateInterval   =   1000 / fps;      //ms
  static const qreal timeUnit   =   sendTimerInterval / 5; // qreal синоним double
  static const qreal bulletVelocity   =   15;

  static const int playerSize  = 7; //in map coordinates

  /************** MAP CONSTS *************/
  static const quint8 mapSizeX = 700;
  static const quint8 mapSizeY = 900;

  /************** BOT CONSTS *************/
  static const int hpEscape = 15; // starts escaping when hp gets lower then that value
  static const quint8 stride = 10; // scale of the grid used by BFS in UtilityAlgorithms
  static const quint8 patrolPointsCount = 5; // number of vertices in patrolled polygon
  static const quint8 patrolEdgeMinLength = 100;
  static const quint32 velocity = 32;
}


#endif /* GAMESCENECONSTS_H_ */
