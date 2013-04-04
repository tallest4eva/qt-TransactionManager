//******************************************************************************
//
//  HEADER NAME: OverviewAccountListItem.cpp
//******************************************************************************

#include <QGridLayout>

#include "OverviewAccountListItem.h"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
OverviewAccountListItem::OverviewAccountListItem
    (
    QWidget* parent
    ):
    QFrame(parent)
{
    setFrameShape( QFrame::StyledPanel );
    setFrameShadow( QFrame::Raised );

    mNameLabel.setText( "Account Name" );
    mBalanceLabel.setText( "$0" );
    mStatusLabel.setText("CLOSED");
    mDateLabel.setText("20xx-xx-xx --> 20yy-yy-yy");

    QFont font;
    font.setPointSize(10);
    mBalanceLabel.setFont(font);
    mStatusLabel.setFont(font);
    mDateLabel.setFont(font);
    font.setBold( true );
    mNameLabel.setFont(font);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( &mNameLabel,    0, 0 );
    layout->addWidget( &mBalanceLabel, 0, 1 );
    layout->addWidget( &mStatusLabel,  1, 0 );
    layout->addWidget( &mDateLabel,    1, 1 );
    setLayout( layout );
    show();
} // OverviewAccountListItem::OverviewAccountListItem

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
OverviewAccountListItem::~OverviewAccountListItem()
{
} // OverviewAccountListItem::~OverviewAccountListItem

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
void OverviewAccountListItem::setAccount
    (
    Account* aAccount
    )
{
    mAccount = aAccount;
    if( mAccount )
    {
        QString str = mAccount->getName();
        if( mAccount->getStatus() == Account::STATUS_CLOSED )
        {
            str.prepend( "<font color=\"grey\">" );
            str.append( "</font>" );
        }
        mNameLabel.setText( str );

        str = "$" + QString::number(mAccount->getBalance(), 'f', 2);
        if( mAccount->getBalance() != 0 )
        {
            str.prepend( (mAccount->getBalance() > 0) ? "<font color=\"darkgreen\">" : "<font color=\"red\">" );
            str.append( "</font>" );
        }
        mBalanceLabel.setText( str );
        mBalanceLabel.setAlignment( Qt::AlignRight );

        str = ( mAccount->getStatus() == Account::STATUS_OPEN ) ? "OPEN" : "CLOSED";
        if( mAccount->getStatus() == Account::STATUS_CLOSED )
        {
            str.prepend( "<font color=\"grey\">" );
            str.append( "</font>" );
        }
        mStatusLabel.setText( str );

        str = mAccount->getOpenDate().toString("yyyy-MM-dd") + " --> ";
        str += ( mAccount->getStatus() == Account::STATUS_OPEN ) ? "   PRESENT" : mAccount->getCloseDate().toString("yyyy-MM-dd");
        if( mAccount->getStatus() == Account::STATUS_CLOSED )
        {
            str.prepend( "<font color=\"grey\">" );
            str.append( "</font>" );
        }
        mDateLabel.setText( str );
        mDateLabel.setAlignment( Qt::AlignRight );
    }
} // OverviewAccountListItem::setAccount
