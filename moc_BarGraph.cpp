/****************************************************************************
** Meta object code from reading C++ file 'BarGraph.h'
**
** Created: Thu Mar 28 14:38:00 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TransactionManager/BarGraph.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BarGraph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DisplayLabel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DisplayLabel[] = {
    "DisplayLabel\0\0clicked()\0"
};

void DisplayLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DisplayLabel *_t = static_cast<DisplayLabel *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DisplayLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DisplayLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_DisplayLabel,
      qt_meta_data_DisplayLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DisplayLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DisplayLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DisplayLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayLabel))
        return static_cast<void*>(const_cast< DisplayLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int DisplayLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void DisplayLabel::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_BarGraph[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   10,    9,    9, 0x05,
      89,   69,    9,    9, 0x05,
     126,   69,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     158,    9,    9,    9, 0x08,
     177,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BarGraph[] = {
    "BarGraph\0\0aFilter\0"
    "transactionFilterSelected(Transaction::FilterType)\0"
    "aStartDate,aEndDate\0"
    "transactionDateSelected(QDate,QDate)\0"
    "reportDateSelected(QDate,QDate)\0"
    "hideDisplayLabel()\0handleDisplayClicked()\0"
};

void BarGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BarGraph *_t = static_cast<BarGraph *>(_o);
        switch (_id) {
        case 0: _t->transactionFilterSelected((*reinterpret_cast< const Transaction::FilterType(*)>(_a[1]))); break;
        case 1: _t->transactionDateSelected((*reinterpret_cast< QDate(*)>(_a[1])),(*reinterpret_cast< QDate(*)>(_a[2]))); break;
        case 2: _t->reportDateSelected((*reinterpret_cast< QDate(*)>(_a[1])),(*reinterpret_cast< QDate(*)>(_a[2]))); break;
        case 3: _t->hideDisplayLabel(); break;
        case 4: _t->handleDisplayClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BarGraph::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BarGraph::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BarGraph,
      qt_meta_data_BarGraph, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BarGraph::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BarGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BarGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BarGraph))
        return static_cast<void*>(const_cast< BarGraph*>(this));
    return QWidget::qt_metacast(_clname);
}

int BarGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void BarGraph::transactionFilterSelected(const Transaction::FilterType & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BarGraph::transactionDateSelected(QDate _t1, QDate _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BarGraph::reportDateSelected(QDate _t1, QDate _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
