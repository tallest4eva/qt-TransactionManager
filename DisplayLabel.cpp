//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: DisplayLabel.cpp
//******************************************************************************

#include "DisplayLabel.hpp"

#include <QPalette>
#include <QDebug>

static const int DOUBLE_CLICK_INTERVAL = 300;                   // Double click interval

//----------------------------------------------------------------------------
// DisplayLabel
//----------------------------------------------------------------------------
DisplayLabel::DisplayLabel()
{
    setFrameShadow( QFrame::Raised );
    setFrameShape( QFrame::StyledPanel );
    setAutoFillBackground( true );
    setBackgroundRole( QPalette::Window );
    QPalette palette;
    palette.setColor( QPalette::Window, Qt::white );
    setPalette( palette );
    QFont font;
    font.setPointSize( 9 );
    setFont( font );

    mPressTimer.setSingleShot( true );
    mReleaseTimer.setSingleShot( true );
    connect( &mPressTimer, SIGNAL(timeout()), this, SLOT(hide()) );
} // DisplayLabel::DisplayLabel

//----------------------------------------------------------------------------
// mouseDoubleClickEvent
//----------------------------------------------------------------------------
void DisplayLabel::mouseDoubleClickEvent( QMouseEvent* aEvent )
{
    QLabel::mouseDoubleClickEvent( aEvent );
    mPressTimer.stop();
    mReleaseTimer.start(DOUBLE_CLICK_INTERVAL);
    clicked();
} // DisplayLabel::mouseDoubleClickEvent

//----------------------------------------------------------------------------
// mousePressEvent
//----------------------------------------------------------------------------
void DisplayLabel::mousePressEvent( QMouseEvent* aEvent )
{
    QLabel::mousePressEvent( aEvent );
    QPalette palette;
    palette.setColor( QPalette::Window, Qt::blue );
    setPalette( palette );
} // DisplayLabel::mousePressEvent

//----------------------------------------------------------------------------
// mouseReleaseEvent
//----------------------------------------------------------------------------
void DisplayLabel::mouseReleaseEvent( QMouseEvent* aEvent )
{
    QLabel::mouseReleaseEvent( aEvent );
    if( !mReleaseTimer.isActive() ){ mPressTimer.start(DOUBLE_CLICK_INTERVAL); }
    QPalette palette;
    palette.setColor( QPalette::Window, Qt::white );
    setPalette( palette );
} // DisplayLabel::mouseReleaseEvent

//----------------------------------------------------------------------------
// setDates
//----------------------------------------------------------------------------
void DisplayLabel::setDates( const QDate& aStartDate, const QDate& aEndDate )
{
    mStartDate = aStartDate;
    mEndDate = aEndDate;
} // DisplayLabel::setDates
