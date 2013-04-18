//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Transaction.h
//******************************************************************************

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDate>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>
#include "Category.h"

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
    enum TransactionType
    {
        INCOME,
        EXPENSE,
        TRANSFER,
        INVALID
    };
    struct FilterType
    {
        bool mAllAccounts;
        bool mShowAccounts;
        QList<Account*> mAccountList;
        bool mAllCategories;
        bool mShowCategories;
        QVector<bool> mCategoryList;
        bool mAllLabels;
        bool mShowLabels;
        QVector<bool> mLabelList;
        bool mAllDates;
        bool mShowDates;
        QDate mStartDate;
        QDate mEndDate;
        FilterType(): mAllAccounts(true), mShowAccounts(false), 
                      mAllCategories(true), mShowCategories(false), mCategoryList(Category::CATEGORY_TYPE_CNT,true),
                      mAllLabels(true), mShowLabels(false), mLabelList(Category::LABEL_CNT,true),
                      mAllDates(true), mShowDates(false), mStartDate(2000,1,1), mEndDate(2000,1,1){}
    };

    // Functions
    explicit Transaction();
    virtual ~Transaction();
    void init( const QString& aString );
    Account* getAccount() const { return mAccount; }
    void  setAccount( Account* aAccount ){ mAccount = aAccount; }
    QDate getTransactionDate() const { return mTransactionDate; }
    void  setTransactionDate( QDate aTransactionDate );
    int   getNumber() const { return mNumber; }
    void  setNumber( int aNumber ){ mNumber = aNumber; }
    QString getDescription() const { return mDescription; }
    void  setDescription( const QString& aDescription ){ mDescription = aDescription; }
    void  setOriginalDescription( const QString& aOriginalDescription ){ mOriginalDescription = aOriginalDescription; }
    Type getType() const { return mType; }
    void  setType( Type aType ){ mType = aType; }
    TransactionType getTransactionType() const;
    float getAmount() const { return mAmount; }
    void  setAmount( float aAmount ){ mAmount = aAmount; }
    float getCurrentBalance() const { return mCurrentBalance; }
    void  setCurrentBalance( float aCurrentBalance ){ mBalanceSet = true; mCurrentBalance = aCurrentBalance; }
    bool  isBalanceSet() const { return mBalanceSet; }
    Category::CategoryIdType getCategory() const { return mCategory; }
    void  setCategory( Category::CategoryIdType aCategory ){ mCategory = aCategory; }
    QList<Category::LabelIdType> getLabels() const { return mLabels; }
    QStringList getLabelStrings() const { return mLabelStrings; }
    void setLabels( const QStringList& aLabels );
    bool matchLabel( Category::LabelIdType aLabel );
    bool matchLabels( const QVector<bool> aLabelMask );
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
    static TransactionType determineTransactionType( Category::CategoryIdType aCategory );
    static bool transactionSortLessThan( Transaction* t1, Transaction* &t2 ){ return *t1 < *t2; }

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
    Category::CategoryIdType mCategory;
    QList<Category::LabelIdType> mLabels;
    QStringList mLabelStrings;
};

#endif // TRANSACTION_H
