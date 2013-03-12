//******************************************************************************
//
//  HEADER NAME: Parser.h
//******************************************************************************

#ifndef PARSER_H
#define PARSER_H

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
        DATE_FORMAT_MMddyy_SLASH,
        DATE_FORMAT_MMddyy_HYPHEN,
        DATE_FORMAT_MMddyyyy_SLASH,
        DATE_FORMAT_MMddyyyy_HYPHEN,
        DATE_FORMAT_Mdyyyy_SLASH,
        DATE_FORMAT_Mdyyyy_HYPHEN,
        DATE_FORMAT_yyMMdd_SLASH,
        DATE_FORMAT_yyMMdd_HYPHEN,
        DATE_FORMAT_yyyyMMdd_SLASH,
        DATE_FORMAT_yyyyMMdd_HYPHEN,
        DATE_FORMAT_ddMMyy_SLASH,
        DATE_FORMAT_ddMMyy_HYPHEN,
        DATE_FORMAT_ddMMyyyy_SLASH,
        DATE_FORMAT_ddMMyyyy_HYPHEN,

        DATE_FORMAT_CNT
    };
    enum SeparatorType
    {
        SEPARATOR_COMMA,
        SEPARATOR_SEMI_COLON,

        SEPARATOR_CNT
    };
    
    // Functions
    static void restore();
    static void parseFile
        (
        QTextStream& aTextStream
        );
        
    // Variables
    static const DateFormatType cDefaultDateFormat;
    static DateFormatType sDateFormat;
    static const SeparatorType cDefaultSeparator;
    static SeparatorType sSeparator;
    static const int cDefaultEntryList[];
    static QVector<int> sEntryList;

    static const char* cDateFormatList[];
    static const char cSeparatorList[];

private:
    // Variables
};

#endif // PARSER_H
