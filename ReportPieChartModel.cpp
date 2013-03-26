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

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ReportPieChartModel::ReportPieChartModel( PieChartType aChartType ):
    QStandardItemModel( 0, 0 ),
    mChartType( aChartType ),
    mPieView( NULL )
{
    setColumnCount( COLUMN_CNT );
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
    QColor baseColor;
    QList<PieDataType> dataList;
    switch( mChartType )
    {
    case ASSET_BY_ACCOUNT:
    case DEBT_BY_ACCOUNT:
        {
            baseColor = ( mChartType == ASSET_BY_ACCOUNT ) ? QColor(Qt::darkGreen).toHsv() : QColor(Qt::darkRed).toHsv();
            baseColor = QColor(0x8A, 0x56, 0xE2);
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
            baseColor = ( mChartType == INCOME_BY_CATEGORY ) ? QColor(Qt::darkGreen).toHsv() : QColor(Qt::darkRed).toHsv();
            QList<Transaction*> transactionList = Transaction::filterTransactions( TransactionManager::mTransactionList, aFilter );
            QVector<float> categoryList( (int)Category::CATEGORY_TYPE_CNT, 0 );
            for( int i = 0; i < transactionList.size(); i++ )
            {
                Transaction* transaction = transactionList[i];
                if( transaction->isIncomeOrExpense() )
                {
                    //categoryList[ transaction->getCategory() ] += transaction
                }
            }
        }
        break;
    }

    if( dataList.size() > 0 )
    {
        qSort( dataList.begin(), dataList.end(), qGreater<PieDataType>() );
        setRowCount( dataList.size() );
        const int colorRange = 240;
        int step = (colorRange / dataList.size());
        int h = baseColor.hue();
        int s = baseColor.saturation();
        int v = baseColor.value();
        for (int i = 0; i < dataList.size(); ++i)
        {
            QColor nextColor;
            int newH = (h + step*i)%colorRange;
            nextColor.setHsv( newH, s, v );
            setData( index(i,(int)COLUMN_NAME), dataList[i].mName );
            setData( index(i,(int)COLUMN_NAME), nextColor, Qt::DecorationRole );
            setData( index(i,(int)COLUMN_VALUE), dataList[i].mValue );
        }
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
    if( mPieView )
    {
    }
} // ReportPieChartModel::setupPieView

