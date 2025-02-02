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
    QByteArrayData data[15];
    char stringdata0[185];
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
QT_MOC_LITERAL(4, 50, 9), // "used_disk"
QT_MOC_LITERAL(5, 60, 10), // "total_disk"
QT_MOC_LITERAL(6, 71, 14), // "updateCpuUsage"
QT_MOC_LITERAL(7, 86, 8), // "used_cpu"
QT_MOC_LITERAL(8, 95, 9), // "total_cpu"
QT_MOC_LITERAL(9, 105, 14), // "updateMemUsage"
QT_MOC_LITERAL(10, 120, 8), // "used_mem"
QT_MOC_LITERAL(11, 129, 9), // "total_mem"
QT_MOC_LITERAL(12, 139, 23), // "onListWidgetItemClicked"
QT_MOC_LITERAL(13, 163, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(14, 180, 4) // "item"

    },
    "Ui_Host_stats\0populateListWidget\0\0"
    "updateDiskUsage\0used_disk\0total_disk\0"
    "updateCpuUsage\0used_cpu\0total_cpu\0"
    "updateMemUsage\0used_mem\0total_mem\0"
    "onListWidgetItemClicked\0QListWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui_Host_stats[] = {

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
       1,    0,   39,    2, 0x0a /* Public */,
       3,    2,   40,    2, 0x0a /* Public */,
       6,    2,   45,    2, 0x0a /* Public */,
       9,    2,   50,    2, 0x0a /* Public */,
      12,    1,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    4,    5,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    7,    8,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void Ui_Host_stats::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Ui_Host_stats *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->populateListWidget(); break;
        case 1: _t->updateDiskUsage((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 2: _t->updateCpuUsage((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 3: _t->updateMemUsage((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 4: _t->onListWidgetItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
