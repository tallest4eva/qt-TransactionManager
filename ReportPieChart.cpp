//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: ReportPieChart.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>
#include <QMouseEvent>

#include "ReportPieChart.hpp"
#include "TransactionManager.hpp"
#include "Account.hpp"
#include "Month.hpp"

static const int COLOR_RANGE = 260;
static const int MAX_COLOR_STEP = 40;
static QColor BASE_COLOR = QColor(140, 80, 230);

//----------------------------------------------------------------------------
// Data sort functions
//----------------------------------------------------------------------------
bool pieDataSortByNameAscending( const ReportPieChart::PieDataType& arg1, const ReportPieChart::PieDataType& arg2 )
{
     return arg1.mName < arg2.mName;
}
bool pieDataSortByBalanceDescending( const ReportPieChart::PieDataType& arg1, const ReportPieChart::PieDataType& arg2 )
{
     return qAbs(arg1.mValue) > qAbs(arg2.mValue);
}

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ReportPieChart::ReportPieChart()
    : mMousePosition( 0, 0 )
    , mChartType( PIE_CHART_CNT )
    , mGroupCategories( false )
    , mSortType( SORT_BY_BALANCE_DESCENDING )
    , mShowTransfers( false )
{
    // Set up display label
    mDisplayLabel.setParent( this );
    mDisplayLabel.hide();
    mDisplayLabel.setGeometry( 0, 0, 200, 90 );
    connect( &mDisplayLabel, SIGNAL(clicked()), this, SLOT(handleDisplayClicked()) );

    mModel = new QStandardItemModel( 0, 0, this );
    mModel->setColumnCount( PieView::COLUMN_CNT );
    setModel( mModel );

    connect( this, SIGNAL(clicked(const QModelIndex&)), this, SLOT(handleItemClicked(const QModelIndex&)) );
} // ReportPieChart::ReportPieChart

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
ReportPieChart::~ReportPieChart()
{
} // ReportPieChart::~ReportPieChart

//----------------------------------------------------------------------------
// clear
//----------------------------------------------------------------------------
void ReportPieChart::clear()
{
    hideDisplayLabel();
    mModel->setRowCount( 0 );
    mDataList.clear();
    updateViewport();
} // ReportPieChart::clear

//----------------------------------------------------------------------------
// Set Transaction Filter
//----------------------------------------------------------------------------
void ReportPieChart::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    hideDisplayLabel();
    mFilter = aFilter;
    mDataList.clear();
    switch( mChartType )
    {
    case ASSET_BY_ACCOUNT:
    case DEBT_BY_ACCOUNT:
        {
            Month* month = Month::getMonth( aFilter.mEndDate );
            if( month )
            {
                for( int i = 0; i < aFilter.mAccountList.size() && i < Account::sAccountList.size(); i++ )
                {
                    if( aFilter.mAccountList[i] )
                    {
                        Account* account = Account::sAccountList[i];
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
                                mDataList.append( data );
                            }
                        }
                    }
                }
            }
        }
        break;
    case INCOME_BY_CATEGORY:
    case EXPENSE_BY_CATEGORY:
        {
            QList<Transaction*> transactionList = Transaction::filterTransactions( TransactionManager::sTransactionList, aFilter );
            int categoryCnt = ( mGroupCategories ) ? (int)Category::PARENT_CATEGORY_TYPE_CNT : (int)Category::getCategoryCount();
            QVector<float> categoryList( categoryCnt, 0 );
            for( int i = 0; i < transactionList.size(); i++ )
            {
                Transaction* transaction = transactionList[i];
                Category::TransactionType transType = transaction->getTransactionType();
                int categoryIdx = ( mGroupCategories ) ? transaction->getParentCategory() : transaction->getCategory();
                if( ( mChartType == INCOME_BY_CATEGORY && transType == Category::TRANSACTION_TYPE_INCOME ) ||
                    ( mChartType == EXPENSE_BY_CATEGORY && transType == Category::TRANSACTION_TYPE_EXPENSE ) ||
                    ( mShowTransfers && transType == Category::TRANSACTION_TYPE_TRANSFER ) )
                {
                    categoryList[categoryIdx] += transaction->getAmount();
                }
            }
            for( int i = 0; i < categoryList.size(); i++ )
            {
                bool addItem = ( (mChartType == INCOME_BY_CATEGORY && categoryList[i] > 0) ||
                                 (mChartType == EXPENSE_BY_CATEGORY && categoryList[i] < 0) );
                if( addItem )
                {
                    PieDataType data;
                    data.mName = ( mGroupCategories ) ? Category::getParentCategoryText( (Category::ParentCategoryType)i ) : Category::getCategoryText( (Category::CategoryIdxType)i, true );
                    data.mValue = categoryList[i];
                    mDataList.append( data );
                }
            }
        }
        break;
    default:
        break;
    }
    updateChart();
} // ReportPieChart::setTransactionFilter

