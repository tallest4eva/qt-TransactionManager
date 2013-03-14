/********************************************************************************
** Form generated from reading UI file 'transactionmanager.ui'
**
** Created: Wed Mar 13 18:38:03 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONMANAGER_H
#define UI_TRANSACTIONMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransactionManager
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionClose;
    QAction *actionAbout;
    QAction *actionDisplayFile;
    QAction *actionDisplayLog;
    QAction *actionFileInputConfig;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *overviewTab;
    QHBoxLayout *horizontalLayout_2;
    QWidget *overviewAccountWidget;
    QVBoxLayout *verticalLayout;
    QLabel *overviewAccountTitle;
    QListWidget *overviewAccountList;
    QWidget *overviewDisplayWidget;
    QHBoxLayout *horizontalLayout_8;
    QFormLayout *formLayout;
    QLabel *overviewNumberOfAccountsLabel;
    QLabel *overviewNumberOfTransactionsLabel;
    QLabel *overviewNumberOfAccountValue;
    QLabel *overviewNumberOfTransactionsValue;
    QLabel *overviewNetWorthValue;
    QLabel *overviewNetWorthLabel;
    QLabel *overviewFirstDateLabel;
    QLabel *overviewFirstDateValue;
    QLabel *overviewLastDateLabel;
    QLabel *overviewLastDateValue;
    QWidget *transactionsTab;
    QHBoxLayout *horizontalLayout_5;
    QWidget *transactionSelectWidget;
    QVBoxLayout *verticalLayout_14;
    QToolBox *transactionToolBox;
    QWidget *transactionAccountToolBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *transactionAllAccountsCheckBox;
    QCheckBox *transactionOpenAccountsCheckBox;
    QGroupBox *transactionAccountGroupBox;
    QVBoxLayout *verticalLayout_3;
    QWidget *transactionCategoriesToolBox;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *transactionAllCategoriesCheckBox;
    QGroupBox *transactionCategoriesGroupBox;
    QVBoxLayout *verticalLayout_5;
    QWidget *transactionLabelsToolBox;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *transactionAllLabelsCheckBox;
    QGroupBox *transactionLabelsGroupBox;
    QVBoxLayout *verticalLayout_7;
    QWidget *transactionDateToolBox;
    QFormLayout *formLayout_1;
    QLabel *transactionStartDateLabel;
    QDateEdit *transactionStartDateEdit;
    QLabel *transactionEndDateLabel;
    QDateEdit *transactionEndDateEdit;
    QPushButton *transactionDateThisYearButton;
    QPushButton *transactionDate1YearButton;
    QPushButton *transactionDate5YearButton;
    QPushButton *transactionDate10YearButton;
    QPushButton *transactionDateAllTimeButton;
    QPushButton *transactionSelectButton;
    QTableView *transactionTableView;
    QWidget *reportTab;
    QHBoxLayout *horizontalLayout_6;
    QWidget *reportSelectWidget;
    QVBoxLayout *verticalLayout_15;
    QToolBox *reportToolBox;
    QWidget *reportAccountToolBox;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *reportAllAccountsCheckBox;
    QCheckBox *reportOpenAccountsCheckBox;
    QGroupBox *reportAccountGroupBox;
    QVBoxLayout *verticalLayout_9;
    QWidget *reportCategoriesToolBox;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *reportAllCategoriesCheckBox;
    QGroupBox *reportCategoriesGroupBox;
    QVBoxLayout *verticalLayout_11;
    QWidget *reportLabelsToolBox;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *reportAllLabelsCheckBox;
    QGroupBox *reportLabelsGroupBox;
    QVBoxLayout *verticalLayout_13;
    QWidget *reportDateToolBox;
    QFormLayout *formLayout_2;
    QLabel *reportStartDateLabel;
    QDateEdit *reportStartDateEdit;
    QLabel *reportEndDateLabel;
    QDateEdit *reportEndDateEdit;
    QPushButton *reportDateThisYearButton;
    QPushButton *reportDate1YearButton;
    QPushButton *reportDate5YearButton;
    QPushButton *reportDate10YearButton;
    QPushButton *reportDateAllTimeButton;
    QPushButton *reportSelectButton;
    QTabWidget *reportDisplayTabWidget;
    QWidget *reportNetIncomeTab;
    QHBoxLayout *horizontalLayout_3;
    QWidget *reportNetWorthTab;
    QHBoxLayout *horizontalLayout_4;
    QWidget *reportListTab;
    QHBoxLayout *horizontalLayout_7;
    QWidget *reportAccountTab;
    QHBoxLayout *horizontalLayout_9;
    QWidget *reportCategoryTab;
    QHBoxLayout *horizontalLayout_10;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuTools;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TransactionManager)
    {
        if (TransactionManager->objectName().isEmpty())
            TransactionManager->setObjectName(QString::fromUtf8("TransactionManager"));
        TransactionManager->resize(1204, 685);
        actionOpen = new QAction(TransactionManager);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(TransactionManager);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        actionSaveAs = new QAction(TransactionManager);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionSaveAs->setEnabled(false);
        actionExit = new QAction(TransactionManager);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionClose = new QAction(TransactionManager);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClose->setEnabled(false);
        actionAbout = new QAction(TransactionManager);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionDisplayFile = new QAction(TransactionManager);
        actionDisplayFile->setObjectName(QString::fromUtf8("actionDisplayFile"));
        actionDisplayLog = new QAction(TransactionManager);
        actionDisplayLog->setObjectName(QString::fromUtf8("actionDisplayLog"));
        actionFileInputConfig = new QAction(TransactionManager);
        actionFileInputConfig->setObjectName(QString::fromUtf8("actionFileInputConfig"));
        centralWidget = new QWidget(TransactionManager);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabShape(QTabWidget::Rounded);
        overviewTab = new QWidget();
        overviewTab->setObjectName(QString::fromUtf8("overviewTab"));
        horizontalLayout_2 = new QHBoxLayout(overviewTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        overviewAccountWidget = new QWidget(overviewTab);
        overviewAccountWidget->setObjectName(QString::fromUtf8("overviewAccountWidget"));
        verticalLayout = new QVBoxLayout(overviewAccountWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        overviewAccountTitle = new QLabel(overviewAccountWidget);
        overviewAccountTitle->setObjectName(QString::fromUtf8("overviewAccountTitle"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        overviewAccountTitle->setFont(font);

        verticalLayout->addWidget(overviewAccountTitle);

        overviewAccountList = new QListWidget(overviewAccountWidget);
        overviewAccountList->setObjectName(QString::fromUtf8("overviewAccountList"));
        overviewAccountList->setSelectionMode(QAbstractItemView::SingleSelection);
        overviewAccountList->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(overviewAccountList);


        horizontalLayout_2->addWidget(overviewAccountWidget);

        overviewDisplayWidget = new QWidget(overviewTab);
        overviewDisplayWidget->setObjectName(QString::fromUtf8("overviewDisplayWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(overviewDisplayWidget->sizePolicy().hasHeightForWidth());
        overviewDisplayWidget->setSizePolicy(sizePolicy1);
        horizontalLayout_8 = new QHBoxLayout(overviewDisplayWidget);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        overviewNumberOfAccountsLabel = new QLabel(overviewDisplayWidget);
        overviewNumberOfAccountsLabel->setObjectName(QString::fromUtf8("overviewNumberOfAccountsLabel"));
        QFont font1;
        font1.setPointSize(10);
        overviewNumberOfAccountsLabel->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, overviewNumberOfAccountsLabel);

        overviewNumberOfTransactionsLabel = new QLabel(overviewDisplayWidget);
        overviewNumberOfTransactionsLabel->setObjectName(QString::fromUtf8("overviewNumberOfTransactionsLabel"));
        overviewNumberOfTransactionsLabel->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, overviewNumberOfTransactionsLabel);

        overviewNumberOfAccountValue = new QLabel(overviewDisplayWidget);
        overviewNumberOfAccountValue->setObjectName(QString::fromUtf8("overviewNumberOfAccountValue"));
        overviewNumberOfAccountValue->setMinimumSize(QSize(0, 25));
        QFont font2;
        font2.setPointSize(12);
        overviewNumberOfAccountValue->setFont(font2);
        overviewNumberOfAccountValue->setFrameShape(QFrame::StyledPanel);
        overviewNumberOfAccountValue->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(0, QFormLayout::FieldRole, overviewNumberOfAccountValue);

        overviewNumberOfTransactionsValue = new QLabel(overviewDisplayWidget);
        overviewNumberOfTransactionsValue->setObjectName(QString::fromUtf8("overviewNumberOfTransactionsValue"));
        overviewNumberOfTransactionsValue->setFont(font2);
        overviewNumberOfTransactionsValue->setFrameShape(QFrame::StyledPanel);
        overviewNumberOfTransactionsValue->setFrameShadow(QFrame::Sunken);
        overviewNumberOfTransactionsValue->setLineWidth(1);

        formLayout->setWidget(1, QFormLayout::FieldRole, overviewNumberOfTransactionsValue);

        overviewNetWorthValue = new QLabel(overviewDisplayWidget);
        overviewNetWorthValue->setObjectName(QString::fromUtf8("overviewNetWorthValue"));
        overviewNetWorthValue->setFont(font2);
        overviewNetWorthValue->setFrameShape(QFrame::StyledPanel);
        overviewNetWorthValue->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(2, QFormLayout::FieldRole, overviewNetWorthValue);

        overviewNetWorthLabel = new QLabel(overviewDisplayWidget);
        overviewNetWorthLabel->setObjectName(QString::fromUtf8("overviewNetWorthLabel"));
        overviewNetWorthLabel->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, overviewNetWorthLabel);

        overviewFirstDateLabel = new QLabel(overviewDisplayWidget);
        overviewFirstDateLabel->setObjectName(QString::fromUtf8("overviewFirstDateLabel"));
        overviewFirstDateLabel->setFont(font1);

        formLayout->setWidget(3, QFormLayout::LabelRole, overviewFirstDateLabel);

        overviewFirstDateValue = new QLabel(overviewDisplayWidget);
        overviewFirstDateValue->setObjectName(QString::fromUtf8("overviewFirstDateValue"));
        overviewFirstDateValue->setFont(font2);
        overviewFirstDateValue->setFrameShape(QFrame::StyledPanel);
        overviewFirstDateValue->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(3, QFormLayout::FieldRole, overviewFirstDateValue);

        overviewLastDateLabel = new QLabel(overviewDisplayWidget);
        overviewLastDateLabel->setObjectName(QString::fromUtf8("overviewLastDateLabel"));
        overviewLastDateLabel->setFont(font1);

        formLayout->setWidget(4, QFormLayout::LabelRole, overviewLastDateLabel);

        overviewLastDateValue = new QLabel(overviewDisplayWidget);
        overviewLastDateValue->setObjectName(QString::fromUtf8("overviewLastDateValue"));
        overviewLastDateValue->setFont(font2);
        overviewLastDateValue->setFrameShape(QFrame::StyledPanel);
        overviewLastDateValue->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(4, QFormLayout::FieldRole, overviewLastDateValue);


        horizontalLayout_8->addLayout(formLayout);


        horizontalLayout_2->addWidget(overviewDisplayWidget);

        tabWidget->addTab(overviewTab, QString());
        transactionsTab = new QWidget();
        transactionsTab->setObjectName(QString::fromUtf8("transactionsTab"));
        horizontalLayout_5 = new QHBoxLayout(transactionsTab);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        transactionSelectWidget = new QWidget(transactionsTab);
        transactionSelectWidget->setObjectName(QString::fromUtf8("transactionSelectWidget"));
        transactionSelectWidget->setMinimumSize(QSize(250, 0));
        transactionSelectWidget->setMaximumSize(QSize(250, 16777215));
        verticalLayout_14 = new QVBoxLayout(transactionSelectWidget);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        transactionToolBox = new QToolBox(transactionSelectWidget);
        transactionToolBox->setObjectName(QString::fromUtf8("transactionToolBox"));
        transactionToolBox->setFont(font2);
        transactionToolBox->setFrameShape(QFrame::NoFrame);
        transactionToolBox->setFrameShadow(QFrame::Plain);
        transactionAccountToolBox = new QWidget();
        transactionAccountToolBox->setObjectName(QString::fromUtf8("transactionAccountToolBox"));
        transactionAccountToolBox->setGeometry(QRect(0, 0, 149, 100));
        verticalLayout_2 = new QVBoxLayout(transactionAccountToolBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        transactionAllAccountsCheckBox = new QCheckBox(transactionAccountToolBox);
        transactionAllAccountsCheckBox->setObjectName(QString::fromUtf8("transactionAllAccountsCheckBox"));

        verticalLayout_2->addWidget(transactionAllAccountsCheckBox);

        transactionOpenAccountsCheckBox = new QCheckBox(transactionAccountToolBox);
        transactionOpenAccountsCheckBox->setObjectName(QString::fromUtf8("transactionOpenAccountsCheckBox"));

        verticalLayout_2->addWidget(transactionOpenAccountsCheckBox);

        transactionAccountGroupBox = new QGroupBox(transactionAccountToolBox);
        transactionAccountGroupBox->setObjectName(QString::fromUtf8("transactionAccountGroupBox"));
        QFont font3;
        font3.setPointSize(9);
        transactionAccountGroupBox->setFont(font3);
        verticalLayout_3 = new QVBoxLayout(transactionAccountGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        verticalLayout_2->addWidget(transactionAccountGroupBox);

        transactionToolBox->addItem(transactionAccountToolBox, QString::fromUtf8("Account"));
        transactionCategoriesToolBox = new QWidget();
        transactionCategoriesToolBox->setObjectName(QString::fromUtf8("transactionCategoriesToolBox"));
        transactionCategoriesToolBox->setGeometry(QRect(0, 0, 140, 70));
        verticalLayout_4 = new QVBoxLayout(transactionCategoriesToolBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        transactionAllCategoriesCheckBox = new QCheckBox(transactionCategoriesToolBox);
        transactionAllCategoriesCheckBox->setObjectName(QString::fromUtf8("transactionAllCategoriesCheckBox"));

        verticalLayout_4->addWidget(transactionAllCategoriesCheckBox);

        transactionCategoriesGroupBox = new QGroupBox(transactionCategoriesToolBox);
        transactionCategoriesGroupBox->setObjectName(QString::fromUtf8("transactionCategoriesGroupBox"));
        transactionCategoriesGroupBox->setFont(font3);
        verticalLayout_5 = new QVBoxLayout(transactionCategoriesGroupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));

        verticalLayout_4->addWidget(transactionCategoriesGroupBox);

        transactionToolBox->addItem(transactionCategoriesToolBox, QString::fromUtf8("Categories"));
        transactionLabelsToolBox = new QWidget();
        transactionLabelsToolBox->setObjectName(QString::fromUtf8("transactionLabelsToolBox"));
        transactionLabelsToolBox->setGeometry(QRect(0, 0, 110, 70));
        verticalLayout_6 = new QVBoxLayout(transactionLabelsToolBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        transactionAllLabelsCheckBox = new QCheckBox(transactionLabelsToolBox);
        transactionAllLabelsCheckBox->setObjectName(QString::fromUtf8("transactionAllLabelsCheckBox"));

        verticalLayout_6->addWidget(transactionAllLabelsCheckBox);

        transactionLabelsGroupBox = new QGroupBox(transactionLabelsToolBox);
        transactionLabelsGroupBox->setObjectName(QString::fromUtf8("transactionLabelsGroupBox"));
        transactionLabelsGroupBox->setFont(font3);
        verticalLayout_7 = new QVBoxLayout(transactionLabelsGroupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));

        verticalLayout_6->addWidget(transactionLabelsGroupBox);

        transactionToolBox->addItem(transactionLabelsToolBox, QString::fromUtf8("Labels"));
        transactionDateToolBox = new QWidget();
        transactionDateToolBox->setObjectName(QString::fromUtf8("transactionDateToolBox"));
        transactionDateToolBox->setGeometry(QRect(0, 0, 232, 405));
        formLayout_1 = new QFormLayout(transactionDateToolBox);
        formLayout_1->setSpacing(6);
        formLayout_1->setContentsMargins(11, 11, 11, 11);
        formLayout_1->setObjectName(QString::fromUtf8("formLayout_1"));
        formLayout_1->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        transactionStartDateLabel = new QLabel(transactionDateToolBox);
        transactionStartDateLabel->setObjectName(QString::fromUtf8("transactionStartDateLabel"));
        transactionStartDateLabel->setMaximumSize(QSize(16777215, 30));

        formLayout_1->setWidget(0, QFormLayout::LabelRole, transactionStartDateLabel);

        transactionStartDateEdit = new QDateEdit(transactionDateToolBox);
        transactionStartDateEdit->setObjectName(QString::fromUtf8("transactionStartDateEdit"));
        transactionStartDateEdit->setCalendarPopup(true);

        formLayout_1->setWidget(0, QFormLayout::FieldRole, transactionStartDateEdit);

        transactionEndDateLabel = new QLabel(transactionDateToolBox);
        transactionEndDateLabel->setObjectName(QString::fromUtf8("transactionEndDateLabel"));

        formLayout_1->setWidget(2, QFormLayout::LabelRole, transactionEndDateLabel);

        transactionEndDateEdit = new QDateEdit(transactionDateToolBox);
        transactionEndDateEdit->setObjectName(QString::fromUtf8("transactionEndDateEdit"));
        transactionEndDateEdit->setCalendarPopup(true);

        formLayout_1->setWidget(2, QFormLayout::FieldRole, transactionEndDateEdit);

        transactionDateThisYearButton = new QPushButton(transactionDateToolBox);
        transactionDateThisYearButton->setObjectName(QString::fromUtf8("transactionDateThisYearButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(transactionDateThisYearButton->sizePolicy().hasHeightForWidth());
        transactionDateThisYearButton->setSizePolicy(sizePolicy2);

        formLayout_1->setWidget(3, QFormLayout::LabelRole, transactionDateThisYearButton);

        transactionDate1YearButton = new QPushButton(transactionDateToolBox);
        transactionDate1YearButton->setObjectName(QString::fromUtf8("transactionDate1YearButton"));
        sizePolicy2.setHeightForWidth(transactionDate1YearButton->sizePolicy().hasHeightForWidth());
        transactionDate1YearButton->setSizePolicy(sizePolicy2);

        formLayout_1->setWidget(4, QFormLayout::LabelRole, transactionDate1YearButton);

        transactionDate5YearButton = new QPushButton(transactionDateToolBox);
        transactionDate5YearButton->setObjectName(QString::fromUtf8("transactionDate5YearButton"));
        sizePolicy2.setHeightForWidth(transactionDate5YearButton->sizePolicy().hasHeightForWidth());
        transactionDate5YearButton->setSizePolicy(sizePolicy2);

        formLayout_1->setWidget(5, QFormLayout::LabelRole, transactionDate5YearButton);

        transactionDate10YearButton = new QPushButton(transactionDateToolBox);
        transactionDate10YearButton->setObjectName(QString::fromUtf8("transactionDate10YearButton"));
        sizePolicy2.setHeightForWidth(transactionDate10YearButton->sizePolicy().hasHeightForWidth());
        transactionDate10YearButton->setSizePolicy(sizePolicy2);

        formLayout_1->setWidget(6, QFormLayout::LabelRole, transactionDate10YearButton);

        transactionDateAllTimeButton = new QPushButton(transactionDateToolBox);
        transactionDateAllTimeButton->setObjectName(QString::fromUtf8("transactionDateAllTimeButton"));
        sizePolicy2.setHeightForWidth(transactionDateAllTimeButton->sizePolicy().hasHeightForWidth());
        transactionDateAllTimeButton->setSizePolicy(sizePolicy2);

        formLayout_1->setWidget(7, QFormLayout::LabelRole, transactionDateAllTimeButton);

        transactionToolBox->addItem(transactionDateToolBox, QString::fromUtf8("Date"));

        verticalLayout_14->addWidget(transactionToolBox);

        transactionSelectButton = new QPushButton(transactionSelectWidget);
        transactionSelectButton->setObjectName(QString::fromUtf8("transactionSelectButton"));
        transactionSelectButton->setFont(font2);

        verticalLayout_14->addWidget(transactionSelectButton);


        horizontalLayout_5->addWidget(transactionSelectWidget);

        transactionTableView = new QTableView(transactionsTab);
        transactionTableView->setObjectName(QString::fromUtf8("transactionTableView"));
        transactionTableView->setFont(font1);
        transactionTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        transactionTableView->setAlternatingRowColors(true);
        transactionTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        transactionTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        transactionTableView->setGridStyle(Qt::DashLine);
        transactionTableView->setWordWrap(false);
        transactionTableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        transactionTableView->verticalHeader()->setVisible(false);

        horizontalLayout_5->addWidget(transactionTableView);

        tabWidget->addTab(transactionsTab, QString());
        reportTab = new QWidget();
        reportTab->setObjectName(QString::fromUtf8("reportTab"));
        horizontalLayout_6 = new QHBoxLayout(reportTab);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        reportSelectWidget = new QWidget(reportTab);
        reportSelectWidget->setObjectName(QString::fromUtf8("reportSelectWidget"));
        reportSelectWidget->setMinimumSize(QSize(250, 0));
        reportSelectWidget->setMaximumSize(QSize(250, 16777215));
        verticalLayout_15 = new QVBoxLayout(reportSelectWidget);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        reportToolBox = new QToolBox(reportSelectWidget);
        reportToolBox->setObjectName(QString::fromUtf8("reportToolBox"));
        reportToolBox->setFont(font2);
        reportToolBox->setFrameShape(QFrame::NoFrame);
        reportToolBox->setFrameShadow(QFrame::Plain);
        reportAccountToolBox = new QWidget();
        reportAccountToolBox->setObjectName(QString::fromUtf8("reportAccountToolBox"));
        reportAccountToolBox->setGeometry(QRect(0, 0, 149, 100));
        verticalLayout_8 = new QVBoxLayout(reportAccountToolBox);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        reportAllAccountsCheckBox = new QCheckBox(reportAccountToolBox);
        reportAllAccountsCheckBox->setObjectName(QString::fromUtf8("reportAllAccountsCheckBox"));

        verticalLayout_8->addWidget(reportAllAccountsCheckBox);

        reportOpenAccountsCheckBox = new QCheckBox(reportAccountToolBox);
        reportOpenAccountsCheckBox->setObjectName(QString::fromUtf8("reportOpenAccountsCheckBox"));

        verticalLayout_8->addWidget(reportOpenAccountsCheckBox);

        reportAccountGroupBox = new QGroupBox(reportAccountToolBox);
        reportAccountGroupBox->setObjectName(QString::fromUtf8("reportAccountGroupBox"));
        reportAccountGroupBox->setFont(font3);
        verticalLayout_9 = new QVBoxLayout(reportAccountGroupBox);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));

        verticalLayout_8->addWidget(reportAccountGroupBox);

        reportToolBox->addItem(reportAccountToolBox, QString::fromUtf8("Account"));
        reportCategoriesToolBox = new QWidget();
        reportCategoriesToolBox->setObjectName(QString::fromUtf8("reportCategoriesToolBox"));
        reportCategoriesToolBox->setGeometry(QRect(0, 0, 140, 70));
        verticalLayout_10 = new QVBoxLayout(reportCategoriesToolBox);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        reportAllCategoriesCheckBox = new QCheckBox(reportCategoriesToolBox);
        reportAllCategoriesCheckBox->setObjectName(QString::fromUtf8("reportAllCategoriesCheckBox"));

        verticalLayout_10->addWidget(reportAllCategoriesCheckBox);

        reportCategoriesGroupBox = new QGroupBox(reportCategoriesToolBox);
        reportCategoriesGroupBox->setObjectName(QString::fromUtf8("reportCategoriesGroupBox"));
        reportCategoriesGroupBox->setFont(font3);
        verticalLayout_11 = new QVBoxLayout(reportCategoriesGroupBox);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));

        verticalLayout_10->addWidget(reportCategoriesGroupBox);

        reportToolBox->addItem(reportCategoriesToolBox, QString::fromUtf8("Categories"));
        reportLabelsToolBox = new QWidget();
        reportLabelsToolBox->setObjectName(QString::fromUtf8("reportLabelsToolBox"));
        reportLabelsToolBox->setGeometry(QRect(0, 0, 110, 70));
        verticalLayout_12 = new QVBoxLayout(reportLabelsToolBox);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        reportAllLabelsCheckBox = new QCheckBox(reportLabelsToolBox);
        reportAllLabelsCheckBox->setObjectName(QString::fromUtf8("reportAllLabelsCheckBox"));

        verticalLayout_12->addWidget(reportAllLabelsCheckBox);

        reportLabelsGroupBox = new QGroupBox(reportLabelsToolBox);
        reportLabelsGroupBox->setObjectName(QString::fromUtf8("reportLabelsGroupBox"));
        reportLabelsGroupBox->setFont(font3);
        verticalLayout_13 = new QVBoxLayout(reportLabelsGroupBox);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));

        verticalLayout_12->addWidget(reportLabelsGroupBox);

        reportToolBox->addItem(reportLabelsToolBox, QString::fromUtf8("Labels"));
        reportDateToolBox = new QWidget();
        reportDateToolBox->setObjectName(QString::fromUtf8("reportDateToolBox"));
        reportDateToolBox->setGeometry(QRect(0, 0, 232, 405));
        formLayout_2 = new QFormLayout(reportDateToolBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        reportStartDateLabel = new QLabel(reportDateToolBox);
        reportStartDateLabel->setObjectName(QString::fromUtf8("reportStartDateLabel"));
        reportStartDateLabel->setMaximumSize(QSize(16777215, 30));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, reportStartDateLabel);

        reportStartDateEdit = new QDateEdit(reportDateToolBox);
        reportStartDateEdit->setObjectName(QString::fromUtf8("reportStartDateEdit"));
        reportStartDateEdit->setCalendarPopup(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, reportStartDateEdit);

        reportEndDateLabel = new QLabel(reportDateToolBox);
        reportEndDateLabel->setObjectName(QString::fromUtf8("reportEndDateLabel"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, reportEndDateLabel);

        reportEndDateEdit = new QDateEdit(reportDateToolBox);
        reportEndDateEdit->setObjectName(QString::fromUtf8("reportEndDateEdit"));
        reportEndDateEdit->setCalendarPopup(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, reportEndDateEdit);

        reportDateThisYearButton = new QPushButton(reportDateToolBox);
        reportDateThisYearButton->setObjectName(QString::fromUtf8("reportDateThisYearButton"));
        sizePolicy2.setHeightForWidth(reportDateThisYearButton->sizePolicy().hasHeightForWidth());
        reportDateThisYearButton->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, reportDateThisYearButton);

        reportDate1YearButton = new QPushButton(reportDateToolBox);
        reportDate1YearButton->setObjectName(QString::fromUtf8("reportDate1YearButton"));
        sizePolicy2.setHeightForWidth(reportDate1YearButton->sizePolicy().hasHeightForWidth());
        reportDate1YearButton->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, reportDate1YearButton);

        reportDate5YearButton = new QPushButton(reportDateToolBox);
        reportDate5YearButton->setObjectName(QString::fromUtf8("reportDate5YearButton"));
        sizePolicy2.setHeightForWidth(reportDate5YearButton->sizePolicy().hasHeightForWidth());
        reportDate5YearButton->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(5, QFormLayout::LabelRole, reportDate5YearButton);

        reportDate10YearButton = new QPushButton(reportDateToolBox);
        reportDate10YearButton->setObjectName(QString::fromUtf8("reportDate10YearButton"));
        sizePolicy2.setHeightForWidth(reportDate10YearButton->sizePolicy().hasHeightForWidth());
        reportDate10YearButton->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(6, QFormLayout::LabelRole, reportDate10YearButton);

        reportDateAllTimeButton = new QPushButton(reportDateToolBox);
        reportDateAllTimeButton->setObjectName(QString::fromUtf8("reportDateAllTimeButton"));
        sizePolicy2.setHeightForWidth(reportDateAllTimeButton->sizePolicy().hasHeightForWidth());
        reportDateAllTimeButton->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(7, QFormLayout::LabelRole, reportDateAllTimeButton);

        reportToolBox->addItem(reportDateToolBox, QString::fromUtf8("Date"));

        verticalLayout_15->addWidget(reportToolBox);

        reportSelectButton = new QPushButton(reportSelectWidget);
        reportSelectButton->setObjectName(QString::fromUtf8("reportSelectButton"));
        reportSelectButton->setFont(font2);

        verticalLayout_15->addWidget(reportSelectButton);


        horizontalLayout_6->addWidget(reportSelectWidget);

        reportDisplayTabWidget = new QTabWidget(reportTab);
        reportDisplayTabWidget->setObjectName(QString::fromUtf8("reportDisplayTabWidget"));
        reportDisplayTabWidget->setTabPosition(QTabWidget::North);
        reportNetIncomeTab = new QWidget();
        reportNetIncomeTab->setObjectName(QString::fromUtf8("reportNetIncomeTab"));
        horizontalLayout_3 = new QHBoxLayout(reportNetIncomeTab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        reportDisplayTabWidget->addTab(reportNetIncomeTab, QString());
        reportNetWorthTab = new QWidget();
        reportNetWorthTab->setObjectName(QString::fromUtf8("reportNetWorthTab"));
        horizontalLayout_4 = new QHBoxLayout(reportNetWorthTab);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        reportDisplayTabWidget->addTab(reportNetWorthTab, QString());
        reportListTab = new QWidget();
        reportListTab->setObjectName(QString::fromUtf8("reportListTab"));
        horizontalLayout_7 = new QHBoxLayout(reportListTab);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        reportDisplayTabWidget->addTab(reportListTab, QString());
        reportAccountTab = new QWidget();
        reportAccountTab->setObjectName(QString::fromUtf8("reportAccountTab"));
        horizontalLayout_9 = new QHBoxLayout(reportAccountTab);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        reportDisplayTabWidget->addTab(reportAccountTab, QString());
        reportCategoryTab = new QWidget();
        reportCategoryTab->setObjectName(QString::fromUtf8("reportCategoryTab"));
        horizontalLayout_10 = new QHBoxLayout(reportCategoryTab);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        reportDisplayTabWidget->addTab(reportCategoryTab, QString());

        horizontalLayout_6->addWidget(reportDisplayTabWidget);

        tabWidget->addTab(reportTab, QString());

        horizontalLayout->addWidget(tabWidget);

        TransactionManager->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TransactionManager);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1204, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        TransactionManager->setMenuBar(menuBar);
        statusBar = new QStatusBar(TransactionManager);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TransactionManager->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        menuHelp->addSeparator();
        menuHelp->addAction(actionDisplayFile);
        menuHelp->addAction(actionDisplayLog);
        menuTools->addAction(actionFileInputConfig);

        retranslateUi(TransactionManager);

        tabWidget->setCurrentIndex(0);
        transactionToolBox->setCurrentIndex(3);
        reportToolBox->setCurrentIndex(3);
        reportDisplayTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TransactionManager);
    } // setupUi

    void retranslateUi(QMainWindow *TransactionManager)
    {
        TransactionManager->setWindowTitle(QApplication::translate("TransactionManager", "TransactionManager", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("TransactionManager", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("TransactionManager", "Save", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setText(QApplication::translate("TransactionManager", "Save As", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("TransactionManager", "Exit", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("TransactionManager", "Close", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("TransactionManager", "About", 0, QApplication::UnicodeUTF8));
        actionDisplayFile->setText(QApplication::translate("TransactionManager", "Display File Contents", 0, QApplication::UnicodeUTF8));
        actionDisplayLog->setText(QApplication::translate("TransactionManager", "Display Log", 0, QApplication::UnicodeUTF8));
        actionFileInputConfig->setText(QApplication::translate("TransactionManager", "File Input Config", 0, QApplication::UnicodeUTF8));
        overviewAccountTitle->setText(QApplication::translate("TransactionManager", "Accounts", 0, QApplication::UnicodeUTF8));
        overviewNumberOfAccountsLabel->setText(QApplication::translate("TransactionManager", "Number of Accounts:", 0, QApplication::UnicodeUTF8));
        overviewNumberOfTransactionsLabel->setText(QApplication::translate("TransactionManager", "Number of Transactions:", 0, QApplication::UnicodeUTF8));
        overviewNumberOfAccountValue->setText(QApplication::translate("TransactionManager", "TextLabel", 0, QApplication::UnicodeUTF8));
        overviewNumberOfTransactionsValue->setText(QApplication::translate("TransactionManager", "TextLabel", 0, QApplication::UnicodeUTF8));
        overviewNetWorthValue->setText(QApplication::translate("TransactionManager", "TextLabel", 0, QApplication::UnicodeUTF8));
        overviewNetWorthLabel->setText(QApplication::translate("TransactionManager", "Net Worth:", 0, QApplication::UnicodeUTF8));
        overviewFirstDateLabel->setText(QApplication::translate("TransactionManager", "Date of First Transaction:", 0, QApplication::UnicodeUTF8));
        overviewFirstDateValue->setText(QApplication::translate("TransactionManager", "TextLabel", 0, QApplication::UnicodeUTF8));
        overviewLastDateLabel->setText(QApplication::translate("TransactionManager", "Date of Last Transaction:", 0, QApplication::UnicodeUTF8));
        overviewLastDateValue->setText(QApplication::translate("TransactionManager", "TextLabel", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(overviewTab), QApplication::translate("TransactionManager", "Overview", 0, QApplication::UnicodeUTF8));
        transactionAllAccountsCheckBox->setText(QApplication::translate("TransactionManager", "All Acounts", 0, QApplication::UnicodeUTF8));
        transactionOpenAccountsCheckBox->setText(QApplication::translate("TransactionManager", "Open Accounts", 0, QApplication::UnicodeUTF8));
        transactionAccountGroupBox->setTitle(QString());
        transactionToolBox->setItemText(transactionToolBox->indexOf(transactionAccountToolBox), QApplication::translate("TransactionManager", "Account", 0, QApplication::UnicodeUTF8));
        transactionAllCategoriesCheckBox->setText(QApplication::translate("TransactionManager", "All Categories", 0, QApplication::UnicodeUTF8));
        transactionCategoriesGroupBox->setTitle(QString());
        transactionToolBox->setItemText(transactionToolBox->indexOf(transactionCategoriesToolBox), QApplication::translate("TransactionManager", "Categories", 0, QApplication::UnicodeUTF8));
        transactionAllLabelsCheckBox->setText(QApplication::translate("TransactionManager", "All Labels", 0, QApplication::UnicodeUTF8));
        transactionLabelsGroupBox->setTitle(QString());
        transactionToolBox->setItemText(transactionToolBox->indexOf(transactionLabelsToolBox), QApplication::translate("TransactionManager", "Labels", 0, QApplication::UnicodeUTF8));
        transactionStartDateLabel->setText(QApplication::translate("TransactionManager", "Start Date:", 0, QApplication::UnicodeUTF8));
        transactionStartDateEdit->setSpecialValueText(QString());
        transactionStartDateEdit->setDisplayFormat(QApplication::translate("TransactionManager", "yyyy-MM-dd", 0, QApplication::UnicodeUTF8));
        transactionEndDateLabel->setText(QApplication::translate("TransactionManager", "End Date:", 0, QApplication::UnicodeUTF8));
        transactionEndDateEdit->setDisplayFormat(QApplication::translate("TransactionManager", "yyyy-MM-dd", 0, QApplication::UnicodeUTF8));
        transactionDateThisYearButton->setText(QApplication::translate("TransactionManager", "This Year", 0, QApplication::UnicodeUTF8));
        transactionDate1YearButton->setText(QApplication::translate("TransactionManager", "1 Year", 0, QApplication::UnicodeUTF8));
        transactionDate5YearButton->setText(QApplication::translate("TransactionManager", "5 Years", 0, QApplication::UnicodeUTF8));
        transactionDate10YearButton->setText(QApplication::translate("TransactionManager", "10 Years", 0, QApplication::UnicodeUTF8));
        transactionDateAllTimeButton->setText(QApplication::translate("TransactionManager", "All Time", 0, QApplication::UnicodeUTF8));
        transactionToolBox->setItemText(transactionToolBox->indexOf(transactionDateToolBox), QApplication::translate("TransactionManager", "Date", 0, QApplication::UnicodeUTF8));
        transactionSelectButton->setText(QApplication::translate("TransactionManager", "Update", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(transactionsTab), QApplication::translate("TransactionManager", "Transactions", 0, QApplication::UnicodeUTF8));
        reportAllAccountsCheckBox->setText(QApplication::translate("TransactionManager", "All Acounts", 0, QApplication::UnicodeUTF8));
        reportOpenAccountsCheckBox->setText(QApplication::translate("TransactionManager", "Open Accounts", 0, QApplication::UnicodeUTF8));
        reportAccountGroupBox->setTitle(QString());
        reportToolBox->setItemText(reportToolBox->indexOf(reportAccountToolBox), QApplication::translate("TransactionManager", "Account", 0, QApplication::UnicodeUTF8));
        reportAllCategoriesCheckBox->setText(QApplication::translate("TransactionManager", "All Categories", 0, QApplication::UnicodeUTF8));
        reportCategoriesGroupBox->setTitle(QString());
        reportToolBox->setItemText(reportToolBox->indexOf(reportCategoriesToolBox), QApplication::translate("TransactionManager", "Categories", 0, QApplication::UnicodeUTF8));
        reportAllLabelsCheckBox->setText(QApplication::translate("TransactionManager", "All Labels", 0, QApplication::UnicodeUTF8));
        reportLabelsGroupBox->setTitle(QString());
        reportToolBox->setItemText(reportToolBox->indexOf(reportLabelsToolBox), QApplication::translate("TransactionManager", "Labels", 0, QApplication::UnicodeUTF8));
        reportStartDateLabel->setText(QApplication::translate("TransactionManager", "Start Date:", 0, QApplication::UnicodeUTF8));
        reportStartDateEdit->setSpecialValueText(QString());
        reportStartDateEdit->setDisplayFormat(QApplication::translate("TransactionManager", "yyyy-MM-dd", 0, QApplication::UnicodeUTF8));
        reportEndDateLabel->setText(QApplication::translate("TransactionManager", "End Date:", 0, QApplication::UnicodeUTF8));
        reportEndDateEdit->setDisplayFormat(QApplication::translate("TransactionManager", "yyyy-MM-dd", 0, QApplication::UnicodeUTF8));
        reportDateThisYearButton->setText(QApplication::translate("TransactionManager", "This Year", 0, QApplication::UnicodeUTF8));
        reportDate1YearButton->setText(QApplication::translate("TransactionManager", "1 Year", 0, QApplication::UnicodeUTF8));
        reportDate5YearButton->setText(QApplication::translate("TransactionManager", "5 Years", 0, QApplication::UnicodeUTF8));
        reportDate10YearButton->setText(QApplication::translate("TransactionManager", "10 Years", 0, QApplication::UnicodeUTF8));
        reportDateAllTimeButton->setText(QApplication::translate("TransactionManager", "All Time", 0, QApplication::UnicodeUTF8));
        reportToolBox->setItemText(reportToolBox->indexOf(reportDateToolBox), QApplication::translate("TransactionManager", "Date", 0, QApplication::UnicodeUTF8));
        reportSelectButton->setText(QApplication::translate("TransactionManager", "Update", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportNetIncomeTab), QApplication::translate("TransactionManager", "Net Income", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportNetIncomeTab), QApplication::translate("TransactionManager", "Income/Expense Bar Chart", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportNetWorthTab), QApplication::translate("TransactionManager", "Net Worth", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportNetWorthTab), QApplication::translate("TransactionManager", "Net Worth Bar Chart", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportListTab), QApplication::translate("TransactionManager", "List", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportAccountTab), QApplication::translate("TransactionManager", "Assets/Debts by Account", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportAccountTab), QApplication::translate("TransactionManager", "Assets/Debts Pie Chart by Account", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportCategoryTab), QApplication::translate("TransactionManager", "Income/Expense by Category", 0, QApplication::UnicodeUTF8));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportCategoryTab), QApplication::translate("TransactionManager", "Income/Expense Pie Chart by Category", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(reportTab), QApplication::translate("TransactionManager", "Reports", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("TransactionManager", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("TransactionManager", "Help", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("TransactionManager", "Tools", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TransactionManager: public Ui_TransactionManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONMANAGER_H
