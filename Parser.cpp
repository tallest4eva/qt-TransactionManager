//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Parser.cpp
//******************************************************************************

#include <QFile>
#include <QString>
#include <QStringList>

#include "Parser.h"
#include "Category.h"
//#include "Logger.h"
#include "Month.h"
#include "TransactionManager.h"

// Const variables
const Parser::DateFormatType Parser::cDefaultDateFormat = Parser::DATE_FORMAT_Mdyy_SLASH;
const Parser::SeparatorType Parser::cDefaultSeparator = Parser::SEPARATOR_COMMA;
const QString Parser::cDefaultAccountTag = "Account";
const QString Parser::cDefaultTransactionTag = "Transaction";
const bool Parser::cDefaultTransactionUseTag = true;
const bool Parser::cDefaultAccountRequireTag = true;
const int Parser::cDefaultEntryList[] =
{
    1,              /* ENTRY_TRANS_DATE           */
    2,              /* ENTRY_TRANS_ACCOUNT_NAME   */
    3,              /* ENTRY_TRANS_DESCRIPTION    */
	INVALID_COLUMN, /* ENTRY_TRANS_ORIG_DESC      */
	5,              /* ENTRY_TRANS_TYPE           */
	6,              /* ENTRY_TRANS_AMOUNT         */
	7,              /* ENTRY_TRANS_BALANCE        */
	8,              /* ENTRY_TRANS_CATEGORY       */
	9,              /* ENTRY_TRANS_LABELS         */
    
	2,              /* ENTRY_ACCOUNT_NAME         */
	3,              /* ENTRY_ACCOUNT_STATUS       */
	4,              /* ENTRY_ACCOUNT_STATE        */
	5,              /* ENTRY_ACCOUNT_ALT_NAMES    */
};
const char* Parser::cDateFormatList[] =
{
    "M/d/yy",     // DATE_FORMAT_Mdyy_SLASH
    "M-d-yy",     // DATE_FORMAT_Mdyy_HYPHEN,
    "M/d/yyyy",   // DATE_FORMAT_Mdyyyy_SLASH,
    "M-d-yyyy",   // DATE_FORMAT_Mdyyyy_HYPHEN,
    "yy/M/d",     // DATE_FORMAT_yyMd_SLASH,
    "yy-M-d",     // DATE_FORMAT_yyMd_HYPHEN,
    "yyyy/M/d",   // DATE_FORMAT_yyyyMd_SLASH,
    "yyyy-M-d",   // DATE_FORMAT_yyyyMd_HYPHEN,
    "d/M/yy",     // DATE_FORMAT_dMyy_SLASH,
    "d-M-yy",     // DATE_FORMAT_dMyy_HYPHEN,
    "d/M/yyyy",   // DATE_FORMAT_dMyyyy_SLASH,
    "d-M-yyyy",   // DATE_FORMAT_dMyyyy_HYPHEN,
};
const char Parser::cSeparatorList[] =
{
    ',',     // SEPARATOR_COMMA
    ';',     // SEPARATOR_SEMI_COLON,
};
static const QString sConfigFileName = "config.cfg";

// Static variables
Parser::ConfigType Parser::sConfig;
int Parser::sPresetSelected = Parser::DEFAULT_CONFIG_IDX;
QList<Parser::ConfigType> Parser::sPresetConfigList;

//----------------------------------------------------------------------------
// Init
//----------------------------------------------------------------------------
void Parser::init()
{
    // Create preset config list
    sPresetConfigList.clear();
    ConfigType config;
    config.mName = "Default Config";
    for( int i = 0; i < ENTRY_CNT; i++ ){ config.mEntryList[i] = cDefaultEntryList[i]; }
    sPresetConfigList.push_back( config );
    ConfigType customConfig = config;
    customConfig.mName = "Custom Config";
    sPresetConfigList.push_back( customConfig );

    // Load configs from file
    QFile file(sConfigFileName);
    if( file.open( QIODevice::ReadOnly ) )
    {
        QTextStream inStream( &file );
        // Skip header line
        QString line = inStream.readLine();
        while( !inStream.atEnd() )
        {
            line = inStream.readLine();
            ConfigType config;
            if( !line.isEmpty() && parseConfigFile(line, config ) )
            {
                sPresetConfigList.push_back( config );
            }
        }
        file.close();
    }

    // Set to default
    applyConfig( DEFAULT_CONFIG_IDX );
} // Parser::init()

