//******************************************************************************
//
//  HEADER NAME: ReportTableView.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>

#include "ReportTableView.h"
#include "TransactionListModel.h"
#include "TransactionManager.h"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ReportTableView::ReportTableView
    (
    QWidget* parent
    ):
    QTableView(parent)
  , mStartDate( 2000, 1, 1 )
  , mEndDate( 2000, 1, 1 )
  , mModel( NULL )
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setAlternatingRowColors(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setGridStyle(Qt::DashLine);
    setWordWrap(false);
    horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
    horizontalHeader()->setSortIndicatorShown( false );
    verticalHeader()->setVisible(false);
    
    mModel = new QStandardItemModel( 0, 0 );
    QStringList headers;
    headers.push_back( "Date" );
    headers.push_back( "Income" );
    headers.push_back( "Expense" );
    headers.push_back( "Net Income" );
    headers.push_back( "Net Worth" );
    mModel->setHorizontalHeaderLabels( headers );
    setModel( mModel );
        
    // Set transaction column widths
    const int columnWidth = 120;
    setColumnWidth( (int)HDR_DATE, columnWidth );
    setColumnWidth( (int)HDR_INCOME, columnWidth );
    setColumnWidth( (int)HDR_EXPENSE, columnWidth );
    setColumnWidth( (int)HDR_NET_INCOME, columnWidth );
    setColumnWidth( (int)HDR_NET_WORTH, columnWidth );

    show();
} // ReportTableView::ReportTableView

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
ReportTableView::~ReportTableView()
{
    delete mModel;
} // ReportTableView::~ReportTableView

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
void ReportTableView::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    mStartDate.setDate( aFilter.mStartDate.year(), aFilter.mStartDate.month(), 1 );
    mEndDate.setDate( aFilter.mEndDate.year(), aFilter.mEndDate.month(), 1 );
    mEndDate = mEndDate.addMonths(1);
    int rowCount = 0;
    mModel->setRowCount( rowCount );
    for( int i = 0; i < TransactionManager::mMonthList.size(); i++ )
    {
        // Date
        Month* month = TransactionManager::mMonthList[i];
        if( mStartDate <= month->getDate() && mEndDate > month->getDate() )
        {
            QStandardItem* item = new QStandardItem();
            item->setTextAlignment( Qt::AlignCenter );
            item->setText( month->getDate().toString("MMM yyyy") );
            mModel->setItem( rowCount, (int)HDR_DATE, item );
            float income = month->getIncome( aFilter );
            float expense = month->getExpense( aFilter );
            NumberStandardItem* numberItem = new NumberStandardItem();
            numberItem->setNumber( income );
            mModel->setItem( rowCount, (int)HDR_INCOME, numberItem );
            numberItem = new NumberStandardItem();
            numberItem->setNumber( expense );
            mModel->setItem( rowCount, (int)HDR_EXPENSE, numberItem );
            numberItem = new NumberStandardItem();
            numberItem->setNumber( income + expense );
            mModel->setItem( rowCount, (int)HDR_NET_INCOME, numberItem );
            numberItem = new NumberStandardItem();
            numberItem->setNumber( month->getNetWorth( aFilter ) );
            mModel->setItem( rowCount, (int)HDR_NET_WORTH, numberItem );
            rowCount++;
        }
    }
} // ReportTableView::setDateRange
