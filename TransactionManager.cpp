//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: TransactionManager.cpp
//******************************************************************************

#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QCheckBox>
#include <QMessageBox>
#include <QTextStream>
#include <QListWidgetItem>

#include <ui_transactionmanager.h>

#include "TransactionManager.hpp"
#include "Account.hpp"
#include "Category.hpp"
#include "DisplayDialog.hpp"
#include "FileConfigDialog.hpp"
#include "Logger.hpp"
#include "Month.hpp"
#include "Parser.hpp"
#include "OverviewAccountListItem.hpp"
#include "TripleRadioButton.hpp"

// Static variables
const QDate TransactionManager::cDefaultStartDate = QDate(2000,1,1);
const QDate TransactionManager::cDefaultEndDate = QDate(2001,1,1);

QStringList TransactionManager::sFileContents;
QList<Transaction*> TransactionManager::sTransactionList;
QList<Month*> TransactionManager::sMonthList;
QDate TransactionManager::sFirstTransactionDate = TransactionManager::cDefaultStartDate;
QDate TransactionManager::sLastTransactionDate = TransactionManager::cDefaultEndDate;
QVector<bool> TransactionManager::sCategoriesEnabledList;
QVector<bool> TransactionManager::sLabelsEnabledList;

static const QString sVersionStr = "1.09";
static const QString sToolboxAccountsStr = "Accounts";
static const QString sToolboxCategoriesStr = "Categories";
static const QString sToolboxLabelsStr = "Labels";
static const QString sToolboxDatesStr = "Date Interval";
static const QString sDateCustomStr = "Custom Dates";
static const QString sDateThisYearStr = "This Year";
static const QString sDate1YearStr = "Last 1 Year";
static const QString sDate3YearStr = "Last 3 Year";
static const QString sDate5YearStr = "Last 5 Years";
static const QString sDate10YearStr = "Last 10 Years";
static const QString sDateAllTimeStr = "All Time";
static const QString sDateInterval1MonthStr = "Monthly";
static const QString sDateInterval3MonthStr = "Quarterly";
static const QString sDateInterval6MonthStr = "BiAnnually";
static const QString sDateInterval1YearStr = "Annually";
static const QString sSortAccountByName = "Account Name";
static const QString sSortAccountByBalance = "Balance";
static const QString sSortAccountByOpenDate = "Open Date";
static const QString sSortChartByBalance = "Sort Chart By Balance";
static const QString sSortChartByName = "Sort Chart By Name";

//----------------------------------------------------------------------------
// Static utility functions
//----------------------------------------------------------------------------
inline Qt::CheckState getCurrentCheckState( bool allChecked, bool aAtLeastOne )
{
    if( allChecked )
    {
        return Qt::Checked;
    }
    return( aAtLeastOne ? Qt::PartiallyChecked : Qt::Unchecked );
}

static QStringList getDateComboBoxList( const QDate& aCurrentDate )
{
    QStringList dateItemList;
    QDate thisYearDate( aCurrentDate.year(), 1, 1 );
    if( TransactionManager::sLastTransactionDate >= thisYearDate ){ dateItemList.push_back( sDateThisYearStr ); }
    if( TransactionManager::sFirstTransactionDate < aCurrentDate.addYears(-1)  ){ dateItemList.push_back( sDate1YearStr ); }
    if( TransactionManager::sFirstTransactionDate < aCurrentDate.addYears(-3)  ){ dateItemList.push_back( sDate3YearStr ); }
    if( TransactionManager::sFirstTransactionDate < aCurrentDate.addYears(-5)  ){ dateItemList.push_back( sDate5YearStr ); }
    if( TransactionManager::sFirstTransactionDate < aCurrentDate.addYears(-10) ){ dateItemList.push_back( sDate10YearStr ); }
    dateItemList.push_back( sDateCustomStr );
    return dateItemList;
}

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
TransactionManager::TransactionManager
    (
    QWidget* aParent
    ):
    QMainWindow( aParent )
    , mUi(new Ui::TransactionManager)
    , mReportNetIncomeGraph( BarGraph::BAR_NET_INCOME )
    , mReportNetWorthGraph( BarGraph::BAR_NET_WORTH )
    , mReportAccountBalanceGraph( BarGraph::BAR_ACCOUNT_BALANCE )
{
    mUi->setupUi(this);

    // Init ui
    init();
    updateUI();
} // TransactionManager::TransactionManager

//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
TransactionManager::~TransactionManager()
{
    deInit();
    delete mUi;
} // TransactionManager::~TransactionManager

