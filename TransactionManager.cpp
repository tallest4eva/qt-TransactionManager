//******************************************************************************
// Author: Obi Modum (tallest4eva)
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
#include <QStandardItemModel>

#include "ui_transactionmanager.h"
#include "TransactionManager.h"
#include "Account.h"
#include "Category.h"
#include "DisplayDialog.h"
#include "FileConfigDialog.h"
#include "Logger.h"
#include "Month.h"
#include "Parser.h"
#include "OverviewAccountListItem.h"

// Static variables
const QDate TransactionManager::cDefaultStartDate = QDate(2000,1,1);
const QDate TransactionManager::cDefaultEndDate = QDate(2001,1,1);

QStringList TransactionManager::sFileContents;
QList<Account*> TransactionManager::sAccountList;
QList<Transaction*> TransactionManager::sTransactionList;
QList<Month*> TransactionManager::sMonthList;
QDate TransactionManager::sFirstTransactionDate = TransactionManager::cDefaultStartDate;
QDate TransactionManager::sLastTransactionDate = TransactionManager::cDefaultEndDate;
QVector<bool> TransactionManager::sCategoriesEnabledList( Category::CATEGORY_TYPE_CNT, false );
QVector<bool> TransactionManager::sLabelsEnabledList( Category::LABEL_CNT, false );

static const QString sToolboxAccountsStr = "Accounts";
static const QString sToolboxCategoriesStr = "Categories";
static const QString sToolboxLabelsStr = "Labels";
static const QString sToolboxDatesStr = "Date Interval";

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
TransactionManager::TransactionManager
    (
    QWidget *parent
    ):
    QMainWindow(parent),
    ui(new Ui::TransactionManager)
{
    ui->setupUi(this);

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
    delete ui;
} // TransactionManager::~TransactionManager

