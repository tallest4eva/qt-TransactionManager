//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: BarGraph.cpp
//******************************************************************************

#include <QtGui>
#include <QHBoxLayout>

#include <qwt_plot_layout.h>

#include "BarGraph.h"
#include "Month.h"
#include "TransactionManager.h"

const QDate BarGraph::REFERENCE_DATE = QDate(1990,1,1);
static const int DISPLAY_LABEL_TIMOEUT = 5000;              // Display label timeout
static const int DOUBLE_CLICK_INTERVAL = 300;               // Double click interval

class TimeScaleDraw : public QwtScaleDraw
{
public:
    virtual QwtText label( double aValue ) const
    {
        QDate date = BarGraph::REFERENCE_DATE.addDays( aValue );
        return QwtText( date.toString("MMMyy") );
    }
};

//----------------------------------------------------------------------------
// DisplayLabel
//----------------------------------------------------------------------------
DisplayLabel::DisplayLabel()
{
    mPressTimer.setSingleShot( true );
    mReleaseTimer.setSingleShot( true );
    connect( &mPressTimer, SIGNAL(timeout()), this, SLOT(hide()) );
} // DisplayLabel::DisplayLabel

//----------------------------------------------------------------------------
// mouseDoubleClickEvent
//----------------------------------------------------------------------------
void DisplayLabel::mouseDoubleClickEvent( QMouseEvent* aEvent )
{
    QLabel::mouseDoubleClickEvent( aEvent );
    mPressTimer.stop();
    mReleaseTimer.start(DOUBLE_CLICK_INTERVAL);
    clicked(); 
} // DisplayLabel::mouseDoubleClickEvent

//----------------------------------------------------------------------------
// mousePressEvent
//----------------------------------------------------------------------------
void DisplayLabel::mousePressEvent( QMouseEvent* aEvent )
{
    QLabel::mousePressEvent( aEvent );
    if( !mReleaseTimer.isActive() ){ mPressTimer.start(DOUBLE_CLICK_INTERVAL); }
} // DisplayLabel::mousePressEvent

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
BarGraph::BarGraph(QWidget *parent) :
    QWidget(parent)
  , mGraphMode( BAR_NET_INCOME )
  , mGrid( NULL )
  , mIncomeCurve( NULL )
  , mPositiveHistogram( NULL )
  , mNegativeHistogram( NULL )
  , mDrag( false )
  , mDataSet( false )
  , mRubberBand( NULL )
{
    setBackgroundRole(QPalette::Base);

    // Create graph
    mPlot.setCanvasBackground( QColor(Qt::white) );
    mPlot.setAxisScaleDraw( QwtPlot::xBottom, new TimeScaleDraw() );
    mGrid = new QwtPlotGrid;
    mGrid->enableXMin(true);
    mGrid->enableYMin(true);
    mGrid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
    mGrid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    mGrid->attach(&mPlot);

    mPositiveHistogram = new QwtPlotHistogram();
    mPositiveHistogram->setStyle(QwtPlotHistogram::Columns);
    mPositiveHistogram->setPen(QPen(Qt::black));
    mPositiveHistogram->setBrush(QBrush(Qt::gray));
    mPositiveHistogram->setOrientation(Qt::Vertical);
    QwtColumnSymbol* symbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
    symbol->setFrameStyle(QwtColumnSymbol::Raised);
    symbol->setLineWidth(2);
    symbol->setPalette(QPalette(Qt::green));
    mPositiveHistogram->setSymbol(symbol);
    mPositiveHistogram->attach( &mPlot );

    mNegativeHistogram = new QwtPlotHistogram();
    mNegativeHistogram->setStyle(QwtPlotHistogram::Columns);
    mNegativeHistogram->setPen(QPen(Qt::black));
    mNegativeHistogram->setBrush(QBrush(Qt::gray));
    mNegativeHistogram->setOrientation(Qt::Vertical);
    symbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
    symbol->setFrameStyle(QwtColumnSymbol::Raised);
    symbol->setLineWidth(2);
    symbol->setPalette(QPalette(Qt::red));
    mNegativeHistogram->setSymbol(symbol);
    mNegativeHistogram->attach(&mPlot);

    mIncomeCurve = new QwtPlotCurve();
    mIncomeCurve->setPen( QPen(QBrush(Qt::black),1) );
    mIncomeCurve->attach(&mPlot);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget( &mPlot );
    setLayout( layout );

    // Set up display label
    mDisplayLabel.setParent( this );
    mDisplayLabel.hide();
    mDisplayLabel.setGeometry( 0, 0, 170, 90 );
    mDisplayLabel.setFrameShadow( QFrame::Raised );
    mDisplayLabel.setFrameShape( QFrame::StyledPanel );
    mDisplayLabel.setPalette( QPalette(Qt::black,Qt::white) );
    mDisplayLabel.setAutoFillBackground( true );
    connect( &mDisplayLabel, SIGNAL(clicked()), this, SLOT(handleDisplayClicked()) );
    QFont font;
    font.setPointSize( 10 );
    mDisplayLabel.setFont( font );
    mRubberBand = new QRubberBand( QRubberBand::Rectangle, this );
    
    clear();
} // BarGraph::BarGraph

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
BarGraph::~BarGraph()
{
    delete mRubberBand;
    delete mGrid;
    delete mIncomeCurve;
    delete mPositiveHistogram;
    delete mNegativeHistogram;
} // BarGraph::~BarGraph

