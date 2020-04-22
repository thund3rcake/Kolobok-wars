#include<Weapon.h>

Weapon::Weapon(QObject * parent) :
    Serializable(parent),
    weaponRegistrator(MetaRegistrator<Weapon>("Weapon")) {}

Weapon::Weapon(const Weapon &rhs) :
    Serializable(rhs.parent()),
    weaponRegistrator(rhs.weaponRegistrator),
    type(rhs.type),
    state(rhs.state),
    target(rhs.target),
    masterId(rhs.masterId) {}

Weapon::~Weapon() {}

Weapon::Type Weapon::getType() const {
    return type;
}
void Weapon::setType(Weapon::Type type) {
    this -> type = type;
}

Weapon::State Weapon::getState() const {
    return state;
}
void Weapon::setState(Weapon::State state) {
    this -> state = state;
}

QPointF Weapon::getTarget() const {
    return target;
}
void Weapon::setTarget(QPointF target) {
    this -> target = target;
}

quint16 Weapon::getMasterId() const {
    return masterId;
}
void Weapon::setMasterId(quint16 masterId) {
    this -> masterId = masterId;
}

quint8 Weapon::getQuintType() const {
    return static_cast<quint8>(this -> type);
}
void Weapon::setQuintType(quint8 type) {
    this -> type = static_cast<Weapon::Type>(type);
}

quint8 Weapon::getQuintState() const {
    return static_cast<quint8>(this -> state);
}
void Weapon::setQuintState(quint8 state) {
    this -> state = static_cast<Weapon::State>(state);
}

bool Weapon::operator == (const Weapon & rhs) const {

    if (rhs.type == this -> type) {
        if (rhs.state == this -> state) {
            if (rhs.target == this -> target) {
                if (rhs.masterId == this -> masterId) {
                    return true;
                }
            }
        }
    }
    return false;
}