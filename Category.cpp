//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Category.cpp
//******************************************************************************

#include "Category.h"
#include "Logger.h"

// Static variables
const Category::CategoryType Category::cCategoryList[] =
{
    { AUTO_AND_TRANSPORT,   "Auto & Transport" },
    { AUTO_AND_TRANSPORT,   "Auto Insurance" },
    { AUTO_AND_TRANSPORT,   "Auto Payment" },
    { AUTO_AND_TRANSPORT,   "Auto Taxes and Fees" },
    { AUTO_AND_TRANSPORT,   "Car Wash/Detail" },
    { AUTO_AND_TRANSPORT,   "Gas & Fuel" },
    { AUTO_AND_TRANSPORT,   "Parking" },
    { AUTO_AND_TRANSPORT,   "Public Transportation" },
    { AUTO_AND_TRANSPORT,   "Service & Parts" },
    
    { BILLS_AND_UTILITIES,  "Bills & Utilities" },
    { BILLS_AND_UTILITIES,  "Home Phone" },
    { BILLS_AND_UTILITIES,  "Internet" },
    { BILLS_AND_UTILITIES,  "Mobile Phone" },
    { BILLS_AND_UTILITIES,  "Phone Card" },
    { BILLS_AND_UTILITIES,  "Television" },
    { BILLS_AND_UTILITIES,  "Utilities" },

    { BUSINESS_SERVICES,    "Business Services" },
    { BUSINESS_SERVICES,    "Advertising" },
    { BUSINESS_SERVICES,    "Legal" },
    { BUSINESS_SERVICES,    "Office Supplies" },
    { BUSINESS_SERVICES,    "Printing" },
    { BUSINESS_SERVICES,    "Shipping" },
    
    { EDUCATION,            "Education" },
    { EDUCATION,            "Books & Supplies" },
    { EDUCATION,            "Student Loan" },
    { EDUCATION,            "Tuition" },
    
    { ENTERTAINMENT,        "Entertainment" },
    { ENTERTAINMENT,        "Amusement" },
    { ENTERTAINMENT,        "Arts" },
    { ENTERTAINMENT,        "Movies & DVDs" },
    { ENTERTAINMENT,        "Music" },
    { ENTERTAINMENT,        "Newspapers & Magazines" },
    { ENTERTAINMENT,        "Night Clubs & Bars" },
    
    { FEES_AND_CHARGES,     "Fees & Charges" },
    { FEES_AND_CHARGES,     "ATM Fee" },
    { FEES_AND_CHARGES,     "Bank Fee" },
    { FEES_AND_CHARGES,     "Finance Charge" },
    { FEES_AND_CHARGES,     "Fines" },
    { FEES_AND_CHARGES,     "Late Fee" },
    { FEES_AND_CHARGES,     "Service Fee" },
    { FEES_AND_CHARGES,     "Trade Commissions" },
    
    { FINANCIAL,            "Financial" },
    { FINANCIAL,            "Financial Advisor" },
    { FINANCIAL,            "Life Insurance" },
    { FINANCIAL,            "Tax Preparation" },
    
    { FOOD_AND_DINING,      "Food & Dining" },
    { FOOD_AND_DINING,      "Alcohol & Bars" },
    { FOOD_AND_DINING,      "Coffee Shops" },
    { FOOD_AND_DINING,      "Fast Food" },
    { FOOD_AND_DINING,      "Groceries" },
    { FOOD_AND_DINING,      "Restaurants" },
    { FOOD_AND_DINING,      "Snacks & Drinks" },
    
    { GIFTS_AND_DONATIONS,  "Gifts & Donations" },
    { GIFTS_AND_DONATIONS,  "Charity" },
    { GIFTS_AND_DONATIONS,  "Family Loan" },
    { GIFTS_AND_DONATIONS,  "Gift" },
    { GIFTS_AND_DONATIONS,  "Personal Loan" },
    
    { HEALTH_AND_FITNESS,   "Health & Fitness" },
    { HEALTH_AND_FITNESS,   "Dentist" },
    { HEALTH_AND_FITNESS,   "Doctor" },
    { HEALTH_AND_FITNESS,   "Eyecare" },
    { HEALTH_AND_FITNESS,   "Gym" },
    { HEALTH_AND_FITNESS,   "Health Insurance" },
    { HEALTH_AND_FITNESS,   "Pharmacy" },
    { HEALTH_AND_FITNESS,   "Sports" },
    
    { HOME,                 "Home" },
    { HOME,                 "Furnishings" },
    { HOME,                 "Home Improvement" },
    { HOME,                 "Home Insurance" },
    { HOME,                 "Home Services" },
    { HOME,                 "Home Supplies" },
    { HOME,                 "Lawn & Garden" },
    { HOME,                 "Mortgage & Rent" },
    
    { INCOME,               "Income" },
    { INCOME,               "Bonus" },
    { INCOME,               "Interest Income" },
    { INCOME,               "Misc Income" },
    { INCOME,               "Paycheck" },
    { INCOME,               "Reimbursement" },
    { INCOME,               "Rental Income" },
    { INCOME,               "Returned Purchase" },
    { INCOME,               "Rewards Income" },
    
    { INVESTMENTS,          "Investments" },
    { INVESTMENTS,          "Buy" },
    { INVESTMENTS,          "Deposit" },
    { INVESTMENTS,          "Dividend & Cap Gains" },
    { INVESTMENTS,          "Retirement Deposit" },
    { INVESTMENTS,          "Retirement Dividend" },
    { INVESTMENTS,          "Sell" },
    { INVESTMENTS,          "Stock Dividends" },
    { INVESTMENTS,          "Stock Purchase" },
    { INVESTMENTS,          "Stock Sale" },
    { INVESTMENTS,          "Withdrawal" },
    
    { KIDS,                 "Kids" },
    { KIDS,                 "Allowance" },
    { KIDS,                 "Baby Supplies" },
    { KIDS,                 "Babysitter & Daycare" },
    { KIDS,                 "Child Support" },
    { KIDS,                 "Kids Activities" },
    { KIDS,                 "Toys" },
    
    { LOANS,                "Loans" },
    { LOANS,                "Loan Fees and Charges" },
    { LOANS,                "Loan Insurance" },
    { LOANS,                "Loan Interest" },
    { LOANS,                "Loan Payment" },
    { LOANS,                "Loan Principal" },
    
    { PERSONAL_CARE,        "Personal Care" },
    { PERSONAL_CARE,        "Hair" },
    { PERSONAL_CARE,        "Laundry" },
    { PERSONAL_CARE,        "Spa & Massage" },
    
    { PETS,                 "Pets" },
    { PETS,                 "Pet Food & Supplies" },
    { PETS,                 "Pet Grooming" },
    { PETS,                 "Veterinary" },
    
    { SHOPPING,             "Shopping" },
    { SHOPPING,             "Books" },
    { SHOPPING,             "Clothing" },
    { SHOPPING,             "Electronics & Software" },
    { SHOPPING,             "General Merchandise" },
    { SHOPPING,             "Hobbies" },
    { SHOPPING,             "Sporting Goods" },
    
    { TAXES,                "Taxes" },
    { TAXES,                "Federal Tax" },
    { TAXES,                "Local Tax" },
    { TAXES,                "Property Tax" },
    { TAXES,                "Sales Tax" },
    { TAXES,                "State Tax" },
    { TAXES,                "Tax Refund" },
    
    { TRANSFER,             "Transfer" },
    { TRANSFER,             "Credit Card Payment" },
    { TRANSFER,             "Family Transfer" },
    { TRANSFER,             "Transfer for Cash Spending" },
    
    { TRAVEL,               "Travel" },
    { TRAVEL,               "Air Travel" },
    { TRAVEL,               "Hotel" },
    { TRAVEL,               "Moving Expenses" },
    { TRAVEL,               "Rental Car & Taxi" },
    { TRAVEL,               "Vacation" },
    
    { UNCATEGORIZED,        "Uncategorized" },
    { UNCATEGORIZED,        "Account Balance" },
    { UNCATEGORIZED,        "Cash & ATM" },
    { UNCATEGORIZED,        "Check" },
    { UNCATEGORIZED,        "Family Expense" },
    { UNCATEGORIZED,        "Family Income" },
    { UNCATEGORIZED,        "Misc Expense" },

    { EXCLUDE,              "Exclude" },
};

