//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: ReportTableView.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>

#include "ReportTableView.hpp"
#include "TransactionList.hpp"
#include "TransactionManager.hpp"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ReportTableView::ReportTableView
    (
    QWidget* parent
    ):
    QTableView(parent)
  , mModel( NULL )
  , mMonthInterval( 1 )
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setAlternatingRowColors(true);
    setGridStyle(Qt::DashLine);
    setWordWrap(false);
    horizontalHeader()->setSortIndicatorShown( true );
    verticalHeader()->setVisible(false);

    mModel = new QStandardItemModel( 0, 0 );
    QStringList headers;
    headers.push_back( "Date" );
    headers.push_back( "Income" );
    headers.push_back( "Expense" );
    headers.push_back( "Net Income" );
    headers.push_back( "Net Transfers" );
    headers.push_back( "Net Worth" );
    mModel->setHorizontalHeaderLabels( headers );
    setModel( mModel );

    // Set transaction column widths
    const int columnWidth = 120;
    setColumnWidth( (int)HDR_DATE, columnWidth );
    setColumnWidth( (int)HDR_INCOME, columnWidth );
    setColumnWidth( (int)HDR_EXPENSE, columnWidth );
    setColumnWidth( (int)HDR_NET_INCOME, columnWidth );
    setColumnWidth( (int)HDR_NET_TRANSFERS, columnWidth );
    setColumnWidth( (int)HDR_NET_WORTH, columnWidth );
    setSortingEnabled( true );

    connect( this, SIGNAL(pressed(const QModelIndex&)), this, SLOT(handleItemPressed(const QModelIndex&)) );
    connect( this, SIGNAL(clicked(const QModelIndex&)), this, SLOT(handleItemPressed(const QModelIndex&)) );
    connect( this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(handleItemDoubleClicked(const QModelIndex&)) );
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
    sortByColumn( (int)HDR_DATE, Qt::AscendingOrder );
} // ReportTableView::clear

//----------------------------------------------------------------------------
// Set Month Interval
//----------------------------------------------------------------------------
void ReportTableView::setMonthInterval( int aMonthInterval )
{
    mMonthInterval = aMonthInterval;
    setTransactionFilter( mFilter );
}

