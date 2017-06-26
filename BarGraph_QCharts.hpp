//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: BarGraph.h
//******************************************************************************

#ifndef BarGraph_HPP
#define BarGraph_HPP

#include <QDate>
#include <QList>
#include <QString>
#include <QWidget>
#include <QRubberBand>
#include <QtCharts>

#include "Account.hpp"
#include "DisplayLabel.hpp"
#include "Transaction.hpp"

class BarGraph : public QWidget
{
    Q_OBJECT

public:
    // Types
    enum BarChartType
    {
        BAR_NET_INCOME,
        BAR_NET_WORTH,
        BAR_ACCOUNT_BALANCE,
    };
    struct BarDataType
    {
        bool set;
        float expense;
        float income;
        float netWorth;
        QDate startDate;
        QDate endDate;
        BarDataType(): set(false), expense(0.0), income(0.0), netWorth(0.0), startDate(2000,1,1), endDate(2000,1,1){}
    };

    // Functions
    BarGraph( BarChartType aGraphMode, QWidget* aParent = 0 );

    ~BarGraph();

    QSize minimumSizeHint() const { return QSize(50, 50); }
    QSize sizeHint() const { return QSize(100, 100); }

    void setMonthInterval( int aMonthInterval );
    void setShowNetIncome( bool aShowNetIncome );
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void clear();

signals:
    void transactionFilterSelected( const Transaction::FilterType& aFilter );
    void transactionDateSelected( QDate aStartDate, QDate aEndDate );
    void reportDateSelected( QDate aStartDate, QDate aEndDate );

private slots:
    void hideDisplayLabel();
    void handleDisplayClicked();
    void handlePlottableMousePressEvent( QMouseEvent* aEvent );
    void handlePlottableMouseMoveEvent( QMouseEvent* aEvent );
    void handlePlottableMouseReleaseEvent( QMouseEvent * aEvent );

private:
    void updateTitleText();

private:
    // Date graph widget
    BarChartType mGraphMode;
    //QCustomPlot mPlot;
    //QCPBars* mPositiveHistogram;
    //QCPBars* mNegativeHistogram;
    DisplayLabel mDisplayLabel;
    Transaction::FilterType mFilter;
    int mStartDragPosition;
    QRubberBand* mRubberBand;
    bool mDrag;
    bool mDataSet;
    int mMonthInterval;
    QList<BarDataType> mBarDataList;
    bool mShowNetIncome;
    QCharts* mCharts;
    QChartView mChartView;

};

#endif // BarGraph_HPP