//----------------------------------------------------------------------------
// Init
//----------------------------------------------------------------------------
void TransactionManager::init()
{
    // Init Parser
    Category::initCategoryList();
    Parser::init();
    sCategoriesEnabledList.fill( false, Category::getCategoryCount() );
    sLabelsEnabledList.fill( false, Category::getLabelCount() );
    mTransactionFilter = Transaction::FilterType();
    mReportFilter = Transaction::FilterType();

    // Set up status labels
    mStatusConfigLabel.setText( "Loaded Config: " + Parser::sPresetConfigList[Parser::sPresetSelected].mName );
    mUi->statusBar->addWidget( &mStatusFileLabel );
    mUi->statusBar->addPermanentWidget( &mStatusConfigLabel );

    // Init tab/toolbox widgets
    mUi->tabWidget->setCurrentIndex(0);
    mUi->transactionToolBox->setCurrentIndex(0);
    mUi->reportToolBox->setCurrentIndex(0);
    mUi->reportDisplayTabWidget->setCurrentIndex(0);
    mUi->transactionListWidget->layout()->addWidget( &mTransactionTableView );

    // Create category tree widget
    mTransactionCategoriesTreeWidget.setColumnCount(1);
    mTransactionCategoriesTreeWidget.setHeaderHidden( true );
    mUi->transactionCategoriesGroupBox->layout()->addWidget( &mTransactionCategoriesTreeWidget );
    connect( &mTransactionCategoriesTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(handleParentCategoriesCheckBoxClicked(QTreeWidgetItem*,int)) );

    mReportCategoriesTreeWidget.setColumnCount(1);
    mReportCategoriesTreeWidget.setHeaderHidden( true );
    mUi->reportCategoriesGroupBox->layout()->addWidget( &mReportCategoriesTreeWidget );
    connect( &mReportCategoriesTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(handleParentCategoriesCheckBoxClicked(QTreeWidgetItem*,int)) );

    for( int i = 0; i < Category::PARENT_CATEGORY_TYPE_CNT; i++ )
    {
        QString str = Category::getParentCategoryText( (Category::ParentCategoryType)i );
        QTreeWidgetItem* treeItem = new QTreeWidgetItem( &mTransactionCategoriesTreeWidget, QStringList(str) );
        treeItem->setFlags( treeItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsAutoTristate );
        treeItem->setCheckState(0, Qt::Checked);
        mTransactionCategoriesTreeWidget.insertTopLevelItem( i, treeItem );
        mTransactionParentCategoriesCheckBoxList.push_back( treeItem );

        treeItem = new QTreeWidgetItem( &mReportCategoriesTreeWidget, QStringList(str) );
        treeItem->setFlags( treeItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsAutoTristate );
        treeItem->setCheckState(0, Qt::Checked);
        mReportCategoriesTreeWidget.insertTopLevelItem( i, treeItem );
        mReportParentCategoriesCheckBoxList.push_back( treeItem );
    }

	int count = Category::getCategoryCount();
    for( int i = 0; i < count; i++ )
    {
        Category::ParentCategoryType parentId = Category::getParentCategoryId( (Category::CategoryIdxType)i );
        QString str = Category::getCategoryText( (Category::CategoryIdxType)i ).replace( "&", "and" );

        QTreeWidgetItem* parentTreeItem = mTransactionCategoriesTreeWidget.topLevelItem( (int)parentId );
        if( parentTreeItem )
        {
            QTreeWidgetItem* treeItem = new QTreeWidgetItem( parentTreeItem, QStringList(str) );
            treeItem->setCheckState(0, Qt::Checked);
            mTransactionCategoriesCheckBoxList.push_back( treeItem );
        }

        parentTreeItem = mReportCategoriesTreeWidget.topLevelItem( (int)parentId );
        if( parentTreeItem )
        {
            QTreeWidgetItem* treeItem = new QTreeWidgetItem( parentTreeItem, QStringList(str) );
            treeItem->setCheckState(0, Qt::Checked);
            mReportCategoriesCheckBoxList.push_back( treeItem );
        }
    }

    // Create Label radio buttons
	count = Category::getLabelCount();
    for( int i = 0; i < count; i++ )
    {
        QString str = Category::getLabelText( (Category::LabelIdType)i );
        TripleRadioButton* radioButton = new TripleRadioButton( str, mUi->transactionLabelsGroupBox );
        connect( radioButton, SIGNAL(buttonClicked()), this, SLOT(handleTransactionLabelsCheckBox_clicked()) );
        mUi->transactionLabelsGroupBox->layout()->addWidget( radioButton );
        mTransactionLabelsButtonList.push_back( radioButton );

        radioButton = new TripleRadioButton( str, mUi->reportLabelsGroupBox );
        connect( radioButton, SIGNAL(buttonClicked()), this, SLOT(handleReportLabelsCheckBox_clicked()) );
        mUi->reportLabelsGroupBox->layout()->addWidget( radioButton );
        mReportLabelsButtonList.push_back( radioButton );
    }

    // Init Account Sort Combo box
    QStringList comboList;
    comboList.push_back( sSortAccountByName );
    comboList.push_back( sSortAccountByBalance );
    comboList.push_back( sSortAccountByOpenDate );
    mUi->overviewSortAccountsComboBox->addItems( comboList );
    mUi->overviewSortAccountsComboBox->setCurrentIndex( 0 );

    // Update date combo boxes
    comboList.clear();
    comboList.push_back( sDateInterval1MonthStr );
    comboList.push_back( sDateInterval3MonthStr );
    comboList.push_back( sDateInterval6MonthStr );
    comboList.push_back( sDateInterval1YearStr  );
    mUi->reportDateIntervalComboBox->addItems( comboList );
    mUi->reportDateIntervalComboBox->setCurrentIndex( comboList.indexOf(sDateInterval1MonthStr) );

    // Set up Report Pie Chart Combo boxes
    comboList.clear();
    comboList.push_back( sSortChartByBalance );
    comboList.push_back( sSortChartByName );
    mUi->mReportAssetDebtComboBox->addItems( comboList );
    mUi->mReportAssetDebtComboBox->setCurrentIndex( 0 );
    mUi->mReportIncomeExpenseComboBox->addItems( comboList );
    mUi->mReportIncomeExpenseComboBox->setCurrentIndex( 0 );
    mUi->mReportSubIncomeExpenseComboBox->addItems( comboList );
    mUi->mReportSubIncomeExpenseComboBox->setCurrentIndex( 0 );

    // Init report graphs, table and pie charts
    mUi->reportNetIncomeTab->layout()->addWidget( &mReportNetIncomeGraph );
    mUi->reportNetWorthTab->layout()->addWidget( &mReportNetWorthGraph );
    mUi->reportAccountBalanceTab->layout()->addWidget( &mReportAccountBalanceGraph );
    mReportNetIncomeGraph.setShowNetIncome( mUi->mReportShowNetIncomeCheckBox->isChecked(), false );
    mReportNetIncomeGraph.setShowTransfers( mUi->mReportShowTransfersCheckBox->isChecked(), false );

    connect( &mReportNetIncomeGraph, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    connect( &mReportNetWorthGraph, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    connect( &mReportAccountBalanceGraph, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    connect( &mReportNetIncomeGraph, SIGNAL(reportDateSelected(QDate,QDate)), this, SLOT(handleShowReportByDate(QDate,QDate)) );
    connect( &mReportNetWorthGraph, SIGNAL(reportDateSelected(QDate,QDate)), this, SLOT(handleShowReportByDate(QDate,QDate)) );
    connect( &mReportAccountBalanceGraph, SIGNAL(reportDateSelected(QDate,QDate)), this, SLOT(handleShowReportByDate(QDate,QDate)) );
    connect( &mReportTableView, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    mUi->reportListTab->layout()->addWidget( &mReportTableView );
    mUi->reportAssetGroupBox->layout()->addWidget( &mAssetsPieChart );
    mUi->reportDebtGroupBox->layout()->addWidget( &mDebtsPieChart );
    mUi->reportIncomeParentGroupBox->layout()->addWidget( &mIncomeParentPieChart );
    mUi->reportExpenseParentGroupBox->layout()->addWidget( &mExpenseParentPieChart );
    mUi->reportIncomeSubGroupBox->layout()->addWidget( &mIncomeSubPieChart );
    mUi->reportExpenseSubGroupBox->layout()->addWidget( &mExpenseSubPieChart );
    mPieChartList.push_back( &mAssetsPieChart );
    mPieChartList.push_back( &mDebtsPieChart );
    mPieChartList.push_back( &mIncomeParentPieChart );
    mPieChartList.push_back( &mExpenseParentPieChart );
    mPieChartList.push_back( &mIncomeSubPieChart );
    mPieChartList.push_back( &mExpenseSubPieChart );
    mAssetsPieChart.setChartType( ReportPieChart::ASSET_BY_ACCOUNT );
    mDebtsPieChart.setChartType( ReportPieChart::DEBT_BY_ACCOUNT );
    mIncomeParentPieChart.setChartType( ReportPieChart::INCOME_BY_CATEGORY );
    mExpenseParentPieChart.setChartType( ReportPieChart::EXPENSE_BY_CATEGORY );
    mIncomeSubPieChart.setChartType( ReportPieChart::INCOME_BY_CATEGORY );
    mExpenseSubPieChart.setChartType( ReportPieChart::EXPENSE_BY_CATEGORY );
    mIncomeParentPieChart.setGroupCategories( true );
    mExpenseParentPieChart.setGroupCategories( true );
    mIncomeParentPieChart.setShowTransfers( mUi->mReportShowTransfersCheckBox->isChecked(), false );
    mExpenseParentPieChart.setShowTransfers( mUi->mReportShowTransfersCheckBox->isChecked(), false );
    mIncomeSubPieChart.setShowTransfers( mUi->mReportShowTransfersCheckBox->isChecked(), false );
    mExpenseSubPieChart.setShowTransfers( mUi->mReportShowTransfersCheckBox->isChecked(), false );
    for( int i = 0; i < mPieChartList.size(); i++ )
    {
        connect( mPieChartList[i], SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    }
} // TransactionManager::init()

//----------------------------------------------------------------------------
// deInit
//----------------------------------------------------------------------------
void TransactionManager::deInit()
{
    clearData();
	int count = Category::getCategoryCount();
    for( int i = 0; i < count; i++ )
    {
        delete mTransactionCategoriesCheckBoxList[i];
        delete mReportCategoriesCheckBoxList[i];
    }
	count = Category::getLabelCount();
    for( int i = 0; i < count; i++ )
    {
        delete mTransactionLabelsButtonList[i];
        delete mReportLabelsButtonList[i];
    }
} // TransactionManager::deInit()

//----------------------------------------------------------------------------
// clearData
//----------------------------------------------------------------------------
void TransactionManager::clearData()
{
    // Clear account data
    mFileName.clear();
    Account::clearAccountList();
    for( int i = 0; i < sTransactionList.size(); i++ )
    {
        delete sTransactionList[i];
    }
    for( int i = 0; i < sMonthList.size(); i++ )
    {
        delete sMonthList[i];
    }
    sTransactionList.clear();
    sMonthList.clear();
    sFileContents.clear();
    sFirstTransactionDate = cDefaultStartDate;
    sLastTransactionDate = cDefaultEndDate;
    sCategoriesEnabledList.fill( false );
    sLabelsEnabledList.fill( false );
    Logger::clearLog();
} // TransactionManager::clearData()

//----------------------------------------------------------------------------
// Handle action
//----------------------------------------------------------------------------
void TransactionManager::on_actionExit_triggered()
{
    on_actionClose_triggered();
    qApp->quit();
} // TransactionManager::on_actionExit_triggered()

//----------------------------------------------------------------------------
// Handle action
//----------------------------------------------------------------------------
void TransactionManager::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName( this, tr("Open File"), QString(), tr("Csv Files (*.csv);;All Files (*.*)") );
    if( !fileName.isEmpty() )
    {
        QFile file(fileName);
        if( !file.open( QIODevice::ReadOnly ) )
        {
            QMessageBox::critical( this, tr("Error"), tr("Could not open file") );
            return;
        }

        // Clear data
        clearData();

        // Parse file contents
        mFileName = fileName;
        QTextStream inStream( &file );
        Parser::parseFile( inStream );
        file.close();

        // Update ui contents
        updateUI();
    }
} // TransactionManager::on_actionOpen_triggered()

//----------------------------------------------------------------------------
// Handle action
//----------------------------------------------------------------------------
void TransactionManager::on_actionClose_triggered()
{
    if( !mFileName.isEmpty() )
    {
        // Clear data and update ui contents
        clearData();
        updateUI();
    }
} // TransactionManager::on_actionClose_triggered()

//----------------------------------------------------------------------------
// on_actionSave_triggered
//----------------------------------------------------------------------------
void TransactionManager::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName( this, tr("Save File"), QString(), tr("Csv Files (*.csv);;All Files (*.*)") );
    if( !fileName.isEmpty() )
    {
        QFile file(fileName);
        if( !file.open( QIODevice::WriteOnly ) )
        {
            // error message
        }
        else
        {
            //QTextStream stream( &file );
            //stream << mUi->textEdit->toPlainText();
            //stream.flush();
            file.close();
        }
    }
} // TransactionManager::on_actionSave_triggered()

//----------------------------------------------------------------------------
// on_actionFileInputConfig_triggered
//----------------------------------------------------------------------------
void TransactionManager::on_actionFileInputConfig_triggered()
{
    FileConfigDialog dialog;
    dialog.exec();

    // Update status label
    mStatusConfigLabel.setText( "Loaded Config: " + Parser::sPresetConfigList[Parser::sPresetSelected].mName );
} // TransactionManager::on_actionFileInputConfig_triggered()

//----------------------------------------------------------------------------
// on_actionDisplayLog_triggered
//----------------------------------------------------------------------------
void TransactionManager::on_actionDisplayAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setText( "Transaction Manager\nAuthor: Obinna Modum (tallest4eva)\nVersion: " + sVersionStr + "\nQt Version: " + QT_VERSION_STR );
    msgBox.setIcon( QMessageBox::Information );
    msgBox.exec();
} // TransactionManager::on_actionDisplayLog_triggered()

//----------------------------------------------------------------------------
// on_actionDisplayFile_triggered
//----------------------------------------------------------------------------
void TransactionManager::on_actionDisplayFile_triggered()
{
    DisplayDialog dialog;
    dialog.setWindowTitle( "Display File Contents" );
    dialog.setDisplay( sFileContents );
    dialog.exec();
} // TransactionManager::on_actionDisplayFile_triggered()

//----------------------------------------------------------------------------
// on_actionDisplayLog_triggered
//----------------------------------------------------------------------------
void TransactionManager::on_actionDisplayLog_triggered()
{
    DisplayDialog dialog;
    dialog.setWindowTitle( "Display Log" );
    dialog.setDisplay( Logger::sLogList );
    dialog.exec();
} // TransactionManager::on_actionDisplayLog_triggered()

//----------------------------------------------------------------------------
// on_actionDisplayHelp_triggered
//----------------------------------------------------------------------------
void TransactionManager::on_actionDisplayHelp_triggered()
{
    QFile file("help.html");
    QStringList fileContents;
    if( file.open( QIODevice::ReadOnly ) )
    {
        QTextStream inStream( &file );
        while( !inStream.atEnd() )
        {
            fileContents.push_back( inStream.readLine() );
        }
        file.close();
    }
    DisplayDialog dialog;
    dialog.setWindowTitle( "Help" );
    dialog.setDisplay( fileContents, "Help file \"help.html\" not found." );
    dialog.resize( 900, 500 );
    dialog.exec();
} // TransactionManager::on_actionDisplayLog_triggered()

//----------------------------------------------------------------------------
// updateUI
//----------------------------------------------------------------------------
void TransactionManager::updateUI()
{
    // Update ui elements, menu and status
    mUi->actionClose->setEnabled( false );
    mUi->actionDisplayFile->setEnabled( false );
    mStatusFileLabel.setText("");

    if( !mFileName.isEmpty() )
    {
        mUi->actionClose->setEnabled( true );
        mUi->actionDisplayFile->setEnabled( true );
        mStatusFileLabel.setText( "File Opened: " + mFileName );
    }

    updateOverviewTab();
    resetTransactionsTab();
    resetReportsTab();

} // TransactionManager::updateUI()

//----------------------------------------------------------------------------
// Update Overview Tab
//----------------------------------------------------------------------------
void TransactionManager::updateOverviewTab()
{
    // Update overview values
    if( !mFileName.isEmpty() )
    {
        QString str = QString::asprintf(
            "%d  (Open: %d | <font color=\"grey\">Closed: %d</font>)",
            Account::sAccountList.size(),
            Account::sAccountOpenList.size(),
            Account::sAccountList.size() - Account::sAccountOpenList.size() );
        mUi->overviewNumberOfAccountValue->setText( str );
        mUi->overviewNumberOfTransactionsValue->setNum( sTransactionList.size() );
        float totalBalance = Account::getTotalAccountBalance();
        mUi->overviewNetWorthValue->setText( Transaction::getAmountText( totalBalance, true ) );
        mUi->overviewFirstDateValue->setText( sFirstTransactionDate.toString("yyyy-MM-dd") );
        mUi->overviewLastDateValue->setText( sLastTransactionDate.toString("yyyy-MM-dd") );
        mUi->overviewSortAccountsComboBox->setEnabled( true );
        mUi->overviewSortAccountsComboBox->setCurrentIndex( 0 );
    }
    else
    {
        mUi->overviewNumberOfAccountValue->setText("--");
        mUi->overviewNumberOfTransactionsValue->setText("--");
        mUi->overviewNetWorthValue->setText("--");
        mUi->overviewFirstDateValue->setText("--");
        mUi->overviewLastDateValue->setText("--");
        mUi->overviewSortAccountsComboBox->setEnabled( false );
        mUi->overviewSortAccountsComboBox->setCurrentIndex( 0 );
    }

    // Update accounts list
    updateAccountsList();
} // TransactionManager::updateOverviewTab()

//----------------------------------------------------------------------------
// update Accounts List
//----------------------------------------------------------------------------
void TransactionManager::updateAccountsList()
{
    // Update overview account list
    mUi->overviewAccountList->clear();
    // End if account list is empty
    if( Account::sAccountList.size() == 0 ){ return; }

    bool showClosed = mUi->overviewShowClosedAccountsCheckBox->isChecked();

    // Sort Account list
    QList<Account*> accountList = Account::sAccountList;
    QString sortBy = mUi->overviewSortAccountsComboBox->currentText();
    if( sortBy == sSortAccountByName )          { qSort( accountList.begin(), accountList.end(), Account::accountSortByNameLessThan ); }
    else if( sortBy == sSortAccountByBalance )  { qSort( accountList.begin(), accountList.end(), Account::accountSortByBalanceLessThan ); }
    else if( sortBy == sSortAccountByOpenDate ) { qSort( accountList.begin(), accountList.end(), Account::accountSortByOpenDateLessThan ); }

    for( int i = 0; i < accountList.size(); i++ )
    {
        if( !accountList[i]->isClosed() || showClosed )
        {
            QListWidgetItem* listItem = new QListWidgetItem();
            listItem->setSizeHint( QSize(0,70) );
            mUi->overviewAccountList->addItem( listItem );

            OverviewAccountListItem* item = new OverviewAccountListItem();
            item->setAccount( accountList[i] );
            mUi->overviewAccountList->setItemWidget( listItem, item );
            item->show();
        }
    }
} // TransactionManager::updateAccountsList()

//----------------------------------------------------------------------------
// Reset Transactions Tab
//----------------------------------------------------------------------------
void TransactionManager::resetTransactionsTab()
{
    bool fileLoaded = !mFileName.isEmpty();

    // Clear transactions tab
    mUi->transactionToolBox->setItemText( mUi->transactionToolBox->indexOf(mUi->transactionAccountToolBox), sToolboxAccountsStr );
    mUi->transactionToolBox->setItemText( mUi->transactionToolBox->indexOf(mUi->transactionCategoriesToolBox), sToolboxCategoriesStr );
    mUi->transactionToolBox->setItemText( mUi->transactionToolBox->indexOf(mUi->transactionLabelsToolBox), sToolboxLabelsStr );
    mUi->transactionToolBox->setItemText( mUi->transactionToolBox->indexOf(mUi->transactionDateToolBox), sToolboxDatesStr );
    for( int i = 0; i < mTransactionAccountsCheckBoxList.size(); i++ )
    {
        mUi->transactionAccountGroupBox->layout()->removeWidget( mTransactionAccountsCheckBoxList[i] );
        delete mTransactionAccountsCheckBoxList[i];
    }
    mTransactionAccountsCheckBoxList.clear();
    for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
    {
        mTransactionCategoriesCheckBoxList[i]->setDisabled( true );
    }
    for( int i = 0; i < mTransactionLabelsButtonList.size(); i++ )
    {
        mTransactionLabelsButtonList[i]->setDisabled( true );
    }

    mUi->transactionAllAccountsCheckBox->setDisabled( !fileLoaded );
    mUi->transactionOpenAccountsCheckBox->setDisabled( !fileLoaded );
    mUi->transactionAllCategoriesCheckBox->setDisabled( !fileLoaded );
    mUi->transactionIncomeCategoriesCheckBox->setDisabled( !fileLoaded );
    mUi->transactionExpenseCategoriesCheckBox->setDisabled( !fileLoaded );
    mUi->transactionTransferCategoriesCheckBox->setDisabled( !fileLoaded );
    mUi->transactionAllLabelsCheckBox->setDisabled( !fileLoaded );

    mUi->transactionSelectButton->setEnabled( fileLoaded );
    mUi->transactionShowInReportsButton->setEnabled( fileLoaded );
    mUi->transactionAllButton->setEnabled( fileLoaded );
    mUi->transactionSearchTextLineEdit->setEnabled( fileLoaded );
    mUi->transactionSearchButton->setEnabled( fileLoaded );
    mUi->transactionSearchClearButton->setEnabled( fileLoaded );

    mUi->transactionStartDateEdit->setDateRange( sFirstTransactionDate, sLastTransactionDate );
    mUi->transactionStartDateEdit->setDate( sFirstTransactionDate );
    mUi->transactionStartDateEdit->setDisabled( true );
    mUi->transactionEndDateEdit->setDateRange( sFirstTransactionDate, sLastTransactionDate );
    mUi->transactionEndDateEdit->setDate( sLastTransactionDate );
    mUi->transactionEndDateEdit->setDisabled( true );
    mUi->transactionDateComboBox->clear();
    mUi->transactionDateComboBox->addItem( sDateAllTimeStr );
    mUi->transactionDateComboBox->setCurrentIndex( 0 );
    mUi->transactionDateComboBox->setEnabled( fileLoaded );
    mUi->transactionDisplayCreditValue->setText("--");
    mUi->transactionDisplayDebitValue->setText("--");
    mUi->transactionDisplayNetValue->setText("--");

    // Update transactions tab
    if( fileLoaded )
    {
        // Create transaction tab check boxes
        for( int i = 0; i < Account::sAccountList.size(); i++ )
        {
            QCheckBox* checkbox = new QCheckBox( Account::sAccountList[i]->getName(), mUi->transactionAccountGroupBox );
            checkbox->setChecked( true );
            connect( checkbox, SIGNAL(clicked(bool)), this, SLOT(handleTransactionAccountsCheckBox_clicked(bool)) );
            mUi->transactionAccountGroupBox->layout()->addWidget( checkbox );
            mTransactionAccountsCheckBoxList.push_back( checkbox );
        }
        for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
        {
            mTransactionCategoriesCheckBoxList[i]->setDisabled( !sCategoriesEnabledList[i] );
        }
        for( int i = 0; i < mTransactionLabelsButtonList.size(); i++ )
        {
            mTransactionLabelsButtonList[i]->setDisabled( !sLabelsEnabledList[i] );
        }
        mUi->transactionDateComboBox->addItems( getDateComboBoxList( QDate::currentDate() ) );
    }

    // Init table
    mTransactionTableView.clear();

    // Update transaction table
    updateTransactionsTab();
} // TransactionManager::resetTransactionsTab()

//----------------------------------------------------------------------------
// Update Transactions Tab
//----------------------------------------------------------------------------
void TransactionManager::updateTransactionsTab()
{
    if( !mFileName.isEmpty() )
    {
        mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
        updateFilterToolBox( TRANSACTION_TAB, TOOLS_ACCOUNTS | TOOLS_CATEGORIES | TOOLS_LABELS, mTransactionFilter );
        mTransactionTableView.setTransactionFilter( mTransactionFilter );
        mTransactionTableView.resort();

        // Update tool box text
        QString str = (mTransactionFilter.allAccountsSelected()) ? ": All" : ": Some";
        mUi->transactionToolBox->setItemText( mUi->transactionToolBox->indexOf(mUi->transactionAccountToolBox), sToolboxAccountsStr + str );
        str = (mTransactionFilter.allCategoriesSelected()) ? ": All" : ": Some";
        mUi->transactionToolBox->setItemText( mUi->transactionToolBox->indexOf(mUi->transactionCategoriesToolBox), sToolboxCategoriesStr + str );
        str = (mTransactionFilter.allLabelsSelected()) ? ": All" : ": Some";
        mUi->transactionToolBox->setItemText( mUi->transactionToolBox->indexOf(mUi->transactionLabelsToolBox), sToolboxLabelsStr + str );
        str = (mTransactionFilter.mDatesAll) ? ": All" : ": Some";
        mUi->transactionToolBox->setItemText( mUi->transactionToolBox->indexOf(mUi->transactionDateToolBox), sToolboxDatesStr + str );
        if( mUi->transactionDateComboBox->currentText() == sDateCustomStr )
        {
            mUi->transactionStartDateEdit->setDisabled( false );
            mUi->transactionEndDateEdit->setDisabled( false );
        }
        else
        {
            mUi->transactionStartDateEdit->setDisabled( true );
            mUi->transactionEndDateEdit->setDisabled( true );
        }

        // Update transaction display values
        str = "<font color=\"green\">" + Transaction::getAmountText( mTransactionTableView.getTotalCredit() ) + "</font>";
        mUi->transactionDisplayCreditValue->setText( str );
        str = "<font color=\"red\">" + Transaction::getAmountText( mTransactionTableView.getTotalDebit() ) + "</font>";
        mUi->transactionDisplayDebitValue->setText( str );
        float netAmount = mTransactionTableView.getNetAmount();
        str = Transaction::getAmountText( netAmount );
        if( netAmount != 0 )
        {
            str.prepend( (netAmount > 0) ? "<font color=\"green\">" : "<font color=\"red\">" );
            str.append( "</font>" );
        }
        mUi->transactionDisplayNetValue->setText( str );
    }
    else
    {
        mTransactionFilter = Transaction::FilterType();
        updateFilterToolBox( TRANSACTION_TAB, TOOLS_ACCOUNTS | TOOLS_CATEGORIES | TOOLS_LABELS, mTransactionFilter );
        mTransactionTableView.clear();
    }
} // TransactionManager::updateTransactionsTab()

//----------------------------------------------------------------------------
// Reset Reports Tab
//----------------------------------------------------------------------------
void TransactionManager::resetReportsTab()
{
    bool fileLoaded = !mFileName.isEmpty();

    // Clear reports tab
    mUi->reportToolBox->setItemText( mUi->reportToolBox->indexOf(mUi->reportAccountToolBox), sToolboxAccountsStr );
    mUi->reportToolBox->setItemText( mUi->reportToolBox->indexOf(mUi->reportCategoriesToolBox), sToolboxCategoriesStr );
    mUi->reportToolBox->setItemText( mUi->reportToolBox->indexOf(mUi->reportLabelsToolBox), sToolboxLabelsStr );
    mUi->reportToolBox->setItemText( mUi->reportToolBox->indexOf(mUi->reportDateToolBox), sToolboxDatesStr );
    for( int i = 0; i < mReportAccountsCheckBoxList.size(); i++ )
    {
        mUi->reportAccountGroupBox->layout()->removeWidget( mReportAccountsCheckBoxList[i] );
        delete mReportAccountsCheckBoxList[i];
    }
    mReportAccountsCheckBoxList.clear();

    for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
    {
        mReportCategoriesCheckBoxList[i]->setDisabled( true );
    }
    for( int i = 0; i < mReportLabelsButtonList.size(); i++ )
    {
        mReportLabelsButtonList[i]->setDisabled( true );
    }
    mUi->reportAllAccountsCheckBox->setDisabled( !fileLoaded );
    mUi->reportOpenAccountsCheckBox->setDisabled( !fileLoaded );
    mUi->reportAllCategoriesCheckBox->setDisabled( !fileLoaded );
    mUi->reportIncomeCategoriesCheckBox->setDisabled( !fileLoaded );
    mUi->reportExpenseCategoriesCheckBox->setDisabled( !fileLoaded );
    mUi->reportTransferCategoriesCheckBox->setDisabled( !fileLoaded );
    mUi->reportAllLabelsCheckBox->setDisabled( !fileLoaded );
    mUi->mReportShowNetIncomeCheckBox->setDisabled( !fileLoaded );
    mUi->mReportShowTransfersCheckBox->setDisabled( !fileLoaded );

    mUi->reportSelectButton->setEnabled( fileLoaded );
    mUi->reportShowInTransactionsButton->setEnabled( fileLoaded );
    mUi->reportAllButton->setEnabled( fileLoaded );
    mUi->mReportAssetDebtComboBox->setEnabled( fileLoaded );
    mUi->mReportAssetDebtComboBox->setCurrentIndex( 0 );
    mUi->mReportIncomeExpenseComboBox->setEnabled( fileLoaded );
    mUi->mReportIncomeExpenseComboBox->setCurrentIndex( 0 );
    mUi->mReportSubIncomeExpenseComboBox->setEnabled( fileLoaded );
    mUi->mReportSubIncomeExpenseComboBox->setCurrentIndex( 0 );

    mUi->reportStartDateEdit->setDateRange( sFirstTransactionDate, sLastTransactionDate );
    mUi->reportStartDateEdit->setDate( sFirstTransactionDate );
    mUi->reportStartDateEdit->setDisabled( true );
    mUi->reportEndDateEdit->setDateRange( sFirstTransactionDate, sLastTransactionDate );
    mUi->reportEndDateEdit->setDate( sLastTransactionDate );
    mUi->reportEndDateEdit->setDisabled( true );
    mUi->reportDateComboBox->clear();
    mUi->reportDateComboBox->addItem( sDateAllTimeStr );
    mUi->reportDateComboBox->setCurrentIndex( 0 );
    mUi->reportDateComboBox->setEnabled( fileLoaded );
    mUi->reportDateIntervalComboBox->setEnabled( fileLoaded );

    // Update reports tab
    if( fileLoaded )
    {
        // Create reports tab check boxes
        for( int i = 0; i < Account::sAccountList.size(); i++ )
        {
            QCheckBox* checkbox = new QCheckBox( Account::sAccountList[i]->getName(), mUi->reportAccountGroupBox );
            connect( checkbox, SIGNAL(clicked(bool)), this, SLOT(handleReportAccountsCheckBox_clicked(bool)) );
            checkbox->setChecked( true );
            mUi->reportAccountGroupBox->layout()->addWidget( checkbox );
            mReportAccountsCheckBoxList.push_back( checkbox );
        }
        for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
        {
            mReportCategoriesCheckBoxList[i]->setDisabled( !sCategoriesEnabledList[i] );
        }
        for( int i = 0; i < mReportLabelsButtonList.size(); i++ )
        {
            mReportLabelsButtonList[i]->setDisabled( !sLabelsEnabledList[i] );
        }
        mUi->reportDateComboBox->addItems( getDateComboBoxList( QDate::currentDate() ) );
    }

    // Update reports
    updateReportsTab();
} // TransactionManager::resetReportsTab()

//----------------------------------------------------------------------------
// Update Reports Tab
//----------------------------------------------------------------------------
void TransactionManager::updateReportsTab()
{
    if( !mFileName.isEmpty() )
    {
        mReportFilter = getTransactionFilter( REPORT_TAB );
        updateFilterToolBox( REPORT_TAB, TOOLS_ACCOUNTS | TOOLS_CATEGORIES | TOOLS_LABELS, mReportFilter );
        mReportNetIncomeGraph.setTransactionFilter( mReportFilter );
        mReportNetWorthGraph.setTransactionFilter( mReportFilter );
        mReportAccountBalanceGraph.setTransactionFilter( mReportFilter );
        mReportTableView.setTransactionFilter( mReportFilter );
        for( int i = 0; i < mPieChartList.size(); i++ )
        {
            mPieChartList[i]->setTransactionFilter( mReportFilter );
        }

        // Update tool box text
        QString str = (mReportFilter.allAccountsSelected()) ? ": All" : ": Some";
        mUi->reportToolBox->setItemText( mUi->reportToolBox->indexOf(mUi->reportAccountToolBox), sToolboxAccountsStr + str );
        str = (mReportFilter.allCategoriesSelected()) ? ": All" : ": Some";
        mUi->reportToolBox->setItemText( mUi->reportToolBox->indexOf(mUi->reportCategoriesToolBox), sToolboxCategoriesStr + str );
        str = (mReportFilter.allLabelsSelected()) ? ": All" : ": Some";
        mUi->reportToolBox->setItemText( mUi->reportToolBox->indexOf(mUi->reportLabelsToolBox), sToolboxLabelsStr + str );
        str = (mReportFilter.mDatesAll) ? ": All" : ": Some";
        mUi->reportToolBox->setItemText( mUi->reportToolBox->indexOf(mUi->reportDateToolBox), sToolboxDatesStr + str );
        if( mUi->reportDateComboBox->currentText() == sDateCustomStr )
        {
            mUi->reportStartDateEdit->setDisabled( false );
            mUi->reportEndDateEdit->setDisabled( false );
        }
        else
        {
            mUi->reportStartDateEdit->setDisabled( true );
            mUi->reportEndDateEdit->setDisabled( true );
        }
    }
    else
    {
        mReportFilter = Transaction::FilterType();
        updateFilterToolBox( REPORT_TAB, TOOLS_ACCOUNTS | TOOLS_CATEGORIES | TOOLS_LABELS, mReportFilter );
        mReportNetIncomeGraph.clear();
        mReportNetWorthGraph.clear();
        mReportAccountBalanceGraph.clear();
        mReportTableView.clear();
        for( int i = 0; i < mPieChartList.size(); i++ )
        {
            mPieChartList[i]->clear();
        }
    }
} // TransactionManager::updateReportsTab()

//----------------------------------------------------------------------------
// Get Filter
//----------------------------------------------------------------------------
Transaction::FilterType TransactionManager::getTransactionFilter( TabType aTabType )
{
    QList<QCheckBox*>& accountsCheckBoxList = ( aTabType == TRANSACTION_TAB ) ? mTransactionAccountsCheckBoxList : mReportAccountsCheckBoxList;
    QList<QTreeWidgetItem*>& categoriesCheckBoxList = ( aTabType == TRANSACTION_TAB ) ? mTransactionCategoriesCheckBoxList : mReportCategoriesCheckBoxList;
    QList<TripleRadioButton*>& labelsRadioButtonList = ( aTabType == TRANSACTION_TAB ) ? mTransactionLabelsButtonList : mReportLabelsButtonList;

    Transaction::FilterType filter(false);
    switch( aTabType )
    {
    case TRANSACTION_TAB:
        filter.selectDateRange( mUi->transactionStartDateEdit->date(), mUi->transactionEndDateEdit->date() );
        filter.mSearchStr = mUi->transactionSearchTextLineEdit->text();
        if( mUi->transactionToolBox->currentWidget() == mUi->transactionAccountToolBox ){ filter.showToolBox = "account"; }
        else if( mUi->transactionToolBox->currentWidget() == mUi->transactionCategoriesToolBox ){ filter.showToolBox = "categories"; }
        else if( mUi->transactionToolBox->currentWidget() == mUi->transactionLabelsToolBox ){ filter.showToolBox = "labels"; }
        else if( mUi->transactionToolBox->currentWidget() == mUi->transactionDateToolBox ){ filter.showToolBox = "dates"; }
        break;
    case REPORT_TAB:
    default:
        filter.selectDateRange( mUi->reportStartDateEdit->date(), mUi->reportEndDateEdit->date() );
        if( mUi->reportToolBox->currentWidget() == mUi->reportAccountToolBox ){ filter.showToolBox = "account"; }
        else if( mUi->reportToolBox->currentWidget() == mUi->reportCategoriesToolBox ){ filter.showToolBox = "categories"; }
        else if( mUi->reportToolBox->currentWidget() == mUi->reportLabelsToolBox ){ filter.showToolBox = "labels"; }
        else if( mUi->reportToolBox->currentWidget() == mUi->reportDateToolBox ){ filter.showToolBox = "dates"; }
        break;
    }

    // Get account filter
    bool accountsAll = true;
    for( int i = 0; i < accountsCheckBoxList.size() && i < filter.mAccountList.size(); i++ )
    {
        filter.mAccountList[i] = accountsCheckBoxList[i]->isChecked();
        accountsAll &= filter.mAccountList[i];
    }
    filter.mAccountsAll = accountsAll;

    // Get categories filter
    bool categoriesAll = true;
    for( int i = 0; i < categoriesCheckBoxList.size(); i++ )
    {
        filter.mCategoryList[i] = ( categoriesCheckBoxList[i]->checkState(0) == Qt::Checked );
        categoriesAll &= filter.mCategoryList[i];
    }
    filter.mCategoriesAll = categoriesAll;

    // Get labels filter
    bool labelsAll = true;
    for( int i = 0; i < labelsRadioButtonList.size(); i++ )
    {
        filter.mLabelList[i] = labelsRadioButtonList[i]->getMatchType();
        if( filter.mLabelList[i] != Transaction::MATCH ){ labelsAll = false; }
    }
    filter.mLabelsAll = labelsAll;

    return filter;
} // TransactionManager::getTransactionFilter()

//----------------------------------------------------------------------------
// Handle Parent Categories Check Box Clicked
//----------------------------------------------------------------------------
void TransactionManager::handleParentCategoriesCheckBoxClicked( QTreeWidgetItem* aItem, int aColumn )
{
    int count = aItem->childCount();
    for( int i = 0; i < count; i++ )
    {
        aItem->child( i )->setCheckState( aColumn, aItem->checkState( aColumn ) );
    }
    if( aItem->treeWidget() == &mTransactionCategoriesTreeWidget )
    {
        mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
        updateFilterToolBox( TRANSACTION_TAB, TOOLS_CATEGORIES, mTransactionFilter );
    }
    else if(  aItem->treeWidget() == &mReportCategoriesTreeWidget )
    {
        mReportFilter = getTransactionFilter( REPORT_TAB );
        updateFilterToolBox( REPORT_TAB, TOOLS_CATEGORIES, mReportFilter );
    }
}

//----------------------------------------------------------------------------
// Handle Show Transaction By Date
//----------------------------------------------------------------------------
void TransactionManager::handleShowTransactionByFilter( const Transaction::FilterType& aFilter )
{
    // Switch to transaction tab
    mUi->tabWidget->setCurrentWidget( mUi->transactionsTab );

    // Display the correct tool box
    if( aFilter.showToolBox == "account" ){ mUi->transactionToolBox->setCurrentWidget( mUi->transactionAccountToolBox ); }
    else if( aFilter.showToolBox == "categories" ){ mUi->transactionToolBox->setCurrentWidget( mUi->transactionCategoriesToolBox ); }
    else if( aFilter.showToolBox == "labels" ){ mUi->transactionToolBox->setCurrentWidget( mUi->transactionLabelsToolBox ); }
    else if( aFilter.showToolBox == "dates" ){ mUi->transactionToolBox->setCurrentWidget( mUi->transactionDateToolBox ); }

    // Update checkboxes
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_ACCOUNTS | TOOLS_CATEGORIES | TOOLS_LABELS, aFilter );
    mUi->transactionStartDateEdit->setDate( ( aFilter.mDatesAll ) ? sFirstTransactionDate : aFilter.mStartDate );
    mUi->transactionEndDateEdit->setDate( ( aFilter.mDatesAll ) ? sLastTransactionDate : aFilter.mEndDate );
    mUi->transactionDateComboBox->setCurrentIndex( mUi->reportDateComboBox->findText( (aFilter.mDatesAll) ? sDateAllTimeStr : sDateCustomStr) );
    mUi->transactionSearchTextLineEdit->setText( aFilter.mSearchStr );
    on_transactionSelectButton_clicked();
} // TransactionManager::handleShowTransactionByFilter

//----------------------------------------------------------------------------
// Handle Show Report By Date
//----------------------------------------------------------------------------
void TransactionManager::handleShowReportByFilter( const Transaction::FilterType& aFilter )
{
    // Switch to report tab
    mUi->tabWidget->setCurrentWidget( mUi->reportTab );

    // Display the correct tool box
    if( aFilter.showToolBox == "account" ){ mUi->reportToolBox->setCurrentWidget( mUi->reportAccountToolBox ); }
    else if( aFilter.showToolBox == "categories" ){ mUi->reportToolBox->setCurrentWidget( mUi->reportCategoriesToolBox ); }
    else if( aFilter.showToolBox == "labels" ){ mUi->reportToolBox->setCurrentWidget( mUi->reportLabelsToolBox ); }
    else if( aFilter.showToolBox == "dates" ){ mUi->reportToolBox->setCurrentWidget( mUi->reportDateToolBox ); }

    // Update checkboxes
    updateFilterToolBox( REPORT_TAB, TOOLS_ACCOUNTS | TOOLS_CATEGORIES | TOOLS_LABELS, aFilter );
    mUi->reportStartDateEdit->setDate( ( aFilter.mDatesAll ) ? sFirstTransactionDate : aFilter.mStartDate );
    mUi->reportEndDateEdit->setDate( ( aFilter.mDatesAll ) ? sLastTransactionDate : aFilter.mEndDate );
    mUi->reportDateComboBox->setCurrentIndex( mUi->reportDateComboBox->findText(sDateCustomStr) );
    on_reportSelectButton_clicked();
} // TransactionManager::handleShowReportByFilter

//----------------------------------------------------------------------------
// Handle Show Report By Date
//----------------------------------------------------------------------------
void TransactionManager::handleShowReportByDate( const QDate& aStartDate, const QDate& aEndDate )
{
    // Switch to report tab
    mUi->tabWidget->setCurrentWidget( mUi->reportTab );
    mUi->reportToolBox->setCurrentWidget( mUi->reportDateToolBox );
    mUi->reportStartDateEdit->setDate( aStartDate );
    mUi->reportEndDateEdit->setDate( aEndDate );
    mUi->reportDateComboBox->setCurrentIndex( mUi->reportDateComboBox->findText(sDateCustomStr) );
    on_reportSelectButton_clicked();
} // TransactionManager::handleShowReportByDate()

//----------------------------------------------------------------------------
// updateAndApplyDates
//----------------------------------------------------------------------------
void TransactionManager::updateAndApplyDates( TabType aTabType, const QDate& aStartDate, const QDate& aEndDate )
{
    switch( aTabType )
    {
    case TRANSACTION_TAB:
        mUi->transactionStartDateEdit->setDate( ( sFirstTransactionDate > aStartDate ) ? sFirstTransactionDate : aStartDate );
        mUi->transactionEndDateEdit->setDate( ( sLastTransactionDate < aEndDate ) ? sLastTransactionDate : aEndDate );
        on_transactionSelectButton_clicked();
        break;
    case REPORT_TAB:
        mUi->reportStartDateEdit->setDate( ( sFirstTransactionDate > aStartDate ) ? sFirstTransactionDate : aStartDate );
        mUi->reportEndDateEdit->setDate( ( sLastTransactionDate < aEndDate ) ? sLastTransactionDate : aEndDate );
        on_reportSelectButton_clicked();
    default:
        break;
    }
} // TransactionManager::updateAndApplyDates()

//----------------------------------------------------------------------------
// Update Check Boxes
//----------------------------------------------------------------------------
void TransactionManager::updateFilterToolBox( TabType aTabType, int aToolBoxType, const Transaction::FilterType& aFilter )
{
    QCheckBox* accountsAllCheckBox = NULL;
    QCheckBox* accountsOpenCheckBox = NULL;
    QCheckBox* categoriesAllCheckBoxList = NULL;
    QCheckBox* categoriesIncomeCheckBoxList = NULL;
    QCheckBox* categoriesExpenseCheckBoxList = NULL;
    QCheckBox* categoriesTransferCheckBoxList = NULL;
    QCheckBox* labelsAllCheckBox = NULL;
    QList<QCheckBox*>& accountsCheckBoxList = ( aTabType == TRANSACTION_TAB ) ? mTransactionAccountsCheckBoxList : mReportAccountsCheckBoxList;
    QList<QTreeWidgetItem*>& categoriesCheckBoxList = ( aTabType == TRANSACTION_TAB ) ? mTransactionCategoriesCheckBoxList : mReportCategoriesCheckBoxList;
    QList<TripleRadioButton*>& labelsRadioButtonList = ( aTabType == TRANSACTION_TAB ) ? mTransactionLabelsButtonList : mReportLabelsButtonList;

    switch( aTabType )
    {
    case TRANSACTION_TAB:
        accountsAllCheckBox = mUi->transactionAllAccountsCheckBox;
        accountsOpenCheckBox = mUi->transactionOpenAccountsCheckBox;
        categoriesAllCheckBoxList = mUi->transactionAllCategoriesCheckBox;
        categoriesIncomeCheckBoxList = mUi->transactionIncomeCategoriesCheckBox;
        categoriesExpenseCheckBoxList = mUi->transactionExpenseCategoriesCheckBox;
        categoriesTransferCheckBoxList = mUi->transactionTransferCategoriesCheckBox;
        labelsAllCheckBox = mUi->transactionAllLabelsCheckBox;
        break;
    case REPORT_TAB:
    default:
        accountsAllCheckBox = mUi->reportAllAccountsCheckBox;
        accountsOpenCheckBox = mUi->reportOpenAccountsCheckBox;
        categoriesAllCheckBoxList = mUi->reportAllCategoriesCheckBox;
        categoriesIncomeCheckBoxList = mUi->reportIncomeCategoriesCheckBox;
        categoriesExpenseCheckBoxList = mUi->reportExpenseCategoriesCheckBox;
        categoriesTransferCheckBoxList = mUi->reportTransferCategoriesCheckBox;
        labelsAllCheckBox = mUi->reportAllLabelsCheckBox;
        break;
    }

    if( aToolBoxType & TOOLS_ACCOUNTS )
    {
		bool selectAllOne = false;
		bool selectOpen = true;
		bool selectOpenOne = false;
		for( int i = 0; i < accountsCheckBoxList.size(); i++ )
		{
			bool checked = aFilter.mAccountList[i];
			accountsCheckBoxList[i]->setChecked( checked );
            if( Account::sAccountList[i]->isOpen() )
            {
                if( checked ){ selectOpenOne = true; } else{ selectOpen = false; }
            }
            if( checked ){ selectAllOne = true; }
		}
        accountsAllCheckBox->setCheckState( getCurrentCheckState( aFilter.allAccountsSelected(), selectAllOne ) );
        accountsOpenCheckBox->setCheckState( getCurrentCheckState( selectOpen, selectOpenOne ) );
    }
    if( aToolBoxType & TOOLS_CATEGORIES )
    {
		bool selectAllOne = false;
		bool selectIncome = true;
		bool selectIncomeOne = false;
		bool selectExpense = true;
		bool selectExpenseOne = false;
		bool selectTransfer = true;
		bool selectTransferOne = false;
        for( int i = 0; i < categoriesCheckBoxList.size(); i++ )
        {
			bool checked = aFilter.mCategoryList[i];
			categoriesCheckBoxList[i]->setCheckState( 0, checked ? Qt::Checked : Qt::Unchecked );
            Category::TransactionType transType = Category::getCategoryTransactionType( (Category::CategoryIdxType)i );
            switch( transType )
            {
            case Category::TRANSACTION_TYPE_INCOME:
                if( checked ){ selectIncomeOne = true; } else{ selectIncome = false; }
                break;
            case Category::TRANSACTION_TYPE_EXPENSE:
                if( checked ){ selectExpenseOne = true; } else{ selectExpense = false; }
                break;
            case Category::TRANSACTION_TYPE_TRANSFER:
                if( checked ){ selectTransferOne = true; } else{ selectTransfer = false; }
                break;
            default:
                break;
            }
            if( checked ){ selectAllOne = true; }
        }
        categoriesAllCheckBoxList->setCheckState( getCurrentCheckState(aFilter.allCategoriesSelected(), selectAllOne) );
        categoriesIncomeCheckBoxList->setCheckState( getCurrentCheckState(selectIncome, selectIncomeOne) );
        categoriesExpenseCheckBoxList->setCheckState( getCurrentCheckState(selectExpense, selectExpenseOne) );
        categoriesTransferCheckBoxList->setCheckState( getCurrentCheckState(selectTransfer, selectTransferOne) );
    }
    if( aToolBoxType & TOOLS_LABELS )
    {
		bool selectAllOne = false;
        for( int i = 0; i < labelsRadioButtonList.size(); i++ )
        {
            labelsRadioButtonList[i]->setMatchType( aFilter.mLabelList[i] );
            if( aFilter.mLabelList[i] == Transaction::MATCH ){ selectAllOne = true; }
        }
        labelsAllCheckBox->setCheckState( getCurrentCheckState(aFilter.allLabelsSelected(), selectAllOne) );
    }

} // TransactionManager::updateFilterToolBox()

//----------------------------------------------------------------------------
// Sort Account combo box activated
//----------------------------------------------------------------------------
void TransactionManager::on_overviewSortAccountsComboBox_activated( const QString& aText )
{
    Q_UNUSED(aText);
    updateAccountsList();
}

//----------------------------------------------------------------------------
// item double clicked
//----------------------------------------------------------------------------
void TransactionManager::on_overviewAccountList_itemDoubleClicked( QListWidgetItem* aItem )
{
    // Show Transactions with selected account
    OverviewAccountListItem* item = (OverviewAccountListItem*)mUi->overviewAccountList->itemWidget( aItem );
    if( item )
    {
        Transaction::FilterType filter = Transaction::FilterType();
        filter.showToolBox = "account";
        filter.selectAllAccounts( false );
        filter.mAccountList[ Account::getAccountIndex(item->getAccount()) ] = true;
        filter.mStartDate = sFirstTransactionDate;
        filter.mEndDate = sLastTransactionDate;
        handleShowTransactionByFilter( filter );
    }
} // TransactionManager::on_overviewAccountList_itemDoubleClicked()

//----------------------------------------------------------------------------
// item double clicked
//----------------------------------------------------------------------------
void TransactionManager::on_overviewAccountList_currentItemChanged( QListWidgetItem* aCurrentItem, QListWidgetItem* aPreviousItem )
{
    OverviewAccountListItem* item = (OverviewAccountListItem*)mUi->overviewAccountList->itemWidget( aCurrentItem );
    if( item )
    {
        item->setSelected( true );
    }
    item = (OverviewAccountListItem*)mUi->overviewAccountList->itemWidget( aPreviousItem );
    if( item )
    {
        item->setSelected( false );
    }
} // TransactionManager::on_overviewAccountList_itemDoubleClicked()

//----------------------------------------------------------------------------
// item show hidden check box clicked
//----------------------------------------------------------------------------
void TransactionManager::on_overviewShowClosedAccountsCheckBox_clicked( bool aChecked )
{
    // Update account list
    Q_UNUSED( aChecked );
    updateAccountsList();
} // TransactionManager::on_overviewShowClosedAccountsCheckBox_clicked()

//----------------------------------------------------------------------------
// Transaction date button slots
//----------------------------------------------------------------------------
void TransactionManager::on_transactionDateComboBox_activated( const QString& aText )
{
    QDate currentDate = QDate::currentDate();
    if( aText == sDateCustomStr )
    {
        mUi->transactionStartDateEdit->setDisabled( false );
        mUi->transactionEndDateEdit->setDisabled( false );
    }
    else if( aText == sDateThisYearStr ){ updateAndApplyDates( TRANSACTION_TAB, QDate(currentDate.year(),1,1), currentDate ); }
    else if( aText == sDate1YearStr )   { updateAndApplyDates( TRANSACTION_TAB, currentDate.addYears(-1), currentDate ); }
    else if( aText == sDate3YearStr )   { updateAndApplyDates( TRANSACTION_TAB, currentDate.addYears(-3), currentDate ); }
    else if( aText == sDate5YearStr )   { updateAndApplyDates( TRANSACTION_TAB, currentDate.addYears(-5), currentDate ); }
    else if( aText == sDate10YearStr )  { updateAndApplyDates( TRANSACTION_TAB, currentDate.addYears(-10), currentDate ); }
    else if( aText == sDateAllTimeStr ) { updateAndApplyDates( TRANSACTION_TAB, sFirstTransactionDate, sLastTransactionDate ); }
}

//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionAllButton_clicked()
{
    mTransactionFilter.selectAll();
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_ACCOUNTS | TOOLS_CATEGORIES | TOOLS_LABELS, mTransactionFilter );
    mUi->transactionStartDateEdit->setDate( sFirstTransactionDate );
    mUi->transactionEndDateEdit->setDate( sLastTransactionDate );
    mUi->transactionSearchTextLineEdit->clear();
    updateTransactionsTab();
}

