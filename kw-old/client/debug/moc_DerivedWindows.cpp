/****************************************************************************
** Meta object code from reading C++ file 'DerivedWindows.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Window/DerivedWindows.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DerivedWindows.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FindWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   12,   11,   11, 0x08,
      87,   85,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FindWindow[] = {
    "FindWindow\0\0connectionInfo\0"
    "startGame(Net::ServerAbout)\0"
    "onStartGame(Net::ServerAbout)\0,\0"
    "catchError(int,QString)\0"
};

void FindWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FindWindow *_t = static_cast<FindWindow *>(_o);
        switch (_id) {
        case 0: _t->startGame((*reinterpret_cast< const Net::ServerAbout(*)>(_a[1]))); break;
        case 1: _t->onStartGame((*reinterpret_cast< const Net::ServerAbout(*)>(_a[1]))); break;
        case 2: _t->catchError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FindWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FindWindow::staticMetaObject = {
    { &Window::staticMetaObject, qt_meta_stringdata_FindWindow,
      qt_meta_data_FindWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FindWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FindWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FindWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FindWindow))
        return static_cast<void*>(const_cast< FindWindow*>(this));
    return Window::qt_metacast(_clname);
}

int FindWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FindWindow::startGame(const Net::ServerAbout & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_OptionsWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_OptionsWindow[] = {
    "OptionsWindow\0"
};

void OptionsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData OptionsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OptionsWindow::staticMetaObject = {
    { &Window::staticMetaObject, qt_meta_stringdata_OptionsWindow,
      qt_meta_data_OptionsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OptionsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OptionsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OptionsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OptionsWindow))
        return static_cast<void*>(const_cast< OptionsWindow*>(this));
    return Window::qt_metacast(_clname);
}

int OptionsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QuitWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QuitWindow[] = {
    "QuitWindow\0"
};

void QuitWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QuitWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QuitWindow::staticMetaObject = {
    { &Window::staticMetaObject, qt_meta_stringdata_QuitWindow,
      qt_meta_data_QuitWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QuitWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QuitWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QuitWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QuitWindow))
        return static_cast<void*>(const_cast< QuitWindow*>(this));
    return Window::qt_metacast(_clname);
}

int QuitWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ErrorWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ErrorWindow[] = {
    "ErrorWindow\0"
};

void ErrorWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ErrorWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ErrorWindow::staticMetaObject = {
    { &Window::staticMetaObject, qt_meta_stringdata_ErrorWindow,
      qt_meta_data_ErrorWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ErrorWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ErrorWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ErrorWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ErrorWindow))
        return static_cast<void*>(const_cast< ErrorWindow*>(this));
    return Window::qt_metacast(_clname);
}

int ErrorWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Window::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
