//******************************************************************************
//
//  HEADER NAME: Month.cpp
//******************************************************************************

#include <QDebug>

#include "Month.h"
#include "TransactionManager.h"

// Static functions
static bool monthSortLessThan( Month* arg1, Month* &arg2 )
{
     return *arg1 < *arg2;
}
//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
Month::Month() :
      mDate( 2000, 1, 1 )
    , mIncome( 0.0 )
    , mExpense( 0.0 )
{
} // Month::Month

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
Month::~Month()
{
} // Month::~Month()

//----------------------------------------------------------------------------
// Operator
//----------------------------------------------------------------------------
bool Month::operator< ( const Month& aMonth ) const
{
    return( getDate() < aMonth.getDate() );
} // Month::operator<

//----------------------------------------------------------------------------
// Operator
//----------------------------------------------------------------------------
bool Month::operator> ( const Month& aMonth ) const
{
    return( getDate() > aMonth.getDate() );
} // Month::operator>

//----------------------------------------------------------------------------
//! Add Transaction
//----------------------------------------------------------------------------
void Month::addTransaction( Transaction* aTransaction )
{
    mTransactionList.push_back( aTransaction );
} // Month::addTransaction()

//----------------------------------------------------------------------------
//! getIncome
//----------------------------------------------------------------------------
float Month::getIncome( const Transaction::FilterType& aFilter ) const
{
    if( aFilter.mAllAccounts && aFilter.mAllCategories && aFilter.mAllLabels && aFilter.mAllDates )
    {
        return mIncome;
    }
    float income = 0.0;
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        Transaction* transaction = mTransactionList[i];
        if( transaction->getTransactionType() == Transaction::INCOME && transaction->matchTransaction( aFilter ) )
        {
            income += transaction->getAmount();
        }
    }
    return income;
} // Month::getIncome()

//----------------------------------------------------------------------------
//! getExpense
//----------------------------------------------------------------------------
float Month::getExpense( const Transaction::FilterType& aFilter ) const
{
    if( aFilter.mAllAccounts && aFilter.mAllCategories && aFilter.mAllLabels && aFilter.mAllDates )
    {
        return mExpense;
    }
    float expense = 0.0;
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        Transaction* transaction = mTransactionList[i];
        if( transaction->getTransactionType() == Transaction::EXPENSE && transaction->matchTransaction( aFilter ) )
        {
            expense += transaction->getAmount();
        }
    }
    return expense;
} // Month::getExpense()

//----------------------------------------------------------------------------
//! getNetWorth
//----------------------------------------------------------------------------
float Month::getNetWorth() const
{
    float netWorth = 0.0;
    for( int i = 0; i < mNetWorthList.size(); i++ )
    {
        netWorth += mNetWorthList[i].mNetWorth;
    }
    return netWorth;
} // Month::getNetWorth()

//----------------------------------------------------------------------------
//! getNetWorth
//----------------------------------------------------------------------------
float Month::getNetWorth( const Transaction::FilterType& aFilter ) const
{
    if( aFilter.mAllAccounts )
    {
        return getNetWorth();
    }
    float netWorth = 0.0;
    for( int i = 0; i < aFilter.mAccountList.size(); i++ )
    {
        int index = Account::getAccountIndex( aFilter.mAccountList[i] );
        if( index >= 0 && mNetWorthList[index].mAccount && aFilter.mAccountList[i] == mNetWorthList[index].mAccount  )
        {
            netWorth += mNetWorthList[index].mNetWorth;
        }
    }
    return netWorth;
} // Month::getNetWorth()
 
//----------------------------------------------------------------------------
//! getNetWorth
//----------------------------------------------------------------------------
float Month::getNetWorth( Account* aAccount, bool* aExist ) const
{
    if( aExist ){ *aExist = false; }
    float netWorth = 0;
    int index = Account::getAccountIndex( aAccount );
    if( index >= 0 && mNetWorthList[index].mAccount == aAccount )
    {
        netWorth = mNetWorthList[index].mNetWorth;
        if( aExist ){ *aExist = true; }
    }
    return netWorth;
} // Month::getNetWorth()