const char* Category::cLabelList[] =
{
    "None",         /* LABEL_NONE       */
    "Reviewed",     /* LABEL_REVIEWED   */
    "Manual",       /* LABEL_MANUAL     */
    "Shared",       /* LABEL_SHARED     */
    "Business",     /* LABEL_BUSINESS   */
    "Family",       /* LABEL_FAMILY     */
    "Projected",    /* LABEL_PROJECTED  */
};
QList<Category::CategoryType> Category::sCategoryList;
    
//----------------------------------------------------------------------------
// addCategory
//----------------------------------------------------------------------------
void Category::addCategory
    (
    const CategoryType& aCategory
    )
{
    getCategoryCount();
    sCategoryList.push_back( aCategory );      
} // Category::addCategory

//----------------------------------------------------------------------------
// getCategoryCount
//----------------------------------------------------------------------------
int Category::getCategoryCount()
{
    if( sCategoryList.size() == 0 )
    { 
        for( int i = 0; i < CATEGORY_TYPE_CNT; i++ )
        {
            sCategoryList.push_back( cCategoryList[i] );
        }
    }
    return sCategoryList.size();
} // Category::getCategoryCount

//----------------------------------------------------------------------------
// getCategoryId
//----------------------------------------------------------------------------
Category::CategoryIdType Category::getCategoryId
    (
    const QString& aCategory
    )
{
    bool found = false;
    CategoryIdType id = UNCATEGORIZED;
    for( int i = 0; i < sCategoryList.size(); i++ )
    {
        if( aCategory == sCategoryList[ i ].text )
        {
            id = (CategoryIdType)i;
            found = true;
            break;
        }
    }
    if( !found )
    {
        Logger::logString( "Could not find category: " + QString(aCategory), Logger::LOG_WARNING );
    }
    return id;
} // Category::getCategoryId

