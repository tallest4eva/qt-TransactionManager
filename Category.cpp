//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Category.cpp
//******************************************************************************

#include "Category.hpp"
#include "Logger.hpp"
#include <QDebug>

// Static variables
const char* cParentCategoryList[] =
{
    "Auto & Transport",         /* AUTO_AND_TRANSPORT  */
    "Bills & Utilities",        /* BILLS_AND_UTILITIES */
    "Business Services",        /* BUSINESS_SERVICES   */
    "Education",                /* EDUCATION           */
    "Entertainment",            /* ENTERTAINMENT       */
    "Fees & Charges",           /* FEES_AND_CHARGES    */
    "Financial",                /* FINANCIAL           */
    "Food & Dining",            /* FOOD_AND_DINING     */
    "Gifts & Donations",        /* GIFTS_AND_DONATIONS */
    "Health & Fitness",         /* HEALTH_AND_FITNESS  */
    "Home",                     /* HOME                */
    "Income",                   /* INCOME              */
    "Investments",              /* INVESTMENTS         */
    "Kids",                     /* KIDS                */
    "Loans",                    /* LOANS               */
    "Misc Expenses",            /* MISC_EXPENSES       */
    "Personal Care",            /* PERSONAL_CARE       */
    "Pets",                     /* PETS                */
    "Shopping",                 /* SHOPPING            */
    "Taxes",                    /* TAXES               */
    "Transfer",                 /* TRANSFER            */
    "Travel",                   /* TRAVEL              */
    "Uncategorized",            /* UNCATEGORIZED       */
    "Exclude",                  /* EXCLUDE             */
};

static QList<Category> sCategoryList;
Category::CategoryIdxType Category::sUnmatchedCategoryIdx = Category::UNCATEGORIZED;
static QList<QString> sLabelList;
static const QString cLabelNone = "None";
const Category::LabelIdType Category::LABEL_INVALID = -1;
const Category::LabelIdType Category::LABEL_NONE = 0;

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
Category::Category
    (
    ParentCategoryType aParentCategory,
    const QString& aText,
    bool aIsParent,
    TransactionType aType
    )
    : parentCategory( aParentCategory )
    , text( aText )
    , type( aType )
    , mIsParent( aIsParent )
{
}

//----------------------------------------------------------------------------
// Operators
//----------------------------------------------------------------------------
bool Category::operator< ( const Category& aCategory ) const
{
    if( parentCategory == aCategory.parentCategory )
    {
        if( mIsParent && !aCategory.mIsParent ){ return true; }
        if( !mIsParent && aCategory.mIsParent ){ return false; }
        return( text < aCategory.text );
    }
    return( parentCategory < aCategory.parentCategory );
}
bool Category::operator> ( const Category& aCategory ) const
{
    if( parentCategory == aCategory.parentCategory )
    {
        return( text > aCategory.text );
    }
    return( parentCategory > aCategory.parentCategory );
}

//----------------------------------------------------------------------------
// initCategoryList
//----------------------------------------------------------------------------
void Category::initCategoryList()
{
    sCategoryList.clear();

    // Add parent categories
    for( int i = 0; i < PARENT_CATEGORY_TYPE_CNT; i++ )
    {
        TransactionType transType = TRANSACTION_TYPE_EXPENSE;
        switch( i )
        {
        case INCOME:
            transType = TRANSACTION_TYPE_INCOME;
            break;
        case TRANSFER:
            transType = TRANSACTION_TYPE_TRANSFER;
            break;
        default:
            break;
        }
        sCategoryList.push_back( Category( (ParentCategoryType)i, cParentCategoryList[i], true, transType ) );
    }
    orderCategoryList();

	sLabelList.clear();
	sLabelList.push_back( cLabelNone );
} // initCategoryList

//----------------------------------------------------------------------------
// addCategory
//----------------------------------------------------------------------------
void Category::addCategory
    (
    const Category& aCategory
    )
{
    sCategoryList.push_back( aCategory );
} // Category::addCategory

//----------------------------------------------------------------------------
// getCategoryCount
//----------------------------------------------------------------------------
int Category::getCategoryCount()
{
    return sCategoryList.size();
} // Category::getCategoryCount

//----------------------------------------------------------------------------
// getCategoryIndex
//----------------------------------------------------------------------------
Category::CategoryIdxType Category::getCategoryIndex
    (
    const QString& aCategory
    )
{
    bool found = false;
    CategoryIdxType id = 0;
    for( int i = 0; i < sCategoryList.size(); i++ )
    {
        if( aCategory == sCategoryList[ i ].text )
        {
            id = (CategoryIdxType)i;
            found = true;
            break;
        }
    }
    if( !found )
    {
        // Category not found. Fall back to unmatched Uncategorized
        Logger::logString( "Could not find category: " + QString(aCategory), Logger::LOG_WARNING );
        id = sUnmatchedCategoryIdx;
    }
    return id;
} // Category::getCategoryIndex

