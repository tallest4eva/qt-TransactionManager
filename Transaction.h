//******************************************************************************
//
//  HEADER NAME: Transaction.h
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
        QList<Account*> mAccountList;
        bool mAllCategories;
        QVector<bool> mCategoryList;
        bool mAllLabels;
        QVector<bool> mLabelList;
        bool mAllDates;
        QDate mStartDate;
        QDate mEndDate;
        FilterType(): mAllAccounts(true), 
                      mAllCategories(true), mCategoryList(Category::CATEGORY_TYPE_CNT,false),
                      mAllLabels(true), mLabelList(Category::LABEL_CNT,false),
                      mAllDates(true), mStartDate(2000,1,1), mEndDate(2000,1,1){}
    };

    // Functions
    explicit Transaction();
    virtual ~Transaction();
    void init
        (
        const QString& aString
        );
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
    void  setCurrentBalance( float aCurrentBalance ){ mCurrentBalance = aCurrentBalance; }
    Category::CategoryIdType getCategory() const { return mCategory; }
    void  setCategory( Category::CategoryIdType aCategory ){ mCategory = aCategory; }
    void  setLabels( const QStringList& aLabels );
    bool matchLabel( Category::LabelIdType aLabel );
    bool matchLabels( const QVector<bool> aLabelMask );
    bool matchTransaction( const FilterType& aFilter );
    bool isIncomeOrExpense();
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
    Category::CategoryIdType mCategory;
    QVector<Category::LabelIdType> mLabels;
};

#endif // TRANSACTION_H