//----------------------------------------------------------------------------
//! Update data
//----------------------------------------------------------------------------
void Month::updateData( Month* aPreviousMonth )
{
    mNetWorthList.clear();
    mNetWorthList.fill( NetWorthType(), TransactionManager::mAccountList.size() );
    if( aPreviousMonth )
    {
        for( int i = 0; i < mNetWorthList.size(); i++ )
        {
            Account* prevAccount = aPreviousMonth->mNetWorthList[i].mAccount;
            if( prevAccount && prevAccount->getCloseDate() > mDate )
            {
                mNetWorthList[i].mAccount = prevAccount;
                mNetWorthList[i].mNetWorth = aPreviousMonth->mNetWorthList[i].mNetWorth;
            }
        }
    }
    if( mTransactionList.size() > 0 )
    {
        qSort( mTransactionList.begin(), mTransactionList.end(), Transaction::transactionSortLessThan );
        for( int i = 0; i < mTransactionList.size(); i++ )
        {
            Transaction* transaction = mTransactionList[i];

            // Determine account net worth
            int index = Account::getAccountIndex( transaction->getAccount() );
            if( index >= 0 )
            {
                mNetWorthList[index].mAccount = transaction->getAccount();
                mNetWorthList[index].mNetWorth = transaction->getCurrentBalance();
            }

            // Skip excluded transfer categories
            Transaction::TransactionType transType = transaction->getTransactionType();
            switch( transType )
            {
            case Transaction::INCOME:
                mIncome += transaction->getAmount();
                break;
            case Transaction::EXPENSE:
                mExpense += transaction->getAmount();
                break;
            }
        }
     }
} // Month::updateData()

//----------------------------------------------------------------------------
// updateMonthList
//----------------------------------------------------------------------------
void Month::updateMonthList()
{
    if( TransactionManager::mMonthList.size() > 0 )
    {
        qSort( TransactionManager::mMonthList.begin(), TransactionManager::mMonthList.end(), monthSortLessThan );
        QDate date = TransactionManager::mMonthList[0]->getDate();
        for( QList<Month*>::iterator i = TransactionManager::mMonthList.begin(); i != TransactionManager::mMonthList.end(); i++ )
        {
            Month* month = *i;
            if( date < month->getDate() )
            {
                Month* newMonth = new Month();
                newMonth->setDate( date );
                i = TransactionManager::mMonthList.insert( i, newMonth );
            }
            date = date.addMonths(1);
        }


        for( int i = 0; i < TransactionManager::mMonthList.size(); i++ )
        {
            TransactionManager::mMonthList[i]->updateData( (i > 0) ? TransactionManager::mMonthList[i-1]: NULL );
        }
    }
} // Month::updateMonthList

//----------------------------------------------------------------------------
// getMonth
//----------------------------------------------------------------------------
Month* Month::getMonth( const QDate& aDate )
{
    Month* month = NULL;
    for( int i = 0; i < TransactionManager::mMonthList.size(); i++ )
    {
        QDate curDate = TransactionManager::mMonthList[i]->getDate();
        if( aDate.year() == curDate.year() && aDate.month() == curDate.month() )
        {
            month = TransactionManager::mMonthList[i];
            break;
        }
    }
    return month;
} // Month::getMonth
//----------------------------------------------------------------------------
// addToMonth
//----------------------------------------------------------------------------
bool Month::addToMonth
    (
    const QDate& aDate,
    Transaction* aTransaction
    )
{
    bool found = false;
    for( int i = TransactionManager::mMonthList.size()-1; i >= 0; --i )
    {
        Month* month = TransactionManager::mMonthList[i];
        if( aDate.year() == month->getDate().year() && aDate.month() == month->getDate().month() )
        {
            month->addTransaction( aTransaction );
            found = true;
            break;
        }
    }
    if( !found )
    {
        Month* month = new Month();
        month->setDate( QDate(aDate.year(), aDate.month(), 1) );
        month->addTransaction( aTransaction );
        TransactionManager::mMonthList.push_back( month );
        found = true;
    }
    return found;
} // Month::addToMonth

