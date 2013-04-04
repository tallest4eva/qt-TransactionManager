//******************************************************************************
//
//  HEADER NAME: TransactionList.cpp
//******************************************************************************

#include <QGridLayout>
#include <QHeaderView>

#include "TransactionList.h"
#include "TransactionManager.h"
#include "Account.h"

// Static variables
const char* TransactionList::cHeaderList[] =
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
    setTextAlignment( Qt::AlignRight | Qt::AlignVCenter );
} // NumberStandardItem::setNumber

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
TransactionList::TransactionList():
    mModel( NULL )
{
    QFont font1;
    font1.setPointSize(10);
    setFont(font1);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setAlternatingRowColors(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setGridStyle(Qt::DashLine);
    setWordWrap(false);
    horizontalHeader()->setSortIndicatorShown( true );
    verticalHeader()->setVisible(false);

    mModel = new QStandardItemModel( 0, 0 );
    setModel( mModel );
    QStringList headers;
    for( int i = 0; i < HDR_CNT; i++ )
    {
        headers.push_back( cHeaderList[i] );
    }
    mModel->setHorizontalHeaderLabels( headers );

    // Set transaction column widths
    const int columnWidth = 90;
    setColumnWidth( (int)HDR_DATE, columnWidth );
    setColumnWidth( (int)HDR_NAME, columnWidth*2 );
    setColumnWidth( (int)HDR_DESCRIPTION, columnWidth*3 );
    setColumnWidth( (int)HDR_AMOUNT, columnWidth );
    setColumnWidth( (int)HDR_BALANCE, columnWidth );
    setColumnWidth( (int)HDR_CATEGORY, columnWidth*2 );
    setSortingEnabled( true );
    //horizontalHeader()->setStretchLastSection( true );
} // TransactionList::TransactionList

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
TransactionList::~TransactionList()
{
    delete mModel;
} // TransactionList::~TransactionList

//----------------------------------------------------------------------------
// setTransactionFilter
//----------------------------------------------------------------------------
void TransactionList::setTransactionFilter( const Transaction::FilterType& aFilter )
{
    mTransactionList = Transaction::filterTransactions( TransactionManager::mTransactionList, aFilter );
    mModel->setRowCount( mTransactionList.size() );
    for( int i = 0; i < mTransactionList.size(); i++ )
    {
        QStandardItem* item = new QStandardItem();
        item->setTextAlignment( Qt::AlignCenter );
        item->setText( mTransactionList[i]->getTransactionDate().toString("yyyy-MM-dd") );
        mModel->setItem( i, (int)HDR_DATE, item );
        mModel->setItem( i, (int)HDR_NAME, new QStandardItem( ( mTransactionList[i]->getAccount() ) ? mTransactionList[i]->getAccount()->getName() : "None" ) );
        mModel->setItem( i, (int)HDR_DESCRIPTION, new QStandardItem( mTransactionList[i]->getDescription() ) );
        NumberStandardItem* numberItem = new NumberStandardItem();
        numberItem->setNumber( mTransactionList[i]->getAmount() );
        mModel->setItem( i, (int)HDR_AMOUNT, numberItem );
        numberItem = new NumberStandardItem();
        numberItem->setNumber( mTransactionList[i]->getCurrentBalance() );
        mModel->setItem( i, (int)HDR_BALANCE, numberItem );
        mModel->setItem( i, (int)HDR_CATEGORY, new QStandardItem( Category::getCategoryText( mTransactionList[i]->getCategory() ) ) );
    }
} // TransactionList::setTransactionFilter

//----------------------------------------------------------------------------
// clear
//----------------------------------------------------------------------------
void TransactionList::clear()
{
    mTransactionList.clear();
    mModel->setRowCount( 0 );
} // TransactionList::clear

//----------------------------------------------------------------------------
// resort
//----------------------------------------------------------------------------
void TransactionList::resort()
{
    // Set transaction column widths
    QHeaderView* header = horizontalHeader();
    if( header->isSortIndicatorShown() )
    {
        Qt::SortOrder order = header->sortIndicatorOrder();
        int column = header->sortIndicatorSection();
        sortByColumn( column, order );
    }
} // TransactionList::resort
