/****************************************************************************
** Meta object code from reading C++ file 'Host_stats.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Host_stats.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Host_stats.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ui_Host_stats_t {
    QByteArrayData data[7];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ui_Host_stats_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ui_Host_stats_t qt_meta_stringdata_Ui_Host_stats = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Ui_Host_stats"
QT_MOC_LITERAL(1, 14, 18), // "populateListWidget"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 15), // "updateDiskUsage"
QT_MOC_LITERAL(4, 50, 14), // "updateCpuUsage"
QT_MOC_LITERAL(5, 65, 5), // "usage"
QT_MOC_LITERAL(6, 71, 14) // "updateMemUsage"

    },
    "Ui_Host_stats\0populateListWidget\0\0"
    "updateDiskUsage\0updateCpuUsage\0usage\0"
    "updateMemUsage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui_Host_stats[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       6,    1,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,    5,
    QMetaType::Void, QMetaType::QReal,    5,

       0        // eod
};

void Ui_Host_stats::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Ui_Host_stats *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->populateListWidget(); break;
        case 1: _t->updateDiskUsage(); break;
        case 2: _t->updateCpuUsage((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 3: _t->updateMemUsage((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Ui_Host_stats::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Ui_Host_stats.data,
    qt_meta_data_Ui_Host_stats,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ui_Host_stats::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui_Host_stats::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ui_Host_stats.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Ui_Host_stats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