//----------------------------------------------------------------------------
// on_transactionSelectButton_clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionSelectButton_clicked()
{
    updateTransactionsTab();
} // TransactionManager::on_transactionSelectButton_clicked()

//----------------------------------------------------------------------------
// on_transactionShowInReportsButton_clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionShowInReportsButton_clicked()
{
    updateTransactionsTab();
    handleShowReportByFilter( mTransactionFilter );
} // TransactionManager::on_transactionShowInReportsButton_clicked()

//----------------------------------------------------------------------------
// on_transactionSearchButton_clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionSearchButton_clicked()
{
    // Update transactions with new search field
    updateTransactionsTab();
} // TransactionManager::on_transactionSearchButton_clicked()

//----------------------------------------------------------------------------
// on_transactionSearchClearButton_clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionSearchClearButton_clicked()
{
    // Clears search field and update
    mUi->transactionSearchTextLineEdit->clear();
    updateTransactionsTab();
} // TransactionManager::on_transactionSearchClearButton_clicked()

//----------------------------------------------------------------------------
// on_transactionSearchTextLineEdit_returnPressed
//----------------------------------------------------------------------------
void TransactionManager::on_transactionSearchTextLineEdit_returnPressed()
{
    updateTransactionsTab();
}

//----------------------------------------------------------------------------
// on_transactionSearchTextLineEdit_textChanged
//----------------------------------------------------------------------------
void TransactionManager::on_transactionSearchTextLineEdit_textChanged( const QString& aText )
{
    Q_UNUSED( aText );
}

