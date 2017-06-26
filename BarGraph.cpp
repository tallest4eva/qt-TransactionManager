//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: BarGraph.cpp
//******************************************************************************

#include <QtGui>
#include <QHBoxLayout>

#include "BarGraph.hpp"
#include "Month.hpp"
#include "TransactionManager.hpp"

static const int SECONDS_IN_A_DAY = 86400;                      // Number of seconds in a day
static const int SECONDS_IN_A_MONTH = SECONDS_IN_A_DAY * 28;    // Number of days in a month
static const int NET_INCOME_GRAPH_IDX = 0;
static const int COLOR_RANGE = 260;
static const int MAX_COLOR_STEP = 40;
static QColor BASE_COLOR = QColor(140, 80, 230);

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
BarGraph::BarGraph( BarChartType aGraphMode, QWidget* aParent ) :
    QWidget( aParent )
  , mGraphMode( aGraphMode )
  , mPositiveHistogram( NULL )
  , mNegativeHistogram( NULL )
  , mRubberBand( NULL )
  , mDrag( false )
  , mDataSet( false )
  , mMonthInterval( 1 )
  , mShowNetIncome( false )
  , mShowTransfers( false )
{
    setBackgroundRole( QPalette::Base );

    // Create graph
    mPlot.xAxis->setTickLabelType( QCPAxis::ltDateTime );
    mPlot.xAxis->setDateTimeFormat( "MMMyyyy" );
    mPlot.xAxis->setTickLabelFont( QFont(QFont().family(), 7) );
    mPlot.xAxis->setAutoTickStep( true );
    mPlot.xAxis->setAutoTickLabels( true );

    mPlot.plotLayout()->insertRow( 0 );
    mPlot.plotLayout()->addElement( 0, 0, new QCPPlotTitle(&mPlot) );
    mPlot.yAxis->setLabel( "Amount ($)" );
    mPlot.xAxis->setLabel( "Date" );

    mPositiveHistogram = new QCPBars( mPlot.xAxis, mPlot.yAxis );
    mPositiveHistogram->setPen(QPen(Qt::black));
    mPositiveHistogram->setBrush(QBrush(Qt::green));
    mPositiveHistogram->setSelectedBrush(QBrush(Qt::green, Qt::Dense1Pattern ));
    mPlot.addPlottable( mPositiveHistogram );

    mNegativeHistogram = new QCPBars( mPlot.xAxis, mPlot.yAxis );
    mNegativeHistogram->setPen(QPen(Qt::black));
    mNegativeHistogram->setBrush(QBrush(Qt::red));
    mNegativeHistogram->setSelectedBrush(QBrush(Qt::red, Qt::Dense1Pattern ));
    mPlot.addPlottable( mNegativeHistogram );

    mPlot.addGraph();
    mPlot.graph(NET_INCOME_GRAPH_IDX)->setPen(QPen(Qt::black));
    mPlot.graph(NET_INCOME_GRAPH_IDX)->setLineStyle(QCPGraph::lsLine);
    mPlot.graph(NET_INCOME_GRAPH_IDX)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));

    // Add mouse events
	connect( &mPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(handlePlottableMousePressEvent(QMouseEvent*)) );
	connect( &mPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(handlePlottableMouseMoveEvent(QMouseEvent*)) );
	connect( &mPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(handlePlottableMouseReleaseEvent(QMouseEvent*)) );

    // Add plotter to widget
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget( &mPlot );
    setLayout( layout );

    // Set up display label
    mDisplayLabel.setParent( this );
    mDisplayLabel.hide();
    if( mGraphMode == BAR_ACCOUNT_BALANCE )
    {
        mDisplayLabel.setGeometry( 0, 0, 270, 135 );
    }
    else
    {
        mDisplayLabel.setGeometry( 0, 0, 175, 105 );
    }
    connect( &mDisplayLabel, SIGNAL(clicked()), this, SLOT(handleDisplayClicked()) );
    mRubberBand = new QRubberBand( QRubberBand::Rectangle, this );

    updateTitleText();
    clear();
} // BarGraph::BarGraph

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
BarGraph::~BarGraph()
{
    delete mRubberBand;
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
    Transaction::FilterType filter = mFilter;
    filter.selectDateRange( mDisplayLabel.getStartDate(), mDisplayLabel.getEndDate() );
    filter.showToolBox = "dates";
    transactionFilterSelected( filter );
} // BarGraph::handleDisplayClicked

