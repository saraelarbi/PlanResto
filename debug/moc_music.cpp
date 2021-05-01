/****************************************************************************
** Meta object code from reading C++ file 'music.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../music.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'music.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_music_t {
    QByteArrayData data[11];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_music_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_music_t qt_meta_stringdata_music = {
    {
QT_MOC_LITERAL(0, 0, 5), // "music"
QT_MOC_LITERAL(1, 6, 17), // "on_ouvrir_clicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "on_play_clicked"
QT_MOC_LITERAL(4, 41, 16), // "on_pause_clicked"
QT_MOC_LITERAL(5, 58, 15), // "on_stop_clicked"
QT_MOC_LITERAL(6, 74, 15), // "on_mute_clicked"
QT_MOC_LITERAL(7, 90, 25), // "on_volume_actionTriggered"
QT_MOC_LITERAL(8, 116, 6), // "action"
QT_MOC_LITERAL(9, 123, 22), // "on_volume_valueChanged"
QT_MOC_LITERAL(10, 146, 5) // "value"

    },
    "music\0on_ouvrir_clicked\0\0on_play_clicked\0"
    "on_pause_clicked\0on_stop_clicked\0"
    "on_mute_clicked\0on_volume_actionTriggered\0"
    "action\0on_volume_valueChanged\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_music[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       9,    1,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void music::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        music *_t = static_cast<music *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_ouvrir_clicked(); break;
        case 1: _t->on_play_clicked(); break;
        case 2: _t->on_pause_clicked(); break;
        case 3: _t->on_stop_clicked(); break;
        case 4: _t->on_mute_clicked(); break;
        //case 5: _t->on_volume_actionTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_volume_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject music::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_music.data,
      qt_meta_data_music,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *music::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *music::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_music.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int music::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
