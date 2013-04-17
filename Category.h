//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Category.h
//******************************************************************************

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category
{
public:
    // Types
    enum CategoryIdType
    {
        AUTO_AND_TRANSPORT,
        AUTO_INSURANCE,
        AUTO_PAYMENT,
        AUTO_TAXES_AND_FEES,
        CAR_WASH_DETAIL,
        GAS_AND_FUEL,
        PARKING,
        PUBLIC_TRANSPORTATION,
        SERVICE_AND_PARTS,
        
        BILLS_AND_UTILITIES,
        HOME_PHONE,
        INTERNET,
        MOBILE_PHONE,
        PHONE_CARD,
        TELEVISION,
        UTILITIES,
        
        BUSINESS_SERVICES,
        ADVERTISING,
        LEGAL,
        OFFICE_SUPPLIES,
        PRINTING,
        SHIPPING,
        
        EDUCATION,
        BOOKS_AND_SUPPLIES,
        STUDENT_LOAN,
        TUITION,
        
        ENTERTAINMENT,
        AMUSEMENT,
        ARTS,
        MOVIES_AND_DVDS,
        MUSIC,
        NEWSPAPERS_AND_MAGAZINES,
        NIGHT_CLUBS_AND_BARS,
        
        FEES_AND_CHARGES,
        ATM_FEE,
        BANK_FEE,
        FINANCE_CHARGE,
        FINES,
        LATE_FEE,
        SERVICE_FEE,
        TRADE_COMMISSIONS,
        
        FINANCIAL,
        FINANCIAL_ADVISOR,
        LIFE_INSURANCE,
        TAX_PREPARATION,
        
        FOOD_AND_DINING,
        ALCOHOL_AND_BARS,
        COFFEE_SHOPS,
        FAST_FOOD,
        GROCERIES,
        RESTAURANTS,
        SNACKS_AND_DRINKS,
        
        GIFTS_AND_DONATIONS,
        CHARITY,
        FAMILY_LOAN,
        GIFT,
        PERSONAL_LOAN,
        
        HEALTH_AND_FITNESS,
        DENTIST,
        DOCTOR,
        EYECARE,
        GYM,
        HEALTH_INSURANCE,
        PHARMACY,
        SPORTS,
        
        HOME,
        FURNISHINGS,
        HOME_IMPROVEMENT,
        HOME_INSURANCE,
        HOME_SERVICES,
        HOME_SUPPLIES,
        LAWN_AND_GARDEN,
        MORTGAGE_AND_RENT,
        
        INCOME,
        BONUS,
        INTEREST_INCOME,
        MISC_INCOME,
        PAYCHECK,
        REIMBURSEMENT,
        RENTAL_INCOME,
        RETURNED_PURCHASE,
        REWARDS_INCOME,
        
        INVESTMENTS,
        BUY,
        DEPOSIT,
        DIVIDEND_AND_CAP_GAINS,
        RETIREMENT_DEPOSIT,
        RETIREMENT_DIVIDENDS,
        SELL,
        STOCK_DIVIDENDS,
        STOCK_PURCHASE,
        STOCK_SALE,
        WITHDRAWAL,
        
        KIDS,
        ALLOWANCE,
        BABY_SUPPLIES,
        BABYSITTER_AND_DAYCARE,
        CHILD_SUPPORT,
        KIDS_ACTIVITIES,
        TOYS,
        
        LOANS,
        LOAN_FEES_AND_CHARGES,
        LOAN_INSURANCE,
        LOAN_INTEREST,
        LOAN_PAYMENT,
        LOAN_PRINCIPAL,
        
        PERSONAL_CARE,
        HAIR,
        LAUNDRY,
        SPA_AND_MASSAGE,
        
        PETS,
        PET_FOOD_AND_SUPPLIES,
        PET_GROOMING,
        VETERINARY,
        
        SHOPPING,
        BOOKS,
        CLOTHING,
        ELECTRONICS_AND_SOFTWARE,
        GENERAL_MERCHANDISE,
        HOBBIES,
        SPORTING_GOODS,
        
        TAXES,
        FEDERAL_TAX,
        LOCAL_TAX,
        PROPERTY_TAX,
        SALES_TAX,
        STATE_TAX,
        TAX_REFUND,
        
        TRANSFER,
        CREDIT_CARD_PAYMENT,
        FAMILY_TRANSFER,
        TRANSFER_FOR_CASH_SPENDING,
        
        TRAVEL,
        AIR_TRAVEL,
        HOTEL,
        MOVING_EXPENSES,
        RENTAL_CAR_AND_TAXI,
        VACATION,
        
        UNCATEGORIZED,
        ACCOUNT_BALANCE,
        CASH_AND_ATM,
        CHECK,
        FAMILY_EXPENSE,
        FAMILY_INCOME,
        MISC_EXPENSE,
        
        CATEGORY_TYPE_CNT
    };

    struct CategoryType
    {
        CategoryIdType parentCategory;
        char* text;
    };

    enum LabelIdType
    {
        LABEL_NONE,
        LABEL_REVIEWED,
        LABEL_MANUAL,
        LABEL_SHARED,
	    LABEL_BUSINESS,
	    LABEL_FAMILY,
        LABEL_PROJECTED,

        LABEL_CNT
    };

    // Functions
    static CategoryIdType getCategoryId
        (
        const QString& aCategory
        );
    static CategoryIdType getParentCategoryId
        (
        CategoryIdType aCategoryId
        );
    static QString getCategoryText
        (
        CategoryIdType aCategoryId,
        bool aFullText = false
        );

    static LabelIdType getLabelId
        (
        const QString& aLabel
        );
    static QString getLabelText
        (
        LabelIdType aLabelId
        );
    
private:
    // Variable
    static const CategoryType cCategoryList[];
    static const char* cLabelList[];
};

#endif // CATEGORY_H
