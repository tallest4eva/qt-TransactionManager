//******************************************************************************
//
//  HEADER NAME: GraphWidget.cpp
//******************************************************************************

#include <QtGui>
#include <QHBoxLayout>

#include <qwt_plot_layout.h>

#include "GraphWidget.h"
#include "Month.h"
#include "TransactionManager.h"

const QDate GraphWidget::REFERENCE_DATE = QDate(1990,1,1);
static const int DISPLAY_LABEL_TIMOEUT = 5000;              // Display label timeout

class TimeScaleDraw : public QwtScaleDraw
{
public:
    virtual QwtText label( double aValue ) const
    {
        QDate date = GraphWidget::REFERENCE_DATE.addDays( aValue );
        return QwtText( date.toString("MMMyy") );
    }
};

GraphWidget::GraphWidget(QWidget *parent) :
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
    mStartDate.setDate( 2000, 1, 1 );
    mEndDate.setDate( 2001, 1, 1 );

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
    mDisplayLabel.setGeometry( 0, 0, 150, 90 );
    mDisplayLabel.setFrameShadow( QFrame::Raised );
    mDisplayLabel.setFrameShape( QFrame::StyledPanel );
    mDisplayLabel.setPalette( QPalette(Qt::black,Qt::white) );
    mDisplayLabel.setAutoFillBackground( true );
    connect( &mDisplayLabel, SIGNAL(clicked()), this, SLOT(handleDisplayClicked()) );

    QFont font;
    font.setPointSize( 10 );
    mDisplayLabel.setFont( font );
    mDisplayTimer.setSingleShot( true );
    connect( &mDisplayTimer, SIGNAL(timeout()), this, SLOT(hideDisplayLabel()) );
    mRubberBand = new QRubberBand( QRubberBand::Rectangle, this );
} // GraphWidget::GraphWidget

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
GraphWidget::~GraphWidget()
{
    mDisplayTimer.stop();
    delete mRubberBand;
    delete mGrid;
    delete mIncomeCurve;
    delete mPositiveHistogram;
    delete mNegativeHistogram;
} // GraphWidget::~GraphWidget

//----------------------------------------------------------------------------
// hideDisplayLabel
//----------------------------------------------------------------------------
void GraphWidget::hideDisplayLabel()
{
    mDisplayTimer.stop();
    mDisplayLabel.hide();
} // GraphWidget::hideDisplayLabel

//----------------------------------------------------------------------------
// handle Display Clicked
//----------------------------------------------------------------------------
void GraphWidget::handleDisplayClicked()
{
    hideDisplayLabel();
    QDate date = mDisplayLabel.getDate();
    transactionDateSelected( date, date.addMonths(1).addDays(-1) );
} // GraphWidget::handleDisplayClicked

//----------------------------------------------------------------------------
// mousePressEvent
//----------------------------------------------------------------------------
void GraphWidget::mousePressEvent( QMouseEvent* aEvent )
{
    mDrag = false;
    QWidget::mousePressEvent( aEvent );

    if( mDataSet )
    {
        QRectF rect = mPlot.plotLayout()->canvasRect();
        mOrigin = QPoint( aEvent->x(), rect.y()+10 );
        mRubberBand->setGeometry( QRect( mOrigin, QSize(0,rect.height()) ) );
        mRubberBand->show();
    }
} // GraphWidget::mousePressEvent

//----------------------------------------------------------------------------
// mouseMoveEvent
//----------------------------------------------------------------------------
void GraphWidget::mouseMoveEvent( QMouseEvent* aEvent )
{
    mDrag = true;
    QWidget::mouseMoveEvent( aEvent );

    if( mDataSet )
    {
        QRectF rect = mRubberBand->rect();
        mRubberBand->setGeometry( QRect(mOrigin, QSize( aEvent->x() - mOrigin.x(),rect.height() )) );
    }
} // GraphWidget::mouseMoveEvent
    
