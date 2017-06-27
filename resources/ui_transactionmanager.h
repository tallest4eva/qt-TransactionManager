/********************************************************************************
** Form generated from reading UI file 'transactionmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONMANAGER_H
#define UI_TRANSACTIONMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransactionManager
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionClose;
    QAction *actionDisplayFile;
    QAction *actionDisplayLog;
    QAction *actionFileInputConfig;
    QAction *actionDisplayHelp;
    QAction *actionDisplayAbout;
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
    QLabel *overviewNumberOfAccountValue;
    QLabel *overviewNumberOfTransactionsLabel;
    QLabel *overviewNumberOfTransactionsValue;
    QLabel *overviewNetWorthLabel;
    QLabel *overviewNetWorthValue;
    QLabel *overviewFirstDateLabel;
    QLabel *overviewFirstDateValue;
    QLabel *overviewLastDateLabel;
    QLabel *overviewLastDateValue;
    QLabel *overviewShowClosedAccountsLabel;
    QCheckBox *overviewShowClosedAccountsCheckBox;
    QLabel *overviewSortAccountsLabel;
    QComboBox *overviewSortAccountsComboBox;
    QSpacerItem *verticalSpacer;
    QLabel *mNotesImageLabel;
    QWidget *transactionsTab;
    QHBoxLayout *horizontalLayout_5;
    QWidget *transactionSelectWidget;
    QVBoxLayout *verticalLayout_14;
    QPushButton *transactionAllButton;
    QPushButton *transactionShowInReportsButton;
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
    QCheckBox *transactionIncomeCategoriesCheckBox;
    QCheckBox *transactionExpenseCategoriesCheckBox;
    QCheckBox *transactionTransferCategoriesCheckBox;
    QGroupBox *transactionCategoriesGroupBox;
    QVBoxLayout *verticalLayout_5;
    QPushButton *mTransactionCategoriesTreeExpandButton;
    QWidget *transactionLabelsToolBox;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *transactionAllLabelsCheckBox;
    QGroupBox *transactionLabelsGroupBox;
    QVBoxLayout *verticalLayout_7;
    QWidget *transactionDateToolBox;
    QFormLayout *formLayout_1;
    QComboBox *transactionDateComboBox;
    QLabel *transactionStartDateLabel;
    QDateEdit *transactionStartDateEdit;
    QLabel *transactionEndDateLabel;
    QDateEdit *transactionEndDateEdit;
    QPushButton *transactionSelectButton;
    QWidget *transactionTabWidget;
    QVBoxLayout *horizontalLayout_21;
    QWidget *transactionSearchWidget;
    QHBoxLayout *horizontalLayout_18;
    QLabel *transactionSearchLabel;
    QLineEdit *transactionSearchTextLineEdit;
    QPushButton *transactionSearchButton;
    QPushButton *transactionSearchClearButton;
    QWidget *transactionListWidget;
    QHBoxLayout *horizontalLayout_20;
    QWidget *transactionDisplayWidget;
    QHBoxLayout *horizontalLayout_19;
    QLabel *transactionDisplayCreditLabel;
    QLabel *transactionDisplayCreditValue;
    QLabel *transactionDisplayDebitLabel;
    QLabel *transactionDisplayDebitValue;
    QLabel *transactionDisplayNetLabel;
    QLabel *transactionDisplayNetValue;
    QWidget *reportTab;
    QHBoxLayout *horizontalLayout_6;
    QWidget *reportSelectWidget;
    QVBoxLayout *verticalLayout_15;
    QPushButton *reportAllButton;
    QPushButton *reportShowInTransactionsButton;
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
    QCheckBox *reportIncomeCategoriesCheckBox;
    QCheckBox *reportExpenseCategoriesCheckBox;
    QCheckBox *reportTransferCategoriesCheckBox;
    QGroupBox *reportCategoriesGroupBox;
    QVBoxLayout *verticalLayout_11;
    QPushButton *mReportCategoriesTreeExpandButton;
    QWidget *reportLabelsToolBox;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *reportAllLabelsCheckBox;
    QGroupBox *reportLabelsGroupBox;
    QVBoxLayout *verticalLayout_13;
    QWidget *reportDateToolBox;
    QFormLayout *formLayout_2;
    QComboBox *reportDateComboBox;
    QLabel *reportStartDateLabel;
    QDateEdit *reportStartDateEdit;
    QLabel *reportEndDateLabel;
    QDateEdit *reportEndDateEdit;
    QLabel *reportDateIntervalLabel;
    QComboBox *reportDateIntervalComboBox;
    QCheckBox *mReportShowNetIncomeCheckBox;
    QCheckBox *mReportShowTransfersCheckBox;
    QPushButton *reportSelectButton;
    QTabWidget *reportDisplayTabWidget;
    QWidget *reportNetIncomeTab;
    QHBoxLayout *horizontalLayout_3;
    QWidget *reportNetWorthTab;
    QHBoxLayout *horizontalLayout_4;
    QWidget *reportListTab;
    QHBoxLayout *horizontalLayout_7;
    QWidget *reportAccountBalanceTab;
    QHBoxLayout *horizontalLayout_25;
    QWidget *reportAccountTab;
    QHBoxLayout *_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_16;
    QComboBox *mReportAssetDebtComboBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *reportAssetGroupBox;
    QHBoxLayout *horizontalLayout_13;
    QGroupBox *reportDebtGroupBox;
    QHBoxLayout *horizontalLayout_14;
    QWidget *reportCategoryTab;
    QHBoxLayout *horizontalLayout_10;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_17;
    QComboBox *mReportIncomeExpenseComboBox;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_22;
    QGroupBox *reportIncomeParentGroupBox;
    QHBoxLayout *horizontalLayout_11;
    QGroupBox *reportExpenseParentGroupBox;
    QHBoxLayout *horizontalLayout_12;
    QWidget *reportSubCategoryTab;
    QHBoxLayout *horizontalLayout_15;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_18;
    QComboBox *mReportSubIncomeExpenseComboBox;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_23;
    QGroupBox *reportIncomeSubGroupBox;
    QHBoxLayout *horizontalLayout_16;
    QGroupBox *reportExpenseSubGroupBox;
    QHBoxLayout *horizontalLayout_17;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuTools;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TransactionManager)
    {
        if (TransactionManager->objectName().isEmpty())
            TransactionManager->setObjectName(QStringLiteral("TransactionManager"));
        TransactionManager->resize(1373, 802);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/resources/app_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        TransactionManager->setWindowIcon(icon);
        actionOpen = new QAction(TransactionManager);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(TransactionManager);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setEnabled(false);
        actionSaveAs = new QAction(TransactionManager);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        actionSaveAs->setEnabled(false);
        actionExit = new QAction(TransactionManager);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionClose = new QAction(TransactionManager);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionClose->setEnabled(false);
        actionDisplayFile = new QAction(TransactionManager);
        actionDisplayFile->setObjectName(QStringLiteral("actionDisplayFile"));
        actionDisplayLog = new QAction(TransactionManager);
        actionDisplayLog->setObjectName(QStringLiteral("actionDisplayLog"));
        actionFileInputConfig = new QAction(TransactionManager);
        actionFileInputConfig->setObjectName(QStringLiteral("actionFileInputConfig"));
        actionDisplayHelp = new QAction(TransactionManager);
        actionDisplayHelp->setObjectName(QStringLiteral("actionDisplayHelp"));
        actionDisplayAbout = new QAction(TransactionManager);
        actionDisplayAbout->setObjectName(QStringLiteral("actionDisplayAbout"));
        centralWidget = new QWidget(TransactionManager);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabShape(QTabWidget::Rounded);
        overviewTab = new QWidget();
        overviewTab->setObjectName(QStringLiteral("overviewTab"));
        horizontalLayout_2 = new QHBoxLayout(overviewTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        overviewAccountWidget = new QWidget(overviewTab);
        overviewAccountWidget->setObjectName(QStringLiteral("overviewAccountWidget"));
        verticalLayout = new QVBoxLayout(overviewAccountWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        overviewAccountTitle = new QLabel(overviewAccountWidget);
        overviewAccountTitle->setObjectName(QStringLiteral("overviewAccountTitle"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        overviewAccountTitle->setFont(font);

        verticalLayout->addWidget(overviewAccountTitle);

        overviewAccountList = new QListWidget(overviewAccountWidget);
        overviewAccountList->setObjectName(QStringLiteral("overviewAccountList"));
        overviewAccountList->setSelectionMode(QAbstractItemView::SingleSelection);
        overviewAccountList->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(overviewAccountList);


        horizontalLayout_2->addWidget(overviewAccountWidget);

        overviewDisplayWidget = new QWidget(overviewTab);
        overviewDisplayWidget->setObjectName(QStringLiteral("overviewDisplayWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(overviewDisplayWidget->sizePolicy().hasHeightForWidth());
        overviewDisplayWidget->setSizePolicy(sizePolicy1);
        horizontalLayout_8 = new QHBoxLayout(overviewDisplayWidget);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        overviewNumberOfAccountsLabel = new QLabel(overviewDisplayWidget);
        overviewNumberOfAccountsLabel->setObjectName(QStringLiteral("overviewNumberOfAccountsLabel"));
        QFont font1;
        font1.setPointSize(10);
        overviewNumberOfAccountsLabel->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, overviewNumberOfAccountsLabel);

        overviewNumberOfAccountValue = new QLabel(overviewDisplayWidget);
        overviewNumberOfAccountValue->setObjectName(QStringLiteral("overviewNumberOfAccountValue"));
        overviewNumberOfAccountValue->setMinimumSize(QSize(0, 25));
        QFont font2;
        font2.setPointSize(12);
        overviewNumberOfAccountValue->setFont(font2);
        overviewNumberOfAccountValue->setFrameShape(QFrame::StyledPanel);
        overviewNumberOfAccountValue->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(0, QFormLayout::FieldRole, overviewNumberOfAccountValue);

        overviewNumberOfTransactionsLabel = new QLabel(overviewDisplayWidget);
        overviewNumberOfTransactionsLabel->setObjectName(QStringLiteral("overviewNumberOfTransactionsLabel"));
        overviewNumberOfTransactionsLabel->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, overviewNumberOfTransactionsLabel);

        overviewNumberOfTransactionsValue = new QLabel(overviewDisplayWidget);
        overviewNumberOfTransactionsValue->setObjectName(QStringLiteral("overviewNumberOfTransactionsValue"));
        overviewNumberOfTransactionsValue->setFont(font2);
        overviewNumberOfTransactionsValue->setFrameShape(QFrame::StyledPanel);
        overviewNumberOfTransactionsValue->setFrameShadow(QFrame::Sunken);
        overviewNumberOfTransactionsValue->setLineWidth(1);

        formLayout->setWidget(1, QFormLayout::FieldRole, overviewNumberOfTransactionsValue);

        overviewNetWorthLabel = new QLabel(overviewDisplayWidget);
        overviewNetWorthLabel->setObjectName(QStringLiteral("overviewNetWorthLabel"));
        overviewNetWorthLabel->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, overviewNetWorthLabel);

        overviewNetWorthValue = new QLabel(overviewDisplayWidget);
        overviewNetWorthValue->setObjectName(QStringLiteral("overviewNetWorthValue"));
        overviewNetWorthValue->setFont(font2);
        overviewNetWorthValue->setFrameShape(QFrame::StyledPanel);
        overviewNetWorthValue->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(2, QFormLayout::FieldRole, overviewNetWorthValue);

        overviewFirstDateLabel = new QLabel(overviewDisplayWidget);
        overviewFirstDateLabel->setObjectName(QStringLiteral("overviewFirstDateLabel"));
        overviewFirstDateLabel->setFont(font1);

        formLayout->setWidget(3, QFormLayout::LabelRole, overviewFirstDateLabel);

        overviewFirstDateValue = new QLabel(overviewDisplayWidget);
        overviewFirstDateValue->setObjectName(QStringLiteral("overviewFirstDateValue"));
        overviewFirstDateValue->setFont(font2);
        overviewFirstDateValue->setFrameShape(QFrame::StyledPanel);
        overviewFirstDateValue->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(3, QFormLayout::FieldRole, overviewFirstDateValue);

        overviewLastDateLabel = new QLabel(overviewDisplayWidget);
        overviewLastDateLabel->setObjectName(QStringLiteral("overviewLastDateLabel"));
        overviewLastDateLabel->setFont(font1);

        formLayout->setWidget(4, QFormLayout::LabelRole, overviewLastDateLabel);

        overviewLastDateValue = new QLabel(overviewDisplayWidget);
        overviewLastDateValue->setObjectName(QStringLiteral("overviewLastDateValue"));
        overviewLastDateValue->setFont(font2);
        overviewLastDateValue->setFrameShape(QFrame::StyledPanel);
        overviewLastDateValue->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(4, QFormLayout::FieldRole, overviewLastDateValue);

        overviewShowClosedAccountsLabel = new QLabel(overviewDisplayWidget);
        overviewShowClosedAccountsLabel->setObjectName(QStringLiteral("overviewShowClosedAccountsLabel"));
        overviewShowClosedAccountsLabel->setFont(font1);

        formLayout->setWidget(5, QFormLayout::LabelRole, overviewShowClosedAccountsLabel);

        overviewShowClosedAccountsCheckBox = new QCheckBox(overviewDisplayWidget);
        overviewShowClosedAccountsCheckBox->setObjectName(QStringLiteral("overviewShowClosedAccountsCheckBox"));
        overviewShowClosedAccountsCheckBox->setEnabled(true);
        overviewShowClosedAccountsCheckBox->setFont(font1);
        overviewShowClosedAccountsCheckBox->setLayoutDirection(Qt::LeftToRight);
        overviewShowClosedAccountsCheckBox->setChecked(false);

        formLayout->setWidget(5, QFormLayout::FieldRole, overviewShowClosedAccountsCheckBox);

        overviewSortAccountsLabel = new QLabel(overviewDisplayWidget);
        overviewSortAccountsLabel->setObjectName(QStringLiteral("overviewSortAccountsLabel"));
        overviewSortAccountsLabel->setFont(font1);

        formLayout->setWidget(6, QFormLayout::LabelRole, overviewSortAccountsLabel);

        overviewSortAccountsComboBox = new QComboBox(overviewDisplayWidget);
        overviewSortAccountsComboBox->setObjectName(QStringLiteral("overviewSortAccountsComboBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(overviewSortAccountsComboBox->sizePolicy().hasHeightForWidth());
        overviewSortAccountsComboBox->setSizePolicy(sizePolicy2);
        overviewSortAccountsComboBox->setMaximumSize(QSize(200, 16777215));
        overviewSortAccountsComboBox->setFont(font2);

        formLayout->setWidget(6, QFormLayout::FieldRole, overviewSortAccountsComboBox);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(7, QFormLayout::FieldRole, verticalSpacer);

        mNotesImageLabel = new QLabel(overviewDisplayWidget);
        mNotesImageLabel->setObjectName(QStringLiteral("mNotesImageLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(mNotesImageLabel->sizePolicy().hasHeightForWidth());
        mNotesImageLabel->setSizePolicy(sizePolicy3);
        mNotesImageLabel->setMaximumSize(QSize(350, 250));
        mNotesImageLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/resources/notes.png")));

        formLayout->setWidget(8, QFormLayout::FieldRole, mNotesImageLabel);


        horizontalLayout_8->addLayout(formLayout);


        horizontalLayout_2->addWidget(overviewDisplayWidget);

        tabWidget->addTab(overviewTab, QString());
        transactionsTab = new QWidget();
        transactionsTab->setObjectName(QStringLiteral("transactionsTab"));
        horizontalLayout_5 = new QHBoxLayout(transactionsTab);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        transactionSelectWidget = new QWidget(transactionsTab);
        transactionSelectWidget->setObjectName(QStringLiteral("transactionSelectWidget"));
        transactionSelectWidget->setMinimumSize(QSize(300, 0));
        transactionSelectWidget->setMaximumSize(QSize(250, 16777215));
        verticalLayout_14 = new QVBoxLayout(transactionSelectWidget);
        verticalLayout_14->setSpacing(2);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(5, 5, 5, 5);
        transactionAllButton = new QPushButton(transactionSelectWidget);
        transactionAllButton->setObjectName(QStringLiteral("transactionAllButton"));
        transactionAllButton->setFont(font2);

        verticalLayout_14->addWidget(transactionAllButton);

        transactionShowInReportsButton = new QPushButton(transactionSelectWidget);
        transactionShowInReportsButton->setObjectName(QStringLiteral("transactionShowInReportsButton"));
        transactionShowInReportsButton->setFont(font2);

        verticalLayout_14->addWidget(transactionShowInReportsButton);

        transactionToolBox = new QToolBox(transactionSelectWidget);
        transactionToolBox->setObjectName(QStringLiteral("transactionToolBox"));
        transactionToolBox->setFont(font2);
        transactionToolBox->setFrameShape(QFrame::NoFrame);
        transactionToolBox->setFrameShadow(QFrame::Plain);
        transactionAccountToolBox = new QWidget();
        transactionAccountToolBox->setObjectName(QStringLiteral("transactionAccountToolBox"));
        transactionAccountToolBox->setGeometry(QRect(0, 0, 290, 470));
        verticalLayout_2 = new QVBoxLayout(transactionAccountToolBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        transactionAllAccountsCheckBox = new QCheckBox(transactionAccountToolBox);
        transactionAllAccountsCheckBox->setObjectName(QStringLiteral("transactionAllAccountsCheckBox"));
        transactionAllAccountsCheckBox->setTristate(true);

        verticalLayout_2->addWidget(transactionAllAccountsCheckBox);

        transactionOpenAccountsCheckBox = new QCheckBox(transactionAccountToolBox);
        transactionOpenAccountsCheckBox->setObjectName(QStringLiteral("transactionOpenAccountsCheckBox"));
        transactionOpenAccountsCheckBox->setFont(font1);
        transactionOpenAccountsCheckBox->setTristate(true);

        verticalLayout_2->addWidget(transactionOpenAccountsCheckBox);

        transactionAccountGroupBox = new QGroupBox(transactionAccountToolBox);
        transactionAccountGroupBox->setObjectName(QStringLiteral("transactionAccountGroupBox"));
        QFont font3;
        font3.setPointSize(9);
        transactionAccountGroupBox->setFont(font3);
        verticalLayout_3 = new QVBoxLayout(transactionAccountGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));

        verticalLayout_2->addWidget(transactionAccountGroupBox);

        transactionToolBox->addItem(transactionAccountToolBox, QStringLiteral("Account"));
        transactionCategoriesToolBox = new QWidget();
        transactionCategoriesToolBox->setObjectName(QStringLiteral("transactionCategoriesToolBox"));
        transactionCategoriesToolBox->setGeometry(QRect(0, 0, 159, 152));
        verticalLayout_4 = new QVBoxLayout(transactionCategoriesToolBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        transactionAllCategoriesCheckBox = new QCheckBox(transactionCategoriesToolBox);
        transactionAllCategoriesCheckBox->setObjectName(QStringLiteral("transactionAllCategoriesCheckBox"));
        transactionAllCategoriesCheckBox->setTristate(true);

        verticalLayout_4->addWidget(transactionAllCategoriesCheckBox);

        transactionIncomeCategoriesCheckBox = new QCheckBox(transactionCategoriesToolBox);
        transactionIncomeCategoriesCheckBox->setObjectName(QStringLiteral("transactionIncomeCategoriesCheckBox"));
        transactionIncomeCategoriesCheckBox->setFont(font1);
        transactionIncomeCategoriesCheckBox->setTristate(true);

        verticalLayout_4->addWidget(transactionIncomeCategoriesCheckBox);

        transactionExpenseCategoriesCheckBox = new QCheckBox(transactionCategoriesToolBox);
        transactionExpenseCategoriesCheckBox->setObjectName(QStringLiteral("transactionExpenseCategoriesCheckBox"));
        transactionExpenseCategoriesCheckBox->setFont(font1);
        transactionExpenseCategoriesCheckBox->setTristate(true);

        verticalLayout_4->addWidget(transactionExpenseCategoriesCheckBox);

        transactionTransferCategoriesCheckBox = new QCheckBox(transactionCategoriesToolBox);
        transactionTransferCategoriesCheckBox->setObjectName(QStringLiteral("transactionTransferCategoriesCheckBox"));
        transactionTransferCategoriesCheckBox->setFont(font1);
        transactionTransferCategoriesCheckBox->setTristate(true);

        verticalLayout_4->addWidget(transactionTransferCategoriesCheckBox);

        transactionCategoriesGroupBox = new QGroupBox(transactionCategoriesToolBox);
        transactionCategoriesGroupBox->setObjectName(QStringLiteral("transactionCategoriesGroupBox"));
        transactionCategoriesGroupBox->setFont(font3);
        verticalLayout_5 = new QVBoxLayout(transactionCategoriesGroupBox);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        mTransactionCategoriesTreeExpandButton = new QPushButton(transactionCategoriesGroupBox);
        mTransactionCategoriesTreeExpandButton->setObjectName(QStringLiteral("mTransactionCategoriesTreeExpandButton"));
        mTransactionCategoriesTreeExpandButton->setMaximumSize(QSize(150, 16777215));

        verticalLayout_5->addWidget(mTransactionCategoriesTreeExpandButton);


        verticalLayout_4->addWidget(transactionCategoriesGroupBox);

        transactionToolBox->addItem(transactionCategoriesToolBox, QStringLiteral("Categories"));
        transactionLabelsToolBox = new QWidget();
        transactionLabelsToolBox->setObjectName(QStringLiteral("transactionLabelsToolBox"));
        transactionLabelsToolBox->setGeometry(QRect(0, 0, 247, 81));
        verticalLayout_6 = new QVBoxLayout(transactionLabelsToolBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        transactionAllLabelsCheckBox = new QCheckBox(transactionLabelsToolBox);
        transactionAllLabelsCheckBox->setObjectName(QStringLiteral("transactionAllLabelsCheckBox"));
        transactionAllLabelsCheckBox->setTristate(true);

        verticalLayout_6->addWidget(transactionAllLabelsCheckBox);

        transactionLabelsGroupBox = new QGroupBox(transactionLabelsToolBox);
        transactionLabelsGroupBox->setObjectName(QStringLiteral("transactionLabelsGroupBox"));
        transactionLabelsGroupBox->setFont(font3);
        verticalLayout_7 = new QVBoxLayout(transactionLabelsGroupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));

        verticalLayout_6->addWidget(transactionLabelsGroupBox);

        transactionToolBox->addItem(transactionLabelsToolBox, QStringLiteral("Labels"));
        transactionDateToolBox = new QWidget();
        transactionDateToolBox->setObjectName(QStringLiteral("transactionDateToolBox"));
        transactionDateToolBox->setGeometry(QRect(0, 0, 211, 111));
        formLayout_1 = new QFormLayout(transactionDateToolBox);
        formLayout_1->setSpacing(6);
        formLayout_1->setContentsMargins(11, 11, 11, 11);
        formLayout_1->setObjectName(QStringLiteral("formLayout_1"));
        formLayout_1->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        transactionDateComboBox = new QComboBox(transactionDateToolBox);
        transactionDateComboBox->setObjectName(QStringLiteral("transactionDateComboBox"));

        formLayout_1->setWidget(0, QFormLayout::SpanningRole, transactionDateComboBox);

        transactionStartDateLabel = new QLabel(transactionDateToolBox);
        transactionStartDateLabel->setObjectName(QStringLiteral("transactionStartDateLabel"));
        transactionStartDateLabel->setMaximumSize(QSize(16777215, 30));

        formLayout_1->setWidget(1, QFormLayout::LabelRole, transactionStartDateLabel);

        transactionStartDateEdit = new QDateEdit(transactionDateToolBox);
        transactionStartDateEdit->setObjectName(QStringLiteral("transactionStartDateEdit"));
        transactionStartDateEdit->setCalendarPopup(true);

        formLayout_1->setWidget(1, QFormLayout::FieldRole, transactionStartDateEdit);

        transactionEndDateLabel = new QLabel(transactionDateToolBox);
        transactionEndDateLabel->setObjectName(QStringLiteral("transactionEndDateLabel"));

        formLayout_1->setWidget(3, QFormLayout::LabelRole, transactionEndDateLabel);

        transactionEndDateEdit = new QDateEdit(transactionDateToolBox);
        transactionEndDateEdit->setObjectName(QStringLiteral("transactionEndDateEdit"));
        transactionEndDateEdit->setCalendarPopup(true);

        formLayout_1->setWidget(3, QFormLayout::FieldRole, transactionEndDateEdit);

        transactionToolBox->addItem(transactionDateToolBox, QStringLiteral("Date"));

        verticalLayout_14->addWidget(transactionToolBox);

        transactionSelectButton = new QPushButton(transactionSelectWidget);
        transactionSelectButton->setObjectName(QStringLiteral("transactionSelectButton"));
        transactionSelectButton->setFont(font2);

        verticalLayout_14->addWidget(transactionSelectButton);


        horizontalLayout_5->addWidget(transactionSelectWidget);

        transactionTabWidget = new QWidget(transactionsTab);
        transactionTabWidget->setObjectName(QStringLiteral("transactionTabWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(transactionTabWidget->sizePolicy().hasHeightForWidth());
        transactionTabWidget->setSizePolicy(sizePolicy4);
        horizontalLayout_21 = new QVBoxLayout(transactionTabWidget);
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        transactionSearchWidget = new QWidget(transactionTabWidget);
        transactionSearchWidget->setObjectName(QStringLiteral("transactionSearchWidget"));
        transactionSearchWidget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_18 = new QHBoxLayout(transactionSearchWidget);
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        transactionSearchLabel = new QLabel(transactionSearchWidget);
        transactionSearchLabel->setObjectName(QStringLiteral("transactionSearchLabel"));
        transactionSearchLabel->setFont(font1);
        transactionSearchLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_18->addWidget(transactionSearchLabel);

        transactionSearchTextLineEdit = new QLineEdit(transactionSearchWidget);
        transactionSearchTextLineEdit->setObjectName(QStringLiteral("transactionSearchTextLineEdit"));
        transactionSearchTextLineEdit->setMinimumSize(QSize(0, 25));
        transactionSearchTextLineEdit->setFont(font2);

        horizontalLayout_18->addWidget(transactionSearchTextLineEdit);

        transactionSearchButton = new QPushButton(transactionSearchWidget);
        transactionSearchButton->setObjectName(QStringLiteral("transactionSearchButton"));
        transactionSearchButton->setFont(font2);

        horizontalLayout_18->addWidget(transactionSearchButton);

        transactionSearchClearButton = new QPushButton(transactionSearchWidget);
        transactionSearchClearButton->setObjectName(QStringLiteral("transactionSearchClearButton"));
        transactionSearchClearButton->setFont(font2);

        horizontalLayout_18->addWidget(transactionSearchClearButton);


        horizontalLayout_21->addWidget(transactionSearchWidget);

        transactionListWidget = new QWidget(transactionTabWidget);
        transactionListWidget->setObjectName(QStringLiteral("transactionListWidget"));
        horizontalLayout_20 = new QHBoxLayout(transactionListWidget);
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_21->addWidget(transactionListWidget);

        transactionDisplayWidget = new QWidget(transactionTabWidget);
        transactionDisplayWidget->setObjectName(QStringLiteral("transactionDisplayWidget"));
        transactionDisplayWidget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_19 = new QHBoxLayout(transactionDisplayWidget);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        transactionDisplayCreditLabel = new QLabel(transactionDisplayWidget);
        transactionDisplayCreditLabel->setObjectName(QStringLiteral("transactionDisplayCreditLabel"));
        transactionDisplayCreditLabel->setFont(font1);
        transactionDisplayCreditLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_19->addWidget(transactionDisplayCreditLabel);

        transactionDisplayCreditValue = new QLabel(transactionDisplayWidget);
        transactionDisplayCreditValue->setObjectName(QStringLiteral("transactionDisplayCreditValue"));
        transactionDisplayCreditValue->setMinimumSize(QSize(0, 25));
        transactionDisplayCreditValue->setFont(font2);
        transactionDisplayCreditValue->setFrameShape(QFrame::StyledPanel);
        transactionDisplayCreditValue->setFrameShadow(QFrame::Sunken);

        horizontalLayout_19->addWidget(transactionDisplayCreditValue);

        transactionDisplayDebitLabel = new QLabel(transactionDisplayWidget);
        transactionDisplayDebitLabel->setObjectName(QStringLiteral("transactionDisplayDebitLabel"));
        transactionDisplayDebitLabel->setFont(font1);
        transactionDisplayDebitLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_19->addWidget(transactionDisplayDebitLabel);

        transactionDisplayDebitValue = new QLabel(transactionDisplayWidget);
        transactionDisplayDebitValue->setObjectName(QStringLiteral("transactionDisplayDebitValue"));
        transactionDisplayDebitValue->setMinimumSize(QSize(0, 25));
        transactionDisplayDebitValue->setFont(font2);
        transactionDisplayDebitValue->setFrameShape(QFrame::StyledPanel);
        transactionDisplayDebitValue->setFrameShadow(QFrame::Sunken);

        horizontalLayout_19->addWidget(transactionDisplayDebitValue);

        transactionDisplayNetLabel = new QLabel(transactionDisplayWidget);
        transactionDisplayNetLabel->setObjectName(QStringLiteral("transactionDisplayNetLabel"));
        transactionDisplayNetLabel->setFont(font1);
        transactionDisplayNetLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_19->addWidget(transactionDisplayNetLabel);

        transactionDisplayNetValue = new QLabel(transactionDisplayWidget);
        transactionDisplayNetValue->setObjectName(QStringLiteral("transactionDisplayNetValue"));
        transactionDisplayNetValue->setMinimumSize(QSize(0, 25));
        transactionDisplayNetValue->setFont(font2);
        transactionDisplayNetValue->setFrameShape(QFrame::StyledPanel);
        transactionDisplayNetValue->setFrameShadow(QFrame::Sunken);

        horizontalLayout_19->addWidget(transactionDisplayNetValue);


        horizontalLayout_21->addWidget(transactionDisplayWidget);


        horizontalLayout_5->addWidget(transactionTabWidget);

        tabWidget->addTab(transactionsTab, QString());
        reportTab = new QWidget();
        reportTab->setObjectName(QStringLiteral("reportTab"));
        horizontalLayout_6 = new QHBoxLayout(reportTab);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        reportSelectWidget = new QWidget(reportTab);
        reportSelectWidget->setObjectName(QStringLiteral("reportSelectWidget"));
        reportSelectWidget->setMinimumSize(QSize(300, 0));
        reportSelectWidget->setMaximumSize(QSize(250, 16777215));
        verticalLayout_15 = new QVBoxLayout(reportSelectWidget);
        verticalLayout_15->setSpacing(2);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(5, 5, 5, 5);
        reportAllButton = new QPushButton(reportSelectWidget);
        reportAllButton->setObjectName(QStringLiteral("reportAllButton"));
        reportAllButton->setFont(font2);

        verticalLayout_15->addWidget(reportAllButton);

        reportShowInTransactionsButton = new QPushButton(reportSelectWidget);
        reportShowInTransactionsButton->setObjectName(QStringLiteral("reportShowInTransactionsButton"));
        reportShowInTransactionsButton->setFont(font2);

        verticalLayout_15->addWidget(reportShowInTransactionsButton);

        reportToolBox = new QToolBox(reportSelectWidget);
        reportToolBox->setObjectName(QStringLiteral("reportToolBox"));
        reportToolBox->setFont(font2);
        reportToolBox->setFrameShape(QFrame::NoFrame);
        reportToolBox->setFrameShadow(QFrame::Plain);
        reportAccountToolBox = new QWidget();
        reportAccountToolBox->setObjectName(QStringLiteral("reportAccountToolBox"));
        reportAccountToolBox->setGeometry(QRect(0, 0, 290, 422));
        verticalLayout_8 = new QVBoxLayout(reportAccountToolBox);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        reportAllAccountsCheckBox = new QCheckBox(reportAccountToolBox);
        reportAllAccountsCheckBox->setObjectName(QStringLiteral("reportAllAccountsCheckBox"));
        reportAllAccountsCheckBox->setTristate(true);

        verticalLayout_8->addWidget(reportAllAccountsCheckBox);

        reportOpenAccountsCheckBox = new QCheckBox(reportAccountToolBox);
        reportOpenAccountsCheckBox->setObjectName(QStringLiteral("reportOpenAccountsCheckBox"));
        reportOpenAccountsCheckBox->setFont(font1);
        reportOpenAccountsCheckBox->setTristate(true);

        verticalLayout_8->addWidget(reportOpenAccountsCheckBox);

        reportAccountGroupBox = new QGroupBox(reportAccountToolBox);
        reportAccountGroupBox->setObjectName(QStringLiteral("reportAccountGroupBox"));
        reportAccountGroupBox->setFont(font3);
        verticalLayout_9 = new QVBoxLayout(reportAccountGroupBox);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));

        verticalLayout_8->addWidget(reportAccountGroupBox);

        reportToolBox->addItem(reportAccountToolBox, QStringLiteral("Account"));
        reportCategoriesToolBox = new QWidget();
        reportCategoriesToolBox->setObjectName(QStringLiteral("reportCategoriesToolBox"));
        reportCategoriesToolBox->setGeometry(QRect(0, 0, 159, 152));
        verticalLayout_10 = new QVBoxLayout(reportCategoriesToolBox);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        reportAllCategoriesCheckBox = new QCheckBox(reportCategoriesToolBox);
        reportAllCategoriesCheckBox->setObjectName(QStringLiteral("reportAllCategoriesCheckBox"));
        reportAllCategoriesCheckBox->setTristate(true);

        verticalLayout_10->addWidget(reportAllCategoriesCheckBox);

        reportIncomeCategoriesCheckBox = new QCheckBox(reportCategoriesToolBox);
        reportIncomeCategoriesCheckBox->setObjectName(QStringLiteral("reportIncomeCategoriesCheckBox"));
        reportIncomeCategoriesCheckBox->setFont(font1);
        reportIncomeCategoriesCheckBox->setTristate(true);

        verticalLayout_10->addWidget(reportIncomeCategoriesCheckBox);

        reportExpenseCategoriesCheckBox = new QCheckBox(reportCategoriesToolBox);
        reportExpenseCategoriesCheckBox->setObjectName(QStringLiteral("reportExpenseCategoriesCheckBox"));
        reportExpenseCategoriesCheckBox->setFont(font1);
        reportExpenseCategoriesCheckBox->setTristate(true);

        verticalLayout_10->addWidget(reportExpenseCategoriesCheckBox);

        reportTransferCategoriesCheckBox = new QCheckBox(reportCategoriesToolBox);
        reportTransferCategoriesCheckBox->setObjectName(QStringLiteral("reportTransferCategoriesCheckBox"));
        reportTransferCategoriesCheckBox->setFont(font1);
        reportTransferCategoriesCheckBox->setTristate(true);

        verticalLayout_10->addWidget(reportTransferCategoriesCheckBox);

        reportCategoriesGroupBox = new QGroupBox(reportCategoriesToolBox);
        reportCategoriesGroupBox->setObjectName(QStringLiteral("reportCategoriesGroupBox"));
        reportCategoriesGroupBox->setFont(font3);
        verticalLayout_11 = new QVBoxLayout(reportCategoriesGroupBox);
        verticalLayout_11->setSpacing(1);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(1, 1, 1, 1);
        mReportCategoriesTreeExpandButton = new QPushButton(reportCategoriesGroupBox);
        mReportCategoriesTreeExpandButton->setObjectName(QStringLiteral("mReportCategoriesTreeExpandButton"));
        mReportCategoriesTreeExpandButton->setMaximumSize(QSize(150, 16777215));

        verticalLayout_11->addWidget(mReportCategoriesTreeExpandButton);


        verticalLayout_10->addWidget(reportCategoriesGroupBox);

        reportToolBox->addItem(reportCategoriesToolBox, QStringLiteral("Categories"));
        reportLabelsToolBox = new QWidget();
        reportLabelsToolBox->setObjectName(QStringLiteral("reportLabelsToolBox"));
        reportLabelsToolBox->setGeometry(QRect(0, 0, 247, 81));
        verticalLayout_12 = new QVBoxLayout(reportLabelsToolBox);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        reportAllLabelsCheckBox = new QCheckBox(reportLabelsToolBox);
        reportAllLabelsCheckBox->setObjectName(QStringLiteral("reportAllLabelsCheckBox"));
        reportAllLabelsCheckBox->setTristate(true);

        verticalLayout_12->addWidget(reportAllLabelsCheckBox);

        reportLabelsGroupBox = new QGroupBox(reportLabelsToolBox);
        reportLabelsGroupBox->setObjectName(QStringLiteral("reportLabelsGroupBox"));
        reportLabelsGroupBox->setFont(font3);
        verticalLayout_13 = new QVBoxLayout(reportLabelsGroupBox);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));

        verticalLayout_12->addWidget(reportLabelsGroupBox);

        reportToolBox->addItem(reportLabelsToolBox, QStringLiteral("Labels"));
        reportDateToolBox = new QWidget();
        reportDateToolBox->setObjectName(QStringLiteral("reportDateToolBox"));
        reportDateToolBox->setGeometry(QRect(0, 0, 238, 142));
        formLayout_2 = new QFormLayout(reportDateToolBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        reportDateComboBox = new QComboBox(reportDateToolBox);
        reportDateComboBox->setObjectName(QStringLiteral("reportDateComboBox"));

        formLayout_2->setWidget(0, QFormLayout::SpanningRole, reportDateComboBox);

        reportStartDateLabel = new QLabel(reportDateToolBox);
        reportStartDateLabel->setObjectName(QStringLiteral("reportStartDateLabel"));
        reportStartDateLabel->setMaximumSize(QSize(16777215, 30));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, reportStartDateLabel);

        reportStartDateEdit = new QDateEdit(reportDateToolBox);
        reportStartDateEdit->setObjectName(QStringLiteral("reportStartDateEdit"));
        reportStartDateEdit->setCalendarPopup(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, reportStartDateEdit);

        reportEndDateLabel = new QLabel(reportDateToolBox);
        reportEndDateLabel->setObjectName(QStringLiteral("reportEndDateLabel"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, reportEndDateLabel);

        reportEndDateEdit = new QDateEdit(reportDateToolBox);
        reportEndDateEdit->setObjectName(QStringLiteral("reportEndDateEdit"));
        reportEndDateEdit->setCalendarPopup(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, reportEndDateEdit);

        reportDateIntervalLabel = new QLabel(reportDateToolBox);
        reportDateIntervalLabel->setObjectName(QStringLiteral("reportDateIntervalLabel"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, reportDateIntervalLabel);

        reportDateIntervalComboBox = new QComboBox(reportDateToolBox);
        reportDateIntervalComboBox->setObjectName(QStringLiteral("reportDateIntervalComboBox"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, reportDateIntervalComboBox);

        reportToolBox->addItem(reportDateToolBox, QStringLiteral("Date"));

        verticalLayout_15->addWidget(reportToolBox);

        mReportShowNetIncomeCheckBox = new QCheckBox(reportSelectWidget);
        mReportShowNetIncomeCheckBox->setObjectName(QStringLiteral("mReportShowNetIncomeCheckBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(mReportShowNetIncomeCheckBox->sizePolicy().hasHeightForWidth());
        mReportShowNetIncomeCheckBox->setSizePolicy(sizePolicy5);
        mReportShowNetIncomeCheckBox->setMaximumSize(QSize(16777215, 16777215));
        QFont font4;
        font4.setPointSize(11);
        mReportShowNetIncomeCheckBox->setFont(font4);
        mReportShowNetIncomeCheckBox->setLayoutDirection(Qt::LeftToRight);
        mReportShowNetIncomeCheckBox->setChecked(true);

        verticalLayout_15->addWidget(mReportShowNetIncomeCheckBox);

        mReportShowTransfersCheckBox = new QCheckBox(reportSelectWidget);
        mReportShowTransfersCheckBox->setObjectName(QStringLiteral("mReportShowTransfersCheckBox"));
        mReportShowTransfersCheckBox->setFont(font4);

        verticalLayout_15->addWidget(mReportShowTransfersCheckBox);

        reportSelectButton = new QPushButton(reportSelectWidget);
        reportSelectButton->setObjectName(QStringLiteral("reportSelectButton"));
        reportSelectButton->setFont(font2);

        verticalLayout_15->addWidget(reportSelectButton);


        horizontalLayout_6->addWidget(reportSelectWidget);

        reportDisplayTabWidget = new QTabWidget(reportTab);
        reportDisplayTabWidget->setObjectName(QStringLiteral("reportDisplayTabWidget"));
        reportDisplayTabWidget->setTabPosition(QTabWidget::North);
        reportNetIncomeTab = new QWidget();
        reportNetIncomeTab->setObjectName(QStringLiteral("reportNetIncomeTab"));
        horizontalLayout_3 = new QHBoxLayout(reportNetIncomeTab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        reportDisplayTabWidget->addTab(reportNetIncomeTab, QString());
        reportNetWorthTab = new QWidget();
        reportNetWorthTab->setObjectName(QStringLiteral("reportNetWorthTab"));
        horizontalLayout_4 = new QHBoxLayout(reportNetWorthTab);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        reportDisplayTabWidget->addTab(reportNetWorthTab, QString());
        reportListTab = new QWidget();
        reportListTab->setObjectName(QStringLiteral("reportListTab"));
        horizontalLayout_7 = new QHBoxLayout(reportListTab);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        reportDisplayTabWidget->addTab(reportListTab, QString());
        reportAccountBalanceTab = new QWidget();
        reportAccountBalanceTab->setObjectName(QStringLiteral("reportAccountBalanceTab"));
        horizontalLayout_25 = new QHBoxLayout(reportAccountBalanceTab);
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        reportDisplayTabWidget->addTab(reportAccountBalanceTab, QString());
        reportAccountTab = new QWidget();
        reportAccountTab->setObjectName(QStringLiteral("reportAccountTab"));
        _2 = new QHBoxLayout(reportAccountTab);
        _2->setSpacing(6);
        _2->setContentsMargins(11, 11, 11, 11);
        _2->setObjectName(QStringLiteral("_2"));
        frame = new QFrame(reportAccountTab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_16 = new QVBoxLayout(frame);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        mReportAssetDebtComboBox = new QComboBox(frame);
        mReportAssetDebtComboBox->setObjectName(QStringLiteral("mReportAssetDebtComboBox"));
        mReportAssetDebtComboBox->setMaximumSize(QSize(200, 16777215));

        verticalLayout_16->addWidget(mReportAssetDebtComboBox);

        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_9 = new QHBoxLayout(widget);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        reportAssetGroupBox = new QGroupBox(widget);
        reportAssetGroupBox->setObjectName(QStringLiteral("reportAssetGroupBox"));
        horizontalLayout_13 = new QHBoxLayout(reportAssetGroupBox);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));

        horizontalLayout_9->addWidget(reportAssetGroupBox);

        reportDebtGroupBox = new QGroupBox(widget);
        reportDebtGroupBox->setObjectName(QStringLiteral("reportDebtGroupBox"));
        horizontalLayout_14 = new QHBoxLayout(reportDebtGroupBox);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));

        horizontalLayout_9->addWidget(reportDebtGroupBox);


        verticalLayout_16->addWidget(widget);


        _2->addWidget(frame);

        reportDisplayTabWidget->addTab(reportAccountTab, QString());
        reportCategoryTab = new QWidget();
        reportCategoryTab->setObjectName(QStringLiteral("reportCategoryTab"));
        horizontalLayout_10 = new QHBoxLayout(reportCategoryTab);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        frame_2 = new QFrame(reportCategoryTab);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_17 = new QVBoxLayout(frame_2);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        mReportIncomeExpenseComboBox = new QComboBox(frame_2);
        mReportIncomeExpenseComboBox->setObjectName(QStringLiteral("mReportIncomeExpenseComboBox"));
        mReportIncomeExpenseComboBox->setMaximumSize(QSize(200, 16777215));

        verticalLayout_17->addWidget(mReportIncomeExpenseComboBox);

        widget_2 = new QWidget(frame_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_22 = new QHBoxLayout(widget_2);
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        reportIncomeParentGroupBox = new QGroupBox(widget_2);
        reportIncomeParentGroupBox->setObjectName(QStringLiteral("reportIncomeParentGroupBox"));
        horizontalLayout_11 = new QHBoxLayout(reportIncomeParentGroupBox);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));

        horizontalLayout_22->addWidget(reportIncomeParentGroupBox);

        reportExpenseParentGroupBox = new QGroupBox(widget_2);
        reportExpenseParentGroupBox->setObjectName(QStringLiteral("reportExpenseParentGroupBox"));
        horizontalLayout_12 = new QHBoxLayout(reportExpenseParentGroupBox);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));

        horizontalLayout_22->addWidget(reportExpenseParentGroupBox);


        verticalLayout_17->addWidget(widget_2);


        horizontalLayout_10->addWidget(frame_2);

        reportDisplayTabWidget->addTab(reportCategoryTab, QString());
        reportSubCategoryTab = new QWidget();
        reportSubCategoryTab->setObjectName(QStringLiteral("reportSubCategoryTab"));
        horizontalLayout_15 = new QHBoxLayout(reportSubCategoryTab);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        frame_3 = new QFrame(reportSubCategoryTab);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_18 = new QVBoxLayout(frame_3);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        mReportSubIncomeExpenseComboBox = new QComboBox(frame_3);
        mReportSubIncomeExpenseComboBox->setObjectName(QStringLiteral("mReportSubIncomeExpenseComboBox"));
        mReportSubIncomeExpenseComboBox->setMaximumSize(QSize(200, 16777215));

        verticalLayout_18->addWidget(mReportSubIncomeExpenseComboBox);

        widget_3 = new QWidget(frame_3);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_23 = new QHBoxLayout(widget_3);
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        reportIncomeSubGroupBox = new QGroupBox(widget_3);
        reportIncomeSubGroupBox->setObjectName(QStringLiteral("reportIncomeSubGroupBox"));
        horizontalLayout_16 = new QHBoxLayout(reportIncomeSubGroupBox);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));

        horizontalLayout_23->addWidget(reportIncomeSubGroupBox);

        reportExpenseSubGroupBox = new QGroupBox(widget_3);
        reportExpenseSubGroupBox->setObjectName(QStringLiteral("reportExpenseSubGroupBox"));
        horizontalLayout_17 = new QHBoxLayout(reportExpenseSubGroupBox);
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));

        horizontalLayout_23->addWidget(reportExpenseSubGroupBox);


        verticalLayout_18->addWidget(widget_3);


        horizontalLayout_15->addWidget(frame_3);

        reportDisplayTabWidget->addTab(reportSubCategoryTab, QString());

        horizontalLayout_6->addWidget(reportDisplayTabWidget);

        tabWidget->addTab(reportTab, QString());

        horizontalLayout->addWidget(tabWidget);

        TransactionManager->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TransactionManager);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1373, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        TransactionManager->setMenuBar(menuBar);
        statusBar = new QStatusBar(TransactionManager);
        statusBar->setObjectName(QStringLiteral("statusBar"));
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
        menuHelp->addAction(actionDisplayAbout);
        menuHelp->addAction(actionDisplayHelp);
        menuHelp->addSeparator();
        menuHelp->addAction(actionDisplayLog);
        menuTools->addAction(actionDisplayFile);
        menuTools->addAction(actionFileInputConfig);

        retranslateUi(TransactionManager);

        tabWidget->setCurrentIndex(0);
        transactionToolBox->setCurrentIndex(0);
        reportToolBox->setCurrentIndex(0);
        reportDisplayTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TransactionManager);
    } // setupUi

    void retranslateUi(QMainWindow *TransactionManager)
    {
        TransactionManager->setWindowTitle(QApplication::translate("TransactionManager", "TransactionManager", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("TransactionManager", "Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("TransactionManager", "Save", Q_NULLPTR));
        actionSaveAs->setText(QApplication::translate("TransactionManager", "Save As", Q_NULLPTR));
        actionExit->setText(QApplication::translate("TransactionManager", "Exit", Q_NULLPTR));
        actionClose->setText(QApplication::translate("TransactionManager", "Close", Q_NULLPTR));
        actionDisplayFile->setText(QApplication::translate("TransactionManager", "Display File Contents", Q_NULLPTR));
        actionDisplayLog->setText(QApplication::translate("TransactionManager", "Display Log", Q_NULLPTR));
        actionFileInputConfig->setText(QApplication::translate("TransactionManager", "Configure Input File", Q_NULLPTR));
        actionDisplayHelp->setText(QApplication::translate("TransactionManager", "Help", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDisplayHelp->setToolTip(QApplication::translate("TransactionManager", "Show Help Documentation", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDisplayAbout->setText(QApplication::translate("TransactionManager", "About", Q_NULLPTR));
        overviewAccountTitle->setText(QApplication::translate("TransactionManager", "Accounts", Q_NULLPTR));
        overviewNumberOfAccountsLabel->setText(QApplication::translate("TransactionManager", "Number of Accounts:", Q_NULLPTR));
        overviewNumberOfAccountValue->setText(QApplication::translate("TransactionManager", "TextLabel", Q_NULLPTR));
        overviewNumberOfTransactionsLabel->setText(QApplication::translate("TransactionManager", "Number of Transactions:", Q_NULLPTR));
        overviewNumberOfTransactionsValue->setText(QApplication::translate("TransactionManager", "TextLabel", Q_NULLPTR));
        overviewNetWorthLabel->setText(QApplication::translate("TransactionManager", "Net Worth:", Q_NULLPTR));
        overviewNetWorthValue->setText(QApplication::translate("TransactionManager", "TextLabel", Q_NULLPTR));
        overviewFirstDateLabel->setText(QApplication::translate("TransactionManager", "Date of First Transaction:", Q_NULLPTR));
        overviewFirstDateValue->setText(QApplication::translate("TransactionManager", "TextLabel", Q_NULLPTR));
        overviewLastDateLabel->setText(QApplication::translate("TransactionManager", "Date of Last Transaction:", Q_NULLPTR));
        overviewLastDateValue->setText(QApplication::translate("TransactionManager", "TextLabel", Q_NULLPTR));
        overviewShowClosedAccountsLabel->setText(QApplication::translate("TransactionManager", "Show Closed Accounts:", Q_NULLPTR));
        overviewShowClosedAccountsCheckBox->setText(QString());
        overviewSortAccountsLabel->setText(QApplication::translate("TransactionManager", "Sort Accounts By:", Q_NULLPTR));
        mNotesImageLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(overviewTab), QApplication::translate("TransactionManager", "Overview", Q_NULLPTR));
        transactionAllButton->setText(QApplication::translate("TransactionManager", "Show All", Q_NULLPTR));
        transactionShowInReportsButton->setText(QApplication::translate("TransactionManager", "Show Filter in Reports ->", Q_NULLPTR));
        transactionAllAccountsCheckBox->setText(QApplication::translate("TransactionManager", "All Acounts", Q_NULLPTR));
        transactionOpenAccountsCheckBox->setText(QApplication::translate("TransactionManager", " Open Accounts", Q_NULLPTR));
        transactionAccountGroupBox->setTitle(QString());
        transactionToolBox->setItemText(transactionToolBox->indexOf(transactionAccountToolBox), QApplication::translate("TransactionManager", "Account", Q_NULLPTR));
        transactionAllCategoriesCheckBox->setText(QApplication::translate("TransactionManager", "All Categories", Q_NULLPTR));
        transactionIncomeCategoriesCheckBox->setText(QApplication::translate("TransactionManager", " Income Categories", Q_NULLPTR));
        transactionExpenseCategoriesCheckBox->setText(QApplication::translate("TransactionManager", " Expense Categories", Q_NULLPTR));
        transactionTransferCategoriesCheckBox->setText(QApplication::translate("TransactionManager", " Transfer Categories", Q_NULLPTR));
        transactionCategoriesGroupBox->setTitle(QString());
        mTransactionCategoriesTreeExpandButton->setText(QApplication::translate("TransactionManager", "Expand All", Q_NULLPTR));
        transactionToolBox->setItemText(transactionToolBox->indexOf(transactionCategoriesToolBox), QApplication::translate("TransactionManager", "Categories", Q_NULLPTR));
        transactionAllLabelsCheckBox->setText(QApplication::translate("TransactionManager", "All Labels", Q_NULLPTR));
        transactionLabelsGroupBox->setTitle(QApplication::translate("TransactionManager", "Labels: Match | Don't Match | Exclude", Q_NULLPTR));
        transactionToolBox->setItemText(transactionToolBox->indexOf(transactionLabelsToolBox), QApplication::translate("TransactionManager", "Labels", Q_NULLPTR));
        transactionStartDateLabel->setText(QApplication::translate("TransactionManager", "Start Date:", Q_NULLPTR));
        transactionStartDateEdit->setSpecialValueText(QString());
        transactionStartDateEdit->setDisplayFormat(QApplication::translate("TransactionManager", "yyyy-MM-dd", Q_NULLPTR));
        transactionEndDateLabel->setText(QApplication::translate("TransactionManager", "End Date:", Q_NULLPTR));
        transactionEndDateEdit->setDisplayFormat(QApplication::translate("TransactionManager", "yyyy-MM-dd", Q_NULLPTR));
        transactionToolBox->setItemText(transactionToolBox->indexOf(transactionDateToolBox), QApplication::translate("TransactionManager", "Date", Q_NULLPTR));
        transactionSelectButton->setText(QApplication::translate("TransactionManager", "Apply", Q_NULLPTR));
        transactionSearchLabel->setText(QApplication::translate("TransactionManager", "Filter Transactions:", Q_NULLPTR));
        transactionSearchButton->setText(QApplication::translate("TransactionManager", "Search", Q_NULLPTR));
        transactionSearchClearButton->setText(QApplication::translate("TransactionManager", "Clear", Q_NULLPTR));
        transactionDisplayCreditLabel->setText(QApplication::translate("TransactionManager", "Total Credit:", Q_NULLPTR));
        transactionDisplayCreditValue->setText(QApplication::translate("TransactionManager", "TextLabel", Q_NULLPTR));
        transactionDisplayDebitLabel->setText(QApplication::translate("TransactionManager", "Total Debit:", Q_NULLPTR));
        transactionDisplayDebitValue->setText(QApplication::translate("TransactionManager", "TextLabel", Q_NULLPTR));
        transactionDisplayNetLabel->setText(QApplication::translate("TransactionManager", "Net Amount:", Q_NULLPTR));
        transactionDisplayNetValue->setText(QApplication::translate("TransactionManager", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(transactionsTab), QApplication::translate("TransactionManager", "Transactions", Q_NULLPTR));
        reportAllButton->setText(QApplication::translate("TransactionManager", "Show All", Q_NULLPTR));
        reportShowInTransactionsButton->setText(QApplication::translate("TransactionManager", "<- Show Filter in Transactions", Q_NULLPTR));
        reportAllAccountsCheckBox->setText(QApplication::translate("TransactionManager", "All Acounts", Q_NULLPTR));
        reportOpenAccountsCheckBox->setText(QApplication::translate("TransactionManager", " Open Accounts", Q_NULLPTR));
        reportAccountGroupBox->setTitle(QString());
        reportToolBox->setItemText(reportToolBox->indexOf(reportAccountToolBox), QApplication::translate("TransactionManager", "Account", Q_NULLPTR));
        reportAllCategoriesCheckBox->setText(QApplication::translate("TransactionManager", "All Categories", Q_NULLPTR));
        reportIncomeCategoriesCheckBox->setText(QApplication::translate("TransactionManager", " Income Categories", Q_NULLPTR));
        reportExpenseCategoriesCheckBox->setText(QApplication::translate("TransactionManager", " Expense Categories", Q_NULLPTR));
        reportTransferCategoriesCheckBox->setText(QApplication::translate("TransactionManager", " Transfer Categories", Q_NULLPTR));
        reportCategoriesGroupBox->setTitle(QString());
        mReportCategoriesTreeExpandButton->setText(QApplication::translate("TransactionManager", "Expand All", Q_NULLPTR));
        reportToolBox->setItemText(reportToolBox->indexOf(reportCategoriesToolBox), QApplication::translate("TransactionManager", "Categories", Q_NULLPTR));
        reportAllLabelsCheckBox->setText(QApplication::translate("TransactionManager", "All Labels", Q_NULLPTR));
        reportLabelsGroupBox->setTitle(QApplication::translate("TransactionManager", "Labels: Match | Don't Match | Exclude", Q_NULLPTR));
        reportToolBox->setItemText(reportToolBox->indexOf(reportLabelsToolBox), QApplication::translate("TransactionManager", "Labels", Q_NULLPTR));
        reportStartDateLabel->setText(QApplication::translate("TransactionManager", "Start Date:", Q_NULLPTR));
        reportStartDateEdit->setSpecialValueText(QString());
        reportStartDateEdit->setDisplayFormat(QApplication::translate("TransactionManager", "yyyy-MM-dd", Q_NULLPTR));
        reportEndDateLabel->setText(QApplication::translate("TransactionManager", "End Date:", Q_NULLPTR));
        reportEndDateEdit->setDisplayFormat(QApplication::translate("TransactionManager", "yyyy-MM-dd", Q_NULLPTR));
        reportDateIntervalLabel->setText(QApplication::translate("TransactionManager", "Report Period:", Q_NULLPTR));
        reportToolBox->setItemText(reportToolBox->indexOf(reportDateToolBox), QApplication::translate("TransactionManager", "Date", Q_NULLPTR));
        mReportShowNetIncomeCheckBox->setText(QApplication::translate("TransactionManager", "Show Net Income", Q_NULLPTR));
        mReportShowTransfersCheckBox->setText(QApplication::translate("TransactionManager", "Show Transfers", Q_NULLPTR));
        reportSelectButton->setText(QApplication::translate("TransactionManager", "Apply", Q_NULLPTR));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportNetIncomeTab), QApplication::translate("TransactionManager", "Net Income", Q_NULLPTR));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportNetIncomeTab), QApplication::translate("TransactionManager", "Income/Expense Bar Chart", Q_NULLPTR));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportNetWorthTab), QApplication::translate("TransactionManager", "Net Worth", Q_NULLPTR));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportNetWorthTab), QApplication::translate("TransactionManager", "Net Worth Bar Chart", Q_NULLPTR));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportListTab), QApplication::translate("TransactionManager", "Report List", Q_NULLPTR));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportListTab), QApplication::translate("TransactionManager", "Income/Expense/Net Worth List", Q_NULLPTR));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportAccountBalanceTab), QApplication::translate("TransactionManager", "Account Balance", Q_NULLPTR));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportAccountBalanceTab), QApplication::translate("TransactionManager", "Account Balance Bar Chart", Q_NULLPTR));
        reportAssetGroupBox->setTitle(QApplication::translate("TransactionManager", "Assets by Account", Q_NULLPTR));
        reportDebtGroupBox->setTitle(QApplication::translate("TransactionManager", "Debts by Account", Q_NULLPTR));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportAccountTab), QApplication::translate("TransactionManager", "Assets/Debts by Account", Q_NULLPTR));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportAccountTab), QApplication::translate("TransactionManager", "Assets/Debts Pie Charts by Account at End Date", Q_NULLPTR));
        reportIncomeParentGroupBox->setTitle(QApplication::translate("TransactionManager", "Income By Parent Category", Q_NULLPTR));
        reportExpenseParentGroupBox->setTitle(QApplication::translate("TransactionManager", "Expense By Parent Category", Q_NULLPTR));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportCategoryTab), QApplication::translate("TransactionManager", "Income/Expense by Parent Category", Q_NULLPTR));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportCategoryTab), QApplication::translate("TransactionManager", "Income/Expense Pie Charts by Parent Category at End Date", Q_NULLPTR));
        reportIncomeSubGroupBox->setTitle(QApplication::translate("TransactionManager", "Income By Sub Category", Q_NULLPTR));
        reportExpenseSubGroupBox->setTitle(QApplication::translate("TransactionManager", "Expense By Sub Category", Q_NULLPTR));
        reportDisplayTabWidget->setTabText(reportDisplayTabWidget->indexOf(reportSubCategoryTab), QApplication::translate("TransactionManager", "Income/Expense by Sub Category", Q_NULLPTR));
        reportDisplayTabWidget->setTabToolTip(reportDisplayTabWidget->indexOf(reportSubCategoryTab), QApplication::translate("TransactionManager", "Income/Expense Pie Charst by Sub Category at End Date", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(reportTab), QApplication::translate("TransactionManager", "Reports", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("TransactionManager", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("TransactionManager", "Help", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("TransactionManager", "Tools", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TransactionManager: public Ui_TransactionManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONMANAGER_H
