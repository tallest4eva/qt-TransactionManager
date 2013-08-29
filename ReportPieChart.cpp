//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: ReportPieChart.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>
#include <QMouseEvent>

#include "ReportPieChart.h"
#include "TransactionManager.h"
#include "Account.h"
#include "Month.h"

static const int COLOR_RANGE = 260;
static const int MAX_COLOR_STEP = 40;
static QColor BASE_COLOR = QColor(140, 80, 230);

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ReportPieChart::ReportPieChart():
    mChartType( PIE_CHART_CNT ),
    mMousePosition( 0, 0 ),
    mGroupCategories( false )
{
    // Set up display label
    mDisplayLabel.setParent( this );
    mDisplayLabel.hide();
    mDisplayLabel.setGeometry( 0, 0, 185, 90 );
    mDisplayLabel.setFrameShadow( QFrame::Raised );
    mDisplayLabel.setFrameShape( QFrame::StyledPanel );
    mDisplayLabel.setPalette( QPalette(Qt::black,Qt::white) );
    mDisplayLabel.setAutoFillBackground( true );
    connect( &mDisplayLabel, SIGNAL(clicked()), this, SLOT(handleDisplayClicked()) );
    QFont font;
    font.setPointSize( 10 );
    mDisplayLabel.setFont( font );

    mModel = new QStandardItemModel( 0, 0 );
    mModel->setColumnCount( PieView::COLUMN_CNT );
    setModel( mModel );

    connect( this, SIGNAL(clicked(const QModelIndex&)), this, SLOT(handleItemClicked(const QModelIndex&)) );
} // ReportPieChart::ReportPieChart

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
ReportPieChart::~ReportPieChart()
{
    delete mModel;
} // ReportPieChart::~ReportPieChart

//----------------------------------------------------------------------------
// clear
//----------------------------------------------------------------------------
void ReportPieChart::clear()
{
    hideDisplayLabel();
    mModel->setRowCount( 0 );
    updateViewport();
} // ReportPieChart::clear

//----------------------------------------------------------------------------
// setTransactionFilter
//----------------------------------------------------------------------------
void ReportPieChart::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    hideDisplayLabel();
    mFilter = aFilter;
    QColor baseColor = BASE_COLOR.toHsv();
    QList<PieDataType> dataList;
    bool positiveValue = true;
    switch( mChartType )
    {
    case ASSET_BY_ACCOUNT:
    case DEBT_BY_ACCOUNT:
        {
            positiveValue = ( mChartType == ASSET_BY_ACCOUNT );
            Month* month = Month::getMonth( aFilter.mEndDate );
            if( month )
            {
                for( int i = 0; i < aFilter.mAccountList.size(); i++ )
                {
                    Account* account = aFilter.mAccountList[i];
                    bool accountExist = false;
                    float netWorth = month->getNetWorth( account, &accountExist );
                    if( accountExist )
                    {
                        bool allow = false;
                        if( netWorth >= 0 )
                        {
                            allow = (mChartType == ASSET_BY_ACCOUNT);
                        }
                        else
                        {
                            allow = (mChartType == DEBT_BY_ACCOUNT);
                            netWorth = -netWorth;
                        }
                        if( allow )
                        {
                            PieDataType data;
                            data.mName = account->getName();
                            data.mValue = netWorth;
                            dataList.push_back( data );
                        }
                    }
                }
            }
        }
        break;
    case INCOME_BY_CATEGORY:
    case EXPENSE_BY_CATEGORY:
        {
            positiveValue = ( mChartType == INCOME_BY_CATEGORY );
            Transaction::FilterType filter = aFilter;
            QList<Transaction*> transactionList = Transaction::filterTransactions( TransactionManager::sTransactionList, filter );
            QVector<float> categoryList( (int)Category::getCategoryCount(), 0 );
            for( int i = 0; i < transactionList.size(); i++ )
            {
                Transaction* transaction = transactionList[i];
                Transaction::TransactionType transType = transaction->getTransactionType();
                Category::CategoryIdType category = transaction->getCategory();
                if( mGroupCategories )
                {
                    category = Category::getParentCategoryId( category );
                }
                if( transType == Transaction::INCOME && mChartType == INCOME_BY_CATEGORY )
                {
                    categoryList[(int)category] += transaction->getAmount();
                }
                else if( transType == Transaction::EXPENSE && mChartType == EXPENSE_BY_CATEGORY )
                {
                    categoryList[(int)category] -= transaction->getAmount();
                }
            }
            for( int i = 0; i < categoryList.size(); i++ )
            {
                if( categoryList[i] > 0 )
                {
                    PieDataType data;
                    data.mName = Category::getCategoryText( (Category::CategoryIdType)i, true );
                    data.mValue = categoryList[i];
                    dataList.push_back( data );
                }
            }
        }
        break;
    }

    mModel->setRowCount( dataList.size() );
    if( dataList.size() > 0 )
    {
        qSort( dataList.begin(), dataList.end(), qGreater<PieDataType>() );
        QColor secondaryLabelColor = ( positiveValue ) ? QColor(Qt::green) : QColor(Qt::red);
        const int colorRange = COLOR_RANGE;
        int step = qMin( MAX_COLOR_STEP, (colorRange / dataList.size()) );
        int h = baseColor.hue();
        int s = baseColor.saturation();
        int v = baseColor.value();
        for (int i = 0; i < dataList.size(); ++i)
        {
            QColor nextColor;
            int newH = (h + step*i)%colorRange;
            nextColor.setHsv( newH, s, v );
            QString valueStr = ( positiveValue ) ? "$" : "-$";
            valueStr += QString::number(dataList[i].mValue, 'f', 2 );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_LABEL), dataList[i].mName );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_LABEL), nextColor, Qt::DecorationRole );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_VALUE), dataList[i].mValue );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_SEC_LABEL), valueStr );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_SEC_LABEL), secondaryLabelColor, Qt::DecorationRole );
        }
    }
    updateViewport();
} // ReportPieChart::setTransactionFilter

