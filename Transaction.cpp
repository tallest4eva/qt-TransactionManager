//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Transaction.cpp
//******************************************************************************

#include "Transaction.hpp"
#include "TransactionManager.hpp"
#include "Account.hpp"

#include <QLocale>

static Account sDefaultAccount = Account();

// Filter functions
Transaction::FilterType::FilterType( bool aSelectAll ):
    showToolBox( "account" ),
    mAccountsAll( aSelectAll ),
    mAccountList( Account::sAccountList.size(), aSelectAll ? true : false ),
    mCategoriesAll( aSelectAll ),
    mCategoryList( Category::getCategoryCount(), aSelectAll ? true : false ),
    mLabelsAll( aSelectAll ),
    mLabelList( Category::getLabelCount(), aSelectAll ? MATCH : DO_NOT_MATCH ),
    mDatesAll( aSelectAll ),
    mStartDate( TransactionManager::sFirstTransactionDate ),
    mEndDate( TransactionManager::sLastTransactionDate )
{
}
QList<Account*> Transaction::FilterType::getSelectedAccounts() const
{
    QList<Account*> selectedAccounts;
    for( int i = 0; i < mAccountList.size() && i < Account::sAccountList.size(); i++ )
    {
        if( mAccountList[i] ){ selectedAccounts.push_back( Account::sAccountList[i] ); }
    }
    return selectedAccounts;
}
void Transaction::FilterType::clearAll()
{
    selectAllAccounts( false );
    selectAllCategories( false );
    selectAllLabels( DO_NOT_MATCH );
    mSearchStr.clear();
}
void Transaction::FilterType::selectAll()
{
    selectAllAccounts( true );
    selectAllCategories( true );
    selectAllLabels( MATCH );
    selectAllDates();
    mSearchStr.clear();
}
void Transaction::FilterType::selectAllAccounts( bool aSelect )
{
    mAccountsAll = aSelect;
    mAccountList.fill( aSelect );
}
void Transaction::FilterType::selectOpenAccounts( bool aSelect )
{
    mAccountsAll = true;
    for( int i = 0; i < mAccountList.size() && i < Account::sAccountList.size(); i++ )
    {
        if( Account::sAccountList[i]->isOpen() ){ mAccountList[i] = aSelect; }
        if( !mAccountList[i] ){ mAccountsAll = false; }
    }
}
void Transaction::FilterType::selectAllCategories( bool aSelect )
{
    for( int i = 0; i < mCategoryList.size(); i++ )
    {
        mCategoryList[i] = aSelect;
    }
    mCategoriesAll = aSelect;
}
void Transaction::FilterType::selectCategories( bool aSelect, Category::TransactionType aTransactionType, bool aClear )
{
    int selectAll = true;
    for( int i = 0; i < mCategoryList.size(); i++ )
    {
        // clear categories if flag is set
        if( aClear ){ mCategoryList[i] = false; }
        if( aTransactionType == Category::getCategoryTransactionType( (Category::CategoryIdxType)i ) )
        {
            mCategoryList[i] = aSelect;
        }
        if( !mCategoryList[i] ){ selectAll = false; }
    }
    mCategoriesAll = selectAll;
}
void Transaction::FilterType::clearAllCategories( const QVector<Category::TransactionType>& aTransactionTypeList )
{
    for( int i = 0; i < mCategoryList.size(); i++ )
    {
        if( aTransactionTypeList.indexOf( Category::getCategoryTransactionType((Category::CategoryIdxType)i) ) != -1 )
        {
            mCategoryList[i] = false;
            mCategoriesAll = false;
        }
    }
}
void Transaction::FilterType::selectAllLabels( MatchType aMatchType )
{
    for( int i = 0; i < mLabelList.size(); i++ )
    {
        mLabelList[i] = aMatchType;
    }
    mLabelsAll = ( aMatchType == MATCH );
}
void Transaction::FilterType::selectAllDates()
{
    mDatesAll = true;
    mStartDate = TransactionManager::sFirstTransactionDate;
    mEndDate = TransactionManager::sLastTransactionDate;
}
void Transaction::FilterType::selectDateRange( const QDate& aStartDate, const QDate& aEndDate )
{
    mDatesAll = true;
    mStartDate = aStartDate;
    mEndDate = aEndDate;

    // Sanity check dates
    if( mStartDate < TransactionManager::sFirstTransactionDate ){ mStartDate = TransactionManager::sFirstTransactionDate; }
    if( mEndDate > TransactionManager::sLastTransactionDate ){ mEndDate = TransactionManager::sLastTransactionDate; }

    // If not all dates are set
    if( TransactionManager::sFirstTransactionDate < mStartDate || TransactionManager::sLastTransactionDate > mEndDate )
    {
        mDatesAll = false;
    }
}

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
void Transaction::setTransactionDate( const QDate& aTransactionDate )
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
// getCategoryLabel
//----------------------------------------------------------------------------
QString Transaction::getCategoryLabel() const
{
    QString label = Category::getCategoryText( mCategoryIdx );
    if( !mUncategorizedLabel.isEmpty() )
    {
        label += ": " + mUncategorizedLabel;
    }
    return label;
} // Transaction::getCategoryLabel

//----------------------------------------------------------------------------
// setCategoryLabel
//----------------------------------------------------------------------------
void Transaction::setCategoryLabel( const QString& aCategoryLabel )
{
    mCategoryIdx = Category::getCategoryIndex( aCategoryLabel );
    if( mCategoryIdx == Category::sUnmatchedCategoryIdx )
    {
        // Category label was unmatched
        mUncategorizedLabel = aCategoryLabel;
    }
} // Transaction::setCategoryLabel

