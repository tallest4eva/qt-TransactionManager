//******************************************************************************
//
//  HEADER NAME: FileConfigDialog.cpp
//******************************************************************************

#include <QGridLayout>
#include <QFormLayout>

#include "FileConfigDialog.h"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
FileConfigDialog::FileConfigDialog
    (
    QWidget* parent
    ):
    QDialog(parent)
{
    mAccountBox.setTitle( "Account Descriptor" );
    mTransactionBox.setTitle( "Transaction Descriptor" );
    
    // Transaction setup
    QFormLayout *fLayout = new QFormLayout;
    for( int i = 0; i < 10; i++ )
    {
        mTransactionDate.addItem( "Column " + QString::number(i), i );
        mTransactionName.addItem( "Column " + QString::number(i), i );
        mTransactionDescription.addItem( "Column " + QString::number(i), i );
        mTransactionType.addItem( "Column " + QString::number(i), i );
        mTransactionAmount.addItem( "Column " + QString::number(i), i );
        mTransactionBalance.addItem( "Column " + QString::number(i), i );
        mTransactionCategory.addItem( "Column " + QString::number(i), i );
        mTransactionLabels.addItem( "Column " + QString::number(i), i );
        mAccountName.addItem( "Column " + QString::number(i), i );
        mAccountStatus.addItem( "Column " + QString::number(i), i );
        mAccountState.addItem( "Column " + QString::number(i), i );
        mAccountAltName.addItem( "Column " + QString::number(i), i );
    }
    for( int i = 0; i < Parser::DATE_FORMAT_CNT; i++ )
    {
        mDateFormat.addItem( Parser::cDateFormatList[i], i );
    }
    fLayout->addRow( "Date:", &mTransactionDate );
    fLayout->addRow( "Name:", &mTransactionName );
    fLayout->addRow( "Description:", &mTransactionDescription );
    fLayout->addRow( "Transaction Type:", &mTransactionType );
    fLayout->addRow( "Amount:", &mTransactionAmount );
    fLayout->addRow( "Balance:", &mTransactionBalance );
    fLayout->addRow( "Category:", &mTransactionCategory );
    fLayout->addRow( "Labels:", &mTransactionLabels );
    fLayout->addRow( "Date Format:", &mDateFormat );
    mTransactionBox.setLayout( fLayout );
    
    // Account setup
    fLayout = new QFormLayout;
    fLayout->addRow( "Name:", &mAccountName );
    fLayout->addRow( "Status:", &mAccountStatus );
    fLayout->addRow( "State:", &mAccountState );
    fLayout->addRow( "Alternate Names:", &mAccountAltName );
    mAccountBox.setLayout( fLayout );

    updateComboBoxes();
    
    // Set up buttons
    mCancelButton.setText( "Cancel" );
    mOkButton.setText( "OK" );
    mRestoreButton.setText( "Restore Default" );
    mRestoreButton.setEnabled( false );
    connect( &mCancelButton, SIGNAL(clicked(bool)), this, SLOT(handleDoneButton(CANCEL_BUTTON)) );
    connect( &mOkButton, SIGNAL(clicked(bool)), this, SLOT(handleDoneButton(OK_BUTTON)) );
    connect( &mRestoreButton, SIGNAL(clicked(bool)), this, SLOT(handleDoneButton(RESTORE_BUTTON)) );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( &mAccountBox,     0, 0, 9, 2 );
    layout->addWidget( &mTransactionBox, 0, 2, 9, 2 );
    layout->addWidget( &mCancelButton,   10, 1 );
    layout->addWidget( &mRestoreButton,  10, 2 );
    layout->addWidget( &mOkButton,       10, 3 );
    setLayout( layout );
    resize( 700, 500 );
    show();
} // FileConfigDialog::FileConfigDialog

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
FileConfigDialog::~FileConfigDialog()
{
} // FileConfigDialog::~FileConfigDialog

//----------------------------------------------------------------------------
// update Combo Boxes
//----------------------------------------------------------------------------
FileConfigDialog::updateComboBoxes()
{
    mTransactionDate.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_TRANS_DATE] );
    mTransactionName.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_TRANS_ACCOUNT_NAME] );
    mTransactionDescription.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_TRANS_DESCRIPTION] );
    mTransactionType.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_TRANS_TYPE] );
    mTransactionAmount.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_TRANS_AMOUNT] );
    mTransactionBalance.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_TRANS_BALANCE] );
    mTransactionCategory.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_TRANS_CATEGORY] );
    mTransactionLabels.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_TRANS_LABELS] );
    mAccountName.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_ACCOUNT_NAME] );
    mAccountStatus.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_ACCOUNT_STATUS] );
    mAccountState.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_ACCOUNT_STATE] );
    mAccountAltName.setCurrentIndex( Parser::sEntryList[Parser::ENTRY_ACCOUNT_ALT_NAMES] );
} // FileConfigDialog::updateComboBoxes

//----------------------------------------------------------------------------
// handleDoneButton
//----------------------------------------------------------------------------
void FileConfigDialog::handleButton( ButtonType aButton )
{
    switch( aButton )
    {
    case CANCEL_BUTTON:
        done( 0 );
        break;
    case RESTORE_BUTTON:
        // Update combo box values
        break;
    case OK_BUTTON:
        done( 0 );
        break;
    }
} // FileConfigDialog::handleDoneButton

//----------------------------------------------------------------------------
// setDisplay
//----------------------------------------------------------------------------
void FileConfigDialog::setDisplay
    (
    const QStringList& aStringList
    )
{
    if( aStringList.count() > 0 )
    {
        mLabel.setText( aStringList.join("\n") );
    }
    else
    {
        mLabel.setText( "No content to display" );
    }
} // FileConfigDialog::setDisplay