//----------------------------------------------------------------------------
// Transactions checkbox slots
//----------------------------------------------------------------------------
void TransactionManager::on_transactionAllAccountsCheckBox_clicked( bool aChecked )
{
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    mTransactionFilter.selectAllAccounts( aChecked );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_ACCOUNTS, mTransactionFilter );
}
void TransactionManager::on_transactionOpenAccountsCheckBox_clicked( bool aChecked )
{
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    mTransactionFilter.selectOpenAccounts( aChecked );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_ACCOUNTS, mTransactionFilter );
}
void TransactionManager::on_transactionAllCategoriesCheckBox_clicked( bool aChecked )
{
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    mTransactionFilter.selectAllCategories( aChecked );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_CATEGORIES, mTransactionFilter );
}
void TransactionManager::on_transactionIncomeCategoriesCheckBox_clicked( bool aChecked )
{
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    mTransactionFilter.selectCategories( aChecked, Category::TRANSACTION_TYPE_INCOME );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_CATEGORIES, mTransactionFilter );
}
void TransactionManager::on_transactionExpenseCategoriesCheckBox_clicked( bool aChecked )
{
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    mTransactionFilter.selectCategories( aChecked, Category::TRANSACTION_TYPE_EXPENSE );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_CATEGORIES, mTransactionFilter );
}
void TransactionManager::on_transactionTransferCategoriesCheckBox_clicked( bool aChecked )
{
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    mTransactionFilter.selectCategories( aChecked, Category::TRANSACTION_TYPE_TRANSFER );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_CATEGORIES, mTransactionFilter );
}
void TransactionManager::on_transactionAllLabelsCheckBox_clicked( bool aChecked )
{
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    mTransactionFilter.selectAllLabels( aChecked ? Transaction::MATCH : Transaction::DO_NOT_MATCH );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_LABELS, mTransactionFilter );
}