//----------------------------------------------------------------------------
// hideDisplayLabel
//----------------------------------------------------------------------------
void BarGraph::hideDisplayLabel()
{
    mDisplayLabel.hide();
} // BarGraph::hideDisplayLabel

//----------------------------------------------------------------------------
// handle Display Clicked
//----------------------------------------------------------------------------
void BarGraph::handleDisplayClicked()
{
    QDate date = mDisplayLabel.getDate();
    Transaction::FilterType filter = mFilter;
    filter.mStartDate = date;
    filter.mEndDate = date.addMonths(1).addDays(-1);
    filter.mAllDates = false;
    filter.mShowDates = true;
    transactionFilterSelected( filter );
} // BarGraph::handleDisplayClicked

//----------------------------------------------------------------------------
// mousePressEvent
//----------------------------------------------------------------------------
void BarGraph::mousePressEvent( QMouseEvent* aEvent )
{
    mDrag = false;
    QWidget::mousePressEvent( aEvent );

    if( mDataSet )
    {
        QRectF rect = mPlot.plotLayout()->canvasRect();
        mMousePosition = QPoint( aEvent->x(), rect.y()+10 );
        mRubberBand->setGeometry( QRect( mMousePosition, QSize(0,rect.height()) ) );
        mRubberBand->show();
    }
} // BarGraph::mousePressEvent

//----------------------------------------------------------------------------
// mouseMoveEvent
//----------------------------------------------------------------------------
void BarGraph::mouseMoveEvent( QMouseEvent* aEvent )
{
    mDrag = true;
    QWidget::mouseMoveEvent( aEvent );

    if( mDataSet )
    {
        QRectF rect = mRubberBand->rect();
        mRubberBand->setGeometry( QRect(mMousePosition, QSize( aEvent->x() - mMousePosition.x(),rect.height() )) );
    }
} // BarGraph::mouseMoveEvent
    
