//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: TransactionManager.h
//******************************************************************************

#ifndef TRANSACTIONMANAGER_HPP
#define TRANSACTIONMANAGER_HPP

#include <QMainWindow>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDate>
#include <QList>
#include <QString>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "Transaction.hpp"
#include "TransactionList.hpp"
#include "BarGraph.hpp"
#include "ReportPieChart.hpp"
#include "ReportTableView.hpp"

class Account;
class Month;
class QListWidgetItem;
class TripleRadioButton;

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
    enum ToolBoxType
    {
        TOOLS_ACCOUNTS      = 1 << 0,
        TOOLS_CATEGORIES    = 1 << 1,
        TOOLS_LABELS        = 1 << 2,
        TOOLS_DATE          = 1 << 3
    };

public:
    // Functions
    explicit TransactionManager(QWidget *parent = 0);
    ~TransactionManager();

    // Variables
    static QStringList sFileContents;
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
    void on_actionDisplayAbout_triggered();
    void on_actionDisplayFile_triggered();
    void on_actionDisplayLog_triggered();
    void on_actionDisplayHelp_triggered();

    void on_overviewAccountList_itemDoubleClicked( QListWidgetItem* aItem );
    void on_overviewAccountList_currentItemChanged( QListWidgetItem* aCurrentItem, QListWidgetItem* aPreviousItem );
    void on_overviewShowClosedAccountsCheckBox_clicked( bool aChecked );
    void on_overviewSortAccountsComboBox_activated( const QString& aText );

    void on_transactionSelectButton_clicked();
    void on_transactionShowInReportsButton_clicked();
    void on_transactionSearchButton_clicked();
    void on_transactionSearchClearButton_clicked();
    void on_transactionSearchTextLineEdit_returnPressed();
    void on_transactionSearchTextLineEdit_textChanged( const QString& aText );
    void on_transactionDateComboBox_activated( const QString& aText );
    void on_transactionAllButton_clicked();
    void on_transactionAllAccountsCheckBox_clicked( bool aChecked );
    void on_transactionOpenAccountsCheckBox_clicked( bool aChecked );
    void on_transactionAllCategoriesCheckBox_clicked( bool aChecked );
    void on_transactionIncomeCategoriesCheckBox_clicked( bool aChecked );
    void on_transactionExpenseCategoriesCheckBox_clicked( bool aChecked );
    void on_transactionTransferCategoriesCheckBox_clicked( bool aChecked );
    void on_transactionAllLabelsCheckBox_clicked( bool aChecked );
    void on_mTransactionCategoriesTreeExpandButton_clicked();
    void handleTransactionAccountsCheckBox_clicked( bool aChecked );
    void handleTransactionLabelsCheckBox_clicked();

    void on_reportAllAccountsCheckBox_clicked( bool aChecked );
    void on_reportOpenAccountsCheckBox_clicked( bool aChecked );
    void on_reportAllCategoriesCheckBox_clicked( bool aChecked );
    void on_reportIncomeCategoriesCheckBox_clicked( bool aChecked );
    void on_reportExpenseCategoriesCheckBox_clicked( bool aChecked );
    void on_reportTransferCategoriesCheckBox_clicked( bool aChecked );
    void on_reportAllLabelsCheckBox_clicked( bool aChecked );
    void on_mReportShowNetIncomeCheckBox_clicked( bool aChecked );
    void on_mReportShowTransfersCheckBox_clicked( bool aChecked );
    void on_mReportCategoriesTreeExpandButton_clicked();
    void on_reportSelectButton_clicked();
    void on_reportShowInTransactionsButton_clicked();
    void on_reportDateComboBox_activated( const QString& aText );
    void on_reportDateIntervalComboBox_activated( const QString& aText );
    void on_reportAllButton_clicked();
    void on_mReportAssetDebtComboBox_currentIndexChanged( const QString& aText );
    void on_mReportIncomeExpenseComboBox_currentIndexChanged( const QString& aText );
    void on_mReportSubIncomeExpenseComboBox_currentIndexChanged( const QString& aText );
    void handleReportAccountsCheckBox_clicked( bool aChecked );
    void handleReportLabelsCheckBox_clicked();

    void handleParentCategoriesCheckBoxClicked( QTreeWidgetItem* aItem, int aColumn );
    void handleShowTransactionByFilter( const Transaction::FilterType& aFilter );
    void handleShowReportByFilter( const Transaction::FilterType& aFilter );
    void handleShowReportByDate( const QDate& aStartDate, const QDate& aEndDate );

private:
    // Functions
    void init();
    void deInit();
    void updateUI();
    void clearData();
    void updateOverviewTab();
    void updateAccountsList();
    void resetTransactionsTab();
    void updateTransactionsTab();
    void resetReportsTab();
    void updateReportsTab();
    Transaction::FilterType getTransactionFilter( TabType aTabType );
    void updateAndApplyDates( TabType aTabType, const QDate& aStartDate, const QDate& aEndDate );
    void updateFilterToolBox( TabType aTabType, int aToolBoxType, const Transaction::FilterType& aFilter );

    // Variables
    Ui::TransactionManager *mUi;
    QString mFileName;
    QLabel mStatusFileLabel;
    QLabel mStatusConfigLabel;
    QList<QCheckBox*> mTransactionAccountsCheckBoxList;
    QTreeWidget mTransactionCategoriesTreeWidget;
    QList<QTreeWidgetItem*> mTransactionParentCategoriesCheckBoxList;
    QList<QTreeWidgetItem*> mTransactionCategoriesCheckBoxList;
    QList<TripleRadioButton*> mTransactionLabelsButtonList;
    QList<QCheckBox*> mReportAccountsCheckBoxList;
    QTreeWidget mReportCategoriesTreeWidget;
    QList<QTreeWidgetItem*> mReportParentCategoriesCheckBoxList;
    QList<QTreeWidgetItem*> mReportCategoriesCheckBoxList;
    QList<TripleRadioButton*> mReportLabelsButtonList;
    Transaction::FilterType mTransactionFilter;
    Transaction::FilterType mReportFilter;
    BarGraph mReportNetIncomeGraph;
    BarGraph mReportNetWorthGraph;
    BarGraph mReportAccountBalanceGraph;
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

#endif // TRANSACTIONMANAGER_HPP
