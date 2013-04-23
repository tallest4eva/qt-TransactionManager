//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: FileConfigDialog.cpp
//******************************************************************************

#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>

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
    setWindowTitle( "File Config Menu" );
    setModal( true );

    mSelected = Parser::sPresetSelected;
    mConfig = Parser::sPresetConfigList[mSelected];
    mConfigBox.setTitle( "Config Presets" );
    mFileBox.setTitle( "File Descriptors" );
    mAccountBox.setTitle( "Account Descriptor Line" );
    mTransactionBox.setTitle( "Transaction Descriptor Line" );
    mAccountDescriptor.setPlaceholderText("<Enter valid Account keyword>");
    mTransactionDescriptor.setPlaceholderText("<Enter valid Transaction keyword>");

    mConfigBox.setLayout( new QVBoxLayout );
    for( int i = 0; i < Parser::sPresetConfigList.size(); i++ )
    {
        QRadioButton* button = new QRadioButton( Parser::sPresetConfigList[i].mName, &mConfigBox );
        connect( button, SIGNAL(clicked()), this, SLOT(handlePresetSelected()) );
        mConfigBox.layout()->addWidget( button );
        mRadioButtonList.push_back( button );
    }

    // Setup Combo boxes
    for( int i = 0; i < Parser::DATE_FORMAT_CNT; i++ )
    {
        mDateFormat.addItem( Parser::cDateFormatList[i], i );
    }
    for( int i = 0; i < Parser::SEPARATOR_CNT; i++ )
    {
        mFileSeperator.addItem( QString(Parser::cSeparatorList[i]), i );
    }
    // Add column combobox items
    for( int i = -1; i < Parser::MAX_COLUMNS; i++ )
    {
        int data = ( i == -1 ) ? Parser::INVALID_COLUMN : i;
        QString str = ( i == -1 ) ? QString("Not Available") : (QString("Column ") + QString::number(i+1));
        mAccountName.addItem( str, data );
        mAccountStatus.addItem( str, data );
        mAccountState.addItem( str, data );
        mAccountAltName.addItem( str, data );
        mTransactionDate.addItem( str, data );
        mTransactionName.addItem( str, data );
        mTransactionDescription.addItem( str, data );
        mTransactionType.addItem( str, data );
        mTransactionAmount.addItem( str, data );
        mTransactionBalance.addItem( str, data );
        mTransactionCategory.addItem( str, data );
        mTransactionLabels.addItem( str, data );
    }

    // Setup Group Boxes
    QFormLayout* fLayout = new QFormLayout;
    fLayout->addRow( "File Separator:", &mFileSeperator );
    fLayout->addRow( "Date Format:", &mDateFormat );
    mFileBox.setLayout( fLayout );
    fLayout = new QFormLayout;
    fLayout->addRow( "Require Account Descriptors:", &mAccountCheckBox );
    fLayout->addRow( "Column 1 Keyword:", &mAccountDescriptor );
    fLayout->addRow( "Name:", &mAccountName );
    fLayout->addRow( "Status:", &mAccountStatus );
    fLayout->addRow( "State:", &mAccountState );
    fLayout->addRow( "Alternate Names:", &mAccountAltName );
    mAccountBox.setLayout( fLayout );
    fLayout = new QFormLayout;
    fLayout->addRow( "Use Transaction Keyword:", &mTransactionCheckBox );
    fLayout->addRow( "Column 1 Keyword:", &mTransactionDescriptor );
    fLayout->addRow( "Date:", &mTransactionDate );
    fLayout->addRow( "Account Name:", &mTransactionName );
    fLayout->addRow( "Description:", &mTransactionDescription );
    fLayout->addRow( "Transaction Type:", &mTransactionType );
    fLayout->addRow( "Amount:", &mTransactionAmount );
    fLayout->addRow( "Balance:", &mTransactionBalance );
    fLayout->addRow( "Category:", &mTransactionCategory );
    fLayout->addRow( "Labels:", &mTransactionLabels );
    mTransactionBox.setLayout( fLayout );

    updateData();
    
    // Set up buttons / checkboxes
    mCancelButton.setText( "Cancel" );
    mDoneButton.setText( "Done" );
    connect( &mCancelButton, SIGNAL(clicked()), this, SLOT(handleCancelButton()) );
    connect( &mDoneButton, SIGNAL(clicked()), this, SLOT(handleDoneButton()) );
    connect( &mTransactionCheckBox, SIGNAL(clicked(bool)), this, SLOT(handleTransactionClicked(bool)) );

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( &mConfigBox,      0, 0, 5, 2 );
    layout->addWidget( &mFileBox,        5, 0, 4, 2 );
    layout->addWidget( &mAccountBox,     0, 2, 4, 2 );
    layout->addWidget( &mTransactionBox, 4, 2, 5, 2 );
    layout->addWidget( &mCancelButton,   10, 2 );
    layout->addWidget( &mDoneButton,     10, 3 );
    setLayout( layout );
    resize( 700, 550 );
    show();
} // FileConfigDialog::FileConfigDialog

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
FileConfigDialog::~FileConfigDialog()
{
    for( int i = 0; i < mRadioButtonList.size(); i++ )
    {
        delete mRadioButtonList[i];
    }
    mRadioButtonList.clear();
} // FileConfigDialog::~FileConfigDialog

