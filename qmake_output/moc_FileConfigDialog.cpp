/****************************************************************************
** Meta object code from reading C++ file 'FileConfigDialog.h'
**
** Created: Tue Dec 3 12:55:51 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TransactionManager/FileConfigDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileConfigDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileConfigDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      50,   41,   17,   17, 0x08,
      81,   17,   17,   17, 0x08,
     102,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FileConfigDialog[] = {
    "FileConfigDialog\0\0handlePresetSelected()\0"
    "aChecked\0handleTransactionClicked(bool)\0"
    "handleCancelButton()\0handleDoneButton()\0"
};

void FileConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileConfigDialog *_t = static_cast<FileConfigDialog *>(_o);
        switch (_id) {
        case 0: _t->handlePresetSelected(); break;
        case 1: _t->handleTransactionClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->handleCancelButton(); break;
        case 3: _t->handleDoneButton(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileConfigDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FileConfigDialog,
      qt_meta_data_FileConfigDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileConfigDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileConfigDialog))
        return static_cast<void*>(const_cast< FileConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int FileConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
