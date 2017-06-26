//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: ReportPieChart.h
//******************************************************************************

#ifndef ReportPieChart_HPP
#define ReportPieChart_HPP

#include <QStandardItemModel>
#include <QList>

#include "BarGraph.hpp"
#include "DisplayLabel.hpp"
#include "PieView.hpp"
#include "Transaction.hpp"

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
    enum SortType
    {
        SORT_BY_BALANCE_DESCENDING,
        SORT_BY_NAME_ASCENDING,
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
    virtual void mouseReleaseEvent( QMouseEvent* aEvent );
    void setChartType( PieChartType aChartType ){ mChartType = aChartType; }
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void setGroupCategories( bool aGroupCategories ){ mGroupCategories = aGroupCategories; }
    void clear();
    void sortChart( SortType aSortType );
    void setShowTransfers( bool aShowTransfers, bool aUpdate = true );

signals:
    void transactionFilterSelected( const Transaction::FilterType& aFilter );

private slots:
    void handleItemClicked( const QModelIndex& aIndex );
    void hideDisplayLabel();
    void handleDisplayClicked();

private:
    // Functions
    void updateChart();

    // Variables
    QStandardItemModel* mModel;
    DisplayLabel mDisplayLabel;
    QPoint mMousePosition;
    Transaction::FilterType mFilter;
    PieChartType mChartType;
    bool mGroupCategories;
    SortType mSortType;
    QList<PieDataType> mDataList;
    bool mShowTransfers;
};

#endif // ReportPieChart_HPP
