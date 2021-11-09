/****************************************************************************
** Meta object code from reading C++ file 'whatsprogmain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../WhatsProg_interface/whatsprogmain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'whatsprogmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WhatsProgMain_t {
    QByteArrayData data[20];
    char stringdata0[419];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WhatsProgMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WhatsProgMain_t qt_meta_stringdata_WhatsProgMain = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WhatsProgMain"
QT_MOC_LITERAL(1, 14, 31), // "on_actionNovo_usuario_triggered"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 36), // "on_actionUsuario_existente_tr..."
QT_MOC_LITERAL(4, 84, 30), // "on_actionDesconectar_triggered"
QT_MOC_LITERAL(5, 115, 23), // "on_actionSair_triggered"
QT_MOC_LITERAL(6, 139, 31), // "on_tableConversas_cellActivated"
QT_MOC_LITERAL(7, 171, 3), // "row"
QT_MOC_LITERAL(8, 175, 6), // "column"
QT_MOC_LITERAL(9, 182, 29), // "on_tableConversas_cellClicked"
QT_MOC_LITERAL(10, 212, 33), // "on_lineEditMensagem_returnPre..."
QT_MOC_LITERAL(11, 246, 32), // "on_actionNova_conversa_triggered"
QT_MOC_LITERAL(12, 279, 35), // "on_actionRemover_conversa_tri..."
QT_MOC_LITERAL(13, 315, 35), // "on_actionApagar_mensagens_tri..."
QT_MOC_LITERAL(14, 351, 16), // "slotCriarUsuario"
QT_MOC_LITERAL(15, 368, 2), // "ip"
QT_MOC_LITERAL(16, 371, 7), // "usuario"
QT_MOC_LITERAL(17, 379, 5), // "senha"
QT_MOC_LITERAL(18, 385, 16), // "slotLogarUsuario"
QT_MOC_LITERAL(19, 402, 16) // "slotNovaConversa"

    },
    "WhatsProgMain\0on_actionNovo_usuario_triggered\0"
    "\0on_actionUsuario_existente_triggered\0"
    "on_actionDesconectar_triggered\0"
    "on_actionSair_triggered\0"
    "on_tableConversas_cellActivated\0row\0"
    "column\0on_tableConversas_cellClicked\0"
    "on_lineEditMensagem_returnPressed\0"
    "on_actionNova_conversa_triggered\0"
    "on_actionRemover_conversa_triggered\0"
    "on_actionApagar_mensagens_triggered\0"
    "slotCriarUsuario\0ip\0usuario\0senha\0"
    "slotLogarUsuario\0slotNovaConversa"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WhatsProgMain[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    2,   83,    2, 0x0a /* Public */,
       9,    2,   88,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    0,   95,    2, 0x0a /* Public */,
      13,    0,   96,    2, 0x0a /* Public */,
      14,    3,   97,    2, 0x0a /* Public */,
      18,    3,  104,    2, 0x0a /* Public */,
      19,    1,  111,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   15,   16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   15,   16,   17,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void WhatsProgMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WhatsProgMain *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionNovo_usuario_triggered(); break;
        case 1: _t->on_actionUsuario_existente_triggered(); break;
        case 2: _t->on_actionDesconectar_triggered(); break;
        case 3: _t->on_actionSair_triggered(); break;
        case 4: _t->on_tableConversas_cellActivated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->on_tableConversas_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->on_lineEditMensagem_returnPressed(); break;
        case 7: _t->on_actionNova_conversa_triggered(); break;
        case 8: _t->on_actionRemover_conversa_triggered(); break;
        case 9: _t->on_actionApagar_mensagens_triggered(); break;
        case 10: _t->slotCriarUsuario((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 11: _t->slotLogarUsuario((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 12: _t->slotNovaConversa((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WhatsProgMain::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_WhatsProgMain.data,
    qt_meta_data_WhatsProgMain,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WhatsProgMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WhatsProgMain::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WhatsProgMain.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int WhatsProgMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