//----------------------------------------------------------------------------
// mousePressEvent
//----------------------------------------------------------------------------
void BarGraph::handlePlottableMousePressEvent( QMouseEvent* aEvent )
{
    mDrag = false;
    QRect axisRect = mPlot.axisRect()->rect();
    if( mDataSet && axisRect.contains( aEvent->x(), aEvent->y() ) )
    {
        mStartDragPosition = aEvent->x();
        int offset = mPlot.xAxis->padding() + mPlot.xAxis->labelPadding();
        mRubberBand->setGeometry( QRect( aEvent->x()+offset, axisRect.y()+offset, 0, axisRect.height() ) );
        mRubberBand->show();
    }
} // BarGraph::mousePressEvent

//----------------------------------------------------------------------------
// mouseMoveEvent
//----------------------------------------------------------------------------
void BarGraph::handlePlottableMouseMoveEvent( QMouseEvent* aEvent )
{
    mDrag = true;
    QRect axisRect = mPlot.axisRect()->rect();
    if( mDataSet && axisRect.contains( aEvent->x(), aEvent->y() ) )
    {
        int offset = mPlot.xAxis->padding() + mPlot.xAxis->labelPadding();
        QRect rect = mRubberBand->geometry();
        rect.setRight( aEvent->x()+offset );
        mRubberBand->setGeometry( rect );
    }
} // BarGraph::mouseMoveEvent

