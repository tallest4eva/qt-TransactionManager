//******************************************************************************
//
//  HEADER NAME: GraphWidget.h
//******************************************************************************

#ifndef GraphWidget_H
#define GraphWidget_H

#include <QDate>
#include <QLabel>
#include <QList>
#include <QPainterPath>
#include <QString>
#include <QTimer>
#include <QWidget>

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_scale_draw.h>

#include "Account.h"
#include "Transaction.h"

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    // Types
    enum BarChartType
    {
        BAR_NET_INCOME,
        BAR_NET_WORTH,
    };

    struct MonthDataType
    {
        float positiveVal;
        float negativeVal;
        float income;
        float expense;
        float netWorth;
        QDate date;
        MonthDataType(): positiveVal(0.0), negativeVal(0.0), income(0.0), expense(0.0), netWorth(0.0), date(2000,1,1){}
    };

    // Variable
    static const QDate REFERENCE_DATE;

    // Functions
    GraphWidget(QWidget *parent = 0);

    ~GraphWidget();

    virtual void mouseReleaseEvent( QMouseEvent * aEvent );

    QSize minimumSizeHint() const { return QSize(50, 50); }
    QSize sizeHint() const { return QSize(100, 100); }

    void setGraphMode( BarChartType aGraphMode );
    void setTransactionData
        (
        const QDate& aStartDate,
        const QDate& aEndDate,
        const QList<Account*>& aAccountList,
        const QList<Transaction*>& aTransactionList
        );

private slots:
    void hideDisplayLabel();

private:
    // Date graph widget
    BarChartType mGraphMode;
    QDate mStartDate;
    QDate mEndDate;
    QwtPlot mPlot;
    QwtPlotGrid* mGrid;
    QwtPlotHistogram* mPositiveHistogram;
    QwtPlotHistogram* mNegativeHistogram;
    QLabel mDisplayLabel;
    QTimer mDisplayTimer;
    QList<MonthDataType> mMonthDataList;

};

class TimeScaleDraw : public QwtScaleDraw
{
public:
    virtual QwtText label( double aValue ) const
    {
        QDate date = GraphWidget::REFERENCE_DATE.addDays( aValue );
        return QwtText( date.toString("MMMyy") );
    }
};

#endif // RENDERAREA_H