//----------------------------------------------------------------------------
// Set transaction filter
//----------------------------------------------------------------------------
void ReportTableView::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    mFilter = aFilter;
    QDate startDate( aFilter.mStartDate.year(), aFilter.mStartDate.month(), 1 );
    QDate endDate( aFilter.mEndDate.year(), aFilter.mEndDate.month(), 1 );
    endDate = endDate.addMonths(1);
    mModel->setRowCount( 0 );
    mRowIntervalList.clear();

    int rowCount = 0;
    float totalIncome = 0;
    float totalExpense = 0;
    float totalNetIncome = 0;
    float totalTransfers = 0;
    float intervalIncome = 0;
    float intervalExpense = 0;
    float intervalNetIncome = 0;
    float intervalTransfers = 0;
    QStandardItem* item = NULL;
    DateStandardItem* dateItem = NULL;
    NumberStandardItem* numberItem = NULL;
    bool isStartDateSet = false;
    Month::DateIntervalType rowDateInterval;
    for( int i = 0; i < TransactionManager::sMonthList.size(); i++ )
    {
        // Date
        Month* month = TransactionManager::sMonthList[i];
        if( startDate <= month->getDate() && endDate > month->getDate() )
        {
            float income = month->getIncome( aFilter );
            float expense = month->getExpense( aFilter );
            float transfers = month->getTransfers( aFilter );
            float netIncome = income + expense;
            intervalIncome += income;
            intervalExpense += expense;
            intervalNetIncome += netIncome;
            intervalTransfers += transfers;

            // Determine whether to create interval row
            if( !isStartDateSet )
            {
                rowDateInterval.startDate = month->getDate();
                isStartDateSet = true;
            }
            QDate nextMonth = month->getDate().addMonths(1);
            if( month->getDate().month() % mMonthInterval == 0 || nextMonth >= endDate )
            {
                dateItem = new DateStandardItem();
                QString dateString = "MMM yyyy";
                if( mMonthInterval > 1 )
                {
                    dateString.prepend( QDate::shortMonthName( rowDateInterval.startDate.month() ) + "-" );
                }
                dateItem->setDate( month->getDate(), dateString );
                mModel->setItem( rowCount, (int)HDR_DATE, dateItem );
                numberItem = new NumberStandardItem();
                numberItem->setNumber( intervalIncome );
                mModel->setItem( rowCount, (int)HDR_INCOME, numberItem );
                numberItem = new NumberStandardItem();
                numberItem->setNumber( intervalExpense );
                mModel->setItem( rowCount, (int)HDR_EXPENSE, numberItem );
                numberItem = new NumberStandardItem();
                numberItem->setNumber( intervalNetIncome );
                mModel->setItem( rowCount, (int)HDR_NET_INCOME, numberItem );
                numberItem = new NumberStandardItem();
                numberItem->setNumber( intervalTransfers );
                mModel->setItem( rowCount, (int)HDR_NET_TRANSFERS, numberItem );
                numberItem = new NumberStandardItem();
                numberItem->setNumber( month->getNetWorth( aFilter ) );
                mModel->setItem( rowCount, (int)HDR_NET_WORTH, numberItem );
                rowCount++;

                intervalIncome = 0;
                intervalExpense = 0;
                intervalNetIncome = 0;
                intervalTransfers = 0;
                rowDateInterval.endDate = month->getDate().addMonths(1).addDays(-1);
                mRowIntervalList.push_back( rowDateInterval );
                isStartDateSet = false;
            }

            // Add to totals
            totalIncome += income;
            totalExpense += expense;
            totalNetIncome += netIncome;
            totalTransfers += transfers;
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
    numberItem = new NumberStandardItem();
    numberItem->setNumber( totalTransfers );
    mModel->setItem( rowCount, (int)HDR_NET_TRANSFERS, numberItem );
} // ReportTableView::setDateRange

//----------------------------------------------------------------------------
// Handle Item Pressed
//----------------------------------------------------------------------------
void ReportTableView::handleItemPressed( const QModelIndex& aIndex )
{
    int columnIndex = aIndex.column();
    switch( columnIndex )
    {
    case HDR_DATE:
    case HDR_NET_WORTH:
        selectRow( aIndex.row() );
        break;
    default:
        setCurrentIndex( aIndex );
        break;
    }
} // ReportTableView::handleItemPressed

//----------------------------------------------------------------------------
// Handle Item Double Clicked
//----------------------------------------------------------------------------
void ReportTableView::handleItemDoubleClicked( const QModelIndex& aIndex )
{
    handleItemPressed( aIndex );
    int rowIndex = aIndex.row();
    int columnIndex = aIndex.column();
    if( rowIndex >= 0 && rowIndex < mRowIntervalList.size() )
    {
        Transaction::FilterType filter = mFilter;
        filter.selectDateRange( mRowIntervalList[ rowIndex ].startDate, mRowIntervalList[ rowIndex ].endDate );
        // Remove uneeded categories
        QVector<Category::TransactionType> categoryList;
        categoryList.append( Category::TRANSACTION_TYPE_BALANCE );
        switch( columnIndex )
        {
        case HDR_INCOME:
            filter.showToolBox = "categories";
            categoryList.append( Category::TRANSACTION_TYPE_EXPENSE );
            categoryList.append( Category::TRANSACTION_TYPE_TRANSFER );
            filter.clearAllCategories( categoryList );
            break;
        case HDR_EXPENSE:
            filter.showToolBox = "categories";
            categoryList.append( Category::TRANSACTION_TYPE_INCOME );
            categoryList.append( Category::TRANSACTION_TYPE_TRANSFER );
            filter.clearAllCategories( categoryList );
            break;
        case HDR_NET_INCOME:
            filter.showToolBox = "categories";
            categoryList.append( Category::TRANSACTION_TYPE_TRANSFER );
            filter.clearAllCategories( categoryList );
            break;
        case HDR_NET_TRANSFERS:
            filter.showToolBox = "categories";
            categoryList.append( Category::TRANSACTION_TYPE_EXPENSE );
            categoryList.append( Category::TRANSACTION_TYPE_INCOME );
            filter.clearAllCategories( categoryList );
            break;
        case HDR_DATE:
        case HDR_NET_WORTH:
            filter.showToolBox = "dates";
            break;
        }
        transactionFilterSelected( filter );
    }
} // ReportTableView::handleItemDoubleClicked