//----------------------------------------------------------------------------
// mouseReleaseEvent
//----------------------------------------------------------------------------
void BarGraph::handlePlottableMouseReleaseEvent( QMouseEvent* aEvent )
{
    mRubberBand->hide();
    int xOffset = mPlot.xAxis->padding() + mPlot.xAxis->labelPadding();
    int yOffset = mPlot.yAxis->padding() + mPlot.yAxis->labelPadding();
    QRect axisRect = mPlot.axisRect()->rect();
    if( !axisRect.contains( aEvent->x(), aEvent->y() ) ){ return; }
    if( mDrag )
    {
        mDrag = false;
        if( mDataSet )
        {
            // Set new report date interval
            double key = mPlot.xAxis->pixelToCoord( mStartDragPosition );
            QDateTime dateTime;
            dateTime.setTime_t( key );
            QDate startDate = dateTime.date();
            key = mPlot.xAxis->pixelToCoord( aEvent->x() );
            dateTime.setTime_t( key );
            QDate endDate = dateTime.date();
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
        int labelRectX = aEvent->x()+xOffset - labelRectW/2;
        labelRectX = ( labelRectX < 0 ) ? 0 : labelRectX;
        labelRectX = ( labelRectX + labelRectW > width() ) ? width() - labelRectW : labelRectX;
        int labelRectY = aEvent->y()+yOffset - labelRectH;
        labelRectY = ( labelRectY < 0 ) ? 0 : labelRectY;
        labelRectY = ( labelRectY + labelRectH > height() ) ? height() - labelRectH : labelRectY;
        mDisplayLabel.move( labelRectX, labelRectY );
        mDisplayLabel.setText( "" );
        mDisplayLabel.hide();

        // Get point info
        double key = mPlot.xAxis->pixelToCoord( aEvent->x() );
        double selectedBalance = mPlot.yAxis->pixelToCoord( aEvent->y() );
        QDateTime dateTime;
        dateTime.setTime_t( key );
        QDate date = dateTime.date();
        for( int i = 0; i < mBarDataList.size(); i++ )
        {
            if( date <= mBarDataList[i].endDate )
            {
                QDate startDate = ( mBarDataList[i].startDate < mFilter.mStartDate ) ? mFilter.mStartDate : mBarDataList[i].startDate;
                QDate endDate = ( mBarDataList[i].endDate > mFilter.mEndDate ) ? mFilter.mEndDate : mBarDataList[i].endDate;
                mDisplayLabel.setDates( startDate, endDate );
                float income = mBarDataList[i].income;
                float expense = mBarDataList[i].expense;
                float netIncome = income + expense;
                float netWorth = mBarDataList[i].netWorth;
                float transfers = mBarDataList[i].transfers;
                QString colorStr = "black";
                QString str = "Month: ";
                // Assumes the dates are in the same year
                if( startDate.month() != endDate.month() ){ str += startDate.toString("MMM") + "-" + endDate.toString("MMM yyyy"); }
                else{ str += startDate.toString("MMM yyyy"); }
                str += "<br>";
                if( mGraphMode == BAR_ACCOUNT_BALANCE )
                {
                    // Display closest account balance, and top 3 accounts info
                    const int cAccountBalanceDisplayCount = 3;
                    QString topAccountsStr;
                    QString selectedAccountStr;
                    float currentDiff = 10000000;
                    for( int j = 0; j < mBarDataList[i].accountList.size(); j++ )
                    {
                        float balance = mBarDataList[i].accountList[j].balance;
                        colorStr = "black";
                        if( balance != 0 ){ colorStr = ( balance > 0 ) ? "green" : "red"; }
                        QString accountStr = "<font size=\"-1\" color=\"" + mBarDataList[i].accountList[j].color.name() + "\">- " +
                               mBarDataList[i].accountList[j].name.left(35) + "</font>: <font color=\"" + colorStr + "\">" +
                               Transaction::getAmountText( balance ) + "</font><br>";

                        float diff = qAbs( selectedBalance - balance );
                        if( diff < currentDiff ){ selectedAccountStr = accountStr; currentDiff = diff; }
                        if( j < cAccountBalanceDisplayCount ){ topAccountsStr += accountStr; }
                    }
                    str += "Selected Account:<br>" + selectedAccountStr;
                    str += "Top Account Balances:<br>" + topAccountsStr;
                }
                else
                {
                    // Net income and Net worth bar graphs
                    if( income != 0 ){ colorStr = ( income > 0 ) ? "green" : "red"; }
                    str += "Income: <font color=\"" + colorStr + "\">" + Transaction::getAmountText( income ) + "</font><br>";
                    colorStr = "black";
                    if( expense != 0 ){ colorStr = ( expense > 0 ) ? "green" : "red"; }
                    str += "Expense: <font color=\"" + colorStr + "\">" + Transaction::getAmountText( expense ) + "</font><br>";
                    colorStr = "black";
                    if( netIncome != 0 ){ colorStr = ( netIncome > 0 ) ? "green" : "red"; }
                    str += "Net Income: <font color=\"" + colorStr + "\">" + Transaction::getAmountText( netIncome ) + "</font><br>";
                    colorStr = "black";
                    if( transfers != 0 ){ colorStr = ( transfers > 0 ) ? "green" : "red"; }
                    str += "Net Transfers: <font color=\"" + colorStr + "\">" + Transaction::getAmountText( transfers ) + "</font><br>";
                }
                colorStr = "black";
                if( netWorth != 0 ){ colorStr = ( netWorth > 0 ) ? "green" : "red"; }
                str += "Net Worth: <font color=\"" + colorStr + "\">" + Transaction::getAmountText( netWorth ) + "</font>";
                str += "<center><font size=\"-2\" color=\"blue\">Double-click to See Transactions</font></center>";
                mDisplayLabel.setText( str );
                mDisplayLabel.show();
                break;
            }
        }
    }
} // BarGraph::handlePlottableMouseReleaseEvent

//----------------------------------------------------------------------------
// UpdateTitleText
//----------------------------------------------------------------------------
void BarGraph::updateTitleText()
{
    QString titleText;
    switch( mMonthInterval )
    {
    case 1:
        titleText = "Monthly";
        break;
    case 3:
        titleText = "Quarterly";
        break;
    case 6:
        titleText = "BiAnnual";
        break;
    case 12:
    default:
        titleText = "Annual";
        break;
    }

    switch( mGraphMode )
    {
    case BAR_NET_INCOME:
        titleText += " Income / Expense";
        if( mShowTransfers ){ titleText += " / Transfers"; }
        if( mShowNetIncome ){ titleText += " / Net Income"; }
        break;
    case BAR_NET_WORTH:
        titleText += " Net Worth";
        break;
    case BAR_ACCOUNT_BALANCE:
        titleText += " Account Balance";
        break;
    default:
        break;
    }
    QCPPlotTitle* title = (QCPPlotTitle*)mPlot.plotLayout()->element( 0, 0 );
    if( title )
    {
        title->setText( titleText );
    }
} // BarGraph::updateTitleText

//----------------------------------------------------------------------------
// clear
//----------------------------------------------------------------------------
void BarGraph::clear()
{
    hideDisplayLabel();
    mFilter = Transaction::FilterType();
    mFilter.mStartDate = TransactionManager::cDefaultStartDate;
    mFilter.mEndDate = TransactionManager::cDefaultEndDate;
    mPlot.xAxis->setRange( QDateTime(mFilter.mStartDate).toTime_t(), QDateTime(mFilter.mEndDate).toTime_t() );
    mPlot.yAxis->setRange( -1000, 1000 );
    mPlot.graph(NET_INCOME_GRAPH_IDX)->clearData();
    mPositiveHistogram->clearData();
    mNegativeHistogram->clearData();
    mPlot.replot();
    mBarDataList.clear();
    mDataSet = false;
} // BarGraph::clear

//----------------------------------------------------------------------------
// Set Show Net Income graph
//----------------------------------------------------------------------------
void BarGraph::setShowNetIncome( bool aShowNetIncome, bool aUpdate )
{
    mShowNetIncome = aShowNetIncome;
    if( aUpdate )
    {
        if( mGraphMode == BAR_NET_INCOME )
        {
            updateTitleText();
            updateChart();
        }
    }
}

//----------------------------------------------------------------------------
// Set Show Transfers
//----------------------------------------------------------------------------
void BarGraph::setShowTransfers( bool aShowTransfers, bool aUpdate )
{
    mShowTransfers = aShowTransfers;
    if( aUpdate )
    {
        if( mGraphMode == BAR_NET_INCOME )
        {
            updateTitleText();
            updateChart();
        }
    }
}

//----------------------------------------------------------------------------
// Set Month Interval
//----------------------------------------------------------------------------
void BarGraph::setMonthInterval( int aMonthInterval )
{
    mMonthInterval = aMonthInterval;
    updateTitleText();
    updateChart();
}

//----------------------------------------------------------------------------
// Set Transaction Data
//----------------------------------------------------------------------------
void BarGraph::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    mFilter = aFilter;
    updateChart();
}

