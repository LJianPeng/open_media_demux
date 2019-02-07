/****************************************************************************
** Meta object code from reading C++ file 'sp_media_parser_qt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sp_media_parser_qt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sp_media_parser_qt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SPas_t {
    QByteArrayData data[19];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SPas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SPas_t qt_meta_stringdata_SPas = {
    {
QT_MOC_LITERAL(0, 0, 4), // "SPas"
QT_MOC_LITERAL(1, 5, 16), // "sp_about_msg_btn"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 21), // "sp_parser_stream_info"
QT_MOC_LITERAL(4, 45, 19), // "sp_show_binary_text"
QT_MOC_LITERAL(5, 65, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(6, 83, 4), // "item"
QT_MOC_LITERAL(7, 88, 21), // "sp_display_binary_hex"
QT_MOC_LITERAL(8, 110, 50), // "on_FrameListTableWidget_custo..."
QT_MOC_LITERAL(9, 161, 3), // "pos"
QT_MOC_LITERAL(10, 165, 16), // "sp_parser_packet"
QT_MOC_LITERAL(11, 182, 16), // "AVFormatContext*"
QT_MOC_LITERAL(12, 199, 7), // "fmt_ctx"
QT_MOC_LITERAL(13, 207, 15), // "AVCodecContext*"
QT_MOC_LITERAL(14, 223, 13), // "pCodecContext"
QT_MOC_LITERAL(15, 237, 21), // "AVCodecParserContext*"
QT_MOC_LITERAL(16, 259, 14), // "pParserContext"
QT_MOC_LITERAL(17, 274, 9), // "AVPacket*"
QT_MOC_LITERAL(18, 284, 3) // "pkt"

    },
    "SPas\0sp_about_msg_btn\0\0sp_parser_stream_info\0"
    "sp_show_binary_text\0QTableWidgetItem*\0"
    "item\0sp_display_binary_hex\0"
    "on_FrameListTableWidget_customContextMenuRequested\0"
    "pos\0sp_parser_packet\0AVFormatContext*\0"
    "fmt_ctx\0AVCodecContext*\0pCodecContext\0"
    "AVCodecParserContext*\0pParserContext\0"
    "AVPacket*\0pkt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SPas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x0a /* Public */,
       7,    1,   49,    2, 0x0a /* Public */,
       8,    1,   52,    2, 0x0a /* Public */,
      10,    4,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Int, 0x80000000 | 11, 0x80000000 | 13, 0x80000000 | 15, 0x80000000 | 17,   12,   14,   16,   18,

       0        // eod
};

void SPas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SPas *_t = static_cast<SPas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sp_about_msg_btn(); break;
        case 1: _t->sp_parser_stream_info(); break;
        case 2: _t->sp_show_binary_text((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->sp_display_binary_hex((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->on_FrameListTableWidget_customContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 5: { int _r = _t->sp_parser_packet((*reinterpret_cast< AVFormatContext*(*)>(_a[1])),(*reinterpret_cast< AVCodecContext*(*)>(_a[2])),(*reinterpret_cast< AVCodecParserContext*(*)>(_a[3])),(*reinterpret_cast< AVPacket*(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject SPas::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SPas.data,
      qt_meta_data_SPas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SPas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SPas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SPas.stringdata0))
        return static_cast<void*>(const_cast< SPas*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SPas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
