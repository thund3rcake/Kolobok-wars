/****************************************************************************
** Meta object code from reading C++ file 'GamePanel.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/GameInterface/GamePanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GamePanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GamePanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x0a,
      33,   30,   10,   10, 0x0a,
      50,   45,   10,   10, 0x0a,
      69,   64,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GamePanel[] = {
    "GamePanel\0\0ammo\0setAmmo(uint)\0hp\0"
    "setHp(uint)\0mins\0setMins(uint)\0secs\0"
    "setSecs(uint)\0"
};

void GamePanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GamePanel *_t = static_cast<GamePanel *>(_o);
        switch (_id) {
        case 0: _t->setAmmo((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->setHp((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: _t->setMins((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 3: _t->setSecs((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GamePanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GamePanel::staticMetaObject = {
    { &QHBoxLayout::staticMetaObject, qt_meta_stringdata_GamePanel,
      qt_meta_data_GamePanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GamePanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GamePanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GamePanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GamePanel))
        return static_cast<void*>(const_cast< GamePanel*>(this));
    return QHBoxLayout::qt_metacast(_clname);
}

int GamePanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
