//******************************************************************************
//
//  HEADER NAME: TransactionListModel.h
//******************************************************************************

#ifndef TransactionListModel_H
#define TransactionListModel_H

#include <QStandardItemModel>
#include <QList>
#include <QTableView>

#include "Transaction.h"

class NumberStandardItem : public QStandardItem
{
public:
    NumberStandardItem::NumberStandardItem() : mNumber(0.0f){}
    bool operator< ( const QStandardItem& other ) const;
    void setNumber( float aNumber );
private:
    float mNumber;
};

class TransactionListModel : public QStandardItemModel
{

public:
    // Types
    enum HeaderType
    {
        HDR_DATE,
        HDR_NAME,
        HDR_DESCRIPTION,
        HDR_AMOUNT,
        HDR_BALANCE,
        HDR_CATEGORY,
//        HDR_LABELS

        HDR_CNT
    };

    // Functions
    explicit TransactionListModel();
    ~TransactionListModel();
    void setTransactionList( QList<Transaction*>& aTransactionList );
    void setupTableView( QTableView* aTableView );
    void resort();

private:
    // Functions

    // Variables
    static const char* cHeaderList[];
    QList<Transaction*> mTransactionList;
    QTableView* mTableView;
};

#endif // TransactionListModel_H
