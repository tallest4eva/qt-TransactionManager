//******************************************************************************
//
//  HEADER NAME: ReportPieChartModel.h
//******************************************************************************

#ifndef ReportPieChartModel_H
#define ReportPieChartModel_H

#include <QStandardItemModel>
#include <QList>

#include "PieView.h"
#include "Transaction.h"

class ReportPieChartModel : public QStandardItemModel
{

public:
    // Types
    enum PieChartType
    {
        ASSET_BY_ACCOUNT,
        DEBT_BY_ACCOUNT,
        INCOME_BY_CATEGORY,
        EXPENSE_BY_CATEGORY,

        PIE_CHART_CNT
    };
    struct PieDataType
    {
        QString mName;
        float mValue;
        PieDataType(): mValue(0.0){}
        bool operator< ( const PieDataType& aValue ) const { return( mValue < aValue.mValue ); }
    };

    // Functions
    explicit ReportPieChartModel( PieChartType aChartType = ASSET_BY_ACCOUNT );
    ~ReportPieChartModel();
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void setupPieView( PieView* aPieView );
    void setGroupCategories( bool aGroupCategories ){ mGroupCategories = aGroupCategories }
    void clear();

private:
    // Functions

    // Variables
    PieChartType mChartType;
    PieView* mPieView;
    bool mGroupCategories;
};

#endif // ReportPieChartModel_H
