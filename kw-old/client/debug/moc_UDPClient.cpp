/****************************************************************************
** Meta object code from reading C++ file 'UDPClient.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Network/UDPClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UDPClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Net__UdpClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   16,   15,   15, 0x05,
     103,   89,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     122,   16,   15,   15, 0x0a,
     178,   15,  170,   15, 0x0a,
     188,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Net__UdpClient[] = {
    "Net::UdpClient\0\0prpt\0"
    "newObjectProperties(NetDataContainer<Net::MovingObjectProperties>*)\0"
    "error,message\0error(int,QString)\0"
    "sendNewObjectPropertie(MovingObjectProperties&)\0"
    "quint16\0getPort()\0"
    "checkError(QAbstractSocket::SocketError)\0"
};

void Net::UdpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UdpClient *_t = static_cast<UdpClient *>(_o);
        switch (_id) {
        case 0: _t->newObjectProperties((*reinterpret_cast< NetDataContainer<Net::MovingObjectProperties>*(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->sendNewObjectPropertie((*reinterpret_cast< MovingObjectProperties(*)>(_a[1]))); break;
        case 3: { quint16 _r = _t->getPort();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = _r; }  break;
        case 4: _t->checkError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Net::UdpClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Net::UdpClient::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Net__UdpClient,
      qt_meta_data_Net__UdpClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Net::UdpClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Net::UdpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Net::UdpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Net__UdpClient))
        return static_cast<void*>(const_cast< UdpClient*>(this));
    return QThread::qt_metacast(_clname);
}

int Net::UdpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Net::UdpClient::newObjectProperties(NetDataContainer<Net::MovingObjectProperties> * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Net::UdpClient::error(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
