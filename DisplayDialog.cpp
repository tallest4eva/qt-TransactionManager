//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: DisplayDialog.cpp
//******************************************************************************

#include <QGridLayout>

#include "DisplayDialog.hpp"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
DisplayDialog::DisplayDialog
    (
    QWidget* parent
    ):
    QDialog(parent)
{
    setModal( true );
    mLabel.setReadOnly( false );
    mLabel.setWordWrapMode( QTextOption::NoWrap );
    mLabel.setReadOnly( true );
    mButton.setText( "Done" );
    mButton.setMaximumWidth( 150 );
    connect( &mButton, SIGNAL(clicked(bool)), this, SLOT(handleDoneButton()) );
    mScrollable.setWidget( &mLabel );
    mScrollable.setWidgetResizable(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( &mScrollable, 0, 0, 10, 10 );
    layout->addWidget( &mButton, 10, 8, 1, 2 );
    setLayout( layout );
    resize( 700, 500 );
    show();
} // DisplayDialog::DisplayDialog

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
DisplayDialog::~DisplayDialog()
{
} // DisplayDialog::~DisplayDialog

//----------------------------------------------------------------------------
// handleDoneButton
//----------------------------------------------------------------------------
void DisplayDialog::handleDoneButton()
{
    done( 0 );
} // DisplayDialog::handleDoneButton

//----------------------------------------------------------------------------
// setDisplay
//----------------------------------------------------------------------------
void DisplayDialog::setDisplay
    (
    const QStringList& aStringList,
    const QString& aEmptyDisplayString
    )
{
    if( aStringList.count() > 0 )
    {
        mLabel.setText( aStringList.join("\n") );
    }
    else
    {
        mLabel.setText( aEmptyDisplayString );
    }
} // DisplayDialog::setDisplay
