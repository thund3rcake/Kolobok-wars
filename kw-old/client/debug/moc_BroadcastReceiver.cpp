/****************************************************************************
** Meta object code from reading C++ file 'BroadcastReceiver.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Network/BroadcastReceiver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BroadcastReceiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Net__BroadcastReceiver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,   24,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Net__BroadcastReceiver[] = {
    "Net::BroadcastReceiver\0\0vectorIndex\0"
    "newServer(int)\0processPendingDatagrams()\0"
};

void Net::BroadcastReceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BroadcastReceiver *_t = static_cast<BroadcastReceiver *>(_o);
        switch (_id) {
        case 0: _t->newServer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->processPendingDatagrams(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Net::BroadcastReceiver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Net::BroadcastReceiver::staticMetaObject = {
    { &QUdpSocket::staticMetaObject, qt_meta_stringdata_Net__BroadcastReceiver,
      qt_meta_data_Net__BroadcastReceiver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Net::BroadcastReceiver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Net::BroadcastReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Net::BroadcastReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Net__BroadcastReceiver))
        return static_cast<void*>(const_cast< BroadcastReceiver*>(this));
    return QUdpSocket::qt_metacast(_clname);
}

int Net::BroadcastReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QUdpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Net::BroadcastReceiver::newServer(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