//----------------------------------------------------------------------------
// Init
//----------------------------------------------------------------------------
void TransactionManager::init()
{
    // Init Parser
    Parser::restore();

    // Init tab/toolbox widgets
    ui->tabWidget->setCurrentIndex(0);
    ui->transactionToolBox->setCurrentIndex(0);
    ui->reportToolBox->setCurrentIndex(0);
    ui->reportDisplayTabWidget->setCurrentIndex(0);
    ui->transactionListWidget->layout()->addWidget( &mTransactionTableView );
    for( int i = 0; i < Category::CATEGORY_TYPE_CNT; i++ )
    {
        QString str = Category::getCategoryText( (Category::CategoryIdType)i, true ).replace( "&", "and" );
        QCheckBox* checkbox = new QCheckBox( str, ui->transactionCategoriesGroupBox );
        ui->transactionCategoriesGroupBox->layout()->addWidget( checkbox );
        mTransactionCategoriesCheckBoxList.push_back( checkbox );

        checkbox = new QCheckBox( str, ui->reportCategoriesGroupBox );
        ui->reportCategoriesGroupBox->layout()->addWidget( checkbox );
        mReportCategoriesCheckBoxList.push_back( checkbox );
    }
    for( int i = 0; i < Category::LABEL_CNT; i++ )
    {
        QString str = Category::getLabelText( (Category::LabelIdType)i );
        QCheckBox* checkbox = new QCheckBox( str, ui->transactionLabelsGroupBox );
        ui->transactionLabelsGroupBox->layout()->addWidget( checkbox );
        mTransactionLabelsCheckBoxList.push_back( checkbox );

        checkbox = new QCheckBox( str, ui->reportLabelsGroupBox );
        ui->reportLabelsGroupBox->layout()->addWidget( checkbox );
        mReportLabelsCheckBoxList.push_back( checkbox );
    }

    // Init report graphs, table and pie charts
    ui->reportNetIncomeTab->layout()->addWidget( &mReportNetIncomeGraph );
    ui->reportNetWorthTab->layout()->addWidget( &mReportNetWorthGraph );
    mReportNetIncomeGraph.setGraphMode( BarGraph::BAR_NET_INCOME );
    mReportNetWorthGraph.setGraphMode( BarGraph::BAR_NET_WORTH );
    connect( &mReportNetIncomeGraph, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    connect( &mReportNetWorthGraph, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    connect( &mReportNetIncomeGraph, SIGNAL(reportDateSelected(QDate,QDate)), this, SLOT(handleShowReportByDate(QDate,QDate)) );
    connect( &mReportNetWorthGraph, SIGNAL(reportDateSelected(QDate,QDate)), this, SLOT(handleShowReportByDate(QDate,QDate)) );
    connect( &mReportTableView, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    ui->reportListTab->layout()->addWidget( &mReportTableView );
    ui->reportAssetGroupBox->layout()->addWidget( &mAssetsPieChart );
    ui->reportDebtGroupBox->layout()->addWidget( &mDebtsPieChart );
    ui->reportIncomeParentGroupBox->layout()->addWidget( &mIncomeParentPieChart );
    ui->reportExpenseParentGroupBox->layout()->addWidget( &mExpenseParentPieChart );
    ui->reportIncomeSubGroupBox->layout()->addWidget( &mIncomeSubPieChart );
    ui->reportExpenseSubGroupBox->layout()->addWidget( &mExpenseSubPieChart );
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
    for( int i = 0; i < Category::CATEGORY_TYPE_CNT; i++ )
    {
        delete mTransactionCategoriesCheckBoxList[i];
        delete mReportCategoriesCheckBoxList[i];
    }
    for( int i = 0; i < Category::LABEL_CNT; i++ )
    {
        delete mTransactionLabelsCheckBoxList[i];
        delete mReportLabelsCheckBoxList[i];
    }
} // TransactionManager::deInit()

//----------------------------------------------------------------------------
// clearData
//----------------------------------------------------------------------------
void TransactionManager::clearData()
{
    // Clear account data
    mFileName.clear();
    for( int i = 0; i < sAccountList.size(); i++ )
    {
        delete sAccountList[i];
    }
    for( int i = 0; i < sTransactionList.size(); i++ )
    {
        delete sTransactionList[i];
    }
    for( int i = 0; i < sMonthList.size(); i++ )
    {
        delete sMonthList[i];
    }
    sAccountList.clear();
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
        QTextStream in( &file );
        Parser::parseFile( in );
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
            //stream << ui->textEdit->toPlainText();
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
} // TransactionManager::on_actionSave_triggered()

//----------------------------------------------------------------------------
// on_actionDisplayLog_triggered
//----------------------------------------------------------------------------
void TransactionManager::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Transaction Manager\nAuthor: tallest4eva\nVersion 1.03");
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
// item double clicked
//----------------------------------------------------------------------------
void TransactionManager::on_overviewAccountList_itemDoubleClicked( QListWidgetItem* aItem )
{
    // Show Transactions with selected account
    int row = ui->overviewAccountList->row( aItem );
    if( row >= 0 && row < sAccountList.size() )
    {
        Transaction::FilterType filter = Transaction::FilterType();
        filter.mAllAccounts = false;
        filter.mShowAccounts = true;
        filter.mAccountList.push_back( sAccountList[row] );
        filter.mStartDate = sFirstTransactionDate;
        filter.mEndDate = sLastTransactionDate;
        handleShowTransactionByFilter( filter );
    }
} // TransactionManager::on_overviewAccountList_itemDoubleClicked()

//----------------------------------------------------------------------------
// updateUI
//----------------------------------------------------------------------------
void TransactionManager::updateUI()
{
    // Update ui elements, menu and status
    ui->actionClose->setEnabled( false );
    ui->actionDisplayFile->setEnabled( false );
    ui->statusBar->removeWidget( &mStatusLabel );
    if( !mFileName.isEmpty() )
    {
        ui->actionClose->setEnabled( true );
        ui->actionDisplayFile->setEnabled( true );
        mStatusLabel.setText( "File Opened: " + mFileName );
        mStatusLabel.show();
        ui->statusBar->addPermanentWidget( &mStatusLabel );
    }
    
    updateOverviewTab();
    initTransactionsTab();
    initReportsTab();

} // TransactionManager::updateUI()

//----------------------------------------------------------------------------
// Update Overview Tab
//----------------------------------------------------------------------------
void TransactionManager::updateOverviewTab()
{
    // Update overview values
    if( !mFileName.isEmpty() )
    {
        ui->overviewNumberOfAccountValue->setNum( sAccountList.size() );
        ui->overviewNumberOfTransactionsValue->setNum( sTransactionList.size() );
        QString str = "$" + QString::number( Account::getTotalAccountBalance(), 'f', 2 );
        if( Account::getTotalAccountBalance() != 0 )
        {
            str.prepend( (Account::getTotalAccountBalance() > 0) ? "<font color=\"darkgreen\">" : "<font color=\"red\">" );
            str.append( "</font>" );
        }
        ui->overviewNetWorthValue->setText( str );
        ui->overviewFirstDateValue->setText( sFirstTransactionDate.toString("yyyy-MM-dd") );
        ui->overviewLastDateValue->setText( sLastTransactionDate.toString("yyyy-MM-dd") );
    }
    else
    {
        ui->overviewNumberOfAccountValue->setText("--");
        ui->overviewNumberOfTransactionsValue->setText("--");
        ui->overviewNetWorthValue->setText("--");
        ui->overviewFirstDateValue->setText("--");
        ui->overviewLastDateValue->setText("--");
    }

    // Update overview account list
    ui->overviewAccountList->clear();
    for( int i = 0; i < sAccountList.size(); i++ )
    {
        QListWidgetItem* listItem = new QListWidgetItem();
        OverviewAccountListItem* item = new OverviewAccountListItem();
        item->setAccount( sAccountList[i] );
        listItem->setSizeHint( QSize(0,70) );
        ui->overviewAccountList->addItem( listItem );
        ui->overviewAccountList->setItemWidget( listItem, item );
    }
} // TransactionManager::updateOverviewTab()

//----------------------------------------------------------------------------
// Init Transactions Tab
//----------------------------------------------------------------------------
void TransactionManager::initTransactionsTab()
{
    // Clear transactions tab
    ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionAccountToolBox), sToolboxAccountsStr );
    ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionCategoriesToolBox), sToolboxCategoriesStr );
    ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionLabelsToolBox), sToolboxLabelsStr );
    ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionDateToolBox), sToolboxDatesStr );
    for( int i = 0; i < mTransactionAccountsCheckBoxList.size(); i++ )
    {
        ui->transactionAccountGroupBox->layout()->removeWidget( mTransactionAccountsCheckBoxList[i] );
        delete mTransactionAccountsCheckBoxList[i];
    }
    mTransactionAccountsCheckBoxList.clear();
    updateCheckBoxes( TRANSACTION_TAB, ACCOUNTS_CHECKBOX, ALL, true );
    updateCheckBoxes( TRANSACTION_TAB, CATEGORIES_CHECKBOX, ALL, true );
    updateCheckBoxes( TRANSACTION_TAB, LABELS_CHECKBOX, ALL, true );
    for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
    {
        mTransactionCategoriesCheckBoxList[i]->setDisabled( true );
    }
    for( int i = 0; i < mTransactionLabelsCheckBoxList.size(); i++ )
    {
        mTransactionLabelsCheckBoxList[i]->setDisabled( true );
    }
    ui->transactionAllAccountsCheckBox->setDisabled( true );
    ui->transactionOpenAccountsCheckBox->setDisabled( true );
    ui->transactionAllCategoriesCheckBox->setDisabled( true );
    ui->transactionIncomeCategoriesCheckBox->setDisabled( true );
    ui->transactionExpenseCategoriesCheckBox->setDisabled( true );
    ui->transactionAllLabelsCheckBox->setDisabled( true );
    ui->transactionStartDateEdit->setDateRange( sFirstTransactionDate, sLastTransactionDate );
    ui->transactionStartDateEdit->setDate( sFirstTransactionDate );
    ui->transactionStartDateEdit->setDisabled( true );
    ui->transactionEndDateEdit->setDateRange( sFirstTransactionDate, sLastTransactionDate );
    ui->transactionEndDateEdit->setDate( sLastTransactionDate );
    ui->transactionEndDateEdit->setDisabled( true );
    ui->transactionDateThisYearButton->setEnabled( false );
    ui->transactionDate1YearButton->setEnabled( false );
    ui->transactionDate5YearButton->setEnabled( false );
    ui->transactionDate10YearButton->setEnabled( false );
    ui->transactionDateAllTimeButton->setEnabled( false );
    ui->transactionSelectButton->setEnabled( false );
    ui->transactionAllButton->setEnabled( false );

    if( !mFileName.isEmpty() )
    {
        // Create / Enable transaction tab check boxes
        ui->transactionAllAccountsCheckBox->setDisabled( false );
        ui->transactionOpenAccountsCheckBox->setDisabled( false );
        ui->transactionAllCategoriesCheckBox->setDisabled( false );
        ui->transactionIncomeCategoriesCheckBox->setDisabled( false );
        ui->transactionExpenseCategoriesCheckBox->setDisabled( false );
        ui->transactionAllLabelsCheckBox->setDisabled( false );
        for( int i = 0; i < sAccountList.size(); i++ )
        {
            QCheckBox* checkbox = new QCheckBox( sAccountList[i]->getName(), ui->transactionAccountGroupBox );
            checkbox->setChecked( true );
            ui->transactionAccountGroupBox->layout()->addWidget( checkbox );
            mTransactionAccountsCheckBoxList.push_back( checkbox );
        }
        for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
        {
            mTransactionCategoriesCheckBoxList[i]->setDisabled( !sCategoriesEnabledList[i] );
        }
        for( int i = 0; i < mTransactionLabelsCheckBoxList.size(); i++ )
        {
            mTransactionLabelsCheckBoxList[i]->setDisabled( !sLabelsEnabledList[i] );
        }
        ui->transactionStartDateEdit->setDisabled( false );
        ui->transactionEndDateEdit->setDisabled( false );
        QDate currentDate = QDate::currentDate();
        QDate thisYearDate( currentDate.year(), 1, 1 );
        ui->transactionDateThisYearButton->setEnabled( sLastTransactionDate >= thisYearDate );
        ui->transactionDate1YearButton->setEnabled( sFirstTransactionDate < currentDate.addYears(-1) );
        ui->transactionDate5YearButton->setEnabled( sFirstTransactionDate < currentDate.addYears(-5) );
        ui->transactionDate10YearButton->setEnabled( sFirstTransactionDate < currentDate.addYears(-10) );
        ui->transactionDateAllTimeButton->setEnabled( true );
        ui->transactionSelectButton->setEnabled( true );
        ui->transactionAllButton->setEnabled( true );
    }

    // Init table
    mTransactionTableView.clear();

    // Update transaction table
    updateTransactionsTab();
} // TransactionManager::initTransactionsTab()

