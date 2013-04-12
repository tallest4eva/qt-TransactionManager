//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: TransactionManager.h
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

#include "Transaction.h"
#include "TransactionList.h"
#include "BarGraph.h"
#include "ReportPieChart.h"
#include "ReportTableView.h"

class Account;
class Month;

namespace Ui
{
    class TransactionManager;
}

class TransactionManager : public QMainWindow
{
    Q_OBJECT
    
private:
    // Types
    enum TabType
    {
        TRANSACTION_TAB,
        REPORT_TAB,

        TAB_CNT
    };
    enum CheckBoxType
    {
        ACCOUNTS_CHECKBOX,
        CATEGORIES_CHECKBOX,
        LABELS_CHECKBOX
    };
    enum SelectType
    {
        ALL,
        OPEN_ACCOUNTS,
        INCOME_CATEGORIES,
        EXPENSE_CATEGORIES
    };

public:
    // Functions
    explicit TransactionManager(QWidget *parent = 0);
    ~TransactionManager();

    // Variables
    static QStringList sFileContents;
    static QList<Account*> sAccountList;
    static QList<Transaction*> sTransactionList;
    static QList<Month*> sMonthList;
    static QDate sFirstTransactionDate;
    static QDate sLastTransactionDate;
    static QVector<bool> sCategoriesEnabledList;
    static QVector<bool> sLabelsEnabledList;

    static const QDate cDefaultStartDate;
    static const QDate cDefaultEndDate;

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
    void on_transactionAllButton_clicked();
    void on_reportDateThisYearButton_clicked();
    void on_reportDate1YearButton_clicked();
    void on_reportDate5YearButton_clicked();
    void on_reportDate10YearButton_clicked();
    void on_reportDateAllTimeButton_clicked();
    void on_reportAllButton_clicked();

    void on_transactionAllAccountsCheckBox_clicked( bool aChecked );
    void on_transactionOpenAccountsCheckBox_clicked( bool aChecked );
    void on_transactionAllCategoriesCheckBox_clicked( bool aChecked );
    void on_transactionIncomeCategoriesCheckBox_clicked( bool aChecked );
    void on_transactionExpenseCategoriesCheckBox_clicked( bool aChecked );
    void on_transactionAllLabelsCheckBox_clicked( bool aChecked );
    void on_reportAllAccountsCheckBox_clicked( bool aChecked );
    void on_reportOpenAccountsCheckBox_clicked( bool aChecked );
    void on_reportAllCategoriesCheckBox_clicked( bool aChecked );
    void on_reportIncomeCategoriesCheckBox_clicked( bool aChecked );
    void on_reportExpenseCategoriesCheckBox_clicked( bool aChecked );
    void on_reportAllLabelsCheckBox_clicked( bool aChecked );

    void handleShowTransactionByFilter( const Transaction::FilterType& aFilter );
    void handleShowReportByDate( QDate aStartDate, QDate aEndDate );

private:
    // Functions
    void init();
    void deInit();
    void updateUI();
    void clearData();
    void updateOverviewTab();
    void initTransactionsTab();
    void updateTransactionsTab();
    void initReportsTab();
    void updateReportsTab();
    Transaction::FilterType getTransactionFilter( TabType aTabType );
    void updateAndApplyDates( TabType aTab, QDate aStartDate, QDate aEndDate );
    void updateCheckBoxes( TabType aTab, CheckBoxType aCheckType, SelectType aSelectType, bool aChecked );

    // Variables
    Ui::TransactionManager *ui;
    QString mFileName;
    QLabel mStatusLabel;
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
    Transaction::FilterType mTransactionFilter;
    Transaction::FilterType mReportFilter;
    BarGraph mReportNetIncomeGraph;
    BarGraph mReportNetWorthGraph;
    TransactionList mTransactionTableView;
    ReportTableView mReportTableView;
    ReportPieChart mAssetsPieChart;
    ReportPieChart mDebtsPieChart;
    ReportPieChart mIncomeParentPieChart;
    ReportPieChart mExpenseParentPieChart;
    ReportPieChart mIncomeSubPieChart;
    ReportPieChart mExpenseSubPieChart;
    QList<ReportPieChart*> mPieChartList;
};

#endif // TRANSACTIONMANAGER_H
