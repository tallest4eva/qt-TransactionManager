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
    float income = 0.0;
    if( aFilter.mAllAccounts && aFilter.mAllCategories && aFilter.mAllLabels && aFilter.mAllDates )
    {
        return mIncome;
    }
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        Transaction* transaction = mTransactionList[i];
        if( transaction->getAmount() >= 0 && transaction->matchTransaction( aFilter ) )
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
    float expense = 0.0;
    if( aFilter.mAllAccounts && aFilter.mAllCategories && aFilter.mAllLabels && aFilter.mAllDates )
    {
        return mExpense;
    }
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        Transaction* transaction = mTransactionList[i];
        if( transaction->getAmount() < 0 && transaction->matchTransaction( aFilter ) )
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
    float netWorth = 0.0;
    int idx = 0;
    for( int i = 0; i < mNetWorthList.size(); i++ )
    {
        if( mNetWorthList[i].mAccount == aFilter.mAccountList[idx] )
        {
            netWorth += mNetWorthList[i].mNetWorth;
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
            if( aPreviousMonth->mNetWorthList[i].mAccount )
            {
                mNetWorthList[i].mAccount = aPreviousMonth->mNetWorthList[i].mAccount;
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
            Category::CategoryIdType category = transaction->getCategory();
            switch( category )
            {
            case Category::TRANSFER:
            case Category::CREDIT_CARD_PAYMENT:
            case Category::FAMILY_TRANSFER:
            case Category::TRANSFER_FOR_CASH_SPENDING:
            case Category::ACCOUNT_BALANCE:
                continue;
            default:
                break;
            }
            if( transaction->getAmount() >= 0 )
            {
                mIncome += transaction->getAmount();
            }
            else
            {
                mExpense += transaction->getAmount();
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
            Month* month = TransactionManager::mMonthList[i];
            TransactionManager::mMonthList[i]->updateData( (i > 0) ? TransactionManager::mMonthList[i-1]: NULL );
        }
    }
} // Month::updateMonthList

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

