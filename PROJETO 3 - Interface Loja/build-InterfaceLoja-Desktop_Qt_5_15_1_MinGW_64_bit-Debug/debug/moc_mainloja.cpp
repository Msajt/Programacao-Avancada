/****************************************************************************
** Meta object code from reading C++ file 'mainloja.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../InterfaceLoja/mainloja.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainloja.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainLoja_t {
    QByteArrayData data[21];
    char stringdata0[360];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainLoja_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainLoja_t qt_meta_stringdata_MainLoja = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MainLoja"
QT_MOC_LITERAL(1, 9, 33), // "on_livrosWidget_cellDoubleCli..."
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 3), // "row"
QT_MOC_LITERAL(4, 48, 6), // "column"
QT_MOC_LITERAL(5, 55, 30), // "on_cdsWidget_cellDoubleClicked"
QT_MOC_LITERAL(6, 86, 31), // "on_dvdsWidget_cellDoubleClicked"
QT_MOC_LITERAL(7, 118, 22), // "on_actionLer_triggered"
QT_MOC_LITERAL(8, 141, 25), // "on_actionSalvar_triggered"
QT_MOC_LITERAL(9, 167, 23), // "on_actionSair_triggered"
QT_MOC_LITERAL(10, 191, 31), // "on_actionIncluirLivro_triggered"
QT_MOC_LITERAL(11, 223, 28), // "on_actionIncluirCD_triggered"
QT_MOC_LITERAL(12, 252, 29), // "on_actionIncluirDVD_triggered"
QT_MOC_LITERAL(13, 282, 16), // "slotIncluirLivro"
QT_MOC_LITERAL(14, 299, 4), // "nome"
QT_MOC_LITERAL(15, 304, 5), // "preco"
QT_MOC_LITERAL(16, 310, 5), // "autor"
QT_MOC_LITERAL(17, 316, 13), // "slotIncluirCD"
QT_MOC_LITERAL(18, 330, 6), // "faixas"
QT_MOC_LITERAL(19, 337, 14), // "slotIncluirDVD"
QT_MOC_LITERAL(20, 352, 7) // "duracao"

    },
    "MainLoja\0on_livrosWidget_cellDoubleClicked\0"
    "\0row\0column\0on_cdsWidget_cellDoubleClicked\0"
    "on_dvdsWidget_cellDoubleClicked\0"
    "on_actionLer_triggered\0on_actionSalvar_triggered\0"
    "on_actionSair_triggered\0"
    "on_actionIncluirLivro_triggered\0"
    "on_actionIncluirCD_triggered\0"
    "on_actionIncluirDVD_triggered\0"
    "slotIncluirLivro\0nome\0preco\0autor\0"
    "slotIncluirCD\0faixas\0slotIncluirDVD\0"
    "duracao"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainLoja[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x08 /* Private */,
       5,    2,   79,    2, 0x08 /* Private */,
       6,    2,   84,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    3,   95,    2, 0x08 /* Private */,
      17,    3,  102,    2, 0x08 /* Private */,
      19,    3,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   20,

       0        // eod
};

void MainLoja::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainLoja *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_livrosWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_cdsWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->on_dvdsWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->on_actionLer_triggered(); break;
        case 4: _t->on_actionSalvar_triggered(); break;
        case 5: _t->on_actionSair_triggered(); break;
        case 6: _t->on_actionIncluirLivro_triggered(); break;
        case 7: _t->on_actionIncluirCD_triggered(); break;
        case 8: _t->on_actionIncluirDVD_triggered(); break;
        case 9: _t->slotIncluirLivro((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 10: _t->slotIncluirCD((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 11: _t->slotIncluirDVD((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainLoja::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainLoja.data,
    qt_meta_data_MainLoja,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainLoja::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainLoja::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainLoja.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainLoja::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
