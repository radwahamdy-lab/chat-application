/****************************************************************************
** Meta object code from reading C++ file 'ClientSession.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../server/ClientSession.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientSession.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_ClientSession_t {
    uint offsetsAndSizes[24];
    char stringdata0[14];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[4];
    char stringdata5[20];
    char stringdata6[7];
    char stringdata7[21];
    char stringdata8[18];
    char stringdata9[17];
    char stringdata10[17];
    char stringdata11[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ClientSession_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ClientSession_t qt_meta_stringdata_ClientSession = {
    {
        QT_MOC_LITERAL(0, 13),  // "ClientSession"
        QT_MOC_LITERAL(14, 11),  // "msgReceived"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 3),  // "Msg"
        QT_MOC_LITERAL(31, 3),  // "msg"
        QT_MOC_LITERAL(35, 19),  // "loginUpdateReceived"
        QT_MOC_LITERAL(55, 6),  // "status"
        QT_MOC_LITERAL(62, 20),  // "signupUpdateReceived"
        QT_MOC_LITERAL(83, 17),  // "usersListReceived"
        QT_MOC_LITERAL(101, 16),  // "msgsListReceived"
        QT_MOC_LITERAL(118, 16),  // "receiverNotFound"
        QT_MOC_LITERAL(135, 6)   // "string"
    },
    "ClientSession",
    "msgReceived",
    "",
    "Msg",
    "msg",
    "loginUpdateReceived",
    "status",
    "signupUpdateReceived",
    "usersListReceived",
    "msgsListReceived",
    "receiverNotFound",
    "string"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ClientSession[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       5,    1,   53,    2, 0x06,    3 /* Public */,
       7,    1,   56,    2, 0x06,    5 /* Public */,
       8,    1,   59,    2, 0x06,    7 /* Public */,
       9,    2,   62,    2, 0x06,    9 /* Public */,
      10,    1,   67,    2, 0x06,   12 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 11,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject ClientSession::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ClientSession.offsetsAndSizes,
    qt_meta_data_ClientSession,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ClientSession_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ClientSession, std::true_type>,
        // method 'msgReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Msg, std::false_type>,
        // method 'loginUpdateReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'signupUpdateReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'usersListReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Msg, std::false_type>,
        // method 'msgsListReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'receiverNotFound'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<string, std::false_type>
    >,
    nullptr
} };

void ClientSession::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientSession *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->msgReceived((*reinterpret_cast< std::add_pointer_t<Msg>>(_a[1]))); break;
        case 1: _t->loginUpdateReceived((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->signupUpdateReceived((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->usersListReceived((*reinterpret_cast< std::add_pointer_t<Msg>>(_a[1]))); break;
        case 4: _t->msgsListReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->receiverNotFound((*reinterpret_cast< std::add_pointer_t<string>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Msg >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Msg >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientSession::*)(Msg );
            if (_t _q_method = &ClientSession::msgReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientSession::*)(bool );
            if (_t _q_method = &ClientSession::loginUpdateReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientSession::*)(bool );
            if (_t _q_method = &ClientSession::signupUpdateReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ClientSession::*)(Msg );
            if (_t _q_method = &ClientSession::usersListReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ClientSession::*)(QString , QString );
            if (_t _q_method = &ClientSession::msgsListReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ClientSession::*)(string );
            if (_t _q_method = &ClientSession::receiverNotFound; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *ClientSession::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientSession::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientSession.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientSession::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ClientSession::msgReceived(Msg _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientSession::loginUpdateReceived(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientSession::signupUpdateReceived(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientSession::usersListReceived(Msg _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClientSession::msgsListReceived(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientSession::receiverNotFound(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
