#include <Player.h>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPixmap>
#include <Utils.h>

Player::Player()
{
    this->setRect( 0, 0, scaledPlayerSize(), scaledPlayerSize() );
}

Player::Player (QString name, Player::Team team):
    team (team),
    name (name)
{
  this->setRect( 0, 0, scaledPlayerSize(), scaledPlayerSize() );
}

void  Player::setHead ( QVector2D vector )
{
  head = vector.normalized();
}

const QVector2D & Player::getHead ()
{
  return head;
}

void Player::paint (
                    QPainter * painter,
                    const QStyleOptionGraphicsItem *,
                    QWidget *
                   )
{
//  qDebug() << "Repaint Player" << id;
  if (position != pos())
    setPos(pos() + intent.toPointF()*consts::sendTimerInterval / 5 / consts::sceneUpdateInterval);
  painter->setRenderHint( QPainter::Antialiasing, true );
  painter->drawEllipse ( QPointF(0,0), scaledPlayerSize(), scaledPlayerSize() );
  painter->drawLine    ( QPointF(0,0), head.toPointF()*scaledPlayerSize() );
}

void Player::setTimeStep (qint32 step)
{
  timeStep = step;
}

qint32 Player::getTimeStep ()
{
  return timeStep;
}
