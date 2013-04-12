//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Account.h
//******************************************************************************

#ifndef Account_H
#define Account_H

#include <QDate>
#include <QList>
#include <QString>
#include <QStringList>

class Transaction;

class Account
{
public:
    // Types
    enum StatusType
    {
        STATUS_OPEN,
        STATUS_CLOSED,
        STATUS_INVALID
    };

    // Functions
    explicit Account();
    virtual ~Account();
    bool  isValid() const { return mValid; }
    QString getName() const { return mName; }
    void  setName( const QString& aAccountName ){ mName = aAccountName; }
    void  setAlternateNames( const QStringList& aAlternateNames ){ mAlternateNames = aAlternateNames; }
    int   getNumber() const { return mNumber; }
    void  setNumber( int aNumber ){ mNumber = aNumber; }
    float getBalance() const { return mBalance; }
    void  setBalance( float aBalance ){ mBalance = aBalance; }
    StatusType getStatus() const { return mStatus; }
    void  setStatus( StatusType aStatus ){ mStatus = aStatus; }
    bool  getAccountComplete() const { return mComplete; }
    void  setAccountComplete( bool aComplete ){ mComplete = aComplete; }
    QDate getOpenDate() const { return mOpenDate; }
    void  setOpenDate( QDate aOpenDate ){ mOpenDate = aOpenDate; }
    QDate getCloseDate() const { return mCloseDate; }
    void  setCloseDate( QDate aCloseDate ){ mCloseDate = aCloseDate; }
    bool  isAccountMatch( const QString& aAccountName, bool aAllowAltNames = false );
    void  addTransaction( Transaction* aTransaction );
    QList<Transaction*> getTransactionList(){ return mTransactionList; }
    void  updateData();
    QString getInfo();
    bool operator== ( const Account& aAccount ) const;

    static void updateAccountList();
    static float getTotalAccountBalance();
    static int getAccountIndex( Account* aAccount );
    static Account* getAccount( const QString& aAccountName, bool aAllowAltNames = false );
    static bool addToAccount( const QString& aAccountName, Transaction* aTransaction );

private:
    bool mValid;
    QString mName;
    int mNumber;
    QStringList mAlternateNames;
    float mBalance;
    StatusType mStatus;
    bool mComplete;
    QDate mOpenDate;
    QDate mCloseDate;
    QList<Transaction*> mTransactionList;
};

#endif // Account_H