//----------------------------------------------------------------------------
// Update Chart
//----------------------------------------------------------------------------
void ReportPieChart::updateChart()
{
    mModel->setRowCount( mDataList.size() );
    if( mDataList.size() > 0 )
    {
        // Sort data items
        switch( mSortType )
        {
        case SORT_BY_BALANCE_DESCENDING:
            qSort( mDataList.begin(), mDataList.end(), pieDataSortByBalanceDescending );
            break;
        case SORT_BY_NAME_ASCENDING:
            qSort( mDataList.begin(), mDataList.end(), pieDataSortByNameAscending );
            break;
        }

        const int colorRange = COLOR_RANGE;
        int step = qMin( MAX_COLOR_STEP, (colorRange / mDataList.size()) );
        QColor baseColor = BASE_COLOR.toHsv();
        int h = baseColor.hue();
        int s = baseColor.saturation();
        int v = baseColor.value();
        for (int i = 0; i < mDataList.size(); ++i)
        {
            QColor secondaryLabelColor = ( mDataList[i].mValue > 0 ) ? QColor(Qt::darkGreen) : QColor(Qt::red);
            QColor nextColor;
            int newH = (h + step*i)%colorRange;
            nextColor.setHsv( newH, s, v );
            QString valueStr = Transaction::getAmountText( mDataList[i].mValue );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_LABEL), mDataList[i].mName );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_LABEL), nextColor, Qt::DecorationRole );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_VALUE), qAbs(mDataList[i].mValue) );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_SEC_LABEL), valueStr );
            mModel->setData( mModel->index(i,(int)PieView::COLUMN_SEC_LABEL), secondaryLabelColor, Qt::DecorationRole );
        }
    }
    updateViewport();
} // ReportPieChart::updateChart

//----------------------------------------------------------------------------
// Sort Chart
//----------------------------------------------------------------------------
void ReportPieChart::sortChart( SortType aSortType )
{
    mSortType = aSortType;
    updateChart();
} // ReportPieChart::sortChart

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
        str += "Amount: <font color=\"green\">" + Transaction::getAmountText(value) + "</font><br>";
        str += "Total: <font color=\"green\">" + Transaction::getAmountText(mTotalValue) + "</font><br>";
        break;
    case DEBT_BY_ACCOUNT:
    case EXPENSE_BY_CATEGORY:
        str = ( mChartType == DEBT_BY_ACCOUNT ) ? "Account: " : "Category: ";
        str += label + "<br>";
        str += "Amount: <font color=\"red\">" + Transaction::getAmountText(-value) + "</font><br>";
        str += "Total: <font color=\"red\">" + Transaction::getAmountText(-mTotalValue) + "</font><br>";
        break;
    default:
        break;
    }
    str += "Percentage(%): " + QString::number( percentage, 'f', 2 ) + "%";
    str += "<center><font size=\"-2\" color=\"blue\">Double-click to See Transactions</font></center>";
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
            filter.showToolBox = "account";
            filter.mAccountsAll = false;
            filter.selectAllAccounts( false );
            Account* account = Account::getAccount( label );
            if( account )
            {
                filter.mAccountList[ Account::getAccountIndex(account) ] = true;
            }
        }
        break;
    case INCOME_BY_CATEGORY:
    case EXPENSE_BY_CATEGORY:
        {
            filter.showToolBox = "categories";
            filter.mCategoriesAll = false;
            filter.mCategoryList.fill( false );
            Category::CategoryIdxType category = Category::getCategoryIndex( label );
            filter.mCategoryList[ (int)category ] = true;
            if( mGroupCategories )
            {
                Category::ParentCategoryType parentCategory = Category::getParentCategoryId( category );
                for( int i = 0; i < Category::getCategoryCount(); i++ )
                {
                    if( parentCategory == Category::getParentCategoryId( (Category::CategoryIdxType)i ) )
                    {
                        filter.mCategoryList[i] = true;
                    }
                }
            }
        }
        break;
    default:
        break;
    }
    transactionFilterSelected( filter );
} // ReportPieChart::handleDisplayClicked

//----------------------------------------------------------------------------
// Set Show Transfers
//----------------------------------------------------------------------------
void ReportPieChart::setShowTransfers( bool aShowTransfers, bool aUpdate )
{
    mShowTransfers = aShowTransfers;
    if( aUpdate )
    {
        switch( mChartType )
        {
        case INCOME_BY_CATEGORY:
        case EXPENSE_BY_CATEGORY:
            setTransactionFilter( mFilter );
            break;
        case ASSET_BY_ACCOUNT:
        case DEBT_BY_ACCOUNT:
        default:
            // Do nothing
            break;
        }
    }
}
