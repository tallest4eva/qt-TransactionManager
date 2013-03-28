//******************************************************************************
//
//  HEADER NAME: ReportPieChartModel.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>

#include "ReportPieChartModel.h"
#include "TransactionManager.h"
#include "Account.h"
#include "Month.h"

static const int COLOR_RANGE = 260;
static const int MAX_COLOR_STEP = 40;
static QColor BASE_COLOR = QColor(140, 80, 230);

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ReportPieChartModel::ReportPieChartModel( PieChartType aChartType ):
    QStandardItemModel( 0, 0 ),
    mChartType( aChartType ),
    mPieView( NULL ),
    mGroupCategories( false )
{
    setColumnCount( PieView::COLUMN_CNT );
} // ReportPieChartModel::ReportPieChartModel

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
ReportPieChartModel::~ReportPieChartModel()
{
} // ReportPieChartModel::~ReportPieChartModel

//----------------------------------------------------------------------------
// clear
//----------------------------------------------------------------------------
void ReportPieChartModel::clear()
{
    setRowCount( 0 );
    if( mPieView )
    {
        mPieView->update();
    }
} // ReportPieChartModel::clear

//----------------------------------------------------------------------------
// ReportPieChartModel
//----------------------------------------------------------------------------
void ReportPieChartModel::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    QColor baseColor = BASE_COLOR.toHsv();
    QColor secondaryLabelColor;
    QList<PieDataType> dataList;
    switch( mChartType )
    {
    case ASSET_BY_ACCOUNT:
    case DEBT_BY_ACCOUNT:
        {
            //baseColor = ( mChartType == ASSET_BY_ACCOUNT ) ? QColor(Qt::green).toHsv() : QColor(Qt::red).toHsv();
            secondaryLabelColor = ( mChartType == ASSET_BY_ACCOUNT ) ? QColor(Qt::green) : QColor(Qt::red);
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
            //baseColor = ( mChartType == INCOME_BY_CATEGORY ) ? QColor(Qt::darkGreen).toHsv() : QColor(Qt::darkRed).toHsv();
            secondaryLabelColor = ( mChartType == INCOME_BY_CATEGORY ) ? QColor(Qt::green) : QColor(Qt::red);
            Transaction::FilterType filter = aFilter;
            //filter.mStartDate.setDate( filter.mStartDate.year(), filter.mStartDate.month(), 1 );
            //filter.mEndDate = filter.mEndDate.addMonths(1).addDays(-1);
            QList<Transaction*> transactionList = Transaction::filterTransactions( TransactionManager::mTransactionList, filter );
            QVector<float> categoryList( (int)Category::CATEGORY_TYPE_CNT, 0 );
            for( int i = 0; i < transactionList.size(); i++ )
            {
                Transaction* transaction = transactionList[i];
                Transaction::TransactionType transType = transaction->getTransactionType();
                CategoryIdType category = transaction->getCategory();
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

    setRowCount( dataList.size() );
    if( dataList.size() > 0 )
    {
        qSort( dataList.begin(), dataList.end(), qGreater<PieDataType>() );
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
            setData( index(i,(int)PieView::COLUMN_LABEL), dataList[i].mName );
            setData( index(i,(int)PieView::COLUMN_LABEL), nextColor, Qt::DecorationRole );
            setData( index(i,(int)PieView::COLUMN_VALUE), dataList[i].mValue );
            setData( index(i,(int)PieView::COLUMN_SEC_LABEL), "$" + QString::number(dataList[i].mValue, 'f', 2 ) );
            setData( index(i,(int)PieView::COLUMN_SEC_LABEL), secondaryLabelColor, Qt::DecorationRole );
        }
    }
    if( mPieView )
    {
        mPieView->updateViewport();
        mPieView->update();
    }
} // ReportPieChartModel::setTransactionFilter

//----------------------------------------------------------------------------
// setupPieView
//----------------------------------------------------------------------------
void ReportPieChartModel::setupPieView
    (
    PieView* aPieView
    )
{
    mPieView = aPieView;
} // ReportPieChartModel::setupPieView

