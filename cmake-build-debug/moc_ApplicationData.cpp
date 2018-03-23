/****************************************************************************
** Meta object code from reading C++ file 'ApplicationData.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ApplicationData.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ApplicationData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApplicationData_t {
    QByteArrayData data[9];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApplicationData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApplicationData_t qt_meta_stringdata_ApplicationData = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ApplicationData"
QT_MOC_LITERAL(1, 16, 15), // "progressStarted"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 15), // "progressNewStep"
QT_MOC_LITERAL(4, 49, 8), // "stepName"
QT_MOC_LITERAL(5, 58, 14), // "subStepsNumber"
QT_MOC_LITERAL(6, 73, 14), // "progressUpdate"
QT_MOC_LITERAL(7, 88, 14), // "currentSubStep"
QT_MOC_LITERAL(8, 103, 15) // "progressStopped"

    },
    "ApplicationData\0progressStarted\0\0"
    "progressNewStep\0stepName\0subStepsNumber\0"
    "progressUpdate\0currentSubStep\0"
    "progressStopped"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApplicationData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    2,   35,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,
       8,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void ApplicationData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ApplicationData *_t = static_cast<ApplicationData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->progressStarted(); break;
        case 1: _t->progressNewStep((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: _t->progressUpdate((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->progressStopped(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ApplicationData::*_t)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApplicationData::progressStarted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ApplicationData::*_t)(const QString , const int ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApplicationData::progressNewStep)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ApplicationData::*_t)(const int ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApplicationData::progressUpdate)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ApplicationData::*_t)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApplicationData::progressStopped)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ApplicationData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ApplicationData.data,
      qt_meta_data_ApplicationData,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ApplicationData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApplicationData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApplicationData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ApplicationData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void ApplicationData::progressStarted()const
{
    QMetaObject::activate(const_cast< ApplicationData *>(this), &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ApplicationData::progressNewStep(const QString _t1, const int _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(const_cast< ApplicationData *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ApplicationData::progressUpdate(const int _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< ApplicationData *>(this), &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ApplicationData::progressStopped()const
{
    QMetaObject::activate(const_cast< ApplicationData *>(this), &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
