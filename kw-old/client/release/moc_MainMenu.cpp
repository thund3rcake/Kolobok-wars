/****************************************************************************
** Meta object code from reading C++ file 'MainMenu.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/MainMenu/MainMenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainMenuScene[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      40,   25,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   14,   14,   14, 0x0a,
      78,   76,   14,   14, 0x0a,
     102,   14,   14,   14, 0x08,
     117,   14,   14,   14, 0x08,
     126,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainMenuScene[] = {
    "MainMenuScene\0\0escaped()\0connectionInfo\0"
    "startGame(Net::ServerAbout)\0pause()\0"
    ",\0catchError(int,QString)\0onDisconnect()\0"
    "onQuit()\0cancelQuit()\0"
};

void MainMenuScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainMenuScene *_t = static_cast<MainMenuScene *>(_o);
        switch (_id) {
        case 0: _t->escaped(); break;
        case 1: _t->startGame((*reinterpret_cast< const Net::ServerAbout(*)>(_a[1]))); break;
        case 2: _t->pause(); break;
        case 3: _t->catchError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->onDisconnect(); break;
        case 5: _t->onQuit(); break;
        case 6: _t->cancelQuit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainMenuScene::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainMenuScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_MainMenuScene,
      qt_meta_data_MainMenuScene, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainMenuScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainMenuScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainMenuScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainMenuScene))
        return static_cast<void*>(const_cast< MainMenuScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int MainMenuScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MainMenuScene::escaped()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainMenuScene::startGame(const Net::ServerAbout & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
