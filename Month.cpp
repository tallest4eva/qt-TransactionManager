//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Month.cpp
//******************************************************************************

#include "Month.hpp"
#include "TransactionManager.hpp"

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
    , mTransfers( 0.0 )
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
    if( aFilter.allSelected() )
    {
        return mIncome;
    }
    float income = 0.0;
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        Transaction* transaction = mTransactionList[i];
        if( transaction->getTransactionType() == Category::TRANSACTION_TYPE_INCOME && transaction->matchTransaction( aFilter ) )
        {
            income += transaction->getAmount();
        }
    }
    return income;
} // Month::getIncome()

//----------------------------------------------------------------------------
//! Get Expense
//----------------------------------------------------------------------------
float Month::getExpense( const Transaction::FilterType& aFilter ) const
{
    if( aFilter.allSelected() )
    {
        return mExpense;
    }
    float expense = 0.0;
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        Transaction* transaction = mTransactionList[i];
        if( transaction->getTransactionType() == Category::TRANSACTION_TYPE_EXPENSE && transaction->matchTransaction( aFilter ) )
        {
            expense += transaction->getAmount();
        }
    }
    return expense;
} // Month::getExpense()

//----------------------------------------------------------------------------
//! Get Transfer
//----------------------------------------------------------------------------
float Month::getTransfers( const Transaction::FilterType& aFilter ) const
{
    if( aFilter.allSelected() )
    {
        return mTransfers;
    }
    float transfers = 0.0;
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        Transaction* transaction = mTransactionList[i];
        if( transaction->getTransactionType() == Category::TRANSACTION_TYPE_TRANSFER && transaction->matchTransaction( aFilter ) )
        {
            transfers += transaction->getAmount();
        }
    }
    return transfers;
} // Month::getTransfers()

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
    if( aFilter.allAccountsSelected() )
    {
        return getNetWorth();
    }
    float netWorth = 0.0;
    for( int i = 0; i < aFilter.mAccountList.size() && i < Account::sAccountList.size(); i++ )
    {
        if( aFilter.mAccountList[i] )
        {
            if( mNetWorthList[i].mAccount && Account::sAccountList[i] == mNetWorthList[i].mAccount )
            {
                netWorth += mNetWorthList[i].mNetWorth;
            }
        }
    }
    return netWorth;
} // Month::getNetWorth()

//----------------------------------------------------------------------------
//! Get Account Balance on this month
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
    mNetWorthList.fill( NetWorthType(), Account::sAccountList.size() );
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
            Category::TransactionType transType = transaction->getTransactionType();
            switch( transType )
            {
            case Category::TRANSACTION_TYPE_INCOME:
                mIncome += transaction->getAmount();
                break;
            case Category::TRANSACTION_TYPE_EXPENSE:
                mExpense += transaction->getAmount();
                break;
            case Category::TRANSACTION_TYPE_TRANSFER:
                mTransfers += transaction->getAmount();
                break;
            default:
                // do nothing
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
    if( TransactionManager::sMonthList.size() > 0 )
    {
        // Sort month list
        qSort( TransactionManager::sMonthList.begin(), TransactionManager::sMonthList.end(), monthSortLessThan );

        // Insert missing months
        QDate date = TransactionManager::sMonthList[0]->getDate();
        for( QList<Month*>::iterator i = TransactionManager::sMonthList.begin(); i != TransactionManager::sMonthList.end(); i++ )
        {
            Month* month = *i;
            if( date < month->getDate() )
            {
                Month* newMonth = new Month();
                newMonth->setDate( date );
                i = TransactionManager::sMonthList.insert( i, newMonth );
            }
            date = date.addMonths(1);
        }

        // Update month info
        for( int i = 0; i < TransactionManager::sMonthList.size(); i++ )
        {
            TransactionManager::sMonthList[i]->updateData( (i > 0) ? TransactionManager::sMonthList[i-1]: NULL );
        }
    }
} // Month::updateMonthList

//----------------------------------------------------------------------------
// getMonth
//----------------------------------------------------------------------------
Month* Month::getMonth( const QDate& aDate )
{
    Month* month = NULL;
    for( int i = 0; i < TransactionManager::sMonthList.size(); i++ )
    {
        QDate curDate = TransactionManager::sMonthList[i]->getDate();
        if( aDate.year() == curDate.year() && aDate.month() == curDate.month() )
        {
            month = TransactionManager::sMonthList[i];
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
    for( int i = TransactionManager::sMonthList.size()-1; i >= 0; --i )
    {
        Month* month = TransactionManager::sMonthList[i];
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
        TransactionManager::sMonthList.push_back( month );
        found = true;
    }
    return found;
} // Month::addToMonth

