//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Account.hpp
//******************************************************************************

#ifndef Account_HPP
#define Account_HPP

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
    bool  isOpen() const { return( mStatus == STATUS_OPEN ); }
    bool  isClosed() const { return( mStatus == STATUS_CLOSED ); }
    bool  getAccountComplete() const { return mComplete; }
    void  setAccountComplete( bool aComplete ){ mComplete = aComplete; }
    QDate getOpenDate() const { return mOpenDate; }
    void  setOpenDate( QDate aOpenDate ){ mOpenDate = aOpenDate; }
    QDate getLastDate() const { return mLastDate; }
    QDate getCloseDate() const { return mCloseDate; }
    void  setCloseDate( QDate aCloseDate ){ mCloseDate = aCloseDate; }
    bool  isAccountMatch( const QString& aAccountName, bool aAllowAltNames = false );
    void  addTransaction( Transaction* aTransaction );
    const QList<Transaction*>& getTransactionList() const { return mTransactionList; }
    void  updateData();
    QString getInfo();
    bool operator== ( const Account& aAccount ) const;

    // Static functions
    static bool accountSortByNameLessThan( Account* arg1, Account* &arg2 );
    static bool accountSortByBalanceLessThan( Account* arg1, Account* &arg2 );
    static bool accountSortByOpenDateLessThan( Account* arg1, Account* &arg2 );
    static void updateAccountList();
    static float getTotalAccountBalance();
    static int getAccountIndex( const Account* aAccount );
    static Account* getAccount( const QString& aAccountName, bool aAllowAltNames = false );
    static bool addToAccount( const QString& aAccountName, Transaction* aTransaction, bool aCreateNewAccount );
    static void addAccount( Account* aAccount );
    static void clearAccountList();

    // Variables
    static QList<Account*> sAccountList;
    static QList<Account*> sAccountOpenList;

private:
    bool mValid;
    QString mName;
    int mNumber;
    QStringList mAlternateNames;
    float mBalance;
    StatusType mStatus;
    bool mComplete;
    QDate mOpenDate;
    QDate mLastDate;
    QDate mCloseDate;
    QList<Transaction*> mTransactionList;
};

#endif // Account_HPP
