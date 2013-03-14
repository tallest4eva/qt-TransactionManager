//******************************************************************************
//
//  HEADER NAME: ReportPieChartModel.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>

#include "ReportPieChartModel.h"
#include "Account.h"

// Static variables
const char* ReportPieChartModel::cHeaderList[] =
{
    "Date",
    "Account",
    "Description",
    "Amount",
    "Balance",
    "Category",
    //"Labels"
};

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ReportPieChartModel::ReportPieChartModel( PieChartType aChartType ):
    QStandardItemModel( 0, 0 ),
    mChartType( aChartType ),
    mPieView( NULL )
{
} // ReportPieChartModel::ReportPieChartModel

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
ReportPieChartModel::~ReportPieChartModel()
{
} // ReportPieChartModel::~ReportPieChartModel

//----------------------------------------------------------------------------
// ReportPieChartModel
//----------------------------------------------------------------------------
void ReportPieChartModel::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    setData( index(0,0), "Value 1" );
    setData( index(0,0), Qt::red, Qt::DecorationRole );
    setData( index(0,1), 10 );
    setData( index(1,0), "Value 2" );
    setData( index(1,0), Qt::blue, Qt::DecorationRole );
    setData( index(1,1), 30 );
    setData( index(2,0), "Value 3" );
    setData( index(2,0), Qt::green, Qt::DecorationRole );
    setData( index(2,1), 40 );

    mTransactionList = Transaction::filterTransactions( TransactionManager::mTransactionList, aFilter );
    setRowCount( mTransactionList.size() );
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        QStandardItem* item = new QStandardItem();
        item->setTextAlignment( Qt::AlignCenter );
        item->setText( mTransactionList[i]->getTransactionDate().toString("yyyy-MM-dd") );
        setItem( i, (int)HDR_DATE, item );
        setItem( i, (int)HDR_NAME, new QStandardItem( ( mTransactionList[i]->getAccount() ) ? mTransactionList[i]->getAccount()->getName() : "None" ) );
        setItem( i, (int)HDR_DESCRIPTION, new QStandardItem( mTransactionList[i]->getDescription() ) );
        NumberStandardItem* numberItem = new NumberStandardItem();
        numberItem->setNumber( mTransactionList[i]->getAmount() );
        setItem( i, (int)HDR_AMOUNT, numberItem );
        numberItem = new NumberStandardItem();
        numberItem->setNumber( mTransactionList[i]->getCurrentBalance() );
        setItem( i, (int)HDR_BALANCE, numberItem );
        setItem( i, (int)HDR_CATEGORY, new QStandardItem( Category::getCategoryText( mTransactionList[i]->getCategory() ) ) );
    }
} // ReportPieChartModel::setTransactionFilter

//----------------------------------------------------------------------------
// setupPieView
//----------------------------------------------------------------------------
void ReportPieChartModel::setupPieView
    (
    QTableView* aTableView
    )
{
    mPieView = aTableView;
    if( mPieView )
    {
        // Set transaction column widths
        const int columnWidth = 95;
        mPieView->setColumnWidth( (int)HDR_DATE, columnWidth );
        mPieView->setColumnWidth( (int)HDR_NAME, columnWidth*2 );
        mPieView->setColumnWidth( (int)HDR_DESCRIPTION, columnWidth*3 );
        mPieView->setColumnWidth( (int)HDR_AMOUNT, columnWidth );
        mPieView->setColumnWidth( (int)HDR_BALANCE, columnWidth );
        mPieView->setColumnWidth( (int)HDR_CATEGORY, columnWidth*2 );
        mPieView->horizontalHeader()->setStretchLastSection( true );
        mPieView->setSortingEnabled( true );
        mPieView->sortByColumn ( (int)HDR_NAME, Qt::AscendingOrder );
    }
} // ReportPieChartModel::setupPieView