//----------------------------------------------------------------------------
// Update Transactions Tab
//----------------------------------------------------------------------------
void TransactionManager::updateTransactionsTab()
{
    if( !mFileName.isEmpty() )
    {
        mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
        mTransactionTableView.setTransactionFilter( mTransactionFilter );
        mTransactionTableView.resort();

        // Update tool box text
        QString str = (mTransactionFilter.mAllAccounts) ? ": All" : ": Some";
        ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionAccountToolBox), sToolboxAccountsStr + str );
        str = (mTransactionFilter.mAllCategories) ? ": All" : ": Some";
        ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionCategoriesToolBox), sToolboxCategoriesStr + str );
        str = (mTransactionFilter.mAllLabels) ? ": All" : ": Some";
        ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionLabelsToolBox), sToolboxLabelsStr + str );
        str = (mTransactionFilter.mAllDates) ? ": All" : ": Some";
        ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionDateToolBox), sToolboxDatesStr + str );
    }
    else
    {
        mTransactionFilter = Transaction::FilterType();
        mTransactionTableView.clear();
    }
} // TransactionManager::updateTransactionsTab()

//----------------------------------------------------------------------------
// Init Reports Tab
//----------------------------------------------------------------------------
void TransactionManager::initReportsTab()
{
    // Clear reports tab
    ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportAccountToolBox), sToolboxAccountsStr );
    ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportCategoriesToolBox), sToolboxCategoriesStr );
    ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportLabelsToolBox), sToolboxLabelsStr );
    ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportDateToolBox), sToolboxDatesStr );
    for( int i = 0; i < mReportAccountsCheckBoxList.size(); i++ )
    {
        ui->reportAccountGroupBox->layout()->removeWidget( mReportAccountsCheckBoxList[i] );
        delete mReportAccountsCheckBoxList[i];
    }
    mReportAccountsCheckBoxList.clear();
    updateCheckBoxes( REPORT_TAB, ACCOUNTS_CHECKBOX, ALL, true );
    updateCheckBoxes( REPORT_TAB, CATEGORIES_CHECKBOX, ALL, true );
    updateCheckBoxes( REPORT_TAB, LABELS_CHECKBOX, ALL, true );
    for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
    {
        mReportCategoriesCheckBoxList[i]->setDisabled( true );
    }
    for( int i = 0; i < mReportLabelsCheckBoxList.size(); i++ )
    {
        mReportLabelsCheckBoxList[i]->setDisabled( true );
    }
    ui->reportAllAccountsCheckBox->setDisabled( true );
    ui->reportOpenAccountsCheckBox->setDisabled( true );
    ui->reportAllCategoriesCheckBox->setDisabled( true );
    ui->reportIncomeCategoriesCheckBox->setDisabled( true );
    ui->reportExpenseCategoriesCheckBox->setDisabled( true );
    ui->reportAllLabelsCheckBox->setDisabled( true );
    ui->reportStartDateEdit->setDisabled( true );
    ui->reportStartDateEdit->setDateRange( sFirstTransactionDate, sLastTransactionDate );
    ui->reportStartDateEdit->setDate( sFirstTransactionDate );
    ui->reportEndDateEdit->setDisabled( true );
    ui->reportEndDateEdit->setDateRange( sFirstTransactionDate, sLastTransactionDate );
    ui->reportEndDateEdit->setDate( sLastTransactionDate );
    ui->reportDateThisYearButton->setEnabled( false );
    ui->reportDate1YearButton->setEnabled( false );
    ui->reportDate5YearButton->setEnabled( false );
    ui->reportDate10YearButton->setEnabled( false );
    ui->reportDateAllTimeButton->setEnabled( false );
    ui->reportSelectButton->setEnabled( false );
    ui->reportAllButton->setEnabled( false );

    // Update reports tab
    if( !mFileName.isEmpty() )
    {
        // Create / Enable reports tab check boxes
        ui->reportAllAccountsCheckBox->setDisabled( false );
        ui->reportOpenAccountsCheckBox->setDisabled( false );
        ui->reportAllCategoriesCheckBox->setDisabled( false );
        ui->reportIncomeCategoriesCheckBox->setDisabled( false );
        ui->reportExpenseCategoriesCheckBox->setDisabled( false );
        ui->reportAllLabelsCheckBox->setDisabled( false );
        for( int i = 0; i < sAccountList.size(); i++ )
        {
            QCheckBox* checkbox = new QCheckBox( sAccountList[i]->getName(), ui->reportAccountGroupBox );
            checkbox->setChecked( true );
            ui->reportAccountGroupBox->layout()->addWidget( checkbox );
            mReportAccountsCheckBoxList.push_back( checkbox );
        }
        for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
        {
            mReportCategoriesCheckBoxList[i]->setDisabled( !sCategoriesEnabledList[i] );
        }
        for( int i = 0; i < mReportLabelsCheckBoxList.size(); i++ )
        {
            mReportLabelsCheckBoxList[i]->setDisabled( !sLabelsEnabledList[i] );
        }
        ui->reportStartDateEdit->setDisabled( false );
        ui->reportEndDateEdit->setDisabled( false );
        QDate currentDate = QDate::currentDate();
        QDate thisYearDate( currentDate.year(), 1, 1 );
        ui->reportDateThisYearButton->setEnabled( sLastTransactionDate >= thisYearDate );
        ui->reportDate1YearButton->setEnabled( sFirstTransactionDate < currentDate.addYears(-1) );
        ui->reportDate5YearButton->setEnabled( sFirstTransactionDate < currentDate.addYears(-5) );
        ui->reportDate10YearButton->setEnabled( sFirstTransactionDate < currentDate.addYears(-10) );
        ui->reportDateAllTimeButton->setEnabled( true );
        ui->reportSelectButton->setEnabled( true );
        ui->reportAllButton->setEnabled( true );
    }

    // Update reports
    updateReportsTab();
} // TransactionManager::initReportsTab()

