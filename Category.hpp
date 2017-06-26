//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Category.h
//******************************************************************************

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QList>

class Category
{
public:
    // Types
    typedef int CategoryIdxType;

    enum ParentCategoryType
    {
        AUTO_AND_TRANSPORT,
        BILLS_AND_UTILITIES,
        BUSINESS_SERVICES,
        EDUCATION,
        ENTERTAINMENT,
        FEES_AND_CHARGES,
        FINANCIAL,
        FOOD_AND_DINING,
        GIFTS_AND_DONATIONS,
        HEALTH_AND_FITNESS,
        HOME,
        INCOME,
        INVESTMENTS,
        KIDS,
        LOANS,
        MISC_EXPENSES,
        PERSONAL_CARE,
        PETS,
        SHOPPING,
        TAXES,
        TRANSFER,
        TRAVEL,
        UNCATEGORIZED,
        EXCLUDE,

        PARENT_CATEGORY_TYPE_CNT
    };

    enum TransactionType
    {
        TRANSACTION_TYPE_EXPENSE,
        TRANSACTION_TYPE_INCOME,
        TRANSACTION_TYPE_TRANSFER,
        TRANSACTION_TYPE_BALANCE
    };

    typedef int LabelIdType;
	static const LabelIdType LABEL_INVALID;
	static const LabelIdType LABEL_NONE;

    // Functions

    // Constructor
    Category
        (
        ParentCategoryType aParentCategory = UNCATEGORIZED,
        const QString& aText = QString(),
        bool aIsParent = false,
        TransactionType aType = TRANSACTION_TYPE_EXPENSE
        );

    static void initCategoryList();
    static void addCategory
        (
        const Category& aCategory
        );
    static int getCategoryCount();
    static CategoryIdxType getCategoryIndex
        (
        const QString& aCategory
        );
    static ParentCategoryType getParentCategoryId
        (
        const QString& aParentCategoryStr
        );
    static ParentCategoryType getParentCategoryId
        (
        CategoryIdxType aCategoryIdx
        );
    static QString getParentCategoryText
        (
        ParentCategoryType aParentCategoryIdx
        );
    static QString getCategoryText
        (
        CategoryIdxType aCategoryIdx,
        bool aFullText = false
        );
    static TransactionType getCategoryTransactionType
        (
        CategoryIdxType aCategoryIdx
        );
    static void orderCategoryList();

    // Label functions
    static void addLabel
        (
        const QString& aLabel
        );
    static LabelIdType getLabelId
        (
        const QString& aLabel
        );
    static QString getLabelText
        (
        LabelIdType aLabelId
        );
    static int getLabelCount();
    static void orderLabelList();

    // Comparators
    bool operator< ( const Category& aCategory ) const;
    bool operator> ( const Category& aCategory ) const;

    // Variables
    static CategoryIdxType sUnmatchedCategoryIdx;

    ParentCategoryType parentCategory;
    QString text;
    TransactionType type;
    bool mIsParent;

private:
};

#endif // CATEGORY_H