//----------------------------------------------------------------------------
// Transactions categories tree expand button
//----------------------------------------------------------------------------
void TransactionManager::on_mTransactionCategoriesTreeExpandButton_clicked()
{
    if( mUi->mTransactionCategoriesTreeExpandButton->text() == "Expand All" )
    {
        mTransactionCategoriesTreeWidget.expandAll();
        mUi->mTransactionCategoriesTreeExpandButton->setText( "Collapse All" );
    }
    else
    {
        mTransactionCategoriesTreeWidget.collapseAll();
        mUi->mTransactionCategoriesTreeExpandButton->setText( "Expand All" );
    }
}

//----------------------------------------------------------------------------
// Handle Transaction check boxes clicked
//----------------------------------------------------------------------------
void TransactionManager::handleTransactionAccountsCheckBox_clicked( bool aChecked )
{
    Q_UNUSED(aChecked);
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_ACCOUNTS, mTransactionFilter );
}
void TransactionManager::handleTransactionLabelsCheckBox_clicked()
{
    mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
    updateFilterToolBox( TRANSACTION_TAB, TOOLS_LABELS, mTransactionFilter );
}

//----------------------------------------------------------------------------
// Report date combo box activated
//----------------------------------------------------------------------------
void TransactionManager::on_reportDateComboBox_activated( const QString& aText )
{
    QDate currentDate = QDate::currentDate();
    if( aText == sDateCustomStr )
    {
        mUi->reportStartDateEdit->setDisabled( false );
        mUi->reportEndDateEdit->setDisabled( false );
    }
    else if( aText == sDateThisYearStr ){ updateAndApplyDates( REPORT_TAB, QDate(currentDate.year(),1,1), currentDate ); }
    else if( aText == sDate1YearStr )   { updateAndApplyDates( REPORT_TAB, currentDate.addYears(-1), currentDate ); }
    else if( aText == sDate3YearStr )   { updateAndApplyDates( REPORT_TAB, currentDate.addYears(-3), currentDate ); }
    else if( aText == sDate5YearStr )   { updateAndApplyDates( REPORT_TAB, currentDate.addYears(-5), currentDate ); }
    else if( aText == sDate10YearStr )  { updateAndApplyDates( REPORT_TAB, currentDate.addYears(-10), currentDate ); }
    else if( aText == sDateAllTimeStr ) { updateAndApplyDates( REPORT_TAB, sFirstTransactionDate, sLastTransactionDate ); }
}