//----------------------------------------------------------------------------
// Set Labels
//----------------------------------------------------------------------------
void Transaction::setLabels
    (
    const QStringList& aLabels
    )
{
    mLabelIdxs.clear();
    mLabelStrings.clear();
    for( int i = 0; i < aLabels.size(); i++ )
    {
        Category::LabelIdType labelIdx = Category::getLabelId( aLabels[i] );
        if( labelIdx != Category::LABEL_INVALID ){ mLabelIdxs.push_back( labelIdx ); }
        mLabelStrings.push_back( aLabels[i] );
    }
    if( mLabelIdxs.isEmpty() )
    {
        mLabelIdxs.push_back( Category::LABEL_NONE );
        mLabelStrings.push_back( Category::getLabelText( Category::LABEL_NONE ) );
    }
    mLabelStrings.sort();
} // Transaction::setLabels

//----------------------------------------------------------------------------
// Match Labels
//----------------------------------------------------------------------------
bool Transaction::matchLabel( Category::LabelIdType aLabel )
{
    bool found = false;
    for( int i = 0; i < mLabelIdxs.size(); i++ )
    {
        if( mLabelIdxs[i] == aLabel )
        {
            found = true;
            break;
        }
    }
    return found;
} // Transaction::matchLabel

//----------------------------------------------------------------------------
// Match Labels
//----------------------------------------------------------------------------
bool Transaction::matchLabels( const QVector<MatchType>& aLabelMask )
{
    bool found = false;
    for( int i = 0; i < mLabelIdxs.size(); i++ )
    {
        if( aLabelMask[(int)mLabelIdxs[i]] == MATCH )
        {
            found = true;
        }
        else if( aLabelMask[(int)mLabelIdxs[i]] == EXCLUDE_MATCH )
        {
            found = false;
			break;
        }
    }
    return found;
} // Transaction::matchLabels

//----------------------------------------------------------------------------
// Matchs transaction with search string
//----------------------------------------------------------------------------
bool Transaction::matchString
    (
    const QString& aMatchString
    )
{
    bool match = ( mDescription.contains( aMatchString, Qt::CaseInsensitive ) ||
              mAccount->getName().contains( aMatchString, Qt::CaseInsensitive ) ||
              QString::number( mAmount ).contains( aMatchString, Qt::CaseInsensitive ) ||
              Category::getCategoryText( mCategoryIdx ).contains( aMatchString, Qt::CaseInsensitive ) ||
              ( mBalanceSet && QString::number( mCurrentBalance ).contains( aMatchString, Qt::CaseInsensitive ) ) ||
              mTransactionDate.toString("yyyy-MM-dd").contains( aMatchString, Qt::CaseInsensitive ) ||
              mLabelStrings.join(",").contains( aMatchString, Qt::CaseInsensitive )
            );
    return match;
} // matchString

//----------------------------------------------------------------------------
// matchTransaction
//----------------------------------------------------------------------------
bool Transaction::matchTransaction( const FilterType& aFilter )
{
    // Match acounts
    bool match = true;
    if( !aFilter.allAccountsSelected() )
    {
        match = aFilter.mAccountList[ Account::getAccountIndex(mAccount) ];
    }

    // Match categories
    if( match && !aFilter.allCategoriesSelected() )
    {
        match = aFilter.mCategoryList[(int)mCategoryIdx];
    }

    // Match labels
    if( match && !aFilter.allLabelsSelected() )
    {
        match = matchLabels( aFilter.mLabelList );
    }

    // Match dates
    if( match && !aFilter.mDatesAll )
    {
        match &= ( mTransactionDate >= aFilter.mStartDate && mTransactionDate <= aFilter.mEndDate );
    }

    // Match dates
    if( match && !aFilter.mSearchStr.isEmpty() )
    {
        match &= matchString( aFilter.mSearchStr );
    }

    return match;
} // Transaction::matchTransaction

//----------------------------------------------------------------------------
// getTransactionType
//----------------------------------------------------------------------------
Category::TransactionType Transaction::getTransactionType() const
{
    Category::TransactionType transType = Category::getCategoryTransactionType( mCategoryIdx );
    if( transType != Category::TRANSACTION_TYPE_TRANSFER && Category::getParentCategoryId( mCategoryIdx ) == Category::UNCATEGORIZED )
    {
        transType = ( mAmount > 0 ) ? Category::TRANSACTION_TYPE_INCOME : Category::TRANSACTION_TYPE_EXPENSE;
    }
    return transType;
} // Transaction::getTransactionType()

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
    info += Category::getCategoryText( mCategoryIdx );
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
    if( aFilter.allSelected() && aFilter.mSearchStr.isEmpty() )
    {
        return aTransactionList;
    }

    QList<Transaction*> transactionList;
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

//----------------------------------------------------------------------------
// Get amount in text with - and string and commas if necessary
//----------------------------------------------------------------------------
QString Transaction::getAmountText( float aAmount, bool aRichTextColor )
{
    QString text = "$" + QLocale::system().toString( aAmount, 'f', 2 );
    text = text.replace("$-", "-$");
    if( aRichTextColor && aAmount != 0 )
    {
        // Add rich text color
        text.prepend( (aAmount > 0) ? "<font color=\"green\">" : "<font color=\"red\">" );
        text.append( "</font>" );
    }
    return text;
} // Transaction::filterTransactions
