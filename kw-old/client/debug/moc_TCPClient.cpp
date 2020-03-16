/****************************************************************************
** Meta object code from reading C++ file 'TCPClient.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Network/TCPClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TCPClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Net__TcpClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      28,   15,   15,   15, 0x05,
      52,   45,   15,   15, 0x05,
     113,   99,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     137,  132,   15,   15, 0x0a,
     151,   45,   15,   15, 0x0a,
     185,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Net__TcpClient[] = {
    "Net::TcpClient\0\0connected()\0"
    "idGoten(quint16)\0option\0"
    "newProperty(NetDataContainer<GameProperties>*)\0"
    "error,message\0error(int,QString)\0mode\0"
    "setMode(Mode)\0pushGamePropertie(GameProperties)\0"
    "start()\0"
};

void Net::TcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TcpClient *_t = static_cast<TcpClient *>(_o);
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->idGoten((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->newProperty((*reinterpret_cast< NetDataContainer<GameProperties>*(*)>(_a[1]))); break;
        case 3: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->setMode((*reinterpret_cast< Mode(*)>(_a[1]))); break;
        case 5: _t->pushGamePropertie((*reinterpret_cast< const GameProperties(*)>(_a[1]))); break;
        case 6: _t->start(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Net::TcpClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Net::TcpClient::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Net__TcpClient,
      qt_meta_data_Net__TcpClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Net::TcpClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Net::TcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Net::TcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Net__TcpClient))
        return static_cast<void*>(const_cast< TcpClient*>(this));
    return QThread::qt_metacast(_clname);
}

int Net::TcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void Net::TcpClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Net::TcpClient::idGoten(quint16 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Net::TcpClient::newProperty(NetDataContainer<GameProperties> * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Net::TcpClient::error(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
