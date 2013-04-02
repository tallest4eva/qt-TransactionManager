//******************************************************************************
//
//  HEADER NAME: TransactionManager.cpp
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
#include "Account.h"
#include "Category.h"
#include "TransactionManager.h"
#include "Month.h"
#include "Parser.h"
#include "OverviewAccountListItem.h"
#include "TransactionListModel.h"
#include "Logger.h"
#include "DisplayDialog.h"
#include "FileConfigDialog.h"
#include "ReportPieChartModel.h"

// Static variables
QStringList TransactionManager::mFileContents;
QList<Account*> TransactionManager::mAccountList;
QList<Transaction*> TransactionManager::mTransactionList;
QList<Month*> TransactionManager::mMonthList;
QDate TransactionManager::mFirstTransactionDate = QDate();
QDate TransactionManager::mLastTransactionDate = QDate();
QVector<bool> TransactionManager::mCategoriesEnabledList( Category::CATEGORY_TYPE_CNT, false );
QVector<bool> TransactionManager::mLabelsEnabledList( Category::LABEL_CNT, false );

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
    delete ui;
} // TransactionManager::~TransactionManager

//----------------------------------------------------------------------------
// Init
//----------------------------------------------------------------------------
void TransactionManager::init()
{
    // Init Parser
    Parser::restore();
    
    ui->tabWidget->setCurrentIndex(0);
    ui->transactionToolBox->setCurrentIndex(0);
    ui->reportToolBox->setCurrentIndex(0);
    ui->reportDisplayTabWidget->setCurrentIndex(0);
    TransactionListModel* model = new TransactionListModel();
    ui->transactionTableView->setModel( model );
    model->setupTableView( ui->transactionTableView );
    ui->transactionOpenAccountsCheckBox->setDisabled( true );
    ui->reportOpenAccountsCheckBox->setDisabled( true );
    for( int i = 0; i < Category::CATEGORY_TYPE_CNT; i++ )
    {
        QCheckBox* checkbox = new QCheckBox( Category::getCategoryText( (Category::CategoryIdType)i, true ), ui->transactionCategoriesGroupBox );
        ui->transactionCategoriesGroupBox->layout()->addWidget( checkbox );
        mTransactionCategoriesCheckBoxList.push_back( checkbox );

        checkbox = new QCheckBox( Category::getCategoryText( (Category::CategoryIdType)i, true ), ui->reportCategoriesGroupBox );
        ui->reportCategoriesGroupBox->layout()->addWidget( checkbox );
        mReportCategoriesCheckBoxList.push_back( checkbox );
    }
    for( int i = 0; i < Category::LABEL_CNT; i++ )
    {
        QCheckBox* checkbox = new QCheckBox( Category::getLabelText((Category::LabelIdType)i), ui->transactionLabelsGroupBox );
        ui->transactionLabelsGroupBox->layout()->addWidget( checkbox );
        mTransactionLabelsCheckBoxList.push_back( checkbox );

        checkbox = new QCheckBox( Category::getLabelText((Category::LabelIdType)i), ui->reportLabelsGroupBox );
        ui->reportLabelsGroupBox->layout()->addWidget( checkbox );
        mReportLabelsCheckBoxList.push_back( checkbox );
    }

    // Init graph
    mReportNetIncomeGraph.setGraphMode( BarGraph::BAR_NET_INCOME );
    mReportNetWorthGraph.setGraphMode( BarGraph::BAR_NET_WORTH );
    connect( &mReportNetIncomeGraph, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    connect( &mReportNetWorthGraph, SIGNAL(transactionFilterSelected(const Transaction::FilterType&)), this, SLOT(handleShowTransactionByFilter(const Transaction::FilterType&)) );
    connect( &mReportNetIncomeGraph, SIGNAL(reportDateSelected(QDate,QDate)), this, SLOT(handleShowReportByDate(QDate,QDate)) );
    connect( &mReportNetWorthGraph, SIGNAL(reportDateSelected(QDate,QDate)), this, SLOT(handleShowReportByDate(QDate,QDate)) );
    ui->reportNetIncomeTab->layout()->addWidget( &mReportNetIncomeGraph );
    ui->reportNetWorthTab->layout()->addWidget( &mReportNetWorthGraph );
    
    // Init report
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

    ReportPieChartModel* pModel = new ReportPieChartModel( ReportPieChartModel::ASSET_BY_ACCOUNT );
    mAssetsPieChart.setModel( pModel );
    pModel->setupPieView( &mAssetsPieChart );
    pModel = new ReportPieChartModel( ReportPieChartModel::DEBT_BY_ACCOUNT );
    mDebtsPieChart.setModel( pModel );
    pModel->setupPieView( &mDebtsPieChart );
    pModel = new ReportPieChartModel( ReportPieChartModel::INCOME_BY_CATEGORY );
    pModel->setGroupCategories( true );
    mIncomeParentPieChart.setModel( pModel );
    pModel->setupPieView( &mIncomeParentPieChart );
    pModel = new ReportPieChartModel( ReportPieChartModel::EXPENSE_BY_CATEGORY );
    pModel->setGroupCategories( true );
    mExpenseParentPieChart.setModel( pModel );
    pModel->setupPieView( &mExpenseParentPieChart );
    pModel = new ReportPieChartModel( ReportPieChartModel::INCOME_BY_CATEGORY );
    mIncomeSubPieChart.setModel( pModel );
    pModel->setupPieView( &mIncomeSubPieChart );
    pModel = new ReportPieChartModel( ReportPieChartModel::EXPENSE_BY_CATEGORY );
    mExpenseSubPieChart.setModel( pModel );
    pModel->setupPieView( &mExpenseSubPieChart );

} // TransactionManager::init()

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
void TransactionManager::on_actionExit_triggered()
{
    on_actionClose_triggered();
    qApp->quit();
} // TransactionManager::on_actionExit_triggered()

//----------------------------------------------------------------------------
// Constructor
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

        // Close previous file
        on_actionClose_triggered();

        // Parse file contents
        mFileName = fileName;
        QTextStream in( &file );
        mAccountList.clear();
        mTransactionList.clear();
        mMonthList.clear();
        mFileContents.clear();
        mFirstTransactionDate.setDate(2000,1,1);
        mLastTransactionDate.setDate(2000,1,1);
        mCategoriesEnabledList.fill( false );
        mLabelsEnabledList.fill( false );

        Parser::parseFile( in );
        file.close();

        // Update ui contents
        updateUI();
    }
} // TransactionManager::on_actionOpen_triggered()

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
void TransactionManager::on_actionClose_triggered()
{
    if( !mFileName.isEmpty() )
    {
        mFileName.clear();

        // Clear account data
        for( int i = 0; i < mAccountList.size(); i++ )
        {
            delete mAccountList[i];
        }
        for( int i = 0; i < mTransactionList.size(); i++ )
        {
            delete mTransactionList[i];
        }
        for( int i = 0; i < mMonthList.size(); i++ )
        {
            delete mMonthList[i];
        }
        mAccountList.clear();
        mTransactionList.clear();
        mMonthList.clear();
        mFileContents.clear();
        mFirstTransactionDate.setDate(2000,1,1);
        mLastTransactionDate.setDate(2000,1,1);
        Logger::clearLog();

        // Update ui contents
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
            QTextStream stream( &file );
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
    msgBox.setText("Transaction Manager\nAuthor: tallest4eva\nVersion 1.0");
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
    dialog.setDisplay( mFileContents );
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
    // Switch to Transactions and show selected account
    int row = ui->overviewAccountList->row( aItem );
    ui->tabWidget->setCurrentWidget( ui->transactionsTab );
    ui->transactionToolBox->setCurrentWidget( ui->transactionAccountToolBox );
    ui->transactionAllAccountsCheckBox->setCheckState( Qt::Unchecked );
    on_transactionAllAccountsCheckBox_stateChanged( (int)Qt::Unchecked );
    if( mTransactionAccountsCheckBoxList.size() > row )
    {
        mTransactionAccountsCheckBoxList[row]->setCheckState( Qt::Checked );
    }
    on_transactionSelectButton_clicked();
} // TransactionManager::on_overviewAccountList_itemDoubleClicked()

//----------------------------------------------------------------------------
// updateUI
//----------------------------------------------------------------------------
void TransactionManager::updateUI()
{
    // Update ui elements, menu and status
    if( !mFileName.isEmpty() )
    {
        ui->actionClose->setEnabled( true );
        ui->actionDisplayFile->setEnabled( true );
        QString message = "File Opened: " + mFileName;
        ui->statusBar->showMessage( message );
    }
    else
    {
        ui->actionClose->setEnabled( false );
        ui->actionDisplayFile->setEnabled( false );
        ui->statusBar->clearMessage();
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
        ui->overviewNumberOfAccountValue->setNum( mAccountList.size() );
        ui->overviewNumberOfTransactionsValue->setNum( mTransactionList.size() );
        QString str = "$" + QString::number( Account::getTotalAccountBalance(), 'f', 2 );
        if( Account::getTotalAccountBalance() != 0 )
        {
            str.prepend( (Account::getTotalAccountBalance() > 0) ? "<font color=\"darkgreen\">" : "<font color=\"red\">" );
            str.append( "</font>" );
        }
        ui->overviewNetWorthValue->setText( str );
        ui->overviewFirstDateValue->setText( mFirstTransactionDate.toString("yyyy-MM-dd") );
        ui->overviewLastDateValue->setText( mLastTransactionDate.toString("yyyy-MM-dd") );
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
    for( int i = 0; i < mAccountList.size(); i++ )
    {
        QListWidgetItem* listItem = new QListWidgetItem();
        OverviewAccountListItem* item = new OverviewAccountListItem();
        item->setAccount( mAccountList[i] );
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
    ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionAccountToolBox), "Account" );
    ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionCategoriesToolBox), "Categories" );
    ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionLabelsToolBox), "Labels" );
    ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionDateToolBox), "Date" );
    for( int i = 0; i < mTransactionAccountsCheckBoxList.size(); i++ )
    {
        ui->transactionAccountGroupBox->layout()->removeWidget( mTransactionAccountsCheckBoxList[i] );
        delete mTransactionAccountsCheckBoxList[i];
    }
    mTransactionAccountsCheckBoxList.clear();
    ui->transactionAllAccountsCheckBox->setCheckState( Qt::Checked );
    ui->transactionAllCategoriesCheckBox->setCheckState( Qt::Checked );
    ui->transactionAllLabelsCheckBox->setCheckState( Qt::Checked );
    for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
    {
        mTransactionCategoriesCheckBoxList[i]->setDisabled( true );
    }
    for( int i = 0; i < mTransactionLabelsCheckBoxList.size(); i++ )
    {
        mTransactionLabelsCheckBoxList[i]->setDisabled( true );
    }
    ui->transactionAllAccountsCheckBox->setDisabled( true );
    ui->transactionAllCategoriesCheckBox->setDisabled( true );
    ui->transactionAllLabelsCheckBox->setDisabled( true );
    ui->transactionStartDateEdit->clear();
    ui->transactionStartDateEdit->clearMinimumDate();
    ui->transactionStartDateEdit->clearMaximumDate();
    ui->transactionStartDateEdit->setDisabled( true );
    ui->transactionEndDateEdit->clear();
    ui->transactionEndDateEdit->clearMinimumDate();
    ui->transactionEndDateEdit->clearMaximumDate();
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
        for( int i = 0; i < mAccountList.size(); i++ )
        {
            QCheckBox* checkbox = new QCheckBox( mAccountList[i]->getName(), ui->transactionAccountGroupBox );
            checkbox->setCheckState( Qt::Checked );
            ui->transactionAccountGroupBox->layout()->addWidget( checkbox );
            mTransactionAccountsCheckBoxList.push_back( checkbox );
        }
        ui->transactionAllAccountsCheckBox->setDisabled( false );
        ui->transactionAllCategoriesCheckBox->setDisabled( false );
        ui->transactionAllLabelsCheckBox->setDisabled( false );
        for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
        {
            mTransactionCategoriesCheckBoxList[i]->setDisabled( !mCategoriesEnabledList[i] );
        }
        for( int i = 0; i < mTransactionLabelsCheckBoxList.size(); i++ )
        {
            mTransactionLabelsCheckBoxList[i]->setDisabled( !mLabelsEnabledList[i] );
        }
        ui->transactionAllAccountsCheckBox->setCheckState( Qt::Checked );
        ui->transactionStartDateEdit->setDate( mFirstTransactionDate );
        ui->transactionStartDateEdit->setMinimumDate( mFirstTransactionDate );
        ui->transactionStartDateEdit->setMaximumDate( mLastTransactionDate );
        ui->transactionStartDateEdit->setDisabled( false );
        ui->transactionEndDateEdit->setDate( mLastTransactionDate );
        ui->transactionEndDateEdit->setMinimumDate( mFirstTransactionDate );
        ui->transactionEndDateEdit->setMaximumDate( mLastTransactionDate );
        ui->transactionEndDateEdit->setDisabled( false );
        QDate currentDate = QDate::currentDate();
        QDate thisYearDate( currentDate.year(), 1, 1 );
        ui->transactionDateThisYearButton->setEnabled( mFirstTransactionDate < thisYearDate );
        ui->transactionDate1YearButton->setEnabled( mFirstTransactionDate < currentDate.addYears(-1) );
        ui->transactionDate5YearButton->setEnabled( mFirstTransactionDate < currentDate.addYears(-5) );
        ui->transactionDate10YearButton->setEnabled( mFirstTransactionDate < currentDate.addYears(-10) );
        ui->transactionDateAllTimeButton->setEnabled( true );
        ui->transactionSelectButton->setEnabled( true );
        ui->transactionAllButton->setEnabled( true );
    }

    // Init table
    TransactionListModel* model = (TransactionListModel*)ui->transactionTableView->model();
    model->clear();
    ui->transactionTableView->sortByColumn ( (int)TransactionListModel::HDR_NAME, Qt::AscendingOrder );

    // Update transaction table
    updateTransactionsTab();
} // TransactionManager::initTransactionsTab()

