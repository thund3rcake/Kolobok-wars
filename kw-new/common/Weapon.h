#ifndef WEAPON_H_
#define WEAPON_H_

#include<CommonGlobal.h>
#include<Serializable.h>
#include <QPoint>
#include <Versions.h>

namespace GameWorld
{

namespace consts {
    static const int weaponDamage = 10;
}

class DATA_EXPORT Weapon : public Serializable {
public:
    enum Type  { Blaster, RocketGun };
    enum State { Fire, NoFire };

    Weapon(){};
    ~Weapon() {
      //qDebug() << "~Weapon";
      //qDebug() << (void*) this;
    }

    Weapon(
                    Type  type,
                    State state,
                    const QPointF & target,
                    quint16 masterId
                    ):
    type(type),
    state(state),
    target(target),
    masterId(masterId) {}

    Q_PROPERTY(Type type
               READ getType
               WRITE setType);
    Q_PROPERTY(State state
               READ getState
               WRITE setState);
    Q_PROPERTY(QPointF target
               READ getTarget
               WRITE setTarget);
    Q_PROPERTY(quint16 masterId
               READ getMasterId
               WRITE setMasterId);

    Type getType() const;
    State getState() const;
    QPointF getTarget() const;
    quint16 getMasterId() const;

    void setType(Type type);
    void setState(State state);
    void setTarget(QPointF target);
    void setMasterId(quint16 masterId);

//private:
    Type type;
    State state;
    QPointF target;
    quint16 masterId;
};


} /* namespace GameWorld */

#endif /* WEAPON_H_ */