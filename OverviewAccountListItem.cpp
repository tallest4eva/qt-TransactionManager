//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: OverviewAccountListItem.cpp
//******************************************************************************

#include <QGridLayout>

#include "OverviewAccountListItem.hpp"
#include "Transaction.hpp"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
OverviewAccountListItem::OverviewAccountListItem
    (
    QWidget* parent
    ):
    QFrame(parent)
{
    mSelected = false;
    setFrameShape( QFrame::StyledPanel );
    setFrameShadow( QFrame::Raised );

    mNameLabel.setText( "Account Name" );
    mBalanceLabel.setText( "$0.00" );
    mTransactionLabel.setText("Transaction count: 0");
    mDateLabel.setText("Status: CLOSED | 20xx-xx-xx --> 20yy-yy-yy");

    QFont font;
    font.setPointSize(10);
    mTransactionLabel.setFont(font);
    mDateLabel.setFont(font);
    font.setBold( true );
    mBalanceLabel.setFont(font);
    mNameLabel.setFont(font);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( &mNameLabel,         0, 0 );
    layout->addWidget( &mBalanceLabel,      0, 1 );
    layout->addWidget( &mTransactionLabel,  1, 0 );
    layout->addWidget( &mDateLabel,         1, 1 );
    setLayout( layout );
} // OverviewAccountListItem::OverviewAccountListItem

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
OverviewAccountListItem::~OverviewAccountListItem()
{
} // OverviewAccountListItem::~OverviewAccountListItem

//----------------------------------------------------------------------------
// Set Account
//----------------------------------------------------------------------------
void OverviewAccountListItem::setAccount
    (
    Account* aAccount
    )
{
    mAccount = aAccount;
    if( mAccount )
    {
        // Update labels with account information
        QString str = mAccount->getName();
        mNameLabel.setText( str );
        str = Transaction::getAmountText( mAccount->getBalance() );
        mBalanceLabel.setText( str );
        mBalanceLabel.setAlignment( Qt::AlignRight );
        str = "Transaction count: " + QString::number( mAccount->getTransactionList().size() );
        mTransactionLabel.setText( str );
        str = ( mAccount->isOpen() ) ? "(Status: OPEN)    " : "(Status: CLOSED)  ";
        str += mAccount->getOpenDate().toString("yyyy-MM-dd") + " --> " + mAccount->getLastDate().toString("yyyy-MM-dd");
        mDateLabel.setAlignment( Qt::AlignRight );
        mDateLabel.setText( str );
    }
    updateLabelColors();
} // OverviewAccountListItem::setAccount

//----------------------------------------------------------------------------
// Set / Deselect account item
//----------------------------------------------------------------------------
void OverviewAccountListItem::setSelected( bool aSelected )
{
    mSelected = aSelected;
} // OverviewAccountListItem::setSelected

//----------------------------------------------------------------------------
// update Label Colors
//----------------------------------------------------------------------------
void OverviewAccountListItem::updateLabelColors()
{
    if( mAccount )
    {
        QPalette palette;
        if( mAccount->getStatus() == Account::STATUS_CLOSED )
        {
            palette.setColor( QPalette::Text, Qt::gray );
            mNameLabel.setPalette( palette );
            mBalanceLabel.setPalette( palette );
            mTransactionLabel.setPalette( palette );
            mDateLabel.setPalette( palette );
        }
        else // If open and not selected
        {
            palette.setColor( QPalette::Text, Qt::black );
            mNameLabel.setPalette( palette );
            mDateLabel.setPalette( palette );
            mTransactionLabel.setPalette( palette );
            if( mAccount->getBalance() != 0 )
            {
                palette.setColor( QPalette::Text, (mAccount->getBalance() > 0) ? Qt::darkGreen : Qt::red );
            }
            mBalanceLabel.setPalette( palette );
        }
    }
} // OverviewAccountListItem::setAccount
