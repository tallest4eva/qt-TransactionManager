//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: TransactionList.h
//******************************************************************************

#ifndef TransactionList_HPP
#define TransactionList_HPP

#include <QStandardItemModel>
#include <QList>
#include <QTableView>

#include "Transaction.hpp"

// Custom Number and Dat Standard Items
class NumberStandardItem : public QStandardItem
{
public:
    NumberStandardItem() : mNumber(0.0f){}
    bool operator< ( const QStandardItem& other ) const;
    void setNumber( float aNumber );
private:
    float mNumber;
};

class DateStandardItem : public QStandardItem
{
public:
    DateStandardItem(){}
    bool operator< ( const QStandardItem& other ) const;
    void setDate( const QDate& aDate, const QString& aFormat );
private:
    QDate mDate;
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
    float getTotalCredit() const { return mTotalCredit; }
    float getTotalDebit() const { return mTotalDebit; }
    float getNetAmount() const { return mTotalNet; }
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void setupTableView( QTableView* aTableView );
    void resort();
    void clear();

private:
    // Functions

    // Variables
    QStandardItemModel* mModel;
    QList<Transaction*> mTransactionList;
    float mTotalCredit;
    float mTotalDebit;
    float mTotalNet;

    static const char* cHeaderList[];
};

#endif // TransactionList_HPP
