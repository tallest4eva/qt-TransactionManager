//******************************************************************************
//
//  HEADER NAME: ReportPieChartModel.h
//******************************************************************************

#ifndef ReportPieChartModel_H
#define ReportPieChartModel_H

#include <QStandardItemModel>
#include <QList>
#include <QPieView>

#include "Transaction.h"

class ReportPieChartModel : public QStandardItemModel
{

public:
    // Types
    enum HeaderType
    {
        HDR_DATE,
        HDR_NAME,
        HDR_DESCRIPTION,
        HDR_AMOUNT,
        HDR_BALANCE,
        HDR_CATEGORY,
//        HDR_LABELS

        HDR_CNT
    };
    enum PieChartType
    {
        ASSET_BY_ACCOUNT,
        DEBT_BY_ACCOUNT,
        INCOME_BY_CATEGORY,
        EXPENSE_BY_CATEGORY,

        HDR_CNT
    };

    // Functions
    explicit ReportPieChartModel( PieChartType aChartType = ASSET_BY_ACCOUNT );
    ~ReportPieChartModel();
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void setupPieView( QPieView* aPieView );

private:
    // Functions

    // Variables
    PieChartType mChartType;
    QList<Transaction*> mTransactionList;
    QPieView* mPieView;
};

#endif // ReportPieChartModel_H
