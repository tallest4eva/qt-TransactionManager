//******************************************************************************
//
//  HEADER NAME: Month.h
//******************************************************************************

#ifndef Month_H
#define Month_H

#include <QDate>
#include <QList>
#include <QString>

#include "Account.h"
#include "Transaction.h"

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

    // Functions
    explicit Month();
    virtual ~Month();

    QDate getDate() const { return mDate; }
    void  setDate( QDate aDate ){ mDate.setDate( aDate.year(), aDate.month(), 1 ); mDateString = mDate.toString("MMM dd yyyy"); }

    float getIncome() const { return mIncome; }
    void  setIncome( float aIncome ){ mIncome = aIncome; }
    float getExpense() const { return mExpense; }
    void  setExpense( float aExpense ){ mExpense = aExpense; }
    bool  getNetWorth( Account* aAccount, float* aNetWorth ) const;
    void  addTransaction( Transaction* aTransaction );
    QList<Transaction*> getTransactionList(){ return mTransactionList; }
    void  updateData();

    // Comparators
    bool operator< ( const Month& aMonth ) const;
    bool operator> ( const Month& aMonth ) const;

    static bool addToMonth( const QDate& aDate, Transaction* aTransaction );

private:
    QDate mDate;
    // To do: Remove
    QString mDateString;
    float mIncome;
    float mExpense;
    QList<Transaction*> mTransactionList;
    QVector<NetWorthType> mNetWorthList;
};

#endif // Month_H
