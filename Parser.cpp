//******************************************************************************
//
//  HEADER NAME: Parser.cpp
//******************************************************************************

#include <QString>
#include <QStringList>

#include "Parser.h"
#include "Category.h"
//#include "Logger.h"
#include "Month.h"
#include "TransactionManager.h"

// Static variables
const Parser::DateFormatType Parser::cDefaultDateFormat = Parser::DATE_FORMAT_MMddyy_SLASH;
Parser::DateFormatType Parser::sDateFormat = Parser::cDefaultDateFormat;
const Parser::SeparatorType Parser::cDefaultSeparator = Parser::SEPARATOR_COMMA;
Parser::SeparatorType Parser::sSeparator = Parser::cDefaultSeparator;
QVector<int> Parser::sEntryList;
const QString Parser::cDefaultAccountTag = "Account";
const QString Parser::cDefaultTransactionTag = "Transaction";
QString Parser::sAccountTag;
QString Parser::sTransactionTag;

const char* Parser::cDateFormatList[] =
{
    "MM/dd/yy",     // DATE_FORMAT_MMddyy_SLASH
    "MM-dd-yy",     // DATE_FORMAT_MMddyy_HYPHEN,
    "MM/dd/yyyy",   // DATE_FORMAT_MMddyyyy_SLASH,
    "MM-dd-yyyy",   // DATE_FORMAT_MMddyyyy_HYPHEN,
    "M/d/yyyy",     // DATE_FORMAT_Mdyyyy_SLASH,
    "M-d-yyyy",     // DATE_FORMAT_Mdyyyy_HYPHEN,
    "yy/MM/dd",     // DATE_FORMAT_yyMMdd_SLASH,
    "yy-MM-dd",     // DATE_FORMAT_yyMMdd_HYPHEN,
    "yyyy/MM/dd",   // DATE_FORMAT_yyyyMMdd_SLASH,
    "yyyy-MM-dd",   // DATE_FORMAT_yyyyMMdd_HYPHEN,
    "dd/MM/yy",     // DATE_FORMAT_ddMMyy_SLASH,
    "dd-MM-yy",     // DATE_FORMAT_ddMMyy_HYPHEN,
    "dd/MM/yyyy",   // DATE_FORMAT_ddMMyyyy_SLASH,
    "dd-MM-yyyy",   // DATE_FORMAT_ddMMyyyy_HYPHEN,
};
const char Parser::cSeparatorList[] =
{
    ',',     // SEPARATOR_COMMA
    ';',     // SEPARATOR_SEMI_COLON,
};

const int Parser::cDefaultEntryList[] =
{
    1,          /* ENTRY_TRANS_DATE           */
    2,          /* ENTRY_TRANS_ACCOUNT_NAME   */
    3,          /* ENTRY_TRANS_DESCRIPTION    */
	4,          /* ENTRY_TRANS_ORIG_DESC      */
	5,          /* ENTRY_TRANS_TYPE           */
	6,          /* ENTRY_TRANS_AMOUNT         */
	7,          /* ENTRY_TRANS_BALANCE        */
	8,          /* ENTRY_TRANS_CATEGORY       */
	9,          /* ENTRY_TRANS_LABELS         */

	2,          /* ENTRY_ACCOUNT_NAME         */
	3,          /* ENTRY_ACCOUNT_STATUS       */
	4,          /* ENTRY_ACCOUNT_STATE        */
	5,          /* ENTRY_ACCOUNT_ALT_NAMES    */
};

//----------------------------------------------------------------------------
// Restore
//----------------------------------------------------------------------------
void Parser::restore()
{
    sDateFormat = cDefaultDateFormat;
    sSeparator = cDefaultSeparator;
    sEntryList.clear();
    for( int i = 0; i < ENTRY_CNT; i++ )
    {
        sEntryList.push_back( cDefaultEntryList[i] );
    }
    sAccountTag = cDefaultAccountTag;
    sTransactionTag = cDefaultTransactionTag;
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
    TransactionManager::sFirstTransactionDate = QDate::currentDate();
    while( !aTextStream.atEnd() )
    {
        QString line = aTextStream.readLine();
        TransactionManager::sFileContents.push_back( line );
        QStringList tokens = line.split( cSeparatorList[sSeparator] );
        if( tokens.size() > 0 && tokens[0] != "" )
        {
            if( tokens[0] == sAccountTag )
            {
                // Fill tokens list to prevent memory error
                int difference = sEntryList[ENTRY_ACCOUNT_ALT_NAMES] - (tokens.size()-1);
                for( int i = 0; i < difference; i++ ){ tokens.push_back(""); }

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
                TransactionManager::sAccountList.push_back( account );
                //logStr = "Adding account:" + QString(account->getInfo());
                //Logger::logString( logStr );
            }
            else if( tokens[0] == sTransactionTag )
            {
                // Fill tokens list to prevent memory error
                int difference = sEntryList[ENTRY_TRANS_LABELS] - (tokens.size()-1);
                for( int i = 0; i < difference; i++ ){ tokens.push_back(""); }

                // Add to transaction list
                Transaction* transaction = new Transaction();
                Account::addToAccount( tokens[sEntryList[ENTRY_TRANS_ACCOUNT_NAME]], transaction ); 
                QDate date = QDate::fromString( tokens[sEntryList[ENTRY_TRANS_DATE]], cDateFormatList[sDateFormat] );
                if( date.isValid() )
                {
                    transaction->setTransactionDate( date );
                }
                Month::addToMonth( transaction->getTransactionDate(), transaction );
                transaction->setNumber( TransactionManager::sTransactionList.size() );
                transaction->setDescription( tokens[sEntryList[ENTRY_TRANS_DESCRIPTION]] );
                transaction->setOriginalDescription( tokens[sEntryList[ENTRY_TRANS_ORIG_DESC]] );
                transaction->setType( ( tokens[sEntryList[ENTRY_TRANS_TYPE]] == "debit" ) ? Transaction::TRANSACTION_DEBIT : Transaction::TRANSACTION_CREDIT );
                transaction->setAmount( tokens[sEntryList[ENTRY_TRANS_AMOUNT]].toFloat() );
                transaction->setCurrentBalance( tokens[sEntryList[ENTRY_TRANS_BALANCE]].toFloat() );
                transaction->setCategory( Category::getCategoryId( tokens[sEntryList[ENTRY_TRANS_CATEGORY]] ) );
                transaction->setLabels( tokens[sEntryList[ENTRY_TRANS_LABELS]].split(' ',QString::SkipEmptyParts) );
                TransactionManager::sTransactionList.push_back( transaction );
                //logStr = "Adding to account:" + QString(transaction->getAccount()->getName()) + QString(transaction->getInfo());
                //Logger::logString( logStr );

                // Update transaction dates
                if( transaction->getTransactionDate() < TransactionManager::sFirstTransactionDate )
                {
                    TransactionManager::sFirstTransactionDate = transaction->getTransactionDate();
                }
                if( transaction->getTransactionDate() > TransactionManager::sLastTransactionDate )
                {
                    TransactionManager::sLastTransactionDate = transaction->getTransactionDate();
                }
                // Update values
                TransactionManager::sCategoriesEnabledList[ (int)transaction->getCategory() ] = true;
                QList<Category::LabelIdType> labels = transaction->getLabels();
                for( int i = 0; i < labels.size(); i++ )
                {
                    TransactionManager::sLabelsEnabledList[ (int)labels[i] ] = true;
                }
            }
        }
    }
    
    // update lists
    Account::updateAccountList();
    Month::updateMonthList();
} // Parser::parseFile