//----------------------------------------------------------------------------
// Update Reports Tab
//----------------------------------------------------------------------------
void TransactionManager::updateReportsTab()
{
    if( !mFileName.isEmpty() )
    {
        mReportFilter = getTransactionFilter( REPORT_TAB );
        mReportNetIncomeGraph.setTransactionFilter( mReportFilter );
        mReportNetWorthGraph.setTransactionFilter( mReportFilter );
        mReportTableView.setTransactionFilter( mReportFilter );
        for( int i = 0; i < mPieChartList.size(); i++ )
        {
            mPieChartList[i]->setTransactionFilter( mReportFilter );
        }

        // Update tool box text
        QString str = (mReportFilter.mAllAccounts) ? ": All" : ": Some";
        ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportAccountToolBox), sToolboxAccountsStr + str );
        str = (mReportFilter.mAllCategories) ? ": All" : ": Some";
        ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportCategoriesToolBox), sToolboxCategoriesStr + str );
        str = (mReportFilter.mAllLabels) ? ": All" : ": Some";
        ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportLabelsToolBox), sToolboxLabelsStr + str );
        str = (mReportFilter.mAllDates) ? ": All" : ": Some";
        ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportDateToolBox), sToolboxDatesStr + str );
    }
    else
    {
        mReportFilter = Transaction::FilterType();
        mReportNetIncomeGraph.clear();
        mReportNetWorthGraph.clear();
        mReportTableView.clear();
        for( int i = 0; i < mPieChartList.size(); i++ )
        {
            mPieChartList[i]->clear();
        }
    }
} // TransactionManager::updateReportsTab()