//----------------------------------------------------------------------------
// mouseReleaseEvent
//----------------------------------------------------------------------------
void BarGraph::mouseReleaseEvent( QMouseEvent* aEvent )
{
    QWidget::mouseReleaseEvent( aEvent );

    mRubberBand->hide();
    int offset = mPlot.plotLayout()->canvasRect().x()+10;
    if( mDrag )
    {
        mDrag = false;
        if( mDataSet )
        {
            // Set new report date interval
            int startDateVal = mPlot.invTransform( QwtPlot::xBottom, mMousePosition.x() - offset );
            QDate startDate = REFERENCE_DATE.addDays( startDateVal );
            int endDateVal = mPlot.invTransform( QwtPlot::xBottom, aEvent->x() - offset );
            QDate endDate = REFERENCE_DATE.addDays( endDateVal );
            if( endDate > startDate )
            {
                startDate.setDate( startDate.year(), startDate.month(), 1 );
                endDate.setDate( endDate.year(), endDate.month(), 1 );
                endDate = endDate.addMonths(1).addDays(-1);
                reportDateSelected( startDate, endDate );
            }
        }
        return;
    }
    
    if( !mDisplayLabel.isHidden() )
    {
        hideDisplayLabel();
    }
    else
    {
        // Place display label
        int labelRectW = mDisplayLabel.width();
        int labelRectH = mDisplayLabel.height();
        int labelRectX = aEvent->x() - labelRectW/2;
        labelRectX = ( labelRectX < 0 ) ? 0 : labelRectX;
        labelRectX = ( labelRectX + labelRectW > width() ) ? width() - labelRectW : labelRectX;
        int labelRectY = aEvent->y() - labelRectH;
        labelRectY = ( labelRectY < 0 ) ? 0 : labelRectY;
        labelRectY = ( labelRectY + labelRectH > height() ) ? height() - labelRectH : labelRectY;
        mDisplayLabel.move( labelRectX, labelRectY );
        mDisplayLabel.setText( "" );
        mDisplayLabel.hide();

        // Get point info
        int dateVal = mPlot.invTransform( QwtPlot::xBottom, aEvent->x() - offset );
        QDate date = REFERENCE_DATE.addDays( dateVal );
        if( mFilter.mStartDate <= date && mFilter.mEndDate >= date )
        {
            mDisplayLabel.setDate( QDate(date.year(), date.month(), 1) );
            for( int i = 0; i < TransactionManager::sMonthList.size(); i++ )
            {
                Month* month = TransactionManager::sMonthList[i];
                if( date.year() == month->getDate().year() && date.month() == month->getDate().month() )
                {
                    float income = month->getIncome( mFilter );
                    float expense = month->getExpense( mFilter );
                    float netWorth = month->getNetWorth( mFilter );
                    QString colorStr = "black";
                    QString str = "Month: " + date.toString("MMM yyyy") + "<br>";
                    if( income != 0 ){ colorStr = ( income > 0 ) ? "green" : "red"; }
                    str += "Income: <font color=\"" + colorStr + "\">$" + QString::number( income, 'f', 2 ) + "</font><br>";
                    colorStr = "black";
                    if( expense != 0 ){ colorStr = ( expense > 0 ) ? "green" : "red"; }
                    str += "Expense: <font color=\"" + colorStr + "\">$" + QString::number( expense, 'f', 2 ) + "</font><br>";
                    colorStr = "black";
                    if( netWorth != 0 ){ colorStr = ( netWorth > 0 ) ? "green" : "red"; }
                    str += "Net Worth: <font color=\"" + colorStr + "\">$" + QString::number( netWorth, 'f', 2 ) + "</font>";
                    str += "<center><font size=\"-2\" color=\"blue\">Dbl click to See Transactions</font></center>";
                    mDisplayLabel.setText( str );
                    mDisplayLabel.show();
                    break;
                }
            }
        }
    }
} // BarGraph::mouseReleaseEvent

//----------------------------------------------------------------------------
// Set Graph Mode
//----------------------------------------------------------------------------
void BarGraph::setGraphMode( BarChartType aGraphMode )
{
    mGraphMode = aGraphMode;
    switch( mGraphMode )
    {
    case BAR_NET_INCOME:
        mPlot.setTitle("Net Income / Expense");
        mPlot.setAxisTitle( QwtPlot::yLeft, "Amount ($)" );
        mPlot.setAxisTitle( QwtPlot::xBottom, "Date" );
        break;
    case BAR_NET_WORTH:
    default:
        mPlot.setTitle("Net Worth");
        mPlot.setAxisTitle( QwtPlot::yLeft, "Amount ($)" );
        mPlot.setAxisTitle( QwtPlot::xBottom, "Date" );
        break;
    }
} // BarGraph::setGraphMode

//----------------------------------------------------------------------------
// clear
//----------------------------------------------------------------------------
void BarGraph::clear()
{
    hideDisplayLabel();
    mFilter = Transaction::FilterType();
    mFilter.mStartDate = TransactionManager::cDefaultStartDate;
    mFilter.mEndDate = TransactionManager::cDefaultEndDate;
    mPlot.setAxisScale( QwtPlot::xBottom, REFERENCE_DATE.daysTo(mFilter.mStartDate), REFERENCE_DATE.daysTo(mFilter.mEndDate), 30.416 );
    mPlot.setAxisScale( QwtPlot::yLeft, -1000, 1000 );
    mIncomeCurve->setSamples( QVector<double>(), QVector<double>() );
    mPositiveHistogram->setSamples( QVector<QwtIntervalSample>() );
    mNegativeHistogram->setSamples( QVector<QwtIntervalSample>() );
    mPlot.replot();
    mDataSet = false;
} // BarGraph::clear