//----------------------------------------------------------------------------
// Report date interval combo box activated
//----------------------------------------------------------------------------
void TransactionManager::on_reportDateIntervalComboBox_activated( const QString& aText )
{
    int monthInterval = 1;
    if( aText == sDateInterval1MonthStr )       { monthInterval = 1; }
    else if( aText == sDateInterval3MonthStr)   { monthInterval = 3; }
    else if( aText == sDateInterval6MonthStr)   { monthInterval = 6; }
    else if( aText == sDateInterval1YearStr  )  { monthInterval = 12; }
    mReportNetIncomeGraph.setMonthInterval( monthInterval );
    mReportNetWorthGraph.setMonthInterval( monthInterval );
    mReportAccountBalanceGraph.setMonthInterval( monthInterval );
    mReportTableView.setMonthInterval( monthInterval );
}

//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportAllButton_clicked()
{
    mReportFilter.selectAll();
    updateFilterToolBox( REPORT_TAB, TOOLS_ACCOUNTS | TOOLS_CATEGORIES | TOOLS_LABELS, mReportFilter );
    mUi->reportStartDateEdit->setDate( sFirstTransactionDate );
    mUi->reportEndDateEdit->setDate( sLastTransactionDate );
    updateReportsTab();
}
//----------------------------------------------------------------------------
// on_reportSelectButton_clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportSelectButton_clicked()
{
    updateReportsTab();
} // TransactionManager::on_reportSelectButton_clicked()

