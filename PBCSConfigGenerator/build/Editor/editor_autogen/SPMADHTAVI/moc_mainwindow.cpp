/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Editor/ui/windows/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PBCS__MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PBCS__MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PBCS__MainWindow_t qt_meta_stringdata_PBCS__MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PBCS::MainWindow"
QT_MOC_LITERAL(1, 17, 8), // "openFile"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "saveFile"
QT_MOC_LITERAL(4, 36, 7), // "newFile"
QT_MOC_LITERAL(5, 44, 13), // "deletePressed"
QT_MOC_LITERAL(6, 58, 8), // "treeMenu"
QT_MOC_LITERAL(7, 67, 3), // "pos"
QT_MOC_LITERAL(8, 71, 14), // "packetMenuOpen"
QT_MOC_LITERAL(9, 86, 16), // "packetMenuDelete"
QT_MOC_LITERAL(10, 103, 20), // "packetMenuChangeType"
QT_MOC_LITERAL(11, 124, 21), // "pkttypeMenuChangeName"
QT_MOC_LITERAL(12, 146, 19), // "pkttypeMenuChangeID"
QT_MOC_LITERAL(13, 166, 23), // "pkttypeMenuChangeParent"
QT_MOC_LITERAL(14, 190, 20), // "pkttypeMenuNewPacket"
QT_MOC_LITERAL(15, 211, 24), // "pkttypeMenuNewPacketType"
QT_MOC_LITERAL(16, 236, 17), // "pkttypeMenuDelete"
QT_MOC_LITERAL(17, 254, 21), // "nullMenuNewPacketType"
QT_MOC_LITERAL(18, 276, 17), // "nullMenuNonTModOn"
QT_MOC_LITERAL(19, 294, 18) // "nullMenuNonTModOff"

    },
    "PBCS::MainWindow\0openFile\0\0saveFile\0"
    "newFile\0deletePressed\0treeMenu\0pos\0"
    "packetMenuOpen\0packetMenuDelete\0"
    "packetMenuChangeType\0pkttypeMenuChangeName\0"
    "pkttypeMenuChangeID\0pkttypeMenuChangeParent\0"
    "pkttypeMenuNewPacket\0pkttypeMenuNewPacketType\0"
    "pkttypeMenuDelete\0nullMenuNewPacketType\0"
    "nullMenuNonTModOn\0nullMenuNonTModOff"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PBCS__MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    1,  103,    2, 0x08 /* Private */,
       8,    0,  106,    2, 0x08 /* Private */,
       9,    0,  107,    2, 0x08 /* Private */,
      10,    0,  108,    2, 0x08 /* Private */,
      11,    0,  109,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    0,  115,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PBCS::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->saveFile(); break;
        case 2: _t->newFile(); break;
        case 3: _t->deletePressed(); break;
        case 4: _t->treeMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 5: _t->packetMenuOpen(); break;
        case 6: _t->packetMenuDelete(); break;
        case 7: _t->packetMenuChangeType(); break;
        case 8: _t->pkttypeMenuChangeName(); break;
        case 9: _t->pkttypeMenuChangeID(); break;
        case 10: _t->pkttypeMenuChangeParent(); break;
        case 11: _t->pkttypeMenuNewPacket(); break;
        case 12: _t->pkttypeMenuNewPacketType(); break;
        case 13: _t->pkttypeMenuDelete(); break;
        case 14: _t->nullMenuNewPacketType(); break;
        case 15: _t->nullMenuNonTModOn(); break;
        case 16: _t->nullMenuNonTModOff(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PBCS::MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_PBCS__MainWindow.data,
    qt_meta_data_PBCS__MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PBCS::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PBCS::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PBCS__MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PBCS::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
