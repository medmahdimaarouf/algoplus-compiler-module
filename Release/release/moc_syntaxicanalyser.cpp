/****************************************************************************
** Meta object code from reading C++ file 'syntaxicanalyser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AlgoPlus_Compilator/syntaxicanalyser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'syntaxicanalyser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SyntaxicAnalyser_t {
    QByteArrayData data[8];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SyntaxicAnalyser_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SyntaxicAnalyser_t qt_meta_stringdata_SyntaxicAnalyser = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 12),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 5),
QT_MOC_LITERAL(4, 37, 13),
QT_MOC_LITERAL(5, 51, 1),
QT_MOC_LITERAL(6, 53, 14),
QT_MOC_LITERAL(7, 68, 1)
    },
    "SyntaxicAnalyser\0Handle_Error\0\0ligne\0"
    "SyntaxicError\0e\0Handle_Warning\0w\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SyntaxicAnalyser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06,
       6,    2,   29,    2, 0x06,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    7,

       0        // eod
};

void SyntaxicAnalyser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SyntaxicAnalyser *_t = static_cast<SyntaxicAnalyser *>(_o);
        switch (_id) {
        case 0: _t->Handle_Error((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< SyntaxicError(*)>(_a[2]))); break;
        case 1: _t->Handle_Warning((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SyntaxicAnalyser::*_t)(const int , SyntaxicError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SyntaxicAnalyser::Handle_Error)) {
                *result = 0;
            }
        }
        {
            typedef void (SyntaxicAnalyser::*_t)(const int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SyntaxicAnalyser::Handle_Warning)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject SyntaxicAnalyser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SyntaxicAnalyser.data,
      qt_meta_data_SyntaxicAnalyser,  qt_static_metacall, 0, 0}
};


const QMetaObject *SyntaxicAnalyser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SyntaxicAnalyser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SyntaxicAnalyser.stringdata))
        return static_cast<void*>(const_cast< SyntaxicAnalyser*>(this));
    return QObject::qt_metacast(_clname);
}

int SyntaxicAnalyser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SyntaxicAnalyser::Handle_Error(const int _t1, SyntaxicError _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SyntaxicAnalyser::Handle_Warning(const int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
