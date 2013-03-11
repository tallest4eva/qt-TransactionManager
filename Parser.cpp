//******************************************************************************
//
//  HEADER NAME: Parser.cpp
//******************************************************************************

#include <QString>
#include <QStringList>

#include "Parser.h"
#include "Category.h"
#include "Logger.h"
#include "TransactionManager.h"

// Static variables
const DateFormatType Parser::cDefaultDateFormat = Parser::DATE_ENTRY_MMddyy_SLASH;
DateFormatType Parser::sDateFormat;

const char* Parser::cDateFormatList[] =
{
    "MM/dd/yy",     // DATE_ENTRY_MMddyy_SLASH
    "MM-dd-yy",     // DATE_ENTRY_MMddyy_HYPHEN,
    "MM/dd/yyyy",   // DATE_ENTRY_MMddyyyy_SLASH,
    "MM-dd-yyyy",   // DATE_ENTRY_MMddyyyy_HYPHEN,
    "yy/MM/dd",     // DATE_ENTRY_yyMMdd_SLASH,
    "yy-MM-dd",     // DATE_ENTRY_yyMMdd_HYPHEN,
    "yyyy/MM/dd",   // DATE_ENTRY_yyyyMMdd_SLASH,
    "yyyy-MM-dd",   // DATE_ENTRY_yyyyMMdd_HYPHEN,
    "dd/MM/yy",     // DATE_ENTRY_ddMMyy_SLASH,
    "dd-MM-yy",     // DATE_ENTRY_ddMMyy_HYPHEN,
    "dd/MM/yyyy",   // DATE_ENTRY_ddMMyyyy_SLASH,
    "dd-MM-yyyy",   // DATE_ENTRY_ddMMyyyy_HYPHEN,
};


const int Parser::cDefaultEntryList[] =
{
    0,          /* ENTRY_TRANS_DATE           */
    1,          /* ENTRY_TRANS_ACCOUNT_NAME   */
    2,          /* ENTRY_TRANS_DESCRIPTION    */
	3,          /* ENTRY_TRANS_ORIG_DESC      */
	4,          /* ENTRY_TRANS_TYPE           */
	5,          /* ENTRY_TRANS_AMOUNT         */
	6,          /* ENTRY_TRANS_BALANCE        */
	7,          /* ENTRY_TRANS_CATEGORY       */
	8,          /* ENTRY_TRANS_LABELS         */

	1,          /* ENTRY_ACCOUNT_NAME         */
	2,          /* ENTRY_ACCOUNT_STATUS       */
	3,          /* ENTRY_ACCOUNT_STATE        */
	4,          /* ENTRY_ACCOUNT_ALT_NAMES    */
};

//----------------------------------------------------------------------------
// Restore
//----------------------------------------------------------------------------
void Parser::restore()
{
    sDateFormat = cDefaultDateFormat;
    sEntryList.clear();
    for( int i = 0; i < ENTRY_CNT; i++ )
    {
        sEntryList.push_back( cDefaultEntryList[i] );
    }
} // Parser::restore()

//----------------------------------------------------------------------------
// Parse File
//----------------------------------------------------------------------------
void Parser::parseFile
    (
    QTextStream& aTextStream
    )
{
    // Parse
    QString logStr;
    aTextStream.seek(0);
    TransactionManager::mFirstTransactionDate = QDate::currentDate();
    TransactionManager::mLastTransactionDate.setDate(1900,1,1);
    while( !aTextStream.atEnd() )
    {
        QString line = aTextStream.readLine();
        TransactionManager::mFileContents.push_back( line );
        QStringList tokens = line.split(',');
        if( tokens.size() > 0 && tokens[0] != "" && tokens[0] != "Date" && !tokens[0].contains("_____") )
        {
            if( tokens[0] == "Account" )
            {
                // Add to account list
                Account* account = new Account();
                account->setName( tokens[sEntryList[ENTRY_ACCOUNT_NAME]] );
                QString altNames = tokens[sEntryList[ENTRY_ACCOUNT_ALT_NAMES]];
                if( !altNames.isEmpty() )
                {
                    account->setAlternateNames( altNames.split(';') );
                }
                account->setStatus( ( tokens[sEntryList[ENTRY_ACCOUNT_STATUS]] == "Open" ) ? Account::STATUS_OPEN : Account::STATUS_CLOSED );
                account->setAccountComplete( ( tokens[sEntryList[ENTRY_ACCOUNT_STATE]] == "Complete" ) ? true : false );
                TransactionManager::mAccountList.push_back( account );
                logStr = "Adding account:" + QString(account->getInfo());
                Logger::logString( logStr );
            }
            else
            {
                // Add to transaction list
                Transaction* transaction = new Transaction();
                QString accountName = "No Account found";
                for( int i = TransactionManager::mAccountList.size()-1; i >= 0; --i )
                {
                    if( TransactionManager::mAccountList[i]->isAccountMatch( tokens[sEntryList[ENTRY_TRANS_ACCOUNT_NAME]] ) )
                    {
                        transaction->setAccount( TransactionManager::mAccountList[i] );
                        accountName = TransactionManager::mAccountList[i]->getName();
                        TransactionManager::mAccountList[i]->addTransaction( transaction );
                        break;
                    }
                }
                transaction->setTransactionDate( QDate::fromString( tokens[sEntryList[ENTRY_TRANS_DATE]], cDateFormatList[sDateFormat] ) );
                transaction->setNumber( TransactionManager::mTransactionList.size() );
                transaction->setDescription( tokens[sEntryList[ENTRY_TRANS_DESCRIPTION]] );
                transaction->setOriginalDescription( tokens[sEntryList[ENTRY_TRANS_ORIG_DESC]] );
                transaction->setType( ( tokens[sEntryList[ENTRY_TRANS_TYPE]] == "debit" ) ? Transaction::TRANSACTION_DEBIT : Transaction::TRANSACTION_CREDIT );
                transaction->setAmount( tokens[sEntryList[ENTRY_TRANS_AMOUNT]].toFloat() );
                transaction->setCurrentBalance( tokens[sEntryList[ENTRY_TRANS_BALANCE]].toFloat() );
                transaction->setCategory( Category::getCategoryId( tokens[sEntryList[ENTRY_TRANS_CATEGORY]] ) );
                transaction->setLabels( tokens[sEntryList[ENTRY_TRANS_LABELS]].split(' ',QString::SkipEmptyParts) );
                TransactionManager::mTransactionList.push_back( transaction );
                logStr = "Adding to account:" + QString(accountName) + QString(transaction->getInfo());
                Logger::logString( logStr );

                // Update transaction dates
                if( transaction->getTransactionDate() < TransactionManager::mFirstTransactionDate )
                {
                    TransactionManager::mFirstTransactionDate = transaction->getTransactionDate();
                }
                if( transaction->getTransactionDate() > TransactionManager::mLastTransactionDate )
                {
                    TransactionManager::mLastTransactionDate = transaction->getTransactionDate();
                }
            }
        }
    }
    
    // Update account info
    for( int i = 0; i < TransactionManager::mAccountList.size(); i++ )
    {
        TransactionManager::mAccountList[i]->updateData();
        Logger::logString( QString(TransactionManager::mAccountList[i]->getInfo()) );
    }
} // Parser::parseFile