//----------------------------------------------------------------------------
// update Data
//----------------------------------------------------------------------------
void FileConfigDialog::updateData()
{
    if( mSelected < mRadioButtonList.size() )
    {
        mRadioButtonList[mSelected]->setChecked( true );
    }
    mFileSeperator.setCurrentIndex( mFileSeperator.findData(mConfig.mSeparator) );
    mDateFormat.setCurrentIndex( mDateFormat.findData(mConfig.mDateFormat) );

    mAccountCheckBox.setChecked( mConfig.mAccountRequireTag );
    mAccountDescriptor.setText( mConfig.mAccountTag );
    mAccountName.setCurrentIndex( mAccountName.findData(mConfig.mEntryList[Parser::ENTRY_ACCOUNT_NAME]) );
    mAccountStatus.setCurrentIndex( mAccountStatus.findData(mConfig.mEntryList[Parser::ENTRY_ACCOUNT_STATUS]) );
    mAccountState.setCurrentIndex( mAccountState.findData(mConfig.mEntryList[Parser::ENTRY_ACCOUNT_STATE]) );
    mAccountAltName.setCurrentIndex( mAccountAltName.findData(mConfig.mEntryList[Parser::ENTRY_ACCOUNT_ALT_NAMES]) );

    mTransactionCheckBox.setChecked( mConfig.mTransactionUseTag );
    mTransactionDescriptor.setText( mConfig.mTransactionTag );
    mTransactionDescriptor.setEnabled( mConfig.mTransactionUseTag );
    mTransactionDate.setCurrentIndex( mTransactionDate.findData(mConfig.mEntryList[Parser::ENTRY_TRANS_DATE]) );
    mTransactionName.setCurrentIndex( mTransactionName.findData(mConfig.mEntryList[Parser::ENTRY_TRANS_ACCOUNT_NAME]) );
    mTransactionDescription.setCurrentIndex( mTransactionDescription.findData(mConfig.mEntryList[Parser::ENTRY_TRANS_DESCRIPTION]) );
    mTransactionType.setCurrentIndex( mTransactionType.findData(mConfig.mEntryList[Parser::ENTRY_TRANS_TYPE]) );
    mTransactionAmount.setCurrentIndex( mTransactionAmount.findData(mConfig.mEntryList[Parser::ENTRY_TRANS_AMOUNT]) );
    mTransactionBalance.setCurrentIndex( mTransactionBalance.findData(mConfig.mEntryList[Parser::ENTRY_TRANS_BALANCE]) );
    mTransactionCategory.setCurrentIndex( mTransactionCategory.findData(mConfig.mEntryList[Parser::ENTRY_TRANS_CATEGORY]) );
    mTransactionLabels.setCurrentIndex( mTransactionLabels.findData(mConfig.mEntryList[Parser::ENTRY_TRANS_LABELS]) );

    bool disable = ( mSelected != Parser::CUSTOM_CONFIG_IDX );
    mFileBox.setDisabled( disable );
    mAccountBox.setDisabled( disable );
    mTransactionBox.setDisabled( disable );
} // FileConfigDialog::updateData