//----------------------------------------------------------------------------
// getCategoryTransactionType
//----------------------------------------------------------------------------
Category::TransactionType Category::getCategoryTransactionType
    (
    CategoryIdxType aCategoryId
    )
{
    Category::TransactionType categoryType = TRANSACTION_TYPE_EXPENSE;
    if( aCategoryId < sCategoryList.count() )
    {
        categoryType = sCategoryList[ aCategoryId ].type;
    }
    return categoryType;
} // Category::getCategoryTransactionType

//----------------------------------------------------------------------------
// getParentCategoryId
//----------------------------------------------------------------------------
Category::ParentCategoryType Category::getParentCategoryId
    (
    const QString& aParentCategoryStr
    )
{
    ParentCategoryType id = UNCATEGORIZED;
    for( int i = 0; i < PARENT_CATEGORY_TYPE_CNT; i++ )
    {
        if( aParentCategoryStr == cParentCategoryList[i] )
        {
            id = (ParentCategoryType)i;
            break;
        }
    }
    return id;
}

//----------------------------------------------------------------------------
// getParentCategoryId
//----------------------------------------------------------------------------
Category::ParentCategoryType Category::getParentCategoryId
    (
    CategoryIdxType aCategoryId
    )
{
    ParentCategoryType id = UNCATEGORIZED;
    if( aCategoryId < sCategoryList.size() )
    {
        id = sCategoryList[ aCategoryId ].parentCategory;
    }
    return id;
} // Category::getParentCategoryId

//----------------------------------------------------------------------------
// getParentCategoryText
//----------------------------------------------------------------------------
QString Category::getParentCategoryText
    (
    ParentCategoryType aParentCategoryIdx
    )
{
    QString text;
    if( aParentCategoryIdx < PARENT_CATEGORY_TYPE_CNT )
    {
        text = cParentCategoryList[ aParentCategoryIdx ];
    }
    return text;
} // getParentCategoryText

//----------------------------------------------------------------------------
// getCategoryText
//----------------------------------------------------------------------------
QString Category::getCategoryText
    (
    CategoryIdxType aCategoryId,
    bool aFullText
    )
{
    QString text;
    if( aCategoryId < sCategoryList.size() )
    {
        if( aFullText && !sCategoryList[ aCategoryId ].mIsParent )
        {
            text = cParentCategoryList[ sCategoryList[ aCategoryId ].parentCategory ];
            text += " > ";
        }
        text += sCategoryList[ aCategoryId ].text;
    }
    return text;
} // Category::getCategoryText

//----------------------------------------------------------------------------
// orderCategoryList
//----------------------------------------------------------------------------
void Category::orderCategoryList()
{
    qSort( sCategoryList );
    sUnmatchedCategoryIdx = getCategoryIndex( cParentCategoryList[ UNCATEGORIZED ] );

    //for( int i = 0; i < sCategoryList.size(); i++ ){ qDebug() << "Category[" << i << "]=" << cParentCategoryList[sCategoryList[i].parentCategory] << sCategoryList[i].text << sCategoryList[i].type; }
} // Category::orderCategoryList

//----------------------------------------------------------------------------
// Add Label
//----------------------------------------------------------------------------
void Category::addLabel
	(
	const QString& aLabel
	)
{
	if( !sLabelList.contains( aLabel ) )
	{
		sLabelList.push_back( aLabel );
	}
}

//----------------------------------------------------------------------------
// getLabelId
//----------------------------------------------------------------------------
Category::LabelIdType Category::getLabelId
    (
    const QString& aLabel
    )
{
	int index = sLabelList.indexOf( aLabel );
    if( index == LABEL_INVALID )
    {
        Logger::logString( "Could not find label: " + aLabel, Logger::LOG_WARNING );
    }
    return index;
} // Category::getLabelId

//----------------------------------------------------------------------------
// getLabelText
//----------------------------------------------------------------------------
QString Category::getLabelText
    (
    LabelIdType aLabelId
    )
{
    QString tag;
    if( aLabelId < sLabelList.count() )
    {
        tag = sLabelList[ aLabelId ];
    }
    return tag;
} // Category::getLabelText

//----------------------------------------------------------------------------
// getLabelCount
//----------------------------------------------------------------------------
int Category::getLabelCount()
{
    return sLabelList.count();
} // Category::getLabelCount

//----------------------------------------------------------------------------
// Order Label List
//----------------------------------------------------------------------------
void Category::orderLabelList()
{
    qSort( sLabelList );
    // Move None Label to first index
    sLabelList.move( sLabelList.indexOf( cLabelNone ), LABEL_NONE );
}
