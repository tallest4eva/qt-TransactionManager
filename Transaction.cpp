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
    mCurrentBalance( 0.0f ),
    mBalanceSet( false )
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
    if( mLabels.isEmpty() )
    {
        mLabels.push_back( Category::LABEL_NONE );
    }
} // Transaction::setLabels

//----------------------------------------------------------------------------
// matchLabels
//----------------------------------------------------------------------------
bool Transaction::matchLabel( Category::LabelIdType aLabel )
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
} // Transaction::matchLabel

//----------------------------------------------------------------------------
// matchLabels
//----------------------------------------------------------------------------
bool Transaction::matchLabels( const QVector<bool> aLabelMask )
{
    bool found = false;
    for( int i = 0; i < mLabels.size(); i++ )
    {
        if( aLabelMask[(int)mLabels[i]] )
        {
            found = true;
            break;
        }
    }
    return found;
} // Transaction::matchLabels

//----------------------------------------------------------------------------
// matchTransaction
//----------------------------------------------------------------------------
bool Transaction::matchTransaction( const FilterType& aFilter )
{ 
    // Match acounts
    bool match = true;
    if( !aFilter.mAllAccounts )
    {
        match = false;
        for( int i = 0; i < aFilter.mAccountList.size(); i++ )
        {
            if( aFilter.mAccountList[i] == mAccount )
            {
                match = true;
                break;
            }
        }
    }

    // Match categories
    if( match && !aFilter.mAllCategories )
    {
        match = aFilter.mCategoryList[(int)mCategory];
    }

    // Match labels
    if( match && !aFilter.mAllLabels )
    {
        match = matchLabels( aFilter.mLabelList );
    }

    // Match dates
    if( match && !aFilter.mAllDates )
    {
        match &= ( mTransactionDate >= aFilter.mStartDate && mTransactionDate <= aFilter.mEndDate );
    }
    return match;
} // Transaction::matchTransaction

//----------------------------------------------------------------------------
// getTransactionType
//----------------------------------------------------------------------------
Transaction::TransactionType Transaction::getTransactionType() const
{
    TransactionType transType = INVALID;
    switch( mCategory )
    {
    // Transfer categories
    case Category::TRANSFER:
    case Category::CREDIT_CARD_PAYMENT:
    case Category::FAMILY_TRANSFER:
    case Category::TRANSFER_FOR_CASH_SPENDING:
    case Category::ACCOUNT_BALANCE:
    case Category::STUDENT_LOAN:
    case Category::LOAN_PAYMENT:
    case Category::STOCK_PURCHASE:
    case Category::STOCK_SALE:
    case Category::FAMILY_LOAN:
    case Category::PERSONAL_LOAN:
        transType = TRANSFER;
        break;
    // Income categories
    case Category::INCOME:
    case Category::BONUS:
    case Category::INTEREST_INCOME:
    case Category::MISC_INCOME:
    case Category::PAYCHECK:
    case Category::REIMBURSEMENT:
    case Category::RENTAL_INCOME:
    case Category::RETURNED_PURCHASE:
    case Category::REWARDS_INCOME:
    case Category::TAX_REFUND:
    case Category::FAMILY_INCOME:
    case Category::DIVIDEND_AND_CAP_GAINS:
    case Category::RETIREMENT_DEPOSIT:
    case Category::RETIREMENT_DIVIDENDS:
        transType = INCOME;
        break;
    case Category::UNCATEGORIZED:
        transType = ( mAmount >= 0 ) ? INCOME : EXPENSE;
        break;
    // Expense categories
    case Category::CHECK:
    case Category::CASH_AND_ATM:
    default:
        transType = EXPENSE;
        break;
    }
    return transType;
} // Transaction::getTransactionType()

//----------------------------------------------------------------------------
// determineTransactionType
//----------------------------------------------------------------------------
Transaction::TransactionType Transaction::determineTransactionType( Category::CategoryIdType aCategory )
{
    Transaction transaction;
    transaction.setCategory( aCategory );
    return transaction.getTransactionType();
} // Transaction::determineTransactionType()

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

//----------------------------------------------------------------------------
// filterTransactions
//----------------------------------------------------------------------------
QList<Transaction*> Transaction::filterTransactions
    (
    const QList<Transaction*>& aTransactionList,
    const FilterType& aFilter
    )
{
    QList<Transaction*> transactionList;
    if( aFilter.mAllAccounts && aFilter.mAllCategories && aFilter.mAllLabels && aFilter.mAllDates )
    {
        return aTransactionList;
    }
    for( int i = 0; i < aTransactionList.size(); i++ )
    {
        Transaction* transaction = aTransactionList[i];
        if( transaction->matchTransaction( aFilter ) )
        {
            transactionList.push_back( transaction );
        }
    }
    return transactionList;
} // Transaction::filterTransactions