//----------------------------------------------------------------------------
// on_reportShowInTransactionsButton_clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportShowInTransactionsButton_clicked()
{
    updateReportsTab();
    handleShowTransactionByFilter( mReportFilter );
} // TransactionManager::on_reportShowInTransactionsButton_clicked()

//----------------------------------------------------------------------------
// Report checkbox slots
//----------------------------------------------------------------------------
void TransactionManager::on_reportAllAccountsCheckBox_clicked( bool aChecked )
{
    mReportFilter = getTransactionFilter( REPORT_TAB );
    mReportFilter.selectAllAccounts( aChecked );
    updateFilterToolBox( REPORT_TAB, TOOLS_ACCOUNTS, mReportFilter );
}
void TransactionManager::on_reportOpenAccountsCheckBox_clicked( bool aChecked )
{
    mReportFilter = getTransactionFilter( REPORT_TAB );
    mReportFilter.selectOpenAccounts( aChecked );
    updateFilterToolBox( REPORT_TAB, TOOLS_ACCOUNTS, mReportFilter );
}
void TransactionManager::on_reportAllCategoriesCheckBox_clicked( bool aChecked )
{
    mReportFilter = getTransactionFilter( REPORT_TAB );
    mReportFilter.selectAllCategories( aChecked );
    updateFilterToolBox( REPORT_TAB, TOOLS_CATEGORIES, mReportFilter );
}
void TransactionManager::on_reportIncomeCategoriesCheckBox_clicked( bool aChecked )
{
    mReportFilter = getTransactionFilter( REPORT_TAB );
    mReportFilter.selectCategories( aChecked, Category::TRANSACTION_TYPE_INCOME );
    updateFilterToolBox( REPORT_TAB, TOOLS_CATEGORIES, mReportFilter );
}
void TransactionManager::on_reportExpenseCategoriesCheckBox_clicked( bool aChecked )
{
    mReportFilter = getTransactionFilter( REPORT_TAB );
    mReportFilter.selectCategories( aChecked, Category::TRANSACTION_TYPE_EXPENSE );
    updateFilterToolBox( REPORT_TAB, TOOLS_CATEGORIES, mReportFilter );
}
void TransactionManager::on_reportTransferCategoriesCheckBox_clicked( bool aChecked )
{
    mReportFilter = getTransactionFilter( REPORT_TAB );
    mReportFilter.selectCategories( aChecked, Category::TRANSACTION_TYPE_TRANSFER );
    updateFilterToolBox( REPORT_TAB, TOOLS_CATEGORIES, mReportFilter );
}
void TransactionManager::on_reportAllLabelsCheckBox_clicked( bool aChecked )
{
    mReportFilter = getTransactionFilter( REPORT_TAB );
    mReportFilter.selectAllLabels( aChecked ? Transaction::MATCH : Transaction::DO_NOT_MATCH );
    updateFilterToolBox( REPORT_TAB, TOOLS_LABELS, mReportFilter );
}

