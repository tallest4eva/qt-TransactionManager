//******************************************************************************
//
//  HEADER NAME: Transaction.h
//******************************************************************************

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDate>
#include <QString>
#include <QStringList>
#include <QVector>
#include "Category.h"

class Account;
class Transaction
{
public:
    // Types
    enum TransactionType
    {
        TRANSACTION_DEBIT,
        TRANSACTION_CREDIT,
        TRANSACTION_INVALID
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
    TransactionType getType(){ return mType; }
    void  setType( TransactionType aType ){ mType = aType; }
    float getAmount() const { return mAmount; }
    void  setAmount( float aAmount ){ mAmount = aAmount; }
    float getCurrentBalance() const { return mCurrentBalance; }
    void  setCurrentBalance( float aCurrentBalance ){ mCurrentBalance = aCurrentBalance; }
    Category::CategoryIdType getCategory() const { return mCategory; }
    void  setCategory( Category::CategoryIdType aCategory ){ mCategory = aCategory; }
    void  setLabels( const QStringList& aLabels );
    bool matchLabels( Category::LabelIdType aLabel );
    QString getInfo();

    // Comparators
    bool operator< ( const Transaction& aTransaction ) const;
    bool operator> ( const Transaction& aTransaction ) const;

private:
    Account* mAccount;
    QDate mTransactionDate;
    int mNumber;
    QString mDescription;
    QString mOriginalDescription;
    TransactionType mType;
    float mAmount;
    float mCurrentBalance;
    Category::CategoryIdType mCategory;
    QVector<Category::LabelIdType> mLabels;
};

#endif // TRANSACTION_H