//----------------------------------------------------------------------------
// mouseReleaseEvent
//----------------------------------------------------------------------------
void GraphWidget::mouseReleaseEvent( QMouseEvent * aEvent )
{
    QWidget::mouseReleaseEvent( aEvent );

    mRubberBand->hide();
    int offset = mPlot.plotLayout()->canvasRect().x()+10;
    if( mDrag )
    {
        mDrag = false;
        if( mDataSet )
        {
            int startDateVal = mPlot.invTransform( QwtPlot::xBottom, mOrigin.x() - offset );
            QDate startDate = REFERENCE_DATE.addDays( startDateVal );
            int endDateVal = mPlot.invTransform( QwtPlot::xBottom, aEvent->x() - offset );
            QDate endDate = REFERENCE_DATE.addDays( endDateVal );
            if( endDate > startDate.addMonths(1) )
            {
                reportDateSelected( startDate, endDate );
            }
        }
        return;
    }
    
    if( mDisplayTimer.isActive() )
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
        QString ref = date.toString("yyyy-MM-dd") + " " + QString::number( aEvent->x() - offset );
        mDisplayLabel.setDate( QDate(date.year(), date.month(), 1) );
        for( int i = 0; i < TransactionManager::mMonthList.size(); i++ )
        {
            Month* month = TransactionManager::mMonthList[i];
            if( date.year() == month->getDate().year() && date.month() == month->getDate().month() )
            {
                QString str = "Month: " + date.toString("MMM yyyy") + "<br>";
                str += "Income: <font color=\"green\">$" + QString::number( month->getIncome( mFilter ), 'f', 2 ) + "</font><br>";
                str += "Expense: <font color=\"red\">$" + QString::number( month->getExpense( mFilter ), 'f', 2 ) + "</font><br>";
                str += "Net Worth: ";
                float netWorth = month->getNetWorth( mFilter );
                if( netWorth != 0 )
                {
                    str += ( netWorth > 0 ) ? "<font color=\"green\">" : "<font color=\"red\">";
                }
                str += "$" + QString::number( netWorth, 'f', 2 );
                if( netWorth != 0 )
                {
                    str += "</font>";
                }
                str += "<center><font color=\"blue\">See Transactions</font></center>";
                mDisplayLabel.setText( str );
                mDisplayLabel.show();
                mDisplayTimer.start( DISPLAY_LABEL_TIMOEUT );
                break;
            }
        }
    }
} // GraphWidget::mouseReleaseEvent

//----------------------------------------------------------------------------
// Set Graph Mode
//----------------------------------------------------------------------------
void GraphWidget::setGraphMode( BarChartType aGraphMode )
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
} // GraphWidget::setGraphMode

//----------------------------------------------------------------------------
// clear
//----------------------------------------------------------------------------
void GraphWidget::clear()
{
    mFilter = Transaction::FilterType();
    mStartDate.setDate( 2000, 1, 1 );
    mEndDate.setDate( 2001, 1, 1 );
    mPlot.setAxisScale( QwtPlot::xBottom, REFERENCE_DATE.daysTo(mStartDate), REFERENCE_DATE.daysTo(mEndDate), 30.416 );
    mPlot.setAxisScale( QwtPlot::yLeft, -1000, 1000 );
    //mIncomeCurve->setSamples( QVector<double>(), QVector<double>() );
    mPositiveHistogram->setSamples( QVector<QwtIntervalSample>() );
    mNegativeHistogram->setSamples( QVector<QwtIntervalSample>() );
    mDataSet = false;
} // GraphWidget::clear

//----------------------------------------------------------------------------
// Set Transaction Data
//----------------------------------------------------------------------------
void GraphWidget::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    mDataSet = false;
    mFilter = aFilter;
    mStartDate = aFilter.mStartDate;
    mEndDate = aFilter.mEndDate;
    hideDisplayLabel();

    // Setup date axis
    mStartDate.setDate( aFilter.mStartDate.year(), aFilter.mStartDate.month(), 1 );
    mEndDate.setDate( aFilter.mEndDate.year(), aFilter.mEndDate.month(), 1 );
    if( mStartDate < mEndDate )
    {
        mEndDate = mEndDate.addMonths(1);
        int monthStep = 1;
        if( mStartDate.daysTo(mEndDate) > 365*7 )
        {
            monthStep = 12;
        }
        else if( mStartDate.daysTo(mEndDate) > 365*3 )
        {
            monthStep = 6;
        }
        else if( mStartDate.daysTo(mEndDate) > 365*1.5 )
        {
            monthStep = 2;
        }
        mPlot.setAxisScale( QwtPlot::xBottom, REFERENCE_DATE.daysTo(mStartDate), REFERENCE_DATE.daysTo(mEndDate), 30.416*monthStep );
        mPlot.updateAxes();
    }

    // Setup histogram
    QVector<QwtIntervalSample> positiveSamples;
    QVector<QwtIntervalSample> negativeSamples;
    QVector<double> curveXSamples;
    QVector<double> curveYSamples;
    float maxValue = 0;
    float minValue = 0;
    for( int i = 0; i < TransactionManager::mMonthList.size(); i++ )
    {
        // Date
        Month* month = TransactionManager::mMonthList[i];
        if( mStartDate <= month->getDate() && mEndDate > month->getDate() )
        {
            float startDay = REFERENCE_DATE.daysTo(month->getDate()) + 2;
            float endDay = startDay + month->getDate().daysInMonth() - 4;
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
    //mIncomeCurve->setSamples( curveXSamples, curveYSamples );
    mPositiveHistogram->setSamples( positiveSamples );
    mNegativeHistogram->setSamples( negativeSamples );
    mPlot.replot();
} // GraphWidget::setTransactionData()

