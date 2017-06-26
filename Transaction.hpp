//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Transaction.h
//******************************************************************************

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <QDate>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>

#include "Category.hpp"

class Account;
class Transaction
{
public:
    // Types
    enum Type
    {
        TRANSACTION_DEBIT,
        TRANSACTION_CREDIT,
        TRANSACTION_INVALID
    };
    enum MatchType
    {
        MATCH,
        DO_NOT_MATCH,
        EXCLUDE_MATCH
    };
    struct FilterType
    {
        QString showToolBox;
        bool mAccountsAll;
        QVector<bool> mAccountList;
        bool mCategoriesAll;
        QVector<bool> mCategoryList;
        bool mLabelsAll;
        QVector<MatchType> mLabelList;
        bool mDatesAll;
        QDate mStartDate;
        QDate mEndDate;
        QString mSearchStr;

        FilterType( bool aSelectAll = true );
        bool allAccountsSelected() const { return mAccountsAll; }
        bool allCategoriesSelected() const { return mCategoriesAll; }
        bool allLabelsSelected() const { return mLabelsAll; }
        bool allSelected() const { return allAccountsSelected() &&
                                          allCategoriesSelected() &&
                                          allLabelsSelected() && mDatesAll; }
        QList<Account*> getSelectedAccounts() const;
        void clearAll();
        void selectAll();
        void selectAllAccounts( bool aSelect );
        void selectOpenAccounts( bool aSelect );
        void selectAllCategories( bool aSelect );
        void selectCategories( bool aSelect, Category::TransactionType aTransactionType, bool aClear = false );
        void clearAllCategories( const QVector<Category::TransactionType>& aTransactionTypeList );
        void selectAllLabels( MatchType aMatchType  );
        void selectAllDates();
        void selectDateRange( const QDate& aStartDate, const QDate& aEndDate );
    };

    // Functions
    explicit Transaction();
    virtual ~Transaction();
    void init( const QString& aString );
    Account* getAccount() const { return mAccount; }
    void  setAccount( Account* aAccount ){ mAccount = aAccount; }
    QDate getTransactionDate() const { return mTransactionDate; }
    void  setTransactionDate( const QDate& aTransactionDate );
    int   getNumber() const { return mNumber; }
    void  setNumber( int aNumber ){ mNumber = aNumber; }
    QString getDescription() const { return mDescription; }
    void  setDescription( const QString& aDescription ){ mDescription = aDescription; }
    QString getOriginalDescription() const { return mOriginalDescription; }
    void  setOriginalDescription( const QString& aOriginalDescription ){ mOriginalDescription = aOriginalDescription; }
    Type getType() const { return mType; }
    void  setType( Type aType ){ mType = aType; }
    Category::TransactionType getTransactionType() const;
    float getAmount() const { return mAmount; }
    void  setAmount( float aAmount ){ mAmount = aAmount; }
    float getCurrentBalance() const { return mCurrentBalance; }
    void  setCurrentBalance( float aCurrentBalance ){ mBalanceSet = true; mCurrentBalance = aCurrentBalance; }
    bool  isBalanceSet() const { return mBalanceSet; }
    Category::CategoryIdxType getCategory() const { return mCategoryIdx; }
    void  setCategory( Category::CategoryIdxType aCategory ){ mCategoryIdx = aCategory; }
    Category::ParentCategoryType getParentCategory() const { return Category::getParentCategoryId( mCategoryIdx ); }
    QString getCategoryLabel() const;
    void  setCategoryLabel( const QString& aCategoryLabel );
    const QList<Category::LabelIdType>& getLabels() const { return mLabelIdxs; }
    const QStringList& getLabelStrings() const { return mLabelStrings; }
    void setLabels( const QStringList& aLabels );
    bool matchLabel( Category::LabelIdType aLabel );
    bool matchLabels( const QVector<MatchType>& aLabelMask );
    bool matchString( const QString& aMatchString );
    bool matchTransaction( const FilterType& aFilter );
    QString getInfo();

    // Comparators
    bool operator< ( const Transaction& aTransaction ) const;
    bool operator> ( const Transaction& aTransaction ) const;

    static QList<Transaction*> filterTransactions
        (
        const QList<Transaction*>& aTransactionList,
        const FilterType& aFilter
        );
    static bool transactionSortLessThan( Transaction* t1, Transaction* &t2 ){ return *t1 < *t2; }
    static QString getAmountText( float aAmount, bool aRichTextColor = false );

private:
    // Variables
    Account* mAccount;
    QDate mTransactionDate;
    int mNumber;
    QString mDescription;
    QString mOriginalDescription;
    Type mType;
    float mAmount;
    float mCurrentBalance;
    bool mBalanceSet;
    Category::CategoryIdxType mCategoryIdx;
    QString mUncategorizedLabel;
    QList<Category::LabelIdType> mLabelIdxs;
    QStringList mLabelStrings;
};

#endif // TRANSACTION_HPP