//----------------------------------------------------------------------------
// filter Transaction List
//----------------------------------------------------------------------------
Transaction::FilterType TransactionManager::getTransactionFilter( TabType aTabType )
{
    Transaction::FilterType filter;
    switch( aTabType )
    {
    case REPORT_TAB:
        for( int i = 0; i < mReportAccountsCheckBoxList.size(); i++ )
        {
            ( mReportAccountsCheckBoxList[i]->checkState() == Qt::Unchecked ) ? filter.mAllAccounts = false : filter.mAccountList.push_back( sAccountList[i] );
        }
        for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
        {
            if( mReportCategoriesCheckBoxList[i]->checkState() == Qt::Unchecked ){ filter.mAllCategories = false; filter.mCategoryList[i] = false; }
        }
        for( int i = 0; i < mReportLabelsCheckBoxList.size(); i++ )
        {
            if( mReportLabelsCheckBoxList[i]->checkState() == Qt::Unchecked ){ filter.mAllLabels = false; filter.mLabelList[i] = false; }
        }
        filter.mStartDate = ui->reportStartDateEdit->date();
        filter.mEndDate = ui->reportEndDateEdit->date();
        break;
    case TRANSACTION_TAB:
    default:
        for( int i = 0; i < mTransactionAccountsCheckBoxList.size(); i++ )
        {
            ( mTransactionAccountsCheckBoxList[i]->checkState() == Qt::Unchecked ) ? filter.mAllAccounts = false : filter.mAccountList.push_back( sAccountList[i] );
        }
        for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
        {
            if( mTransactionCategoriesCheckBoxList[i]->checkState() == Qt::Unchecked ){ filter.mAllCategories = false; filter.mCategoryList[i] = false; }
        }
        for( int i = 0; i < mTransactionLabelsCheckBoxList.size(); i++ )
        {
            if( mTransactionLabelsCheckBoxList[i]->checkState() == Qt::Unchecked ){ filter.mAllLabels = false; filter.mLabelList[i] = false; }
        }
        filter.mStartDate = ui->transactionStartDateEdit->date();
        filter.mEndDate = ui->transactionEndDateEdit->date();
        break;
    }
    // If not all dates are set
    if( sFirstTransactionDate < filter.mStartDate || sLastTransactionDate > filter.mEndDate )
    {
        filter.mAllDates = false;
    }
    return filter;
} // TransactionManager::getTransactionFilter()