//----------------------------------------------------------------------------
// applyConfig
//----------------------------------------------------------------------------
void Parser::applyConfig( int aConfigIdx )
{
    if( aConfigIdx < sPresetConfigList.size() )
    {
        sConfig = sPresetConfigList[aConfigIdx];
        sPresetSelected = aConfigIdx;
    }
} // Parser::applyConfig()

//----------------------------------------------------------------------------
// Parse File
//----------------------------------------------------------------------------
void Parser::parseFile
    (
    QTextStream& aTextStream
    )
{
    // Parse input file
    aTextStream.seek(0);
    QDate firstDate = QDate::currentDate();
    QChar separator = cSeparatorList[sConfig.mSeparator];
    while( !aTextStream.atEnd() )
    {
        QString line = aTextStream.readLine();
        TransactionManager::sFileContents.push_back( line );

        // Skip empty lines
        if( line.isEmpty() ){ continue; }
        
        QStringList tokens;
        if( line.contains("\"") )
        {
            // Handle double quotes with csv reader
	        int position = 0;
            QRegExp regEx("(?:^|,)(\"(?:[^\"]+|\"\")*\"|[^,]*)");
	        while( line.size() > position && (position = regEx.indexIn(line, position)) != -1 )
            {
		        QString col;
		        if( regEx.cap(1).size() > 0 )
                {
			        col = regEx.cap(1);
                }
		        else if( regEx.cap(2).size() > 0 )
                {
			        col = regEx.cap(2);
                }
                position += ( col.size() ) ? regEx.matchedLength() : 1;
                col.remove('\"');
		        tokens << col;
	        }
        }
        else
        {
            // Use regular comma splitter
            tokens = line.split( separator );
        }
        if( tokens.size() > 0 )
        {
            if( tokens[0] == sConfig.mAccountTag )
            {
                // Add to account list
                Account* account = new Account();
                if( sConfig.mEntryList[ENTRY_ACCOUNT_NAME] != INVALID_COLUMN ){ account->setName( sConfig.getEntry(tokens, ENTRY_ACCOUNT_NAME) ); }
                QString altNames = sConfig.getEntry(tokens, ENTRY_ACCOUNT_ALT_NAMES);
                if( !altNames.isEmpty() ){ account->setAlternateNames( altNames.split(';') ); }
                account->setStatus( ( sConfig.getEntry(tokens, ENTRY_ACCOUNT_STATUS) == "Closed" ) ? Account::STATUS_CLOSED : Account::STATUS_OPEN );
                account->setAccountComplete( ( sConfig.getEntry(tokens, ENTRY_ACCOUNT_STATE) == "Incomplete" ) ? false : true );
                TransactionManager::sAccountList.push_back( account );
                //Logger::logString( "Adding account:" + QString(account->getInfo()) );
            }
            else if( !sConfig.mTransactionUseTag || tokens[0] == sConfig.mTransactionTag )
            {
                // Add to transaction list
                QString dateFormat = ( sConfig.mDateFormat == DATE_FORMAT_CUSTOM ) ? sConfig.mDateFormatStr : cDateFormatList[sConfig.mDateFormat];
                QDate date = QDate::fromString( sConfig.getEntry(tokens, ENTRY_TRANS_DATE), dateFormat );
                if( !date.isValid() ){ continue; }
                Transaction* transaction = new Transaction();
                transaction->setTransactionDate( date );
                Account::addToAccount( sConfig.getEntry(tokens, ENTRY_TRANS_ACCOUNT_NAME), transaction, !sConfig.mAccountRequireTag );
                Month::addToMonth( transaction->getTransactionDate(), transaction );
                transaction->setNumber( TransactionManager::sTransactionList.size() );
                transaction->setDescription( sConfig.getEntry(tokens, ENTRY_TRANS_DESCRIPTION) );
                transaction->setAmount( sConfig.getEntry(tokens, ENTRY_TRANS_AMOUNT).toFloat() );
                transaction->setCategory( Category::getCategoryId( sConfig.getEntry(tokens, ENTRY_TRANS_CATEGORY) ) );
                transaction->setLabels( sConfig.getEntry(tokens, ENTRY_TRANS_LABELS).split(' ',QString::SkipEmptyParts) );
                transaction->setOriginalDescription( sConfig.getEntry(tokens, ENTRY_TRANS_ORIG_DESC) );
                if( sConfig.mEntryList[ENTRY_TRANS_TYPE] != INVALID_COLUMN && !sConfig.getEntry(tokens, ENTRY_TRANS_TYPE).isEmpty() )
                {
                    transaction->setType( ( sConfig.getEntry(tokens, ENTRY_TRANS_TYPE) == "debit" ) ? Transaction::TRANSACTION_DEBIT : Transaction::TRANSACTION_CREDIT );
                }
                if( sConfig.mEntryList[ENTRY_TRANS_BALANCE] != INVALID_COLUMN && !sConfig.getEntry(tokens, ENTRY_TRANS_BALANCE).isEmpty() )
                {
                    transaction->setCurrentBalance( sConfig.getEntry(tokens, ENTRY_TRANS_BALANCE).toFloat() );
                }
                TransactionManager::sTransactionList.push_back( transaction );
                //Logger::logString( "Adding to account:" + QString(transaction->getAccount()->getName()) + QString(transaction->getInfo()) );

                // Update transaction dates / values
                if( transaction->getTransactionDate() < firstDate )
                {
                    firstDate = transaction->getTransactionDate();
                }
                if( transaction->getTransactionDate() > TransactionManager::sLastTransactionDate )
                {
                    TransactionManager::sLastTransactionDate = transaction->getTransactionDate();
                }
                TransactionManager::sCategoriesEnabledList[ (int)transaction->getCategory() ] = true;
                QList<Category::LabelIdType> labels = transaction->getLabels();
                for( int i = 0; i < labels.size(); i++ )
                {
                    TransactionManager::sLabelsEnabledList[ (int)labels[i] ] = true;
                }
            }
        }
    }
    
    // update dates and lists
    if( firstDate < QDate::currentDate() )
    {
        TransactionManager::sFirstTransactionDate = firstDate;
    }
    Account::updateAccountList();
    Month::updateMonthList();
} // Parser::parseFile

