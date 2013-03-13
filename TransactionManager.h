//******************************************************************************
//
//  HEADER NAME: TransactionManager.h
//******************************************************************************

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QDate>
#include <QList>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <QCheckBox>

#include "Account.h"
#include "Month.h"
#include "Transaction.h"
#include "GraphWidget.h"
#include "PieView.h"
#include "ReportTableView.h"

namespace Ui
{
    class TransactionManager;
}

class TransactionManager : public QMainWindow
{
    Q_OBJECT
    
public:
    // Types
    enum TabType
    {
        TRANSACTION_TAB,
        REPORT_TAB,

        TAB_CNT
    };
    struct TransactionFilterType
    {
        bool allAccounts;
        QList<Account*> accountList;
        bool allCategories;
        QList<Category::CategoryIdType> categoriesList;
        bool allLabels;
        QList<Category::LabelIdType> LabelList;
        TransactionFilterType(): allAccounts(true), allCategories(true), allLabels(true){} 
    };

    // Functions
    explicit TransactionManager(QWidget *parent = 0);
    ~TransactionManager();

    // Variables
    static QStringList mFileContents;
    static QList<Account*> mAccountList;
    static QList<Transaction*> mTransactionList;
    static QList<Month*> mMonthList;
    static QDate mFirstTransactionDate;
    static QDate mLastTransactionDate;

private slots:
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionClose_triggered();
    void on_actionFileInputConfig_triggered();
    void on_actionAbout_triggered();
    void on_actionDisplayFile_triggered();
    void on_actionDisplayLog_triggered();

    void on_overviewAccountList_itemDoubleClicked( QListWidgetItem* aItem );
    void on_transactionSelectButton_clicked();
    void on_reportSelectButton_clicked();
    void on_transactionDateThisYearButton_clicked();
    void on_transactionDate1YearButton_clicked();
    void on_transactionDate5YearButton_clicked();
    void on_transactionDate10YearButton_clicked();
    void on_transactionDateAllTimeButton_clicked();
    void on_reportDateThisYearButton_clicked();
    void on_reportDate1YearButton_clicked();
    void on_reportDate5YearButton_clicked();
    void on_reportDate10YearButton_clicked();
    void on_reportDateAllTimeButton_clicked();

    void on_transactionAllAccountsCheckBox_stateChanged( int aCheckState );
    void on_transactionAllCategoriesCheckBox_stateChanged( int aCheckState );
    void on_transactionAllLabelsCheckBox_stateChanged( int aCheckState );
    void on_reportAllAccountsCheckBox_stateChanged( int aCheckState );
    void on_reportAllCategoriesCheckBox_stateChanged( int aCheckState );
    void on_reportAllLabelsCheckBox_stateChanged( int aCheckState );
    void handleShowTransactionByDate( QDate aStartDate, QDate aEndDate );

private:
    // Functions
    void init();
    void updateUI();
    void updateOverviewTab();
    void initTransactionsTab();
    void updateTransactionsTab();
    void initReportsTab();
    void updateReportsTab();
    QList<Account*> filterAccountList( TabType aTabType );
    QList<Transaction*> filterTransactionList( TabType aTabType );

    // Variables
    Ui::TransactionManager *ui;
    QString mFileName;
    QList<QCheckBox*> mTransactionAccountsCheckBoxList;
    QList<QCheckBox*> mTransactionCategoriesCheckBoxList;
    QList<QCheckBox*> mTransactionLabelsCheckBoxList;
    QList<QCheckBox*> mReportAccountsCheckBoxList;
    QList<QCheckBox*> mReportCategoriesCheckBoxList;
    QList<QCheckBox*> mReportLabelsCheckBoxList;
    QButtonGroup mTransactionAccountsCheckBoxGroup;
    QButtonGroup mTransactionCategoriesCheckBoxGroup;
    QButtonGroup mTransactionLabelsCheckBoxGroup;
    QButtonGroup mReportAccountsCheckBoxGroup;
    QButtonGroup mReportCategoriesCheckBoxGroup;
    QButtonGroup mReportLabelsCheckBoxGroup;
    GraphWidget mReportNetIncomeGraph;
    GraphWidget mReportNetWorthGraph;
    ReportTableView mReportTableView;
    PieView mAssetsPieChart;
    PieView mDebtsPieChart;
    PieView mIncomePieChart;
    PieView mExpensePieChart;
};

#endif // TRANSACTIONMANAGER_H
