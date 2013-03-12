//******************************************************************************
//
//  HEADER NAME: Month.cpp
//******************************************************************************

#include <QDebug>

#include "Month.h"
#include "TransactionManager.h"

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

bool Month::getNetWorth( Account* aAccount, float* aNetWorth ) const
{
    bool found = false;
    int index = Account::getAccountIndex( aAccount );
    if( index >= 0 && mNetWorthList[index].mAccount == aAccount )
    {
        *aNetWorth = mNetWorthList[index].mNetWorth;
        found = true;
    }
    return found;
}

//----------------------------------------------------------------------------
//! Update data
//----------------------------------------------------------------------------
void Month::updateData()
{
    mNetWorthList.fill( NetWorthType(), TransactionManager::mAccountList.size() );
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

            // Skip exlcuded transfer categories
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

