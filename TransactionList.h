//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: TransactionList.h
//******************************************************************************

#ifndef TransactionList_H
#define TransactionList_H

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

class TransactionList : public QTableView
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
        HDR_LABELS,

        HDR_CNT
    };

    // Functions
    explicit TransactionList();
    ~TransactionList();
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void setupTableView( QTableView* aTableView );
    void resort();
    void clear();

private:
    // Functions

    // Variables
    QStandardItemModel* mModel;
    QList<Transaction*> mTransactionList;

    static const char* cHeaderList[];
};

#endif // TransactionList_H