//----------------------------------------------------------------------------
// Update Transactions Tab
//----------------------------------------------------------------------------
void TransactionManager::updateTransactionsTab()
{
    TransactionListModel* model = (TransactionListModel*)ui->transactionTableView->model();
    if( !mFileName.isEmpty() )
    {
        mTransactionFilter = getTransactionFilter( TRANSACTION_TAB );
        model->setTransactionFilter( mTransactionFilter );
        model->resort();

        // Update tool box text
        QString str = (mTransactionFilter.mAllAccounts) ? "All" : "Some";
        ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionAccountToolBox), "Account: " + str );
        str = (mTransactionFilter.mAllCategories) ? "All" : "Some";
        ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionCategoriesToolBox), "Categories: " + str );
        str = (mTransactionFilter.mAllLabels) ? "All" : "Some";
        ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionLabelsToolBox), "Labels: " + str );
        str = (mTransactionFilter.mAllDates) ? "All" : "Some";
        ui->transactionToolBox->setItemText( ui->transactionToolBox->indexOf(ui->transactionDateToolBox), "Date: " + str );
    }
    else
    {
        mTransactionFilter = Transaction::FilterType();
        model->clear();
    }
} // TransactionManager::updateTransactionsTab()

//----------------------------------------------------------------------------
// Init Reports Tab
//----------------------------------------------------------------------------
void TransactionManager::initReportsTab()
{
    // Clear reports tab
    ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportAccountToolBox), "Account" );
    ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportCategoriesToolBox), "Categories" );
    ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportLabelsToolBox), "Labels" );
    ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportDateToolBox), "Date" );
    for( int i = 0; i < mReportAccountsCheckBoxList.size(); i++ )
    {
        ui->reportAccountGroupBox->layout()->removeWidget( mReportAccountsCheckBoxList[i] );
        delete mReportAccountsCheckBoxList[i];
    }
    mReportAccountsCheckBoxList.clear();
    ui->reportAllAccountsCheckBox->setCheckState( Qt::Checked );
    ui->reportAllCategoriesCheckBox->setCheckState( Qt::Checked );
    ui->reportAllLabelsCheckBox->setCheckState( Qt::Checked );
    for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
    {
        mReportCategoriesCheckBoxList[i]->setDisabled( true );
    }
    for( int i = 0; i < mReportLabelsCheckBoxList.size(); i++ )
    {
        mReportLabelsCheckBoxList[i]->setDisabled( true );
    }
    ui->reportAllAccountsCheckBox->setDisabled( true );
    ui->reportAllCategoriesCheckBox->setDisabled( true );
    ui->reportAllLabelsCheckBox->setDisabled( true );
    ui->reportStartDateEdit->clear();
    ui->reportStartDateEdit->clearMinimumDate();
    ui->reportStartDateEdit->clearMaximumDate();
    ui->reportStartDateEdit->setDisabled( true );
    ui->reportEndDateEdit->clear();
    ui->reportEndDateEdit->clearMinimumDate();
    ui->reportEndDateEdit->clearMaximumDate();
    ui->reportEndDateEdit->setDisabled( true );
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
        for( int i = 0; i < mAccountList.size(); i++ )
        {
            QCheckBox* checkbox = new QCheckBox( mAccountList[i]->getName(), ui->reportAccountGroupBox );
            checkbox->setCheckState( Qt::Checked );
            ui->reportAccountGroupBox->layout()->addWidget( checkbox );
            mReportAccountsCheckBoxList.push_back( checkbox );
        }
        ui->reportAllAccountsCheckBox->setDisabled( false );
        ui->reportAllCategoriesCheckBox->setDisabled( false );
        ui->reportAllLabelsCheckBox->setDisabled( false );
        for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
        {
            mReportCategoriesCheckBoxList[i]->setDisabled( !mCategoriesEnabledList[i] );
        }
        for( int i = 0; i < mReportLabelsCheckBoxList.size(); i++ )
        {
            mReportLabelsCheckBoxList[i]->setDisabled( !mLabelsEnabledList[i] );
        }
        ui->reportAllAccountsCheckBox->setCheckState( Qt::Checked );
        ui->reportStartDateEdit->setDate( mFirstTransactionDate );
        ui->reportStartDateEdit->setMinimumDate( mFirstTransactionDate );
        ui->reportStartDateEdit->setMaximumDate( mLastTransactionDate );
        ui->reportStartDateEdit->setDisabled( false );
        ui->reportEndDateEdit->setDate( mLastTransactionDate );
        ui->reportEndDateEdit->setMinimumDate( mFirstTransactionDate );
        ui->reportEndDateEdit->setMaximumDate( mLastTransactionDate );
        ui->reportEndDateEdit->setDisabled( false );
        QDate currentDate = QDate::currentDate();
        QDate thisYearDate( currentDate.year(), 1, 1 );
        ui->reportDateThisYearButton->setEnabled( mFirstTransactionDate < thisYearDate );
        ui->reportDate1YearButton->setEnabled( mFirstTransactionDate < currentDate.addYears(-1) );
        ui->reportDate5YearButton->setEnabled( mFirstTransactionDate < currentDate.addYears(-5) );
        ui->reportDate10YearButton->setEnabled( mFirstTransactionDate < currentDate.addYears(-10) );
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
            ReportPieChartModel* model = (ReportPieChartModel*)mPieChartList[i]->model();
            model->setTransactionFilter( mReportFilter );
        }

        // Update tool box text
        QString str = (mReportFilter.mAllAccounts) ? "All" : "Some";
        ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportAccountToolBox), "Account: " + str );
        str = (mReportFilter.mAllCategories) ? "All" : "Some";
        ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportCategoriesToolBox), "Categories: " + str );
        str = (mReportFilter.mAllLabels) ? "All" : "Some";
        ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportLabelsToolBox), "Labels: " + str );
        str = (mReportFilter.mAllDates) ? "All" : "Some";
        ui->reportToolBox->setItemText( ui->reportToolBox->indexOf(ui->reportDateToolBox), "Date: " + str );
    }
    else
    {
        mReportFilter = Transaction::FilterType();
        mReportNetIncomeGraph.clear();
        mReportNetWorthGraph.clear();
        mReportTableView.clear();
        for( int i = 0; i < mPieChartList.size(); i++ )
        {
            ReportPieChartModel* model = (ReportPieChartModel*)mPieChartList[i]->model();
            model->clear();
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
            ( mReportAccountsCheckBoxList[i]->checkState() == Qt::Unchecked ) ? filter.mAllAccounts = false : filter.mAccountList.push_back( mAccountList[i] );
        }
        for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
        {
            ( mReportCategoriesCheckBoxList[i]->checkState() == Qt::Unchecked ) ? filter.mAllCategories = false : filter.mCategoryList[i] = true;
        }
        for( int i = 0; i < mReportLabelsCheckBoxList.size(); i++ )
        {
            ( mReportLabelsCheckBoxList[i]->checkState() == Qt::Unchecked ) ? filter.mAllLabels = false : filter.mLabelList[i] = true;
        }
        filter.mStartDate = ui->reportStartDateEdit->date();
        filter.mEndDate = ui->reportEndDateEdit->date();
        break;
    case TRANSACTION_TAB:
    default:
        for( int i = 0; i < mTransactionAccountsCheckBoxList.size(); i++ )
        {
            ( mTransactionAccountsCheckBoxList[i]->checkState() == Qt::Unchecked ) ? filter.mAllAccounts = false : filter.mAccountList.push_back( mAccountList[i] );
        }
        for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
        {
            ( mTransactionCategoriesCheckBoxList[i]->checkState() == Qt::Unchecked ) ? filter.mAllCategories = false : filter.mCategoryList[i] = true;
        }
        for( int i = 0; i < mTransactionLabelsCheckBoxList.size(); i++ )
        {
            ( mTransactionLabelsCheckBoxList[i]->checkState() == Qt::Unchecked ) ? filter.mAllLabels = false : filter.mLabelList[i] = true;
        }
        filter.mStartDate = ui->transactionStartDateEdit->date();
        filter.mEndDate = ui->transactionEndDateEdit->date();
        break;
    }
    // If not all dates are set
    if( mFirstTransactionDate < filter.mStartDate || mLastTransactionDate > filter.mEndDate )
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
    ui->transactionToolBox->setCurrentWidget( ui->transactionDateToolBox );
    on_transactionAllAccountsCheckBox_stateChanged( (int)Qt::Unchecked );
    for( int i = 0; i < aFilter.mAccountList.size(); i++ )
    {
        int index = Account::getAccountIndex( aFilter.mAccountList[i] );
        if( index >= 0 )
        {
            mTransactionAccountsCheckBoxList[index]->setCheckState( Qt::Checked );
        }
    }
    for( int i = 0; i < aFilter.mCategoryList.size(); i++ )
    {
        mTransactionCategoriesCheckBoxList[i]->setCheckState( ( aFilter.mCategoryList[i] ) ? Qt::Checked : Qt::Unchecked );
    }
    for( int i = 0; i < aFilter.mLabelList.size(); i++ )
    {
        mTransactionLabelsCheckBoxList[i]->setCheckState( ( aFilter.mLabelList[i] ) ? Qt::Checked : Qt::Unchecked );
    }
    ui->transactionStartDateEdit->setDate( aFilter.mStartDate );
    ui->transactionEndDateEdit->setDate( aFilter.mEndDate );
    on_transactionSelectButton_clicked();
} // TransactionManager::handleShowTransactionByFilter

