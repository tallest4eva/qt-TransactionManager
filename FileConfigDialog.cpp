//******************************************************************************
//
//  HEADER NAME: FileConfigDialog.cpp
//******************************************************************************

#include <QGridLayout>
#include <QFormLayout>

#include "FileConfigDialog.h"
#include "Parser.h"

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
FileConfigDialog::FileConfigDialog
    (
    QWidget* parent
    ):
    QDialog(parent)
{
    setWindowTitle( "File Config Menu" );

    mFileBox.setTitle( "File Descriptors" );
    mAccountBox.setTitle( "Account Descriptors" );
    mTransactionBox.setTitle( "Transaction Descriptors" );
    
    // Setup Combo boxes
    for( int i = 0; i < Parser::DATE_FORMAT_CNT; i++ )
    {
        mDateFormat.addItem( Parser::cDateFormatList[i], i );
    }
    for( int i = 0; i < Parser::SEPARATOR_CNT; i++ )
    {
        mFileSeperator.addItem( QString(Parser::cSeparatorList[i]), i );
    }
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

    // Setup Group Boxes
    QFormLayout* fLayout = new QFormLayout;
    fLayout->addRow( "File Separator:", &mFileSeperator );
    fLayout->addRow( "Date Format:", &mDateFormat );
    mFileBox.setLayout( fLayout );
    fLayout = new QFormLayout;
    fLayout->addRow( "Name:", &mAccountName );
    fLayout->addRow( "Status:", &mAccountStatus );
    fLayout->addRow( "State:", &mAccountState );
    fLayout->addRow( "Alternate Names:", &mAccountAltName );
    mAccountBox.setLayout( fLayout );
    fLayout = new QFormLayout;
    fLayout->addRow( "Date:", &mTransactionDate );
    fLayout->addRow( "Name:", &mTransactionName );
    fLayout->addRow( "Description:", &mTransactionDescription );
    fLayout->addRow( "Transaction Type:", &mTransactionType );
    fLayout->addRow( "Amount:", &mTransactionAmount );
    fLayout->addRow( "Balance:", &mTransactionBalance );
    fLayout->addRow( "Category:", &mTransactionCategory );
    fLayout->addRow( "Labels:", &mTransactionLabels );
    mTransactionBox.setLayout( fLayout );

    updateComboBoxes();
    
    // Set up buttons
    mCancelButton.setText( "Cancel" );
    mDoneButton.setText( "Done" );
    mRestoreButton.setText( "Restore Default" );
    connect( &mCancelButton, SIGNAL(clicked()), this, SLOT(handleCancelButton()) );
    connect( &mDoneButton, SIGNAL(clicked()), this, SLOT(handleDoneButton()) );
    connect( &mRestoreButton, SIGNAL(clicked()), this, SLOT(handleRestoreButton()) );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( &mFileBox,        0, 0, 4, 2 );
    layout->addWidget( &mAccountBox,     4, 0, 5, 2 );
    layout->addWidget( &mTransactionBox, 0, 2, 9, 2 );
    layout->addWidget( &mCancelButton,   10, 1 );
    layout->addWidget( &mRestoreButton,  10, 2 );
    layout->addWidget( &mDoneButton,     10, 3 );
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
void FileConfigDialog::updateComboBoxes()
{
    mFileSeperator.setCurrentIndex( Parser::sSeparator );
    mDateFormat.setCurrentIndex( Parser::sDateFormat );
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
// handleCancelButton
//----------------------------------------------------------------------------
void FileConfigDialog::handleCancelButton()
{
    // Close dialog
    done( 0 );
} // FileConfigDialog::handleCancelButton()

//----------------------------------------------------------------------------
// handleRestoreButton
//----------------------------------------------------------------------------
void FileConfigDialog::handleRestoreButton()
{
    // Restore parser defaults
    Parser::restore();
    updateComboBoxes();
} // FileConfigDialog::handleRestoreButton()

//----------------------------------------------------------------------------
// handleDoneButton
//----------------------------------------------------------------------------
void FileConfigDialog::handleDoneButton()
{
    // Save current combo box values
    Parser::sSeparator = (Parser::SeparatorType)mFileSeperator.currentIndex();
    Parser::sDateFormat = (Parser::DateFormatType)mDateFormat.currentIndex();
    Parser::sEntryList[Parser::ENTRY_TRANS_DATE] = mTransactionDate.currentIndex();
    Parser::sEntryList[Parser::ENTRY_TRANS_ACCOUNT_NAME] = mTransactionName.currentIndex();
    Parser::sEntryList[Parser::ENTRY_TRANS_DESCRIPTION] = mTransactionDescription.currentIndex();
    Parser::sEntryList[Parser::ENTRY_TRANS_TYPE] = mTransactionType.currentIndex();
    Parser::sEntryList[Parser::ENTRY_TRANS_AMOUNT] = mTransactionAmount.currentIndex();
    Parser::sEntryList[Parser::ENTRY_TRANS_BALANCE] = mTransactionBalance.currentIndex();
    Parser::sEntryList[Parser::ENTRY_TRANS_CATEGORY] = mTransactionCategory.currentIndex();
    Parser::sEntryList[Parser::ENTRY_TRANS_LABELS] = mTransactionLabels.currentIndex();
    Parser::sEntryList[Parser::ENTRY_ACCOUNT_NAME] = mAccountName.currentIndex();
    Parser::sEntryList[Parser::ENTRY_ACCOUNT_STATUS] = mAccountStatus.currentIndex();
    Parser::sEntryList[Parser::ENTRY_ACCOUNT_STATE] = mAccountState.currentIndex();
    Parser::sEntryList[Parser::ENTRY_ACCOUNT_ALT_NAMES] = mAccountAltName.currentIndex();

    // Close dialog
    done( 0 );
} // FileConfigDialog::handleDoneButton
