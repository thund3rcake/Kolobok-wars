/****************************************************************************
** Meta object code from reading C++ file 'GameScene.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/GameWorld/GameScene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GameWorld__GameScene[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      32,   30,   21,   21, 0x05,
      51,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   21,   21,   21, 0x0a,
     128,   21,   21,   21, 0x0a,
     193,   30,   21,   21, 0x0a,
     217,   21,   21,   21, 0x0a,
     227,   21,   21,   21, 0x0a,
     247,  244,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GameWorld__GameScene[] = {
    "GameWorld::GameScene\0\0pause()\0,\0"
    "error(int,QString)\0keyPressed()\0"
    "updatePlayerPos(NetDataContainer<Net::MovingObjectProperties>*)\0"
    "updateBulletsPos(NetDataContainer<Net::MovingObjectProperties>*)\0"
    "catchError(int,QString)\0repaint()\0"
    "characterSteer()\0id\0setOwnId(quint16)\0"
};

void GameWorld::GameScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GameScene *_t = static_cast<GameScene *>(_o);
        switch (_id) {
        case 0: _t->pause(); break;
        case 1: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->keyPressed(); break;
        case 3: _t->updatePlayerPos((*reinterpret_cast< NetDataContainer<Net::MovingObjectProperties>*(*)>(_a[1]))); break;
        case 4: _t->updateBulletsPos((*reinterpret_cast< NetDataContainer<Net::MovingObjectProperties>*(*)>(_a[1]))); break;
        case 5: _t->catchError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->repaint(); break;
        case 7: _t->characterSteer(); break;
        case 8: _t->setOwnId((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GameWorld::GameScene::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GameWorld::GameScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_GameWorld__GameScene,
      qt_meta_data_GameWorld__GameScene, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GameWorld::GameScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GameWorld::GameScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GameWorld::GameScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameWorld__GameScene))
        return static_cast<void*>(const_cast< GameScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int GameWorld::GameScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GameWorld::GameScene::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GameWorld::GameScene::error(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameWorld::GameScene::keyPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
