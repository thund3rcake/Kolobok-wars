/****************************************************************************
** Meta object code from reading C++ file 'LanTab.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Window/LanTab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LanTab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LanTab[] = {

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
      22,    8,    7,    7, 0x05,
      56,   41,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,    7,    7,    7, 0x08,
      99,    7,    7,    7, 0x08,
     113,    7,    7,    7, 0x08,
     131,  129,    7,    7, 0x08,
     171,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LanTab[] = {
    "LanTab\0\0errno,message\0error(int,QString)\0"
    "connectionInfo\0startGame(Net::ServerAbout)\0"
    "refreshStart()\0refreshStop()\0"
    "addNewItem(int)\0,\0"
    "onServerSelection(QTreeWidgetItem*,int)\0"
    "onConnectClicked()\0"
};

void LanTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LanTab *_t = static_cast<LanTab *>(_o);
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->startGame((*reinterpret_cast< const Net::ServerAbout(*)>(_a[1]))); break;
        case 2: _t->refreshStart(); break;
        case 3: _t->refreshStop(); break;
        case 4: _t->addNewItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onServerSelection((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->onConnectClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LanTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LanTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LanTab,
      qt_meta_data_LanTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LanTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LanTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LanTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LanTab))
        return static_cast<void*>(const_cast< LanTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int LanTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void LanTab::error(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LanTab::startGame(const Net::ServerAbout & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
