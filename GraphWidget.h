//******************************************************************************
//
//  HEADER NAME: GraphWidget.h
//******************************************************************************

#ifndef GraphWidget_H
#define GraphWidget_H

#include <QDate>
#include <QLabel>
#include <QList>
#include <QString>
#include <QTimer>
#include <QWidget>

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>

#include "Account.h"
#include "Transaction.h"

class DisplayLabel : public QLabel
{
    Q_OBJECT
public:
    virtual void mouseReleaseEvent( QMouseEvent * aEvent ){ QLabel::mouseReleaseEvent( aEvent ); clicked(); }
    QDate getDate() const { return mDate; }
    void  setDate( QDate aDate ){ mDate = aDate; }
signals:
    void clicked();
private:
    QDate mDate;
};

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
        float income;
        float expense;
        float netWorth;
        QDate date;
        MonthDataType(): income(0.0), expense(0.0), netWorth(0.0), date(2000,1,1){}
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

signals:
    void dateSelected( QDate aStartDate, QDate aEndDate );

private slots:
    void hideDisplayLabel();
    void handleDisplayClicked();

private:
    // Date graph widget
    BarChartType mGraphMode;
    QDate mStartDate;
    QDate mEndDate;
    QwtPlot mPlot;
    QwtPlotGrid* mGrid;
    QwtPlotCurve* mIncomeCurve;
    QwtPlotHistogram* mPositiveHistogram;
    QwtPlotHistogram* mNegativeHistogram;
    DisplayLabel mDisplayLabel;
    QTimer mDisplayTimer;
    QList<MonthDataType> mMonthDataList;

};

#endif // RENDERAREA_H
