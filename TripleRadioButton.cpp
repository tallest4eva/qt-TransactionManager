//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: TripleRadioButton.cpp
//******************************************************************************

#include <QGridLayout>

#include "TripleRadioButton.hpp"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
TripleRadioButton::TripleRadioButton
    (
    const QString& aLabelText,
    QWidget* aParent
    ):
    QWidget( aParent )
{
    mNameLabel.setText( aLabelText + ":" );
    mNameLabel.setMinimumWidth( 100 );

    connect( &mMatchButton,      SIGNAL(clicked()), this, SIGNAL(buttonClicked()) );
    connect( &mDoNotMatchButton, SIGNAL(clicked()), this, SIGNAL(buttonClicked()) );
    connect( &mExcludeButton,    SIGNAL(clicked()), this, SIGNAL(buttonClicked()) );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( &mNameLabel,         0, 0 );
    layout->addWidget( &mMatchButton,       0, 1 );
    layout->addWidget( &mDoNotMatchButton,  0, 2 );
    layout->addWidget( &mExcludeButton,     0, 3 );
    setLayout( layout );
} // TripleRadioButton::TripleRadioButton

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
TripleRadioButton::~TripleRadioButton()
{
} // TripleRadioButton::~TripleRadioButton

//----------------------------------------------------------------------------
// Set Match Type
//----------------------------------------------------------------------------
void TripleRadioButton::setMatchType( Transaction::MatchType aMatchType )
{
    switch( aMatchType )
    {
    case Transaction::MATCH:
        mMatchButton.setChecked( true );
        break;
    case Transaction::DO_NOT_MATCH:
        mDoNotMatchButton.setChecked( true );
        break;
    case Transaction::EXCLUDE_MATCH:
        mExcludeButton.setChecked( true );
        break;
    }
} // TripleRadioButton::setMatchType

//----------------------------------------------------------------------------
// Get Match Type
//----------------------------------------------------------------------------
Transaction::MatchType TripleRadioButton::getMatchType() const
{
    Transaction::MatchType match = Transaction::MATCH;
    if( mDoNotMatchButton.isChecked() ){ match = Transaction::DO_NOT_MATCH; }
    else if( mExcludeButton.isChecked() ){ match = Transaction::EXCLUDE_MATCH; }
    return match;
} // TripleRadioButton::getMatchType
