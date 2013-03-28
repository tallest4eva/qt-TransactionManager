//******************************************************************************
//
//  HEADER NAME: BarGraph.h
//******************************************************************************

#ifndef BarGraph_H
#define BarGraph_H

#include <QDate>
#include <QLabel>
#include <QList>
#include <QString>
#include <QTimer>
#include <QWidget>
#include <QRubberBand>

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
    virtual void mouseDoubleClickEvent( QMouseEvent* aEvent ){ QLabel::mouseDoubleClickEvent( aEvent ); clicked(); }
    QDate getDate() const { return mDate; }
    void  setDate( QDate aDate ){ mDate = aDate; }
signals:
    void clicked();
private:
    QDate mDate;
};

class BarGraph : public QWidget
{
    Q_OBJECT

public:
    // Types
    enum BarChartType
    {
        BAR_NET_INCOME,
        BAR_NET_WORTH,
    };

    // Variable
    static const QDate REFERENCE_DATE;

    // Functions
    BarGraph(QWidget *parent = 0);

    ~BarGraph();

    virtual void mousePressEvent( QMouseEvent* aEvent );
    virtual void mouseMoveEvent( QMouseEvent* aEvent );
    virtual void mouseReleaseEvent( QMouseEvent * aEvent );

    QSize minimumSizeHint() const { return QSize(50, 50); }
    QSize sizeHint() const { return QSize(100, 100); }

    void setGraphMode( BarChartType aGraphMode );
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void clear();

signals:
    void transactionFilterSelected( const Transaction::FilterType& aFilter );
    void transactionDateSelected( QDate aStartDate, QDate aEndDate );
    void reportDateSelected( QDate aStartDate, QDate aEndDate );

private slots:
    void hideDisplayLabel();
    void handleDisplayClicked();

private:
    // Date graph widget
    BarChartType mGraphMode;
    QwtPlot mPlot;
    QwtPlotGrid* mGrid;
    QwtPlotCurve* mIncomeCurve;
    QwtPlotHistogram* mPositiveHistogram;
    QwtPlotHistogram* mNegativeHistogram;
    DisplayLabel mDisplayLabel;
    QTimer mDisplayTimer;
    Transaction::FilterType mFilter;
    QPoint mOrigin;
    QRubberBand* mRubberBand;
    bool mDrag;
    bool mDataSet;

};

#endif // BarGraph_H