//----------------------------------------------------------------------------
// handlePresetSelected
//----------------------------------------------------------------------------
void FileConfigDialog::handlePresetSelected()
{
    for( int i = 0; i < mRadioButtonList.size(); i++ )
    {
        if( mRadioButtonList[i]->isChecked() )
        {
            mSelected = i;
            mConfig = Parser::sPresetConfigList[mSelected];
            break;
        }
    }
    // Update config widgets
    updateData();
} // FileConfigDialog::handlePresetSelected

//----------------------------------------------------------------------------
// handleTransactionClicked
//----------------------------------------------------------------------------
void FileConfigDialog::handleTransactionClicked( bool aChecked )
{
    mTransactionDescriptor.setEnabled( aChecked );
} // FileConfigDialog::handleTransactionClicked

//----------------------------------------------------------------------------
// handleCancelButton
//----------------------------------------------------------------------------
void FileConfigDialog::handleCancelButton()
{
    // Close dialog
    done( 0 );
} // FileConfigDialog::handleCancelButton()

//----------------------------------------------------------------------------
// handleDoneButton
//----------------------------------------------------------------------------
void FileConfigDialog::handleDoneButton()
{
    if( mSelected == Parser::CUSTOM_CONFIG_IDX )
    {
        // Update customconfig with combo box values
        mConfig.mSeparator = (Parser::SeparatorType)mFileSeperator.itemData( mFileSeperator.currentIndex() ).toInt();
        mConfig.mDateFormat = (Parser::DateFormatType)mDateFormat.itemData( mDateFormat.currentIndex() ).toInt();

        mConfig.mAccountRequireTag = mAccountCheckBox.isChecked();
        if( !mAccountDescriptor.text().isEmpty() ){ mConfig.mAccountTag = mAccountDescriptor.text(); }
        mConfig.mEntryList[Parser::ENTRY_ACCOUNT_NAME] = mAccountName.itemData( mAccountName.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_ACCOUNT_STATUS] = mAccountStatus.itemData( mAccountStatus.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_ACCOUNT_STATE] = mAccountState.itemData( mAccountState.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_ACCOUNT_ALT_NAMES] = mAccountAltName.itemData( mAccountAltName.currentIndex() ).toInt();

        mConfig.mTransactionUseTag = mTransactionCheckBox.isChecked();
        if( mConfig.mTransactionUseTag && !mTransactionDescriptor.text().isEmpty() ){ mConfig.mTransactionTag = mTransactionDescriptor.text(); }
        mConfig.mEntryList[Parser::ENTRY_TRANS_DATE] = mTransactionDate.itemData( mTransactionDate.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_TRANS_ACCOUNT_NAME] = mTransactionName.itemData( mTransactionName.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_TRANS_DESCRIPTION] = mTransactionDescription.itemData( mTransactionDescription.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_TRANS_TYPE] = mTransactionType.itemData( mTransactionType.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_TRANS_AMOUNT] = mTransactionAmount.itemData( mTransactionAmount.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_TRANS_BALANCE] = mTransactionBalance.itemData( mTransactionBalance.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_TRANS_CATEGORY] = mTransactionCategory.itemData( mTransactionCategory.currentIndex() ).toInt();
        mConfig.mEntryList[Parser::ENTRY_TRANS_LABELS] = mTransactionLabels.itemData( mTransactionLabels.currentIndex() ).toInt();

        Parser::sPresetConfigList[ Parser::CUSTOM_CONFIG_IDX ] = mConfig;
    }

    // Apply selected config
    Parser::applyConfig( mSelected );

    // Close dialog
    done( 0 );
} // FileConfigDialog::handleDoneButton