//----------------------------------------------------------------------------
// Handle check box clicked
//----------------------------------------------------------------------------
void TransactionManager::handleReportAccountsCheckBox_clicked( bool aChecked )
{
    Q_UNUSED(aChecked);
    mReportFilter = getTransactionFilter( REPORT_TAB );
    updateFilterToolBox( REPORT_TAB, TOOLS_ACCOUNTS, mReportFilter );
}
void TransactionManager::handleReportLabelsCheckBox_clicked()
{
    mReportFilter = getTransactionFilter( REPORT_TAB );
    updateFilterToolBox( REPORT_TAB, TOOLS_LABELS, mReportFilter );
}

//----------------------------------------------------------------------------
// Reports categories tree expand button
//----------------------------------------------------------------------------
void TransactionManager::on_mReportCategoriesTreeExpandButton_clicked()
{
    if( mUi->mReportCategoriesTreeExpandButton->text() == "Expand All" )
    {
        mReportCategoriesTreeWidget.expandAll();
        mUi->mReportCategoriesTreeExpandButton->setText( "Collapse All" );
    }
    else
    {
        mReportCategoriesTreeWidget.collapseAll();
        mUi->mReportCategoriesTreeExpandButton->setText( "Expand All" );
    }
}

//----------------------------------------------------------------------------
// Show net income on graph
//----------------------------------------------------------------------------
void TransactionManager::on_mReportShowNetIncomeCheckBox_clicked( bool aChecked )
{
    mReportNetIncomeGraph.setShowNetIncome( aChecked );
}

//----------------------------------------------------------------------------
// Show transfers in reports
//----------------------------------------------------------------------------
void TransactionManager::on_mReportShowTransfersCheckBox_clicked( bool aChecked )
{
    mReportNetIncomeGraph.setShowTransfers( aChecked );
    mIncomeParentPieChart.setShowTransfers( aChecked );
    mExpenseParentPieChart.setShowTransfers( aChecked );
    mIncomeSubPieChart.setShowTransfers( aChecked );
    mExpenseSubPieChart.setShowTransfers( aChecked );
}

//----------------------------------------------------------------------------
// handle report pie chart combo boxes
//----------------------------------------------------------------------------
void TransactionManager::on_mReportAssetDebtComboBox_currentIndexChanged( const QString& aText )
{
    ReportPieChart::SortType sortType = ReportPieChart::SORT_BY_BALANCE_DESCENDING;
    if( aText == sSortChartByBalance )  { sortType = ReportPieChart::SORT_BY_BALANCE_DESCENDING; }
    else if( aText == sSortChartByName ){ sortType = ReportPieChart::SORT_BY_NAME_ASCENDING; }
    mAssetsPieChart.sortChart( sortType );
    mDebtsPieChart.sortChart( sortType );
}
void TransactionManager::on_mReportIncomeExpenseComboBox_currentIndexChanged( const QString& aText )
{
    ReportPieChart::SortType sortType = ReportPieChart::SORT_BY_BALANCE_DESCENDING;
    if( aText == sSortChartByBalance )  { sortType = ReportPieChart::SORT_BY_BALANCE_DESCENDING; }
    else if( aText == sSortChartByName ){ sortType = ReportPieChart::SORT_BY_NAME_ASCENDING; }
    mIncomeParentPieChart.sortChart( sortType );
    mExpenseParentPieChart.sortChart( sortType );
}
void TransactionManager::on_mReportSubIncomeExpenseComboBox_currentIndexChanged( const QString& aText )
{
    ReportPieChart::SortType sortType = ReportPieChart::SORT_BY_BALANCE_DESCENDING;
    if( aText == sSortChartByBalance )  { sortType = ReportPieChart::SORT_BY_BALANCE_DESCENDING; }
    else if( aText == sSortChartByName ){ sortType = ReportPieChart::SORT_BY_NAME_ASCENDING; }
    mIncomeSubPieChart.sortChart( sortType );
    mExpenseSubPieChart.sortChart( sortType );
}
