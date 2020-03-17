#include<Weapon.h>

namespace GameWorld {


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
}