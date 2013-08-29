//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Parser.h
//******************************************************************************

#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <QTextStream>
#include <QList>

#include "Account.h"
#include "Transaction.h"

class Parser
{
public:
    // Types
    enum EntryType
    {
        ENTRY_TRANS_DATE,
        ENTRY_TRANS_ACCOUNT_NAME,
        ENTRY_TRANS_DESCRIPTION,
	    ENTRY_TRANS_ORIG_DESC,
	    ENTRY_TRANS_TYPE,
	    ENTRY_TRANS_AMOUNT,
	    ENTRY_TRANS_BALANCE,
	    ENTRY_TRANS_CATEGORY,
	    ENTRY_TRANS_LABELS,

	    ENTRY_ACCOUNT_NAME,
	    ENTRY_ACCOUNT_STATUS,
	    ENTRY_ACCOUNT_STATE,
	    ENTRY_ACCOUNT_ALT_NAMES,

        ENTRY_CNT
    };
    enum DateFormatType
    {
        DATE_FORMAT_Mdyy_SLASH,
        DATE_FORMAT_Mdyy_HYPHEN,
        DATE_FORMAT_Mdyyyy_SLASH,
        DATE_FORMAT_Mdyyyy_HYPHEN,
        DATE_FORMAT_yyMd_SLASH,
        DATE_FORMAT_yyMd_HYPHEN,
        DATE_FORMAT_yyyyMd_SLASH,
        DATE_FORMAT_yyyyMd_HYPHEN,
        DATE_FORMAT_dMyy_SLASH,
        DATE_FORMAT_dMyy_HYPHEN,
        DATE_FORMAT_dMyyyy_SLASH,
        DATE_FORMAT_dMyyyy_HYPHEN,

        DATE_FORMAT_CNT,
        DATE_FORMAT_CUSTOM = DATE_FORMAT_CNT
    };
    enum SeparatorType
    {
        SEPARATOR_COMMA,
        SEPARATOR_PIPE,

        SEPARATOR_CNT
    };
    struct ConfigType
    {
        QString mName;
        DateFormatType mDateFormat;
        QString mDateFormatStr;
        SeparatorType mSeparator;
        QString mAccountTag;
        bool mTransactionUseTag;
        QString mTransactionTag;
        QVector<int> mEntryList;
        ConfigType(): mDateFormat(cDefaultDateFormat), mSeparator(cDefaultSeparator),
                      mAccountTag(cDefaultAccountTag), mTransactionUseTag(cDefaultTransactionUseTag), mTransactionTag(cDefaultTransactionTag),
                      mEntryList( ENTRY_CNT, INVALID_COLUMN ){}
        QString getEntry( const QStringList& aTokenList, int aEntry )
        {
            QString token;
            if( aEntry < ENTRY_CNT && mEntryList[aEntry] != INVALID_COLUMN && mEntryList[aEntry] < aTokenList.size() )
            {
                token = aTokenList[ mEntryList[aEntry] ];
            }
            return token;
        }
    };
    
    // Functions
    static void init();
    static void applyConfig( int aConfigIdx );
    static void parseFile( QTextStream& aTextStream );
    static void parseConfigFile( QFile& aConfigFile );
        
    // Variables
    static const int MAX_COLUMNS = 12;
    static const int INVALID_COLUMN = 0xffff;
    static const int DEFAULT_CONFIG_IDX = 0;
    static const int CUSTOM_CONFIG_IDX = 1;

    static const char* cDateFormatList[];
    static const char cSeparatorList[];

    static const DateFormatType cDefaultDateFormat;
    static const SeparatorType cDefaultSeparator;
    static const QString cDefaultAccountTag;
    static const bool cDefaultTransactionUseTag;
    static const QString cDefaultTransactionTag;
    static const int cDefaultEntryList[];

    static ConfigType sConfig;
    static int sPresetSelected;
    static QList<ConfigType> sPresetConfigList;

private:
    // Variables
};

#endif // PARSER_H
