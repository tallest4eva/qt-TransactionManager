//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Parser.cpp
//******************************************************************************

#include <QString>
#include <QStringList>
#include <QtXml>
#include <QDebug>

#include "Parser.hpp"
#include "Category.hpp"
#include "Logger.hpp"
#include "Month.hpp"
#include "TransactionManager.hpp"

// Const variables
const int Parser::MAX_COLUMNS = 12;
const int Parser::INVALID_COLUMN = 0xffff;
const int Parser::DEFAULT_CONFIG_IDX = 0;
const int Parser::CUSTOM_CONFIG_IDX = 1;

const Parser::DateFormatType Parser::cDefaultDateFormat = Parser::DATE_FORMAT_yyyyMd_HYPHEN;
const Parser::SeparatorType Parser::cDefaultSeparator = Parser::SEPARATOR_COMMA;
const QString Parser::cDefaultAccountTag = "Account";
const QString Parser::cDefaultTransactionTag = "Transaction";
const bool Parser::cDefaultTransactionUseTag = true;
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
    '|',     // SEPARATOR_PIPE,
};
static const QString sConfigFileName = "config.cfg";
static const QString TAG_CONFIGS = "configs";
static const QString TAG_CONFIG = "config";
static const QString TAG_CATEGORY = "category";
static const QString TAG_LABEL = "label";

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
        parseConfigFile( file );
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
            QString expStr;
            switch( sConfig.mSeparator )
            {
            case SEPARATOR_PIPE:
                expStr = "(?:^|\\|)(\"(?:[^\"]+|\"\")*\"|[^\\|]*)";
                break;
            case SEPARATOR_COMMA:
            default:
                expStr = "(?:^|,)(\"(?:[^\"]+|\"\")*\"|[^,]*)";
                break;
            }
            int position = 0;
            QRegExp regEx( expStr );
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
            //qDebug() << line; for( int i = 0; i < tokens.size(); i++ ){ qDebug() << "Item: " << QString::number(i) << ": " << tokens[i]; }
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
                Account::addAccount( account );
            }
            else if( !sConfig.mTransactionUseTag || tokens[0] == sConfig.mTransactionTag )
            {
                // Add to transaction list
                QString dateFormat = ( sConfig.mDateFormat == DATE_FORMAT_CUSTOM ) ? sConfig.mDateFormatStr : cDateFormatList[sConfig.mDateFormat];
                QDate date = QDate::fromString( sConfig.getEntry(tokens, ENTRY_TRANS_DATE), dateFormat );
                Category::CategoryIdxType categoryId = Category::getCategoryIndex( sConfig.getEntry(tokens, ENTRY_TRANS_CATEGORY) );

                // Skip invalid transactions
                if( !date.isValid() || Category::getParentCategoryId( categoryId ) == Category::EXCLUDE ){ continue; }

                Transaction* transaction = new Transaction();
                transaction->setTransactionDate( date );
                Account::addToAccount( sConfig.getEntry(tokens, ENTRY_TRANS_ACCOUNT_NAME), transaction, true );
                Month::addToMonth( transaction->getTransactionDate(), transaction );
                transaction->setNumber( TransactionManager::sTransactionList.size() );
                transaction->setDescription( sConfig.getEntry(tokens, ENTRY_TRANS_DESCRIPTION) );
                transaction->setAmount( sConfig.getEntry(tokens, ENTRY_TRANS_AMOUNT).remove(',').toFloat() );
                transaction->setCategoryLabel( sConfig.getEntry(tokens, ENTRY_TRANS_CATEGORY) );
                transaction->setLabels( sConfig.getEntry(tokens, ENTRY_TRANS_LABELS).split(' ',QString::SkipEmptyParts) );
                transaction->setOriginalDescription( sConfig.getEntry(tokens, ENTRY_TRANS_ORIG_DESC) );
                if( sConfig.mEntryList[ENTRY_TRANS_TYPE] != INVALID_COLUMN && !sConfig.getEntry(tokens, ENTRY_TRANS_TYPE).isEmpty() )
                {
                    transaction->setType( ( sConfig.getEntry(tokens, ENTRY_TRANS_TYPE) == "debit" ) ? Transaction::TRANSACTION_DEBIT : Transaction::TRANSACTION_CREDIT );
                }
                if( sConfig.mEntryList[ENTRY_TRANS_BALANCE] != INVALID_COLUMN && !sConfig.getEntry(tokens, ENTRY_TRANS_BALANCE).isEmpty() )
                {
                    transaction->setCurrentBalance( sConfig.getEntry(tokens, ENTRY_TRANS_BALANCE).remove(',').toFloat() );
                }
                TransactionManager::sTransactionList.push_back( transaction );
                //qDebug() << "Adding to account:" << transaction->getAccount()->getName() << transaction->getInfo();

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
void Parser::parseConfigFile
    (
    QFile& aConfigFile
    )
{
    QDomDocument doc( "configFile" );
    QString errorMsg;
    int errorLine = 0;
    int errorColumn = 0;
    if( !doc.setContent( &aConfigFile, &errorMsg, &errorLine, &errorColumn ) )
    {
        Logger::logString( "Error. Failed to parse config.cfg file: " + errorMsg + "Line: " + QString::number(errorLine) + "Column: " + QString::number(errorColumn), Logger::LOG_ERROR );
        return;
    }

    QDomElement configsElement = doc.firstChildElement( TAG_CONFIGS );
    if( !configsElement.isNull() )
    {
        bool sortCategoryList = false;
        bool sortLabelList = false;
        for( QDomElement element = configsElement.firstChildElement(); !element.isNull(); element = element.nextSiblingElement() )
        {
            // Get config content
            if( element.tagName() == TAG_CONFIG )
            {
                ConfigType config;
                config.mName = element.attribute("name");

                // Get config date format
                QDomElement childElement = element.firstChildElement("dateFormat");
                if( !childElement.isNull() && !childElement.text().isEmpty() )
                {
                    QString dateFormat = childElement.text();
                    dateFormat.replace("MM", "M");
                    dateFormat.replace("dd", "d");
                    bool found = false;
                    for( int i = 0; i < DATE_FORMAT_CNT; i++ )
                    {
                        if( dateFormat == cDateFormatList[i] )
                        {
                            config.mDateFormat = (DateFormatType)i;
                            found = true;
                            break;
                        }
                    }
                    if( !found )
                    {
                        config.mDateFormat = DATE_FORMAT_CUSTOM;
                        config.mDateFormatStr = dateFormat;
                    }
                }

                // Get config account info
                childElement = element.firstChildElement("account");
                if( !childElement.isNull() )
                {
                    if( !childElement.attribute("keyword").isEmpty() ){         config.mAccountTag = childElement.attribute("keyword"); }
                    if( !childElement.attribute("name").isEmpty() ){            config.mEntryList[ENTRY_ACCOUNT_NAME] = childElement.attribute("name").toInt(); }
                    if( !childElement.attribute("status").isEmpty() ){          config.mEntryList[ENTRY_ACCOUNT_STATUS] = childElement.attribute("status").toInt(); }
                    if( !childElement.attribute("state").isEmpty() ){           config.mEntryList[ENTRY_ACCOUNT_STATE] = childElement.attribute("state").toInt(); }
                    if( !childElement.attribute("alternateNames").isEmpty() ){  config.mEntryList[ENTRY_ACCOUNT_ALT_NAMES] = childElement.attribute("alternateNames").toInt(); }
                }

                // Get config transaction info
                childElement = element.firstChildElement("transaction");
                if( !childElement.isNull() )
                {
                    config.mTransactionUseTag = false;
                    if( !childElement.attribute("keyword").isEmpty() )
                    {
                        config.mTransactionUseTag = true;
                        config.mTransactionTag = childElement.attribute("keyword");
                    }
                    if( !childElement.attribute("date").isEmpty() ){                config.mEntryList[ENTRY_TRANS_DATE] = childElement.attribute("date").toInt(); }
                    if( !childElement.attribute("name").isEmpty() ){                config.mEntryList[ENTRY_TRANS_ACCOUNT_NAME] = childElement.attribute("name").toInt(); }
                    if( !childElement.attribute("description").isEmpty() ){         config.mEntryList[ENTRY_TRANS_DESCRIPTION] = childElement.attribute("description").toInt(); }
                    if( !childElement.attribute("originalDescription").isEmpty() ){ config.mEntryList[ENTRY_TRANS_ORIG_DESC] = childElement.attribute("originalDescription").toInt(); }
                    if( !childElement.attribute("type").isEmpty() ){                config.mEntryList[ENTRY_TRANS_TYPE] = childElement.attribute("type").toInt(); }
                    if( !childElement.attribute("amount").isEmpty() ){              config.mEntryList[ENTRY_TRANS_AMOUNT] = childElement.attribute("amount").toInt(); }
                    if( !childElement.attribute("balance").isEmpty() ){             config.mEntryList[ENTRY_TRANS_BALANCE] = childElement.attribute("balance").toInt(); }
                    if( !childElement.attribute("category").isEmpty() ){            config.mEntryList[ENTRY_TRANS_CATEGORY] = childElement.attribute("category").toInt(); }
                    if( !childElement.attribute("labels").isEmpty() ){              config.mEntryList[ENTRY_TRANS_LABELS] = childElement.attribute("labels").toInt(); }
                }

                // Update default config using config file
                if( config.mName == "Default Config" )
                {
                    sPresetConfigList[ DEFAULT_CONFIG_IDX ] = config;
                    sPresetConfigList[ CUSTOM_CONFIG_IDX ] = config;
                    sPresetConfigList[ CUSTOM_CONFIG_IDX ].mName = "Custom Config";
                }
                else
                {
                    sPresetConfigList.push_back( config );
                }
            } // if element.tagName() == TAG_CONFIG

            else if( element.tagName() == TAG_CATEGORY )
            {
                QString categoryStr = element.attribute("category");
                QString subCategoryStr = element.attribute("subCategory");
                QString typeStr = element.attribute("type");
                // If new category is defined
                if( !categoryStr.isEmpty() && !subCategoryStr.isEmpty() )
                {
                    Category category;
                    category.parentCategory = Category::getParentCategoryId( categoryStr );
                    category.text = subCategoryStr;
                    if( !typeStr.isEmpty() )
                    {
                        if( typeStr == "transfer" ){ category.type = Category::TRANSACTION_TYPE_TRANSFER; }
                        else if( typeStr == "income" ){ category.type = Category::TRANSACTION_TYPE_INCOME; }
                        else if( typeStr == "balance" ){ category.type = Category::TRANSACTION_TYPE_BALANCE; }
                        // else default to expense
                    }
                    Category::addCategory( category );
                    sortCategoryList = true;
                }
            } // if element.tagName() == TAG_CATEGORY

            else if( element.tagName() == TAG_LABEL )
            {
                QString labelStr = element.attribute("name");
				Category::addLabel( labelStr );
				sortLabelList = true;
			} // if element.tagName() == TAG_CATEGORY
        } // for element

        // Sort Category list
        if( sortCategoryList )
        {
            Category::orderCategoryList();
        }
		if( sortLabelList )
		{
            Category::orderLabelList();
		}
    }
} // Parser::parseConfigFile
