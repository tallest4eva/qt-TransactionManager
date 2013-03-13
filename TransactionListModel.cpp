//******************************************************************************
//
//  HEADER NAME: TransactionListModel.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>

#include "TransactionListModel.h"
#include "Account.h"

// Static variables
const char* TransactionListModel::cHeaderList[] =
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
// Operator <
//----------------------------------------------------------------------------
bool NumberStandardItem::operator< ( const QStandardItem& other ) const
{
    return mNumber < other.text().remove('$').toFloat();
} // NumberStandardItem::operator<

//----------------------------------------------------------------------------
// setNumber
//----------------------------------------------------------------------------
void NumberStandardItem::setNumber( float aNumber )
{
    mNumber = aNumber;
    if( mNumber != 0 )
    {
        setForeground( ( mNumber > 0 ) ? Qt::darkGreen : Qt::red );
    }
    setText( "$" + QString::number(mNumber,'f',2) );
    setTextAlignment( Qt::AlignRight );
} // NumberStandardItem::setNumber

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
TransactionListModel::TransactionListModel():
    QStandardItemModel( 0, 0 ),
    mTableView( NULL )
{
    QStringList headers;
    for( int i = 0; i < HDR_CNT; i++ )
    {
        headers.push_back( cHeaderList[i] );
    }
    setHorizontalHeaderLabels( headers );
} // TransactionListModel::TransactionListModel

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
TransactionListModel::~TransactionListModel()
{
} // TransactionListModel::~TransactionListModel

//----------------------------------------------------------------------------
// setTransactionList
//----------------------------------------------------------------------------
void TransactionListModel::setTransactionList
    (
    QList<Transaction*>& aTransactionList
    )
{
    mTransactionList = aTransactionList;
    setRowCount( mTransactionList.size() );
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        // Date
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
} // TransactionListModel::setTransactionList

//----------------------------------------------------------------------------
// setTransactionList
//----------------------------------------------------------------------------
void TransactionListModel::setupTableView
    (
    QTableView* aTableView
    )
{
    mTableView = aTableView;
    if( mTableView )
    {
        // Set transaction column widths
        const int columnWidth = 95;
        mTableView->setColumnWidth( (int)HDR_DATE, columnWidth );
        mTableView->setColumnWidth( (int)HDR_NAME, columnWidth*2 );
        mTableView->setColumnWidth( (int)HDR_DESCRIPTION, columnWidth*3 );
        mTableView->setColumnWidth( (int)HDR_AMOUNT, columnWidth );
        mTableView->setColumnWidth( (int)HDR_BALANCE, columnWidth );
        mTableView->setColumnWidth( (int)HDR_CATEGORY, columnWidth*2 );
        mTableView->horizontalHeader()->setStretchLastSection( true );
        mTableView->setSortingEnabled( true );
        mTableView->sortByColumn ( (int)HDR_NAME, Qt::AscendingOrder );
    }
} // TransactionListModel::setTransactionList

//----------------------------------------------------------------------------
// resort
//----------------------------------------------------------------------------
void TransactionListModel::resort()
{
    if( mTableView )
    {
        // Set transaction column widths
        QHeaderView* header = mTableView->horizontalHeader();
        if( header->isSortIndicatorShown() )
        {
            Qt::SortOrder order = header->sortIndicatorOrder();
            int column = header->sortIndicatorSection();
            mTableView->sortByColumn( column, order );
        }
    }
} // TransactionListModel::resort

