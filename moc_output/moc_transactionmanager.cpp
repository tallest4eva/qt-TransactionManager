/****************************************************************************
** Meta object code from reading C++ file 'TransactionManager.h'
**
** Created: Fri Apr 5 16:45:42 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TransactionManager/TransactionManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TransactionManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TransactionManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      46,   19,   19,   19, 0x08,
      72,   19,   19,   19, 0x08,
      98,   19,   19,   19, 0x08,
     125,   19,   19,   19, 0x08,
     162,   19,   19,   19, 0x08,
     189,   19,   19,   19, 0x08,
     222,   19,   19,   19, 0x08,
     260,  254,   19,   19, 0x08,
     319,   19,   19,   19, 0x08,
     356,   19,   19,   19, 0x08,
     388,   19,   19,   19, 0x08,
     431,   19,   19,   19, 0x08,
     471,   19,   19,   19, 0x08,
     511,   19,   19,   19, 0x08,
     552,   19,   19,   19, 0x08,
     594,   19,   19,   19, 0x08,
     628,   19,   19,   19, 0x08,
     666,   19,   19,   19, 0x08,
     701,   19,   19,   19, 0x08,
     736,   19,   19,   19, 0x08,
     772,   19,   19,   19, 0x08,
     809,   19,   19,   19, 0x08,
     847,  838,   19,   19, 0x08,
     895,  838,   19,   19, 0x08,
     944,  838,   19,   19, 0x08,
     994,  838,   19,   19, 0x08,
    1047,  838,   19,   19, 0x08,
    1101,  838,   19,   19, 0x08,
    1147,  838,   19,   19, 0x08,
    1190,  838,   19,   19, 0x08,
    1234,  838,   19,   19, 0x08,
    1279,  838,   19,   19, 0x08,
    1327,  838,   19,   19, 0x08,
    1376,  838,   19,   19, 0x08,
    1425, 1417,   19,   19, 0x08,
    1500, 1480,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TransactionManager[] = {
    "TransactionManager\0\0on_actionExit_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionClose_triggered()\0"
    "on_actionFileInputConfig_triggered()\0"
    "on_actionAbout_triggered()\0"
    "on_actionDisplayFile_triggered()\0"
    "on_actionDisplayLog_triggered()\0aItem\0"
    "on_overviewAccountList_itemDoubleClicked(QListWidgetItem*)\0"
    "on_transactionSelectButton_clicked()\0"
    "on_reportSelectButton_clicked()\0"
    "on_transactionDateThisYearButton_clicked()\0"
    "on_transactionDate1YearButton_clicked()\0"
    "on_transactionDate5YearButton_clicked()\0"
    "on_transactionDate10YearButton_clicked()\0"
    "on_transactionDateAllTimeButton_clicked()\0"
    "on_transactionAllButton_clicked()\0"
    "on_reportDateThisYearButton_clicked()\0"
    "on_reportDate1YearButton_clicked()\0"
    "on_reportDate5YearButton_clicked()\0"
    "on_reportDate10YearButton_clicked()\0"
    "on_reportDateAllTimeButton_clicked()\0"
    "on_reportAllButton_clicked()\0aChecked\0"
    "on_transactionAllAccountsCheckBox_clicked(bool)\0"
    "on_transactionOpenAccountsCheckBox_clicked(bool)\0"
    "on_transactionAllCategoriesCheckBox_clicked(bool)\0"
    "on_transactionIncomeCategoriesCheckBox_clicked(bool)\0"
    "on_transactionExpenseCategoriesCheckBox_clicked(bool)\0"
    "on_transactionAllLabelsCheckBox_clicked(bool)\0"
    "on_reportAllAccountsCheckBox_clicked(bool)\0"
    "on_reportOpenAccountsCheckBox_clicked(bool)\0"
    "on_reportAllCategoriesCheckBox_clicked(bool)\0"
    "on_reportIncomeCategoriesCheckBox_clicked(bool)\0"
    "on_reportExpenseCategoriesCheckBox_clicked(bool)\0"
    "on_reportAllLabelsCheckBox_clicked(bool)\0"
    "aFilter\0handleShowTransactionByFilter(Transaction::FilterType)\0"
    "aStartDate,aEndDate\0"
    "handleShowReportByDate(QDate,QDate)\0"
};

void TransactionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TransactionManager *_t = static_cast<TransactionManager *>(_o);
        switch (_id) {
        case 0: _t->on_actionExit_triggered(); break;
        case 1: _t->on_actionOpen_triggered(); break;
        case 2: _t->on_actionSave_triggered(); break;
        case 3: _t->on_actionClose_triggered(); break;
        case 4: _t->on_actionFileInputConfig_triggered(); break;
        case 5: _t->on_actionAbout_triggered(); break;
        case 6: _t->on_actionDisplayFile_triggered(); break;
        case 7: _t->on_actionDisplayLog_triggered(); break;
        case 8: _t->on_overviewAccountList_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->on_transactionSelectButton_clicked(); break;
        case 10: _t->on_reportSelectButton_clicked(); break;
        case 11: _t->on_transactionDateThisYearButton_clicked(); break;
        case 12: _t->on_transactionDate1YearButton_clicked(); break;
        case 13: _t->on_transactionDate5YearButton_clicked(); break;
        case 14: _t->on_transactionDate10YearButton_clicked(); break;
        case 15: _t->on_transactionDateAllTimeButton_clicked(); break;
        case 16: _t->on_transactionAllButton_clicked(); break;
        case 17: _t->on_reportDateThisYearButton_clicked(); break;
        case 18: _t->on_reportDate1YearButton_clicked(); break;
        case 19: _t->on_reportDate5YearButton_clicked(); break;
        case 20: _t->on_reportDate10YearButton_clicked(); break;
        case 21: _t->on_reportDateAllTimeButton_clicked(); break;
        case 22: _t->on_reportAllButton_clicked(); break;
        case 23: _t->on_transactionAllAccountsCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->on_transactionOpenAccountsCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->on_transactionAllCategoriesCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->on_transactionIncomeCategoriesCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->on_transactionExpenseCategoriesCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_transactionAllLabelsCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->on_reportAllAccountsCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->on_reportOpenAccountsCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->on_reportAllCategoriesCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->on_reportIncomeCategoriesCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->on_reportExpenseCategoriesCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->on_reportAllLabelsCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->handleShowTransactionByFilter((*reinterpret_cast< const Transaction::FilterType(*)>(_a[1]))); break;
        case 36: _t->handleShowReportByDate((*reinterpret_cast< QDate(*)>(_a[1])),(*reinterpret_cast< QDate(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TransactionManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TransactionManager::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TransactionManager,
      qt_meta_data_TransactionManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TransactionManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TransactionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TransactionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TransactionManager))
        return static_cast<void*>(const_cast< TransactionManager*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TransactionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