//----------------------------------------------------------------------------
// Update chart
//----------------------------------------------------------------------------
void BarGraph::updateChart()
{
    mDataSet = false;
    hideDisplayLabel();
    mPlot.graph(NET_INCOME_GRAPH_IDX)->clearData();
    mPositiveHistogram->clearData();
    mNegativeHistogram->clearData();
    mBarDataList.clear();

    // Setup date axis
    QDate originalStartDate = mFilter.mStartDate;
    QDate originalEndDate = mFilter.mEndDate;
    mFilter.mStartDate.setDate( originalStartDate.year(), originalStartDate.month(), 1 );
    mFilter.mEndDate.setDate( originalEndDate.year(), originalEndDate.month(), originalEndDate.daysInMonth() );
    QDate rangeStartDate = mFilter.mStartDate;
    QDate rangeEndDate = mFilter.mEndDate;
    if( mFilter.mStartDate < mFilter.mEndDate )
    {
        if( mMonthInterval > 1 )
        {
            int month = rangeStartDate.month() - 1;
            rangeStartDate = rangeStartDate.addMonths( -(month % mMonthInterval) );
            month = rangeEndDate.month();
            rangeEndDate = rangeEndDate.addMonths( (month%mMonthInterval != 0) ? mMonthInterval - (month % mMonthInterval) : 0 );
        }
        mPlot.xAxis->setRange( QDateTime( rangeStartDate.addDays(-3) ).toTime_t(), QDateTime( rangeEndDate ).toTime_t() );
        if( mPositiveHistogram ){ mPositiveHistogram->setWidth( SECONDS_IN_A_MONTH * mMonthInterval ); }
        if( mNegativeHistogram ){ mNegativeHistogram->setWidth( SECONDS_IN_A_MONTH * mMonthInterval ); }

        // Set up date ticks
        int monthCount = 0;
        for( QDate startDate = mFilter.mStartDate; startDate < originalEndDate; startDate = startDate.addMonths(1) ){ monthCount++; }
        if( monthCount < 12 ){ mPlot.xAxis->setAutoTickCount( monthCount ); }
        else if( monthCount < 36 ){ mPlot.xAxis->setAutoTickCount( monthCount/3 ); }
        else if( monthCount < 72 ){ mPlot.xAxis->setAutoTickCount( monthCount/6 ); }
        else{ mPlot.xAxis->setAutoTickCount( monthCount/12 ); }
    }

    // Setup account plotlines
    QVector<QVector<double>> accountSamples;
    QList<Account*> accountList = mFilter.getSelectedAccounts();
    // Bail if no accounts is selected
    if( accountList.isEmpty() ){ mPlot.replot(); return; }

    QList<QColor> accountColorList;
    if( mGraphMode == BAR_ACCOUNT_BALANCE )
    {
        // Clear previous account plotlines
        while( mPlot.graphCount() > 1 )
        {
            mPlot.removeGraph( NET_INCOME_GRAPH_IDX+1 );
        }
        // Add each account plotline
        const int colorRange = COLOR_RANGE;
        int step = qMin( MAX_COLOR_STEP, (colorRange / accountList.size()) );
        QColor baseColor = BASE_COLOR.toHsv();
        int h = baseColor.hue();
        int s = baseColor.saturation();
        int v = baseColor.value();
        for( int i = 0; i < accountList.size(); i++ )
        {
            mPlot.addGraph();
            QColor nextColor;
            int newH = (h + step*i)%colorRange;
            nextColor.setHsv( newH, s, v );
            QPen pen( nextColor );
            pen.setWidth( 2 );
            mPlot.graph(NET_INCOME_GRAPH_IDX+i)->setPen(pen);
            mPlot.graph(NET_INCOME_GRAPH_IDX+i)->setLineStyle(QCPGraph::lsLine);
            mPlot.graph(NET_INCOME_GRAPH_IDX+i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
            accountColorList.append( nextColor );
            accountSamples.push_back( QVector<double>() );
        }
    }

    // Setup histograms
    QVector<double> keySamples;
    QVector<double> positiveSamples;
    QVector<double> negativeSamples;
    QVector<double> differenceSamples;
    float maxValue = 0;
    float minValue = 0;
    BarDataType barData;
    for( int i = 0; i < TransactionManager::sMonthList.size(); i++ )
    {
        Month* month = TransactionManager::sMonthList[i];
        QDate date = month->getDate();
        if( mFilter.mStartDate <= date && mFilter.mEndDate >= date )
        {
            // Set values
            if( !barData.set )
            {
                barData.set = true;
                barData.startDate = ( keySamples.empty() ) ? rangeStartDate : date;
                barData.endDate = barData.startDate.addMonths( mMonthInterval ).addDays(-1);
            }
            barData.income += month->getIncome( mFilter );
            barData.expense += month->getExpense( mFilter );
            barData.transfers += month->getTransfers( mFilter );

            // Create plot points on month intervals
            if( date.month() % mMonthInterval == 0 || date.addMonths(1) >= mFilter.mEndDate )
            {
                float income = barData.income;
                float expense = barData.expense;
                if( mShowTransfers )
                {
                    if( barData.transfers > 0 ){ income += barData.transfers; }
                    else{ expense += barData.transfers; }
                }
                barData.netWorth = month->getNetWorth( mFilter );
                keySamples.append( QDateTime( barData.startDate.addDays(28*mMonthInterval/2) ).toTime_t() );
                switch( mGraphMode )
                {
                case BAR_NET_INCOME:
                    positiveSamples.append( income );
                    negativeSamples.append( expense );
                    differenceSamples.append( income + expense );
                    if( positiveSamples.last() > maxValue ){ maxValue = positiveSamples.last(); }
                    if( negativeSamples.last() < minValue ){ minValue = negativeSamples.last(); }
                    break;
                case BAR_NET_WORTH:
                    positiveSamples.append( (barData.netWorth > 0) ? barData.netWorth : 0 );
                    negativeSamples.append( (barData.netWorth < 0) ? barData.netWorth : 0 );
                    if( positiveSamples.last() > maxValue ){ maxValue = positiveSamples.last(); }
                    if( negativeSamples.last() < minValue ){ minValue = negativeSamples.last(); }
                    break;
                case BAR_ACCOUNT_BALANCE:
                    // Add each account plotline
                    for( int i = 0; i < accountList.size(); i++ )
                    {
                        bool accountExist = false;
                        double balance = month->getNetWorth( accountList[i], &accountExist );
                        accountSamples[i].append( balance );
                        if( balance > maxValue ){ maxValue = balance; }
                        if( balance < minValue ){ minValue = balance; }

                        if( accountExist )
                        {
                            AccountInfoType accountInfo;
                            accountInfo.name = accountList[i]->getName();
                            accountInfo.color = accountColorList[i];
                            accountInfo.balance = balance;
                            barData.accountList.append( accountInfo );
                        }
                    }
                    qSort( barData.accountList );
                    break;
                }
                mBarDataList.append( barData );
                barData = BarDataType();
            }
            mDataSet = true;
        }
    }

    // Don't show difference plot if more that 3 years
    mPlot.yAxis->setRange( minValue * 1.3, maxValue * 1.2 );
    switch( mGraphMode )
    {
    case BAR_NET_INCOME:
    case BAR_NET_WORTH:
        if( mShowNetIncome ){ mPlot.graph(NET_INCOME_GRAPH_IDX)->setData( keySamples, differenceSamples ); }
        mPositiveHistogram->setData( keySamples, positiveSamples );
        mNegativeHistogram->setData( keySamples, negativeSamples );
        break;
    case BAR_ACCOUNT_BALANCE:
        // Add each account plotline
        for( int i = 0; i < accountList.size(); i++ )
        {
            mPlot.graph(NET_INCOME_GRAPH_IDX+i)->setData( keySamples, accountSamples[i] );
        }
        break;
    default:
        break;
    }
    mPlot.replot();
} // BarGraph::setTransactionData()

