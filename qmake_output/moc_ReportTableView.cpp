/****************************************************************************
** Meta object code from reading C++ file 'ReportTableView.h'
**
** Created: Wed Aug 28 15:56:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TransactionManager/ReportTableView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReportTableView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReportTableView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   76,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ReportTableView[] = {
    "ReportTableView\0\0aFilter\0"
    "transactionFilterSelected(Transaction::FilterType)\0"
    "aIndex\0handleItemDoubleClicked(QModelIndex)\0"
};

void ReportTableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReportTableView *_t = static_cast<ReportTableView *>(_o);
        switch (_id) {
        case 0: _t->transactionFilterSelected((*reinterpret_cast< const Transaction::FilterType(*)>(_a[1]))); break;
        case 1: _t->handleItemDoubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ReportTableView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReportTableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_ReportTableView,
      qt_meta_data_ReportTableView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportTableView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportTableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportTableView))
        return static_cast<void*>(const_cast< ReportTableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int ReportTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ReportTableView::transactionFilterSelected(const Transaction::FilterType & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
