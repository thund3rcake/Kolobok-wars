#ifndef WEAPON_H_
#define WEAPON_H_

#include <CommonGlobal.h>
#include <Utils.h>
#include <Serializable.h>
#include <MetaRegistrator.h>
#include <QPoint>
#include <Versions.h>

namespace GameWorld {

namespace consts {
    static const int weaponDamage = 10;
}

class KW_COMMON_EXPORT Weapon : public Serializable {
    Q_OBJECT
public:
    enum Type  { Blaster = 1,
                                RocketGun = 2};
    enum State { Fire = 1,
                                NoFire = 2};

    explicit Weapon(QObject * parent = 0);

    Weapon(
                    Weapon::Type type,
                    State state,
                    const QPointF & target,
                    quint16 masterId,
                    QObject * parent = 0
                    ):
        Serializable(parent),
        weaponRegistrator(MetaRegistrator<Weapon>("Weapon")),
        type(type),
        state(state),
        target(target),
        masterId(masterId) {}

    Weapon(const Weapon & rhs);

    virtual ~Weapon();

    bool operator == (const GameWorld::Weapon & rhs) const;

    Q_PROPERTY(quint8 type
               READ getQuintType
               WRITE setQuintType);
    Q_PROPERTY(quint8 state
               READ getQuintState
               WRITE setQuintState);
    Q_PROPERTY(QPointF target
               READ getTarget
               WRITE setTarget);
    Q_PROPERTY(quint16 masterId
               READ getMasterId
               WRITE setMasterId);

    Weapon::Type getType() const;
    Weapon::State getState() const;
    quint8 getQuintType() const;
    quint8 getQuintState() const;
    QPointF getTarget() const;
    quint16 getMasterId() const;

    void setType(Weapon::Type type);
    void setState(Weapon::State state);
    void setQuintType(quint8 type);
    void setQuintState(quint8 state);
    void setTarget(QPointF target);
    void setMasterId(quint16 masterId);

private:
    MetaRegistrator<Weapon> weaponRegistrator;
    Type type;
    State state;
    QPointF target;
    quint16 masterId;
};

} /* namespace GameWorld */

Q_DECLARE_METATYPE(GameWorld::Weapon);
Q_DECLARE_TYPEINFO(GameWorld::Weapon, Q_COMPLEX_TYPE);


#endif /* WEAPON_H_ */