//----------------------------------------------------------------------------
// Handle Show Transaction By Date
//----------------------------------------------------------------------------
void TransactionManager::handleShowTransactionByFilter( const Transaction::FilterType& aFilter )
{
    // Switch to transaction tab
    ui->tabWidget->setCurrentWidget( ui->transactionsTab );

    // Display the correct tool box
    if( aFilter.mShowAccounts ){ ui->transactionToolBox->setCurrentWidget( ui->transactionAccountToolBox ); }
    else if( aFilter.mShowCategories ){ ui->transactionToolBox->setCurrentWidget( ui->transactionCategoriesToolBox ); }
    else if( aFilter.mShowLabels ){ ui->transactionToolBox->setCurrentWidget( ui->transactionLabelsToolBox ); }
    else if( aFilter.mShowDates ){ ui->transactionToolBox->setCurrentWidget( ui->transactionDateToolBox ); }

    // Update checkboxes
    if( aFilter.mAllAccounts )
    {
        updateCheckBoxes( TRANSACTION_TAB, ACCOUNTS_CHECKBOX, ALL, true );
    }
    else
    {
        updateCheckBoxes( TRANSACTION_TAB, ACCOUNTS_CHECKBOX, ALL, false );
        for( int i = 0; i < aFilter.mAccountList.size(); i++ )
        {
            int index = Account::getAccountIndex( aFilter.mAccountList[i] );
            if( index >= 0 )
            {
                mTransactionAccountsCheckBoxList[index]->setChecked( true );
            }
        }
    }
    for( int i = 0; i < aFilter.mCategoryList.size(); i++ )
    {
        mTransactionCategoriesCheckBoxList[i]->setChecked( aFilter.mCategoryList[i] );
    }
    for( int i = 0; i < aFilter.mLabelList.size(); i++ )
    {
        mTransactionLabelsCheckBoxList[i]->setChecked( aFilter.mLabelList[i] );
    }
    ui->transactionStartDateEdit->setDate( ( aFilter.mAllDates ) ? sFirstTransactionDate : aFilter.mStartDate );
    ui->transactionEndDateEdit->setDate( ( aFilter.mAllDates ) ? sLastTransactionDate : aFilter.mEndDate );
    on_transactionSelectButton_clicked();
} // TransactionManager::handleShowTransactionByFilter

//----------------------------------------------------------------------------
// Handle Show Report By Date
//----------------------------------------------------------------------------
void TransactionManager::handleShowReportByDate( QDate aStartDate, QDate aEndDate )
{
    // Switch to report tab
    ui->tabWidget->setCurrentWidget( ui->reportTab );
    ui->reportToolBox->setCurrentWidget( ui->reportDateToolBox );
    ui->reportStartDateEdit->setDate( aStartDate );
    ui->reportEndDateEdit->setDate( aEndDate );
    on_reportSelectButton_clicked();
} // TransactionManager::handleShowReportByDate()

//----------------------------------------------------------------------------
// updateAndApplyDates
//----------------------------------------------------------------------------
void TransactionManager::updateAndApplyDates( TabType aTab, QDate aStartDate, QDate aEndDate )
{
    switch( aTab )
    {
    case TRANSACTION_TAB:
        ui->transactionStartDateEdit->setDate( ( sFirstTransactionDate > aStartDate ) ? sFirstTransactionDate : aStartDate );
        ui->transactionEndDateEdit->setDate( ( sLastTransactionDate < aEndDate ) ? sLastTransactionDate : aEndDate );
        on_transactionSelectButton_clicked();
        break;
    case REPORT_TAB:
        ui->reportStartDateEdit->setDate( ( sFirstTransactionDate > aStartDate ) ? sFirstTransactionDate : aStartDate );
        ui->reportEndDateEdit->setDate( ( sLastTransactionDate < aEndDate ) ? sLastTransactionDate : aEndDate );
        on_reportSelectButton_clicked();
    default:
        break;
    }
} // TransactionManager::updateAndApplyDates()