//----------------------------------------------------------------------------
// mouseReleaseEvent
//----------------------------------------------------------------------------
void ReportPieChart::mouseReleaseEvent( QMouseEvent* aEvent )
{
    mMousePosition = aEvent->pos();
    if( !mDisplayLabel.isHidden() )
    {
        // Hide display label and clear index
        hideDisplayLabel();
    }
    else
    {
        PieView::mouseReleaseEvent( aEvent );
    }
} // ReportPieChart::mouseReleaseEvent

//----------------------------------------------------------------------------
// handleItemClicked
//----------------------------------------------------------------------------
void ReportPieChart::handleItemClicked( const QModelIndex& aIndex )
{
    // Place display label
    int labelRectW = mDisplayLabel.width();
    int labelRectH = mDisplayLabel.height();
    int labelRectX = mMousePosition.x() - labelRectW/2;
    labelRectX = ( labelRectX < 0 ) ? 0 : labelRectX;
    labelRectX = ( labelRectX + labelRectW > width() ) ? width() - labelRectW : labelRectX;
    int labelRectY = mMousePosition.y() - labelRectH;
    labelRectY = ( labelRectY < 0 ) ? 0 : labelRectY;
    labelRectY = ( labelRectY + labelRectH > height() ) ? height() - labelRectH : labelRectY;
    mDisplayLabel.move( labelRectX, labelRectY );

    int row = aIndex.row();
    QModelIndex valueIndex = mModel->index(row, (int)COLUMN_VALUE, rootIndex());
    double value = mModel->data(valueIndex).toDouble();
    double percentage = ( mTotalValue > 0 ) ? value*100/mTotalValue : 0;
    QModelIndex labelIndex = model()->index(row, (int)COLUMN_LABEL, rootIndex());
    QString label = mModel->data(labelIndex).toString();
    QStringList list = label.split( " > ", QString::SkipEmptyParts );
    if( list.size() == 2 ){ label = list[1]; }
    mDisplayLabel.setString( label );

    QString str;
    switch( mChartType )
    {
    case ASSET_BY_ACCOUNT:
    case INCOME_BY_CATEGORY:
        str = ( mChartType == ASSET_BY_ACCOUNT ) ? "Account: " : "Category: ";
        str += label + "<br>";
        str += "Amount: <font color=\"green\">$" + QString::number(value, 'f', 2) + "</font><br>";
        str += "Total: <font color=\"green\">$" + QString::number(mTotalValue, 'f', 2) + "</font><br>";
        break;
    case DEBT_BY_ACCOUNT:
    case EXPENSE_BY_CATEGORY:
        str = ( mChartType == DEBT_BY_ACCOUNT ) ? "Account: " : "Category: ";
        str += label + "<br>";
        str += "Amount: <font color=\"red\">-$" + QString::number(value, 'f', 2) + "</font><br>";
        str += "Total: <font color=\"red\">-$" + QString::number(mTotalValue, 'f', 2) + "</font><br>";
        break;
    }
    str += "Percentage(%): " + QString::number( percentage, 'f', 2 ) + "%";
    str += "<center><font size=\"-2\" color=\"blue\">Dbl click to See Transactions</font></center>";
    mDisplayLabel.setText( str );
    mDisplayLabel.show();
} // ReportPieChart::handleItemClicked

//----------------------------------------------------------------------------
// hideDisplayLabel
//----------------------------------------------------------------------------
void ReportPieChart::hideDisplayLabel()
{
    mDisplayLabel.hide();
    setCurrentIndex( mModel->index(-1,-1,rootIndex()) );
} // ReportPieChart::hideDisplayLabel

//----------------------------------------------------------------------------
// handle Display Clicked
//----------------------------------------------------------------------------
void ReportPieChart::handleDisplayClicked()
{
    QString label = mDisplayLabel.getString();
    Transaction::FilterType filter = mFilter;
    switch( mChartType )
    {
    case ASSET_BY_ACCOUNT:
    case DEBT_BY_ACCOUNT:
        {
            filter.mAllAccounts = false;
            filter.mAccountList.clear();
            Account* account = Account::getAccount( label );
            if( account )
            {
                filter.mAccountList.push_back( account );
            }
            filter.mShowAccounts = true;
        }
        break;
    case INCOME_BY_CATEGORY:
    case EXPENSE_BY_CATEGORY:
        {
            filter.mAllCategories = false;
            filter.mCategoryList.fill( false );
            Category::CategoryIdType category = Category::getCategoryId( label );
            filter.mCategoryList[ (int)category ] = true;
            if( mGroupCategories )
            {
                for( int i = 0; i < Category::getCategoryCount(); i++ )
                {
                    if( category == Category::getParentCategoryId( (Category::CategoryIdType)i ) )
                    {
                        filter.mCategoryList[i] = true;
                    }
                }
            }
            filter.mShowCategories = true;
        }
        break;
    }
    transactionFilterSelected( filter );
} // ReportPieChart::handleDisplayClicked
