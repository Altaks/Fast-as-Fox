/****************************************************************************
** Meta object code from reading C++ file 'level.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../FastAsFox/FastAsFoxGame/level.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'level.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSLevelENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSLevelENDCLASS = QtMocHelpers::stringData(
    "Level",
    "updateLCD",
    "",
    "changeHedgehogsDirection",
    "playerCollidesHedgehog",
    "levelOverByDeath",
    "handleCoinCollected",
    "finish",
    "getLcdCount",
    "std::string"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSLevelENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[6];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[23];
    char stringdata5[17];
    char stringdata6[20];
    char stringdata7[7];
    char stringdata8[12];
    char stringdata9[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSLevelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSLevelENDCLASS_t qt_meta_stringdata_CLASSLevelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 5),  // "Level"
        QT_MOC_LITERAL(6, 9),  // "updateLCD"
        QT_MOC_LITERAL(16, 0),  // ""
        QT_MOC_LITERAL(17, 24),  // "changeHedgehogsDirection"
        QT_MOC_LITERAL(42, 22),  // "playerCollidesHedgehog"
        QT_MOC_LITERAL(65, 16),  // "levelOverByDeath"
        QT_MOC_LITERAL(82, 19),  // "handleCoinCollected"
        QT_MOC_LITERAL(102, 6),  // "finish"
        QT_MOC_LITERAL(109, 11),  // "getLcdCount"
        QT_MOC_LITERAL(121, 11)   // "std::string"
    },
    "Level",
    "updateLCD",
    "",
    "changeHedgehogsDirection",
    "playerCollidesHedgehog",
    "levelOverByDeath",
    "handleCoinCollected",
    "finish",
    "getLcdCount",
    "std::string"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLevelENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x0a,    6 /* Public */,
       8,    0,   62,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 9,

       0        // eod
};

Q_CONSTINIT const QMetaObject Level::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSLevelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLevelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLevelENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Level, std::true_type>,
        // method 'updateLCD'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeHedgehogsDirection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playerCollidesHedgehog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'levelOverByDeath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleCoinCollected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'finish'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getLcdCount'
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>
    >,
    nullptr
} };

void Level::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Level *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateLCD(); break;
        case 1: _t->changeHedgehogsDirection(); break;
        case 2: _t->playerCollidesHedgehog(); break;
        case 3: _t->levelOverByDeath(); break;
        case 4: _t->handleCoinCollected(); break;
        case 5: _t->finish(); break;
        case 6: { std::string _r = _t->getLcdCount();
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *Level::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Level::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLevelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Level::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
