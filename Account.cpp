//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Account.cpp
//******************************************************************************

#include "Account.h"
#include "Transaction.h"
#include "TransactionManager.h"

// Static functions
static bool accountSortLessThan( Account* arg1, Account* &arg2 )
{
     return arg1->getName() < arg2->getName();
}
//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
Account::Account() :
    mValid( false ),
    mName( "None" ),
    mNumber( -1 ),
    mBalance( 0 ),
    mStatus( STATUS_INVALID ),
    mComplete( false ),
    mOpenDate( 2000, 1, 1 ),
    mCloseDate( QDate::currentDate() )
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
    return( getName() == aAccount.getName() );
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
    if( mName.isEmpty() ){ mName = "Unknown"; }
    mValid = true;
    qSort( mTransactionList.begin(), mTransactionList.end(), Transaction::transactionSortLessThan );
    if( mTransactionList.size() > 0 )
    {
        for( int i = 0; i < mTransactionList.size(); i++ )
        {
            Transaction* transaction = mTransactionList[i];

            // Update transaction amounts
            Transaction::Type type = transaction->getType();
            switch( type )
            {
            case Transaction::TRANSACTION_DEBIT:
                if( transaction->getAmount() > 0 )
                {
                    transaction->setAmount( -transaction->getAmount() );
                }
                break;
            case Transaction::TRANSACTION_CREDIT:
                if( transaction->getAmount() < 0 )
                {
                    transaction->setAmount( -transaction->getAmount() );
                }
                break;
            case Transaction::TRANSACTION_INVALID:
                transaction->setType( (transaction->getAmount() < 0) ? Transaction::TRANSACTION_DEBIT : Transaction::TRANSACTION_CREDIT );
                break;
            }

            // Update transaction current balances if account state is complete
            if( mComplete && !transaction->isBalanceSet() )
            {
                float prevBalance = ( i > 0 ) ? mTransactionList[i-1]->getCurrentBalance() : 0;
                transaction->setCurrentBalance( prevBalance + transaction->getAmount() );
            }
        }

        // Update account balance and dates
        mOpenDate = mTransactionList[0]->getTransactionDate();
        Transaction* last = mTransactionList[mTransactionList.size()-1];
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
bool Account::isAccountMatch( const QString& aAccountName, bool aAllowAltNames ) 
{
    bool found = false;
    if( mName == aAccountName )
    {
        found = true;
    }
    else if( aAllowAltNames )
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
// updateAccountList
//----------------------------------------------------------------------------
void Account::updateAccountList()
{
    qSort( TransactionManager::sAccountList.begin(), TransactionManager::sAccountList.end(), accountSortLessThan );
    for( int i = 0; i < TransactionManager::sAccountList.size(); i++ )
    {
        TransactionManager::sAccountList[i]->updateData();
        TransactionManager::sAccountList[i]->setNumber( i );
    }
} // Account::updateAccountList

//----------------------------------------------------------------------------
// getAccountIndex
//----------------------------------------------------------------------------
int Account::getAccountIndex( Account* aAccount )
{
    int index = -1;
    if( aAccount )
    {
        index = aAccount->getNumber();
    }
    return index;
} // Account::getAccountIndex

//----------------------------------------------------------------------------
// getAccount. Allows for alternate names
//----------------------------------------------------------------------------
Account* Account::getAccount( const QString& aAccountName, bool aAllowAltNames )
{
    Account* account = NULL;
    for( int i = 0; i < TransactionManager::sAccountList.size(); i++ )
    {
        if( TransactionManager::sAccountList[i]->isAccountMatch( aAccountName, aAllowAltNames ) )
        {
            account = TransactionManager::sAccountList[i];
            break;
        }
    }
    return account;
} // Account::getAccount()

//----------------------------------------------------------------------------
// addToAccount. Allows for alternate names
//----------------------------------------------------------------------------
bool Account::addToAccount
    (
    const QString& aAccountName,
    Transaction* aTransaction,
    bool aCreateNewAccount
    )
{
    bool found = false;
    for( int i = TransactionManager::sAccountList.size()-1; i >= 0; --i )
    {
        if( TransactionManager::sAccountList[i]->isAccountMatch( aAccountName, true ) )
        {
            aTransaction->setAccount( TransactionManager::sAccountList[i] );
            TransactionManager::sAccountList[i]->addTransaction( aTransaction );
            found = true;
            break;
        }
    }
    if( !found && aCreateNewAccount )
    {
        // Create new account
        Account* account = new Account();
        account->setName( aAccountName );
        account->setStatus( STATUS_OPEN );

        // Set as complete to allow auto net worth calculations
        account->setAccountComplete( true );
        aTransaction->setAccount( account );
        account->addTransaction( aTransaction );
        TransactionManager::sAccountList.push_back( account );
        //Logger::logString( "Adding account:" + QString(account->getInfo()) );
        found = true;
    }
    return found;
} // Account::addToAccount

//----------------------------------------------------------------------------
// getTotalAccountBalance
//----------------------------------------------------------------------------
float Account::getTotalAccountBalance()
{
    float balance = 0;
    for( int i = 0; i < TransactionManager::sAccountList.size(); i++ )
    {
        balance += TransactionManager::sAccountList[i]->getBalance();
    }
    return balance;
} // Account::getTotalAccountBalance()

