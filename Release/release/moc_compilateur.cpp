/****************************************************************************
** Meta object code from reading C++ file 'compilateur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AlgoPlus_Compilator/compilateur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'compilateur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Compilateur_t {
    QByteArrayData data[13];
    char stringdata[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Compilateur_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Compilateur_t qt_meta_stringdata_Compilateur = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 8),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 16),
QT_MOC_LITERAL(4, 39, 5),
QT_MOC_LITERAL(5, 45, 10),
QT_MOC_LITERAL(6, 56, 7),
QT_MOC_LITERAL(7, 64, 7),
QT_MOC_LITERAL(8, 72, 19),
QT_MOC_LITERAL(9, 92, 18),
QT_MOC_LITERAL(10, 111, 22),
QT_MOC_LITERAL(11, 134, 9),
QT_MOC_LITERAL(12, 144, 11)
    },
    "Compilateur\0hasError\0\0CompilationError\0"
    "error\0hasWarning\0Warning\0warning\0"
    "CompilationFinished\0CompilationStarted\0"
    "CompilationInterrepted\0emitError\0"
    "emitWarning\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Compilateur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06,
       5,    1,   52,    2, 0x06,
       8,    0,   55,    2, 0x06,
       9,    0,   56,    2, 0x06,
      10,    0,   57,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      11,    1,   58,    2, 0x08,
      12,    1,   61,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Compilateur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Compilateur *_t = static_cast<Compilateur *>(_o);
        switch (_id) {
        case 0: _t->hasError((*reinterpret_cast< const CompilationError(*)>(_a[1]))); break;
        case 1: _t->hasWarning((*reinterpret_cast< const Warning(*)>(_a[1]))); break;
        case 2: _t->CompilationFinished(); break;
        case 3: _t->CompilationStarted(); break;
        case 4: _t->CompilationInterrepted(); break;
        case 5: _t->emitError((*reinterpret_cast< const CompilationError(*)>(_a[1]))); break;
        case 6: _t->emitWarning((*reinterpret_cast< const Warning(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Compilateur::*_t)(const CompilationError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Compilateur::hasError)) {
                *result = 0;
            }
        }
        {
            typedef void (Compilateur::*_t)(const Warning );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Compilateur::hasWarning)) {
                *result = 1;
            }
        }
        {
            typedef void (Compilateur::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Compilateur::CompilationFinished)) {
                *result = 2;
            }
        }
        {
            typedef void (Compilateur::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Compilateur::CompilationStarted)) {
                *result = 3;
            }
        }
        {
            typedef void (Compilateur::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Compilateur::CompilationInterrepted)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Compilateur::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Compilateur.data,
      qt_meta_data_Compilateur,  qt_static_metacall, 0, 0}
};


const QMetaObject *Compilateur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Compilateur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Compilateur.stringdata))
        return static_cast<void*>(const_cast< Compilateur*>(this));
    return QObject::qt_metacast(_clname);
}

int Compilateur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Compilateur::hasError(const CompilationError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Compilateur::hasWarning(const Warning _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Compilateur::CompilationFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Compilateur::CompilationStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Compilateur::CompilationInterrepted()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
