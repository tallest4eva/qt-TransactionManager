//******************************************************************************
//
//  HEADER NAME: Account.cpp
//******************************************************************************

#include <QDebug>

#include "Account.h"
#include "TransactionManager.h"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
Account::Account() :
    mName( "None" ),
    mBalance( 0 ),
    mStatus( STATUS_INVALID ),
    mComplete( false ),
    mOpenDate( 2000, 1, 1 ),
    mCloseDate( 2000, 1, 1 )
{
} // Account::Account

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
Account::~Account()
{
} // Account::~Account()

//----------------------------------------------------------------------------
//! operator ==
//----------------------------------------------------------------------------
bool Account::operator== ( const Account& aAccount ) const
{
    return ( getName() == aAccount.getName() );
} // Account::operator==()

//----------------------------------------------------------------------------
//! Add Transaction
//----------------------------------------------------------------------------
void Account::addTransaction( Transaction* aTransaction )
{
    mTransactionList.push_back( aTransaction );
} // Account::addTransaction()

//----------------------------------------------------------------------------
//! Update account data
//----------------------------------------------------------------------------
void Account::updateData()
{
    qSort( mTransactionList.begin(), mTransactionList.end(), Transaction::transactionSortLessThan );
    if( mTransactionList.size() > 0 )
    {
        mOpenDate = mTransactionList[0]->getTransactionDate();
        Transaction *last = mTransactionList[mTransactionList.size()-1];
        mBalance = last->getCurrentBalance();
        if( mStatus == STATUS_CLOSED && last->getDescription() == "Account Closed" )
        {
            mCloseDate = last->getTransactionDate();
        }
     }
} // Account::updateData()

//----------------------------------------------------------------------------
//! Checks if name matches this account
//----------------------------------------------------------------------------
bool Account::isAccountMatch( const QString& aAccountName ) 
{
    bool found = false;
    if( mName == aAccountName )
    {
        found = true;
    }
    else
    {
        for( int i = 0; i < mAlternateNames.size(); i++ )
        {
            if( mAlternateNames[i] == aAccountName )
            {
                found = true;
                break;
            }
        } 
    }
    return found;
} // Account::isAccountMatch()

//----------------------------------------------------------------------------
// Get Info
//----------------------------------------------------------------------------
QString Account::getInfo()
{
    QString info = "Acount -> Name:";
    info += mName;
    //info = "Alt. Names: "
    //info = mAlternateNames;
    info += "  Balance: $";
    info += QString::number( mBalance, 'f', 2 );
    info += "  Status: ";
    info += ( mStatus == STATUS_OPEN ) ? "Open" : "Close" ;
    info += "  State: ";
    info += ( mComplete ) ? "Complete" : "Incomplete" ;
    info += "  Open Date: ";
    info += mOpenDate.toString("yyyy-MM-dd");
    info += "  Close Date: ";
    info += mCloseDate.toString("yyyy-MM-dd");
    return info;
} // Account::getInfo

//----------------------------------------------------------------------------
// getAccountIndex
//----------------------------------------------------------------------------
int Account::getAccountIndex( Account* aAccount )
{
    int index = -1;
    for( int i = 0; i < TransactionManager::mAccountList.size(); i++ )
    {
        if( aAccount == TransactionManager::mAccountList[i] )
        {
            index = i;
            break;
        }
    }
    return index;
} // Account::getAccountIndex

//----------------------------------------------------------------------------
// addToAccount. Allows for alternate names
//----------------------------------------------------------------------------
bool Account::addToAccount
    (
    const QString& aAccountName,
    Transaction* aTransaction
    )
{
    bool found = false;
    for( int i = TransactionManager::mAccountList.size()-1; i >= 0; --i )
    {
        if( TransactionManager::mAccountList[i]->isAccountMatch( aAccountName ) )
        {
            aTransaction->setAccount( TransactionManager::mAccountList[i] );
            TransactionManager::mAccountList[i]->addTransaction( aTransaction );
            found = true;
            break;
        }
    }
    return found;
} // Account::addToAccount

//----------------------------------------------------------------------------
// getTotalAccountBalance
//----------------------------------------------------------------------------
float Account::getTotalAccountBalance()
{
    float balance = 0;
    for( int i = 0; i < TransactionManager::mAccountList.size(); i++ )
    {
        balance += TransactionManager::mAccountList[i]->getBalance();
    }
    return balance;
} // Account::getTotalAccountBalance()