//----------------------------------------------------------------------------
// updateCheckBoxes
//----------------------------------------------------------------------------
void TransactionManager::updateCheckBoxes( TabType aTab, CheckBoxType aCheckType, SelectType aSelectType, bool aChecked )
{
    QCheckBox* accountsAllCheckBox = NULL;
    QCheckBox* accountsOpenCheckBox = NULL;
    QCheckBox* categoriesAllCheckBoxList = NULL;
    QCheckBox* categoriesIncomeCheckBoxList = NULL;
    QCheckBox* categoriesExpenseCheckBoxList = NULL;
    QCheckBox* labelsAllCheckBox = NULL;
    QList<QCheckBox*>& accountsCheckBoxList = QList<QCheckBox*>();
    QList<QCheckBox*>& categoriesCheckBoxList = QList<QCheckBox*>();
    QList<QCheckBox*>& labelsCheckBoxList = QList<QCheckBox*>();
    switch( aTab )
    {
    case TRANSACTION_TAB:
        accountsAllCheckBox = ui->transactionAllAccountsCheckBox;
        accountsOpenCheckBox = ui->transactionOpenAccountsCheckBox;
        categoriesAllCheckBoxList = ui->transactionAllCategoriesCheckBox;
        categoriesIncomeCheckBoxList = ui->transactionIncomeCategoriesCheckBox;
        categoriesExpenseCheckBoxList = ui->transactionExpenseCategoriesCheckBox;
        labelsAllCheckBox = ui->transactionAllLabelsCheckBox;

        accountsCheckBoxList = mTransactionAccountsCheckBoxList;
        categoriesCheckBoxList = mTransactionCategoriesCheckBoxList;
        labelsCheckBoxList = mTransactionLabelsCheckBoxList;
        break;
    case REPORT_TAB:
    default:
        accountsAllCheckBox = ui->reportAllAccountsCheckBox;
        accountsOpenCheckBox = ui->reportOpenAccountsCheckBox;
        categoriesAllCheckBoxList = ui->reportAllCategoriesCheckBox;
        categoriesIncomeCheckBoxList = ui->reportIncomeCategoriesCheckBox;
        categoriesExpenseCheckBoxList = ui->reportExpenseCategoriesCheckBox;
        labelsAllCheckBox = ui->reportAllLabelsCheckBox;

        accountsCheckBoxList = mReportAccountsCheckBoxList;
        categoriesCheckBoxList = mReportCategoriesCheckBoxList;
        labelsCheckBoxList = mReportLabelsCheckBoxList;
        break;
    }
    switch( aCheckType )
    {
    case ACCOUNTS_CHECKBOX:
        accountsAllCheckBox->setChecked( ( aSelectType == ALL ) ? aChecked : false );
        accountsOpenCheckBox->setChecked( ( aSelectType == OPEN_ACCOUNTS ) ? aChecked : false );
        for( int i = 0; i < accountsCheckBoxList.size(); i++ )
        {
            if( aSelectType == ALL )
            {
                accountsCheckBoxList[i]->setChecked( aChecked );
            }
            else if( aSelectType == OPEN_ACCOUNTS )
            {
                accountsCheckBoxList[i]->setChecked( ( sAccountList[i]->getStatus() == Account::STATUS_OPEN ) ? aChecked : false );
            }
        }
        break;
    case CATEGORIES_CHECKBOX:
        categoriesAllCheckBoxList->setChecked( ( aSelectType == ALL ) ? aChecked : false );
        categoriesIncomeCheckBoxList->setChecked( ( aSelectType == INCOME_CATEGORIES ) ? aChecked : false );
        categoriesExpenseCheckBoxList->setChecked( ( aSelectType == EXPENSE_CATEGORIES ) ? aChecked : false );
        for( int i = 0; i < categoriesCheckBoxList.size(); i++ )
        {
            if( aSelectType == ALL )
            {
                categoriesCheckBoxList[i]->setChecked( aChecked );
            }
            else if( aSelectType == INCOME_CATEGORIES )
            {
                categoriesCheckBoxList[i]->setChecked( ( Transaction::determineTransactionType( (Category::CategoryIdType)i ) == Transaction::INCOME ) ? aChecked : false );
            }
            else if( aSelectType == EXPENSE_CATEGORIES )
            {
                categoriesCheckBoxList[i]->setChecked( ( Transaction::determineTransactionType( (Category::CategoryIdType)i ) == Transaction::EXPENSE ) ? aChecked : false );
            }
        }
        break;
    case LABELS_CHECKBOX:
        labelsAllCheckBox->setChecked( ( aSelectType == ALL ) ? aChecked : false );
        for( int i = 0; i < labelsCheckBoxList.size(); i++ )
        {
            labelsCheckBoxList[i]->setChecked( aChecked );
        }
        break;
    }

} // TransactionManager::updateCheckBoxes()

//----------------------------------------------------------------------------
// Transaction date button slots
//----------------------------------------------------------------------------
void TransactionManager::on_transactionDateThisYearButton_clicked() { updateAndApplyDates( TRANSACTION_TAB, QDate(QDate::currentDate().year(),1,1), QDate::currentDate() ); }
void TransactionManager::on_transactionDate1YearButton_clicked()    { updateAndApplyDates( TRANSACTION_TAB, QDate::currentDate().addYears(-1), QDate::currentDate() ); }
void TransactionManager::on_transactionDate5YearButton_clicked()    { updateAndApplyDates( TRANSACTION_TAB, QDate::currentDate().addYears(-5), QDate::currentDate() ); }
void TransactionManager::on_transactionDate10YearButton_clicked()   { updateAndApplyDates( TRANSACTION_TAB, QDate::currentDate().addYears(-10), QDate::currentDate() ); }
void TransactionManager::on_transactionDateAllTimeButton_clicked()  { updateAndApplyDates( TRANSACTION_TAB, sFirstTransactionDate, sLastTransactionDate ); }

//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionAllButton_clicked()
{
    updateCheckBoxes( TRANSACTION_TAB, ACCOUNTS_CHECKBOX, ALL, true );
    updateCheckBoxes( TRANSACTION_TAB, CATEGORIES_CHECKBOX, ALL, true );
    updateCheckBoxes( TRANSACTION_TAB, LABELS_CHECKBOX, ALL, true );
    ui->transactionStartDateEdit->setDate( sFirstTransactionDate );
    ui->transactionEndDateEdit->setDate( sLastTransactionDate );
    on_transactionSelectButton_clicked();
}
//----------------------------------------------------------------------------
// on_transactionSelectButton_clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionSelectButton_clicked()
{
    updateTransactionsTab();
} // TransactionManager::on_transactionSelectButton_clicked()

