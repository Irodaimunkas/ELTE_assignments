/****************************************************************************
** Meta object code from reading C++ file 'fightinghamsterrobots.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FightingHamsterRobots/fightinghamsterrobots.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fightinghamsterrobots.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FightingHamsterRobots_t {
    QByteArrayData data[11];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FightingHamsterRobots_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FightingHamsterRobots_t qt_meta_stringdata_FightingHamsterRobots = {
    {
QT_MOC_LITERAL(0, 0, 21), // "FightingHamsterRobots"
QT_MOC_LITERAL(1, 22, 13), // "keyPressEvent"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 10), // "QKeyEvent*"
QT_MOC_LITERAL(4, 48, 14), // "onPlayerOneWon"
QT_MOC_LITERAL(5, 63, 14), // "onPlayerTwoWon"
QT_MOC_LITERAL(6, 78, 6), // "onDraw"
QT_MOC_LITERAL(7, 85, 15), // "deleteLabelGrid"
QT_MOC_LITERAL(8, 101, 12), // "onKeyPressed"
QT_MOC_LITERAL(9, 114, 5), // "event"
QT_MOC_LITERAL(10, 120, 7) // "newGame"

    },
    "FightingHamsterRobots\0keyPressEvent\0"
    "\0QKeyEvent*\0onPlayerOneWon\0onPlayerTwoWon\0"
    "onDraw\0deleteLabelGrid\0onKeyPressed\0"
    "event\0newGame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FightingHamsterRobots[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void,

       0        // eod
};

void FightingHamsterRobots::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FightingHamsterRobots *_t = static_cast<FightingHamsterRobots *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->onPlayerOneWon(); break;
        case 2: _t->onPlayerTwoWon(); break;
        case 3: _t->onDraw(); break;
        case 4: _t->deleteLabelGrid(); break;
        case 5: _t->onKeyPressed((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 6: _t->newGame(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FightingHamsterRobots::*_t)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FightingHamsterRobots::keyPressEvent)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FightingHamsterRobots::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FightingHamsterRobots.data,
      qt_meta_data_FightingHamsterRobots,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FightingHamsterRobots::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FightingHamsterRobots::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FightingHamsterRobots.stringdata0))
        return static_cast<void*>(const_cast< FightingHamsterRobots*>(this));
    return QWidget::qt_metacast(_clname);
}

int FightingHamsterRobots::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void FightingHamsterRobots::keyPressEvent(QKeyEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