//----------------------------------------------------------------------------
// getParentCategoryId
//----------------------------------------------------------------------------
Category::CategoryIdType Category::getParentCategoryId
    (
    CategoryIdType aCategoryId
    )
{
    CategoryIdType id = UNCATEGORIZED;
    if( aCategoryId < sCategoryList.size() )
    {
        id = sCategoryList[ aCategoryId ].parentCategory;
    }
    return id;
} // Category::getParentCategoryId

//----------------------------------------------------------------------------
// getCategoryText
//----------------------------------------------------------------------------
QString Category::getCategoryText
    (
    CategoryIdType aCategoryId,
    bool aFullText
    )
{
    QString text;
    if( aCategoryId < sCategoryList.size() )
    {
        CategoryIdType parentCategoryId = sCategoryList[ aCategoryId ].parentCategory;
        if( aFullText && aCategoryId != parentCategoryId )
        {
            text = sCategoryList[ parentCategoryId ].text;
            text += " > ";
        }
        text += sCategoryList[ aCategoryId ].text;
    }
    return text;
} // Category::getCategoryText

//----------------------------------------------------------------------------
// getLabelId
//----------------------------------------------------------------------------
Category::LabelIdType Category::getLabelId
    (
    const QString& aLabel
    )
{
    bool found = false;
    LabelIdType id = LABEL_NONE;
    if( !aLabel.isEmpty() )
    {
        for( int i = 0; i < LABEL_CNT; i++ )
        {
            if( aLabel == QString(cLabelList[ i ]) )
            {
                id = (LabelIdType)i;
                found = true;
                break;
            }
        }
    }
    if( !found )
    {
        Logger::logString( "Could not find tag: " + QString(aLabel), Logger::LOG_WARNING );
    }
    return id;
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
    if( aLabelId < LABEL_CNT )
    {
        tag = cLabelList[ aLabelId ];
    }
    return tag;
} // Category::getLabelText
