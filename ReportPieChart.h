//******************************************************************************
//
//  HEADER NAME: ReportPieChart.h
//******************************************************************************

#ifndef ReportPieChart_H
#define ReportPieChart_H

#include <QStandardItemModel>
#include <QList>

#include "PieView.h"
#include "BarGraph.h"
#include "Transaction.h"

class ReportPieChart : public PieView
{
    Q_OBJECT

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
    explicit ReportPieChart();
    ~ReportPieChart();
    virtual void mouseReleaseEvent( QMouseEvent * aEvent );
    void setChartType( PieChartType aChartType ){ mChartType = aChartType; }
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void setGroupCategories( bool aGroupCategories ){ mGroupCategories = aGroupCategories; }
    void clear();

private slots:
    void handleItemClicked( const QModelIndex& aIndex );
    void hideDisplayLabel();
    void handleDisplayClicked();

private:
    // Functions

    // Variables
    QStandardItemModel* mModel;
    DisplayLabel mDisplayLabel;
    QPoint mMousePosition;
    Transaction::FilterType mFilter;
    PieChartType mChartType;
    bool mGroupCategories;
};

#endif // ReportPieChart_H
