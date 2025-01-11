/****************************************************************************
** Meta object code from reading C++ file 'NetworkAction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../NetworkAction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetworkAction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ui_Network_Window_t {
    QByteArrayData data[14];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ui_Network_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ui_Network_Window_t qt_meta_stringdata_Ui_Network_Window = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Ui_Network_Window"
QT_MOC_LITERAL(1, 18, 11), // "ScanNetwork"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "startIP"
QT_MOC_LITERAL(4, 39, 5), // "endIP"
QT_MOC_LITERAL(5, 45, 11), // "isHostAlive"
QT_MOC_LITERAL(6, 57, 2), // "ip"
QT_MOC_LITERAL(7, 60, 9), // "scanPorts"
QT_MOC_LITERAL(8, 70, 12), // "QHostAddress"
QT_MOC_LITERAL(9, 83, 7), // "address"
QT_MOC_LITERAL(10, 91, 10), // "QList<int>"
QT_MOC_LITERAL(11, 102, 11), // "portsToScan"
QT_MOC_LITERAL(12, 114, 16), // "getHostIpAddress"
QT_MOC_LITERAL(13, 131, 11) // "getHostName"

    },
    "Ui_Network_Window\0ScanNetwork\0\0startIP\0"
    "endIP\0isHostAlive\0ip\0scanPorts\0"
    "QHostAddress\0address\0QList<int>\0"
    "portsToScan\0getHostIpAddress\0getHostName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui_Network_Window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x0a /* Public */,
       5,    1,   44,    2, 0x0a /* Public */,
       7,    2,   47,    2, 0x0a /* Public */,
      12,    0,   52,    2, 0x0a /* Public */,
      13,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Bool, QMetaType::QString,    6,
    QMetaType::QStringList, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::QString,
    QMetaType::QString, 0x80000000 | 8,    9,

       0        // eod
};

void Ui_Network_Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Ui_Network_Window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ScanNetwork((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: { bool _r = _t->isHostAlive((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { QStringList _r = _t->scanPorts((*reinterpret_cast< const QHostAddress(*)>(_a[1])),(*reinterpret_cast< const QList<int>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->getHostIpAddress();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->getHostName((*reinterpret_cast< const QHostAddress(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Ui_Network_Window::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Ui_Network_Window.data,
    qt_meta_data_Ui_Network_Window,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ui_Network_Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui_Network_Window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ui_Network_Window.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Ui_Network_Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
