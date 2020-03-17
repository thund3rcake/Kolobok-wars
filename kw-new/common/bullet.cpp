#include <Bullet.h>
#include <Entity.h>
#include <QPainter>
#include <CommonGlobal.h>
#include <GameWorldConsts.h>
#include <math.h>

GameWorld::Bullet::Bullet (
               int id,
               const QPointF & position,
               QPointF& targAbs,
               Weapon::Type typ
               ):
    MovingEntity(id, position, QVector2D(-position+targAbs).normalized()),
    reached(false)
{
    setPosition (position);
    weapon.type = typ;
    weapon.target = targAbs;
    setRect(position.x(), position.y(),
            consts::playerSize/4, consts::playerSize/4);
}

void GameWorld::Bullet::paint (
                   QPainter * painter,
                   const QStyleOptionGraphicsItem *,
                   QWidget *
                   )
{
    //устанавливает границу прямоугольника (класс-родитель)
    //void QGraphicsRectItem::setRect(qreal x, qreal y, qreal width, qreal height)
    setRect( getPosition().x() - consts::playerSize/8, getPosition().y() - consts::playerSize/8,
             consts::playerSize/4, consts::playerSize/4);

     //это не работает!
     //drawRect(int x, int y, int width, int height)
     //playerSize/8 == 0, playerSize/4 == 1
     painter->drawRect( getPosition().x()-consts::playerSize/8, getPosition().y()-consts::playerSize/8,
                        consts::playerSize/4, consts::playerSize/4);
}

bool GameWorld::Bullet::isTargetReach ()
{
  if ( reached == true ) return true;

  double dx = abs ( getPosition().x() - weapon.target.rx() );
  double dy = abs ( getPosition().y() - weapon.target.ry() );

  if ( dx < consts::bulletVelocity &&
       dy < consts::bulletVelocity )
  {
    setPosition ( weapon.target );
    reached = true;
    return true;
  }
  return false;
}