//----------------------------------------------------------------------------
// Report date button slots
//----------------------------------------------------------------------------
void TransactionManager::on_reportDateThisYearButton_clicked()  { updateAndApplyDates( REPORT_TAB, QDate(QDate::currentDate().year(),1,1), QDate::currentDate() ); }
void TransactionManager::on_reportDate1YearButton_clicked()     { updateAndApplyDates( REPORT_TAB, QDate::currentDate().addYears(-1), QDate::currentDate() ); }
void TransactionManager::on_reportDate5YearButton_clicked()     { updateAndApplyDates( REPORT_TAB, QDate::currentDate().addYears(-5), QDate::currentDate() ); }
void TransactionManager::on_reportDate10YearButton_clicked()    { updateAndApplyDates( REPORT_TAB, QDate::currentDate().addYears(-10), QDate::currentDate() ); }
void TransactionManager::on_reportDateAllTimeButton_clicked()   { updateAndApplyDates( REPORT_TAB, sFirstTransactionDate, sLastTransactionDate ); }

//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportAllButton_clicked()
{
    updateCheckBoxes( REPORT_TAB, ACCOUNTS_CHECKBOX, ALL, true );
    updateCheckBoxes( REPORT_TAB, CATEGORIES_CHECKBOX, ALL, true );
    updateCheckBoxes( REPORT_TAB, LABELS_CHECKBOX, ALL, true );
    ui->reportStartDateEdit->setDate( sFirstTransactionDate );
    ui->reportEndDateEdit->setDate( sLastTransactionDate );
    on_reportSelectButton_clicked();
}
//----------------------------------------------------------------------------
// on_reportSelectButton_clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportSelectButton_clicked()
{
    updateReportsTab();
} // TransactionManager::on_reportSelectButton_clicked()

//----------------------------------------------------------------------------
// Transactions checkbox slots
//----------------------------------------------------------------------------
void TransactionManager::on_transactionAllAccountsCheckBox_clicked( bool aChecked )      { updateCheckBoxes( TRANSACTION_TAB, ACCOUNTS_CHECKBOX, ALL, aChecked ); }
void TransactionManager::on_transactionOpenAccountsCheckBox_clicked( bool aChecked )     { updateCheckBoxes( TRANSACTION_TAB, ACCOUNTS_CHECKBOX, OPEN_ACCOUNTS, aChecked ); }
void TransactionManager::on_transactionAllCategoriesCheckBox_clicked( bool aChecked )    { updateCheckBoxes( TRANSACTION_TAB, CATEGORIES_CHECKBOX, ALL, aChecked ); }
void TransactionManager::on_transactionIncomeCategoriesCheckBox_clicked( bool aChecked ) { updateCheckBoxes( TRANSACTION_TAB, CATEGORIES_CHECKBOX, INCOME_CATEGORIES, aChecked ); }
void TransactionManager::on_transactionExpenseCategoriesCheckBox_clicked( bool aChecked ){ updateCheckBoxes( TRANSACTION_TAB, CATEGORIES_CHECKBOX, EXPENSE_CATEGORIES, aChecked ); }
void TransactionManager::on_transactionAllLabelsCheckBox_clicked( bool aChecked )        { updateCheckBoxes( TRANSACTION_TAB, LABELS_CHECKBOX, ALL, aChecked ); }

//----------------------------------------------------------------------------
// Report checkbox slots
//----------------------------------------------------------------------------
void TransactionManager::on_reportAllAccountsCheckBox_clicked( bool aChecked )      { updateCheckBoxes( REPORT_TAB, ACCOUNTS_CHECKBOX, ALL, aChecked ); }
void TransactionManager::on_reportOpenAccountsCheckBox_clicked( bool aChecked )     { updateCheckBoxes( REPORT_TAB, ACCOUNTS_CHECKBOX, OPEN_ACCOUNTS, aChecked ); }
void TransactionManager::on_reportAllCategoriesCheckBox_clicked( bool aChecked )    { updateCheckBoxes( REPORT_TAB, CATEGORIES_CHECKBOX, ALL, aChecked ); }
void TransactionManager::on_reportIncomeCategoriesCheckBox_clicked( bool aChecked ) { updateCheckBoxes( REPORT_TAB, CATEGORIES_CHECKBOX, INCOME_CATEGORIES, aChecked ); }
void TransactionManager::on_reportExpenseCategoriesCheckBox_clicked( bool aChecked ){ updateCheckBoxes( REPORT_TAB, CATEGORIES_CHECKBOX, EXPENSE_CATEGORIES, aChecked ); }
void TransactionManager::on_reportAllLabelsCheckBox_clicked( bool aChecked )        { updateCheckBoxes( REPORT_TAB, LABELS_CHECKBOX, ALL, aChecked ); }
