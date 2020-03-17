#ifndef BULLET_H_
#define BULLET_H_

#include <Entity.h>
#include <Weapon.h>
#include <QVector2D>

namespace GameWorld
{

//Наследуется от MovingEntity (координаты точки + направление) и от QGraphicsRectItem (прямоугольник)
class Bullet: public MovingEntity, public QGraphicsRectItem
{
public:
    Bullet (int, const QPointF&, QPointF&, Weapon::Type );

    virtual
    //отрисовывает пулю
    void paint (
               QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget = 0
               );
    //определяет, попало или нет
    bool isTargetReach ();

private:
    Bullet ();
    Bullet (const Bullet& rhs);
    Bullet& operator= (const Bullet& rhs);

    Weapon weapon;
    bool  reached; //temporary flag, this flag needs until bullets don't removed
};

} /* namespace GameWorld */

#endif /* BULLET_H_ */