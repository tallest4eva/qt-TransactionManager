//******************************************************************************
//
//  HEADER NAME: GraphWidget.cpp
//******************************************************************************

#include <QtGui>
#include <QHBoxLayout>

#include <qwt_plot_layout.h>

#include "GraphWidget.h"

const QDate GraphWidget::REFERENCE_DATE = QDate(1990,1,1);
static const int DISPLAY_LABEL_TIMOEUT = 3000;              // Display label timeout

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
} // GraphWidget::GraphWidget

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
GraphWidget::~GraphWidget()
{
    mDisplayTimer.stop();
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
    dateSelected( date, date.addMonths(1).addDays(-1) );
} // GraphWidget::handleDisplayClicked

//----------------------------------------------------------------------------
// mouseReleaseEvent
//----------------------------------------------------------------------------
void GraphWidget::mouseReleaseEvent( QMouseEvent * aEvent )
{
    QWidget::mouseReleaseEvent( aEvent );

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
        QRectF rect = mPlot.plotLayout()->canvasRect();
        int dateVal = mPlot.invTransform( QwtPlot::xBottom, aEvent->x() - rect.x() );
        QDate date = REFERENCE_DATE.addDays( dateVal-10 );
        mDisplayLabel.setDate( QDate(date.year(), date.month(), 1) );
        for( int i = 0; i < mMonthDataList.size(); i++ )
        {
            if( date.year() == mMonthDataList[i].date.year() && date.month() == mMonthDataList[i].date.month() )
            {
                QString str = "Month: " + date.toString("MMM yyyy") + "<br>";
                str += "Income: <font color=\"green\">$" + QString::number( mMonthDataList[i].income, 'f', 2 ) + "</font><br>";
                str += "Expense: <font color=\"red\">$" + QString::number( mMonthDataList[i].expense, 'f', 2 ) + "</font><br>";
                str += "Net Worth: ";
                if( mMonthDataList[i].netWorth != 0 )
                {
                    str += ( mMonthDataList[i].netWorth > 0 ) ? "<font color=\"green\">" : "<font color=\"red\">";
                }
                str += "$" + QString::number( mMonthDataList[i].netWorth, 'f', 2 );
                if( mMonthDataList[i].netWorth != 0 )
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
// Set Transaction Data
//----------------------------------------------------------------------------
void GraphWidget::setTransactionData
    (
    const QDate& aStartDate,
    const QDate& aEndDate,
    const QList<Account*>& aAccountList,
    const QList<Transaction*>& aTransactionList
    )
{
    mStartDate = aStartDate;
    mEndDate = aEndDate;
    mMonthDataList.clear();
    hideDisplayLabel();

    // Setup date axis
    if( mStartDate < mEndDate )
    {
        int monthStep = 1;
        QDate startDate = QDate( mStartDate.year(), mStartDate.month(), 1 );
        QDate endDate = QDate( mEndDate.year(), mEndDate.month(), 1 );
        endDate = endDate.addMonths(1);
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
        mPlot.setAxisScale( QwtPlot::xBottom, REFERENCE_DATE.daysTo(startDate), REFERENCE_DATE.daysTo(endDate), 30.416*monthStep );
        mPlot.updateAxes();

        // Create month list
        for( QDate date = startDate; date < endDate; date = date.addMonths(1) )
        {
            MonthDataType data;
            data.date = date;
            mMonthDataList.push_back( data );
        }
    }
    
    // Calculate income / expense
    if( aTransactionList.size() > 0 )
    {
        for( int i = 0; i < aTransactionList.size(); i++ )
        {
            Transaction* transaction = aTransactionList[i];

            // Skip transfer categories
            Category::CategoryIdType category = transaction->getCategory();
            switch( category )
            {
            case Category::TRANSFER:
            case Category::CREDIT_CARD_PAYMENT:
            case Category::FAMILY_TRANSFER:
            case Category::TRANSFER_FOR_CASH_SPENDING:
            case Category::ACCOUNT_BALANCE:
                continue;
            default:
                break;
            }

            // Create income/expense data list
            QDate date = transaction->getTransactionDate();
            for( int j = 0; j < mMonthDataList.size(); j++ )
            {
                if( date.year() == mMonthDataList[j].date.year() && date.month() == mMonthDataList[j].date.month() )
                {
                    if( transaction->getType() == Transaction::TRANSACTION_CREDIT )
                    {
                        mMonthDataList[j].income += transaction->getAmount();
                    }
                    else
                    {
                        mMonthDataList[j].expense += transaction->getAmount();
                    }
                    break;
                }
            }
        }
    }

    // Calculate net worth
    if( aAccountList.size() > 0 )
    {
        for( int i = 0; i < aAccountList.size(); i++ )
        {
            QList<Transaction*> transactionList = aAccountList[i]->getTransactionList();
            QVector<float> netWorth( mMonthDataList.size(), 0 );
            for( int j = 0; j < mMonthDataList.size(); j++ )
            {
                float currentNetWorth = 0;
                for( int k = 0; k < transactionList.size(); k++ )
                {
                    Transaction* transaction = transactionList[k];
                    QDate date = transaction->getTransactionDate();
                    if( date >= mMonthDataList[j].date.addMonths(1) )
                    {
                        netWorth[j] = currentNetWorth;
                        break;
                    }
                    else if( k == transactionList.size()-1 )
                    {
                        netWorth[j] = transaction->getCurrentBalance();
                    }
                    currentNetWorth = transaction->getCurrentBalance();
                }
            }
            for( int j = 0; j < mMonthDataList.size(); j++ )
            {
                mMonthDataList[j].netWorth += netWorth[j];
            }
        }
    }

    // Setup histogram
    QVector<QwtIntervalSample> positiveSamples;
    QVector<QwtIntervalSample> negativeSamples;
    QVector<double> curveXSamples;
    QVector<double> curveYSamples;
    if( mMonthDataList.size() > 0 )
    {
        float maxValue = 0;
        float minValue = 0;
        for( int i = 0; i < mMonthDataList.size(); i++ )
        {
            float startDay = REFERENCE_DATE.daysTo(mMonthDataList[i].date) + 2;
            float endDay = startDay + mMonthDataList[i].date.daysInMonth() - 4;
            float positiveValue = 0;
            float negativeValue = 0;
            switch( mGraphMode )
            {
            case BAR_NET_INCOME:
                positiveValue = mMonthDataList[i].income;
                negativeValue = mMonthDataList[i].expense;
                curveXSamples.push_back( REFERENCE_DATE.daysTo(mMonthDataList[i].date)+14 );
                curveYSamples.push_back( mMonthDataList[i].income + mMonthDataList[i].expense );
                break;
            case BAR_NET_WORTH:
                ( mMonthDataList[i].netWorth > 0 ) ? positiveValue = mMonthDataList[i].netWorth : negativeValue = mMonthDataList[i].netWorth;
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
        }
        mPlot.setAxisScale( QwtPlot::yLeft, minValue*1.20, maxValue*1.20 );
    }
    //mIncomeCurve->setSamples( curveXSamples, curveYSamples );
    mPositiveHistogram->setSamples( positiveSamples );
    mNegativeHistogram->setSamples( negativeSamples );
    mPlot.replot();
} // GraphWidget::setTransactionData()

