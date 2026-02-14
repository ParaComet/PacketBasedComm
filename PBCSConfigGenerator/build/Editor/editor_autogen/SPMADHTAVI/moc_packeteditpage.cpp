/****************************************************************************
** Meta object code from reading C++ file 'packeteditpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Editor/ui/windows/packeteditpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packeteditpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PBCS__PacketEditPage_t {
    QByteArrayData data[15];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PBCS__PacketEditPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PBCS__PacketEditPage_t qt_meta_stringdata_PBCS__PacketEditPage = {
    {
QT_MOC_LITERAL(0, 0, 20), // "PBCS::PacketEditPage"
QT_MOC_LITERAL(1, 21, 10), // "nameEdited"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 7), // "newName"
QT_MOC_LITERAL(4, 41, 14), // "nameEditFinish"
QT_MOC_LITERAL(5, 56, 8), // "IDEdited"
QT_MOC_LITERAL(6, 65, 8), // "newIDStr"
QT_MOC_LITERAL(7, 74, 12), // "IDEditFinish"
QT_MOC_LITERAL(8, 87, 9), // "upClicked"
QT_MOC_LITERAL(9, 97, 11), // "downClicked"
QT_MOC_LITERAL(10, 109, 15), // "dataNameChanged"
QT_MOC_LITERAL(11, 125, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(12, 143, 4), // "item"
QT_MOC_LITERAL(13, 148, 10), // "addClicked"
QT_MOC_LITERAL(14, 159, 13) // "deleteClicked"

    },
    "PBCS::PacketEditPage\0nameEdited\0\0"
    "newName\0nameEditFinish\0IDEdited\0"
    "newIDStr\0IDEditFinish\0upClicked\0"
    "downClicked\0dataNameChanged\0"
    "QTableWidgetItem*\0item\0addClicked\0"
    "deleteClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PBCS__PacketEditPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       4,    0,   62,    2, 0x08 /* Private */,
       5,    1,   63,    2, 0x08 /* Private */,
       7,    0,   66,    2, 0x08 /* Private */,
       8,    0,   67,    2, 0x08 /* Private */,
       9,    0,   68,    2, 0x08 /* Private */,
      10,    1,   69,    2, 0x08 /* Private */,
      13,    0,   72,    2, 0x08 /* Private */,
      14,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PBCS::PacketEditPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PacketEditPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->nameEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->nameEditFinish(); break;
        case 2: _t->IDEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->IDEditFinish(); break;
        case 4: _t->upClicked(); break;
        case 5: _t->downClicked(); break;
        case 6: _t->dataNameChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->addClicked(); break;
        case 8: _t->deleteClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PBCS::PacketEditPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PBCS__PacketEditPage.data,
    qt_meta_data_PBCS__PacketEditPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PBCS::PacketEditPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PBCS::PacketEditPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PBCS__PacketEditPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PBCS::PacketEditPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
