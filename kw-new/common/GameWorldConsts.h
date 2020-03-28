#ifndef GAMESCENECONSTS_H_
#define GAMESCENECONSTS_H_

#include <QtCore>
#include <CommonGlobal.h>

namespace GameWorld
{

namespace consts
{
  static const int KW_COMMON_EXPORT heightOfVisibleArea = 200; //TODO: what do we need to do with the 4:3 monitors
  static const int KW_COMMON_EXPORT widthOfVisibleArea  = 90;  // or 16:10?


  static const int KW_COMMON_EXPORT fps                   =   100;
  static const int KW_COMMON_EXPORT sendTimerInterval     =   1000/25;      //ms
  static const int KW_COMMON_EXPORT sceneUpdateInterval   =   1000/fps;      //ms
  static const qreal KW_COMMON_EXPORT timeUnit   =   sendTimerInterval/5; // qreal синоним double
  static const qreal KW_COMMON_EXPORT bulletVelocity   =   15;

  static const int KW_COMMON_EXPORT playerSize  = 7; //in map coordinates
}

} /* namespace GameWorld */

#endif /* GAMESCENECONSTS_H_ */