//----------------------------------------------------------------------------
// Handle Show Transaction By Date
//----------------------------------------------------------------------------
void TransactionManager::handleShowTransactionByDate( QDate aStartDate, QDate aEndDate )
{
    // Switch to transaction tab
    ui->tabWidget->setCurrentWidget( ui->transactionsTab );
    ui->transactionToolBox->setCurrentWidget( ui->transactionDateToolBox );
    ui->transactionStartDateEdit->setDate( aStartDate );
    ui->transactionEndDateEdit->setDate( aEndDate );
    ui->transactionAllAccountsCheckBox->setCheckState( Qt::Checked );
    on_transactionAllAccountsCheckBox_stateChanged( (int)Qt::Checked );
    ui->transactionAllCategoriesCheckBox->setCheckState( Qt::Checked );
    on_transactionAllCategoriesCheckBox_stateChanged( (int)Qt::Checked );
    ui->transactionAllLabelsCheckBox->setCheckState( Qt::Checked );
    on_transactionAllLabelsCheckBox_stateChanged( (int)Qt::Checked );
    on_transactionSelectButton_clicked();
} // TransactionManager::handleShowTransactionByDate()

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
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionDateThisYearButton_clicked()
{
    QDate date( QDate::currentDate().year(), 1, 1 );
    QDate startDate = ( mFirstTransactionDate > date ) ? mFirstTransactionDate : date;
    QDate endDate = ( mLastTransactionDate < QDate::currentDate() ) ? mLastTransactionDate : QDate::currentDate();
    ui->transactionStartDateEdit->setDate( startDate );
    ui->transactionEndDateEdit->setDate( endDate );
    on_transactionSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionDate1YearButton_clicked()
{
    QDate date( QDate::currentDate().addYears(-1) );
    QDate startDate = ( mFirstTransactionDate > date ) ? mFirstTransactionDate : date;
    QDate endDate = ( mLastTransactionDate < QDate::currentDate() ) ? mLastTransactionDate : QDate::currentDate();
    ui->transactionStartDateEdit->setDate( startDate );
    ui->transactionEndDateEdit->setDate( endDate );
    on_transactionSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionDate5YearButton_clicked()
{
    QDate date( QDate::currentDate().addYears(-5) );
    QDate startDate = ( mFirstTransactionDate > date ) ? mFirstTransactionDate : date;
    QDate endDate = ( mLastTransactionDate < QDate::currentDate() ) ? mLastTransactionDate : QDate::currentDate();
    ui->transactionStartDateEdit->setDate( startDate );
    ui->transactionEndDateEdit->setDate( endDate );
    on_transactionSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionDate10YearButton_clicked()
{
    QDate date( QDate::currentDate().addYears(-10) );
    QDate startDate = ( mFirstTransactionDate > date ) ? mFirstTransactionDate : date;
    QDate endDate = ( mLastTransactionDate < QDate::currentDate() ) ? mLastTransactionDate : QDate::currentDate();
    ui->transactionStartDateEdit->setDate( startDate );
    ui->transactionEndDateEdit->setDate( endDate );
    on_transactionSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionDateAllTimeButton_clicked()
{
    ui->transactionStartDateEdit->setDate( mFirstTransactionDate );
    ui->transactionEndDateEdit->setDate( mLastTransactionDate );
    on_transactionSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_transactionAllButton_clicked()
{
    ui->transactionStartDateEdit->setDate( mFirstTransactionDate );
    ui->transactionEndDateEdit->setDate( mLastTransactionDate );
    ui->transactionAllAccountsCheckBox->setCheckState( Qt::Checked );
    on_transactionAllAccountsCheckBox_stateChanged( (int)Qt::Checked );
    ui->transactionAllCategoriesCheckBox->setCheckState( Qt::Checked );
    on_transactionAllCategoriesCheckBox_stateChanged( (int)Qt::Checked );
    ui->transactionAllLabelsCheckBox->setCheckState( Qt::Checked );
    on_transactionAllLabelsCheckBox_stateChanged( (int)Qt::Checked );
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
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportDateThisYearButton_clicked()
{
    QDate date( QDate::currentDate().year(), 1, 1 );
    QDate startDate = ( mFirstTransactionDate > date ) ? mFirstTransactionDate : date;
    QDate endDate = ( mLastTransactionDate < QDate::currentDate() ) ? mLastTransactionDate : QDate::currentDate();
    ui->reportStartDateEdit->setDate( startDate );
    ui->reportEndDateEdit->setDate( endDate );
    on_reportSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportDate1YearButton_clicked()
{
    QDate date( QDate::currentDate().addYears(-1) );
    QDate startDate = ( mFirstTransactionDate > date ) ? mFirstTransactionDate : date;
    QDate endDate = ( mLastTransactionDate < QDate::currentDate() ) ? mLastTransactionDate : QDate::currentDate();
    ui->reportStartDateEdit->setDate( startDate );
    ui->reportEndDateEdit->setDate( endDate );
    on_reportSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportDate5YearButton_clicked()
{
    QDate date( QDate::currentDate().addYears(-5) );
    QDate startDate = ( mFirstTransactionDate > date ) ? mFirstTransactionDate : date;
    QDate endDate = ( mLastTransactionDate < QDate::currentDate() ) ? mLastTransactionDate : QDate::currentDate();
    ui->reportStartDateEdit->setDate( startDate );
    ui->reportEndDateEdit->setDate( endDate );
    on_reportSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportDate10YearButton_clicked()
{
    QDate date( QDate::currentDate().addYears(-10) );
    QDate startDate = ( mFirstTransactionDate > date ) ? mFirstTransactionDate : date;
    QDate endDate = ( mLastTransactionDate < QDate::currentDate() ) ? mLastTransactionDate : QDate::currentDate();
    ui->reportStartDateEdit->setDate( startDate );
    ui->reportEndDateEdit->setDate( endDate );
    on_reportSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportDateAllTimeButton_clicked()
{
    ui->reportStartDateEdit->setDate( mFirstTransactionDate );
    ui->reportEndDateEdit->setDate( mLastTransactionDate );
    on_reportSelectButton_clicked();
}
//----------------------------------------------------------------------------
// Button clicked
//----------------------------------------------------------------------------
void TransactionManager::on_reportAllButton_clicked()
{
    ui->reportStartDateEdit->setDate( mFirstTransactionDate );
    ui->reportEndDateEdit->setDate( mLastTransactionDate );
    ui->reportAllAccountsCheckBox->setCheckState( Qt::Checked );
    on_reportAllAccountsCheckBox_stateChanged( (int)Qt::Checked );
    ui->reportAllCategoriesCheckBox->setCheckState( Qt::Checked );
    on_reportAllCategoriesCheckBox_stateChanged( (int)Qt::Checked );
    ui->reportAllLabelsCheckBox->setCheckState( Qt::Checked );
    on_reportAllLabelsCheckBox_stateChanged( (int)Qt::Checked );
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
// on_transactionAllAccountsCheckBox_stateChanged
//----------------------------------------------------------------------------
void TransactionManager::on_transactionAllAccountsCheckBox_stateChanged( int aCheckState )
{
    for( int i = 0; i < mTransactionAccountsCheckBoxList.size(); i++ )
    {
        mTransactionAccountsCheckBoxList[i]->setCheckState( (Qt::CheckState)aCheckState );
    }
} // TransactionManager::on_transactionAllAccountsCheckBox_stateChanged()

//----------------------------------------------------------------------------
// on_transactionAllCategoriesCheckBox_stateChanged
//----------------------------------------------------------------------------
void TransactionManager::on_transactionAllCategoriesCheckBox_stateChanged( int aCheckState )
{
    for( int i = 0; i < mTransactionCategoriesCheckBoxList.size(); i++ )
    {
        mTransactionCategoriesCheckBoxList[i]->setCheckState( (Qt::CheckState)aCheckState );
    }
} // TransactionManager::on_transactionAllCategoriesCheckBox_stateChanged()

//----------------------------------------------------------------------------
// on_transactionAllLabelsCheckBox_stateChanged
//----------------------------------------------------------------------------
void TransactionManager::on_transactionAllLabelsCheckBox_stateChanged( int aCheckState )
{
    for( int i = 0; i < mTransactionLabelsCheckBoxList.size(); i++ )
    {
        mTransactionLabelsCheckBoxList[i]->setCheckState( (Qt::CheckState)aCheckState );
    }
} // TransactionManager::on_transactionAllLabelsCheckBox_stateChanged()

//----------------------------------------------------------------------------
// on_reportAllAccountsCheckBox_stateChanged
//----------------------------------------------------------------------------
void TransactionManager::on_reportAllAccountsCheckBox_stateChanged( int aCheckState )
{
    for( int i = 0; i < mReportAccountsCheckBoxList.size(); i++ )
    {
        mReportAccountsCheckBoxList[i]->setCheckState( (Qt::CheckState)aCheckState );
    }
} // TransactionManager::on_reportAllAccountsCheckBox_stateChanged()

//----------------------------------------------------------------------------
// on_reportAllCategoriesCheckBox_stateChanged
//----------------------------------------------------------------------------
void TransactionManager::on_reportAllCategoriesCheckBox_stateChanged( int aCheckState )
{
    for( int i = 0; i < mReportCategoriesCheckBoxList.size(); i++ )
    {
        mReportCategoriesCheckBoxList[i]->setCheckState( (Qt::CheckState)aCheckState );
    }
} // TransactionManager::on_reportAllCategoriesCheckBox_stateChanged()

//----------------------------------------------------------------------------
// on_reportAllLabelsCheckBox_stateChanged
//----------------------------------------------------------------------------
void TransactionManager::on_reportAllLabelsCheckBox_stateChanged( int aCheckState )
{
    for( int i = 0; i < mReportLabelsCheckBoxList.size(); i++ )
    {
        mReportLabelsCheckBoxList[i]->setCheckState( (Qt::CheckState)aCheckState );
    }
} // TransactionManager::on_reportAllLabelsCheckBox_stateChanged()
