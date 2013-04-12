//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: ReportTableView.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>

#include "Month.h"
#include "ReportTableView.h"
#include "TransactionList.h"
#include "TransactionManager.h"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ReportTableView::ReportTableView
    (
    QWidget* parent
    ):
    QTableView(parent)
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

    connect( this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(handleItemDoubleClicked(const QModelIndex&)) );

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
// clear
//----------------------------------------------------------------------------
void ReportTableView::clear()
{
    mFilter = Transaction::FilterType();
    mModel->setRowCount( 0 );
} // ReportTableView::clear

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
void ReportTableView::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    mFilter = aFilter;
    QDate startDate( aFilter.mStartDate.year(), aFilter.mStartDate.month(), 1 );
    QDate endDate( aFilter.mEndDate.year(), aFilter.mEndDate.month(), 1 );
    endDate = endDate.addMonths(1);
    mModel->setRowCount( 0 );
    mMonthList.clear();

    int rowCount = 0;
    float totalIncome = 0;
    float totalExpense = 0;
    float totalNetIncome = 0;
    QStandardItem* item = NULL;
    NumberStandardItem* numberItem = NULL;
    for( int i = 0; i < TransactionManager::sMonthList.size(); i++ )
    {
        // Date
        Month* month = TransactionManager::sMonthList[i];
        if( startDate <= month->getDate() && endDate > month->getDate() )
        {
            item = new QStandardItem();
            item->setTextAlignment( Qt::AlignCenter );
            item->setText( month->getDate().toString("MMM yyyy") );
            mModel->setItem( rowCount, (int)HDR_DATE, item );
            float income = month->getIncome( aFilter );
            float expense = month->getExpense( aFilter );
            float netIncome = income + expense;
            numberItem = new NumberStandardItem();
            numberItem->setNumber( income );
            mModel->setItem( rowCount, (int)HDR_INCOME, numberItem );
            numberItem = new NumberStandardItem();
            numberItem->setNumber( expense );
            mModel->setItem( rowCount, (int)HDR_EXPENSE, numberItem );
            numberItem = new NumberStandardItem();
            numberItem->setNumber( netIncome );
            mModel->setItem( rowCount, (int)HDR_NET_INCOME, numberItem );
            numberItem = new NumberStandardItem();
            numberItem->setNumber( month->getNetWorth( aFilter ) );
            mModel->setItem( rowCount, (int)HDR_NET_WORTH, numberItem );
            rowCount++;
            mMonthList.push_back( month );

            // Add to totals
            totalIncome += income;
            totalExpense += expense;
            totalNetIncome += netIncome;
        }
    }

    // Add Totals row
    item = new QStandardItem();
    item->setTextAlignment( Qt::AlignCenter );
    item->setText( "Totals" );
    mModel->setItem( rowCount, (int)HDR_DATE, item );
    numberItem = new NumberStandardItem();
    numberItem->setNumber( totalIncome );
    mModel->setItem( rowCount, (int)HDR_INCOME, numberItem );
    numberItem = new NumberStandardItem();
    numberItem->setNumber( totalExpense );
    mModel->setItem( rowCount, (int)HDR_EXPENSE, numberItem );
    numberItem = new NumberStandardItem();
    numberItem->setNumber( totalNetIncome );
    mModel->setItem( rowCount, (int)HDR_NET_INCOME, numberItem );
} // ReportTableView::setDateRange

//----------------------------------------------------------------------------
// handleItemDoubleClicked
//----------------------------------------------------------------------------
void ReportTableView::handleItemDoubleClicked( const QModelIndex& aIndex )
{
    if( aIndex.row() >= 0 && aIndex.row() < mMonthList.size() )
    {
        Month* month = mMonthList[ aIndex.row() ];
        Transaction::FilterType filter = mFilter;
        filter.mStartDate = month->getDate();
        filter.mEndDate = month->getDate().addMonths(1).addDays(-1);
        filter.mAllDates = false;
        filter.mShowDates = true;
        transactionFilterSelected( filter );
    }
} // ReportTableView::handleItemDoubleClicked