//----------------------------------------------------------------------------
// parseConfigFile
//----------------------------------------------------------------------------
bool Parser::parseConfigFile
    (
    const QString& aLine,
    ConfigType& aInConfig
    )
{
    bool success = false;
    QStringList tokens = aLine.split(',');
    if( tokens.size() == CONFIG_ENTRY_CNT )
    {
        // Read config file line
        aInConfig.mName = tokens[CONFIG_ENTRY_NAME];
        QString dateFormat = tokens[CONFIG_ENTRY_DATE];
        if( !dateFormat.isEmpty() )
        {
            dateFormat.replace("MM", "M");
            dateFormat.replace("dd", "d");
            bool found = false;
            for( int i = 0; i < DATE_FORMAT_CNT; i++ )
            {
                if( dateFormat == cDateFormatList[i] )
                {
                    aInConfig.mDateFormat = (DateFormatType)i;
                    found = true;
                    break;
                }
            }
            if( !found )
            {
                aInConfig.mDateFormat = DATE_FORMAT_CUSTOM;
                aInConfig.mDateFormatStr = dateFormat;
            }
        }
        aInConfig.mAccountRequireTag = ( tokens[CONFIG_ENTRY_ACCOUNT_USE_KW] == "true" ) ? true : false;
        if( !tokens[CONFIG_ENTRY_ACCOUNT_KW].isEmpty() ){ aInConfig.mAccountTag = tokens[CONFIG_ENTRY_ACCOUNT_KW]; }
        aInConfig.mTransactionUseTag = ( tokens[CONFIG_ENTRY_TRANS_USE_KW] == "true" ) ? true : false;
        if( !tokens[CONFIG_ENTRY_TRANS_KW].isEmpty() ){ aInConfig.mTransactionTag = tokens[CONFIG_ENTRY_TRANS_KW]; }
        if( !tokens[CONFIG_ENTRY_ACCOUNT_COLUMNS].isEmpty() )
        {
            QStringList cols = tokens[CONFIG_ENTRY_ACCOUNT_COLUMNS].split(';');
            int idx = ENTRY_ACCOUNT_NAME;
            for( int i = 0; idx <= ENTRY_ACCOUNT_ALT_NAMES && i < cols.size(); i++ )
            {
                aInConfig.mEntryList[idx] = ( !cols[i].isEmpty() ) ? cols[i].toInt() : INVALID_COLUMN;
                idx++;
            }
        }
        if( !tokens[CONFIG_ENTRY_TRANS_COLUMNS].isEmpty() )
        {
            QStringList cols = tokens[CONFIG_ENTRY_TRANS_COLUMNS].split(';');
            int idx = ENTRY_TRANS_DATE;
            for( int i = 0; idx <= ENTRY_TRANS_LABELS && i < cols.size(); i++ )
            {
                aInConfig.mEntryList[idx] = ( !cols[i].isEmpty() ) ? cols[i].toInt() : INVALID_COLUMN;
                idx++;
            }
        }
        success = true;
    }
    return success;
} // Parser::parseConfigFile