//----------------------------------------------------------------------------
// Set Transaction Data
//----------------------------------------------------------------------------
void BarGraph::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    mDataSet = false;
    mFilter = aFilter;
    hideDisplayLabel();

    // Setup date axis
    mFilter.mStartDate.setDate( aFilter.mStartDate.year(), aFilter.mStartDate.month(), 1 );
    mFilter.mEndDate.setDate( aFilter.mEndDate.year(), aFilter.mEndDate.month(), 1 );
    if( aFilter.mStartDate < aFilter.mEndDate )
    {
        int monthStep = 1;
        mFilter.mEndDate = mFilter.mEndDate.addMonths(1).addDays(-1);
        if( mFilter.mStartDate.daysTo(mFilter.mEndDate) > 365*7 )
        {
            monthStep = 12;
        }
        else if( mFilter.mStartDate.daysTo(mFilter.mEndDate) > 365*3 )
        {
            monthStep = 6;
        }
        else if( mFilter.mStartDate.daysTo(mFilter.mEndDate) > 365*1.5 )
        {
            monthStep = 2;
        }
        mPlot.setAxisScale( QwtPlot::xBottom, REFERENCE_DATE.daysTo(mFilter.mStartDate), REFERENCE_DATE.daysTo(mFilter.mEndDate), 30.416*monthStep );
        mPlot.updateAxes();
    }

    // Setup histogram
    QVector<QwtIntervalSample> positiveSamples;
    QVector<QwtIntervalSample> negativeSamples;
    QVector<double> curveXSamples;
    QVector<double> curveYSamples;
    float maxValue = 0;
    float minValue = 0;
    const int BAR_BUFFER = 3;
    for( int i = 0; i < TransactionManager::sMonthList.size(); i++ )
    {
        // Date
        Month* month = TransactionManager::sMonthList[i];
        if( mFilter.mStartDate <= month->getDate() && mFilter.mEndDate >= month->getDate() )
        {
            float startDay = REFERENCE_DATE.daysTo(month->getDate()) + BAR_BUFFER;
            float endDay = startDay + month->getDate().daysInMonth() - BAR_BUFFER*2;
            float positiveValue = 0;
            float negativeValue = 0;
            float netWorth = 0;
            switch( mGraphMode )
            {
            case BAR_NET_INCOME:
                positiveValue = month->getIncome( mFilter );
                negativeValue = month->getExpense( mFilter );
                curveXSamples.push_back( REFERENCE_DATE.daysTo(month->getDate())+14 );
                curveYSamples.push_back( positiveValue + negativeValue );
                break;
            case BAR_NET_WORTH:
                netWorth = month->getNetWorth( mFilter );
                ( netWorth > 0 ) ? positiveValue = netWorth : negativeValue = netWorth;
                break;
            }
            QwtIntervalSample sample;
            sample.interval = QwtInterval( startDay, endDay );
            sample.value = positiveValue;
            positiveSamples.push_back( sample );
            sample.value = negativeValue;
            negativeSamples.push_back( sample );

            // Set max values
            maxValue = ( positiveValue > maxValue ) ? positiveValue : maxValue;
            minValue = ( negativeValue < minValue ) ? negativeValue : minValue;
            mDataSet = true;
        }
    }

    mPlot.setAxisScale( QwtPlot::yLeft, minValue*1.20, maxValue*1.20 );
    ( positiveSamples.size() < 15 ) ? mIncomeCurve->setSamples( curveXSamples, curveYSamples ) : mIncomeCurve->setSamples( QVector<double>(), QVector<double>() );
    mPositiveHistogram->setSamples( positiveSamples );
    mNegativeHistogram->setSamples( negativeSamples );
    mPlot.replot();
} // BarGraph::setTransactionData()

