//******************************************************************************
//
//  HEADER NAME: Transaction.cpp
//******************************************************************************

#include "Transaction.h"
#include "Account.h"

static Account sDefaultAccount = Account();

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
Transaction::Transaction():
    mAccount( &sDefaultAccount ),
    mTransactionDate( 2000, 1, 1 ),
    mNumber( 0 ),
    mType( TRANSACTION_INVALID ),
    mAmount( 0.0f ),
    mCurrentBalance( 0.0f )
{
} // Transaction::Transaction

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
Transaction::~Transaction()
{
} // Transaction::~Transaction

//----------------------------------------------------------------------------
// Operator
//----------------------------------------------------------------------------
bool Transaction::operator< ( const Transaction& aTransaction ) const
{
    if( getTransactionDate() < aTransaction.getTransactionDate() )
    {
        return true;
    }
    else if( getTransactionDate() == aTransaction.getTransactionDate() )
    {
        return( getNumber() > aTransaction.getNumber() );
    }
    return false;
} // Transaction::operator<

//----------------------------------------------------------------------------
// Operator
//----------------------------------------------------------------------------
bool Transaction::operator> ( const Transaction& aTransaction ) const
{
    if( getTransactionDate() > aTransaction.getTransactionDate() )
    {
        return true;
    }
    else if( getTransactionDate() == aTransaction.getTransactionDate() )
    {
        return( getNumber() < aTransaction.getNumber() );
    }
    return false;
} // Transaction::operator>

//----------------------------------------------------------------------------
// Add Transaction
//----------------------------------------------------------------------------
void Transaction::setTransactionDate( QDate aTransactionDate )
{
    if( aTransactionDate.year() < 2000 )
    {
        mTransactionDate.setDate( aTransactionDate.year()+100,aTransactionDate.month(), aTransactionDate.day() );
    }
    else
    {
        mTransactionDate = aTransactionDate;
    }
} // Transaction::setTransactionDate

//----------------------------------------------------------------------------
// Set Labels
//----------------------------------------------------------------------------
void Transaction::setLabels
    (
    const QStringList& aLabels
    )
{
    mLabels.clear();
    for( int i = 0; i < aLabels.size(); i++ )
    {
        mLabels.push_back( Category::getLabelId( aLabels[i] ) );
    }
} // Transaction::setLabels

//----------------------------------------------------------------------------
// Set Labels
//----------------------------------------------------------------------------
bool Transaction::matchLabels( Category::LabelIdType aLabel )
{
    bool found = false;
    for( int i = 0; i < mLabels.size(); i++ )
    {
        if( mLabels[i] == aLabel )
        {
            found = true;
            break;
        }
    }
    return found;
} // Transaction::setLabels

//----------------------------------------------------------------------------
// Get Info
//----------------------------------------------------------------------------
QString Transaction::getInfo()
{
    QString info = "Transaction -> Date:";
    info += mTransactionDate.toString("yyyy-MM-dd");
    info += "  Description:";
    info += mDescription;
    info += "  Number:";
    info += QString::number(mNumber);
    info += "  Account Name:";
    info += mAccount->getName();
    info += "  Type:";
    info += ( mType == TRANSACTION_DEBIT ) ? "Debit" : "Credit" ;
    info += "  Amount: $";
    info += QString::number(mAmount, 'f', 2 );
    info += "  Current Balance: $";
    info += QString::number(mCurrentBalance, 'f', 2 );
    info += "  Category:";
    info += Category::getCategoryText( mCategory );
    return info;
} // Transaction::getInfo

