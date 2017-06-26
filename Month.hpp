//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Month.h
//******************************************************************************

#ifndef Month_HPP
#define Month_HPP

#include <QDate>
#include <QList>
#include <QString>

#include "Account.hpp"
#include "Transaction.hpp"

class Month
{
public:
    // Types
    struct NetWorthType
    {
        Account* mAccount;
        float mNetWorth;
        NetWorthType(): mAccount(NULL), mNetWorth(0.0){}
    };
    struct DateIntervalType
    {
        QDate startDate;
        QDate endDate;
        DateIntervalType(): startDate(2000,1,1), endDate(2000,1,1){}
    };

    // Functions
    explicit Month();
    virtual ~Month();

    QDate getDate() const { return mDate; }
    void  setDate( const QDate& aDate ){ mDate.setDate( aDate.year(), aDate.month(), 1 ); mDateString = mDate.toString("MMM dd yyyy"); }

    float getIncome() const { return mIncome; }
    float getIncome( const Transaction::FilterType& aFilter ) const;
    void  setIncome( float aIncome ){ mIncome = aIncome; }
    float getExpense() const { return mExpense; }
    float getExpense( const Transaction::FilterType& aFilter ) const;
    void  setExpense( float aExpense ){ mExpense = aExpense; }
    float getTransfers() const { return mTransfers; }
    float getTransfers( const Transaction::FilterType& aFilter ) const;
    void  setTransfers( float aTransfers ){ mTransfers = aTransfers; }
    float getNetWorth() const;
    float getNetWorth( const Transaction::FilterType& aFilter ) const;
    float getNetWorth( Account* aAccount, bool* aExist = NULL ) const;
    void  addTransaction( Transaction* aTransaction );
    const QList<Transaction*>& getTransactionList() const { return mTransactionList; }
    void  updateData( Month* aPreviousMonth = NULL );

    // Comparators
    bool operator< ( const Month& aMonth ) const;
    bool operator> ( const Month& aMonth ) const;

    static void updateMonthList();
    static Month* getMonth( const QDate& aDate );
    static bool addToMonth( const QDate& aDate, Transaction* aTransaction );

private:
    QDate mDate;
    // To do: Remove
    QString mDateString;
    float mIncome;
    float mExpense;
    float mTransfers;
    QList<Transaction*> mTransactionList;
    QVector<NetWorthType> mNetWorthList;
};

#endif // Month_HPP
