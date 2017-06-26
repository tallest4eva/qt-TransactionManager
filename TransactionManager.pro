#-------------------------------------------------
#
# Project created by QtCreator 2013-02-02T18:07:22
#
#-------------------------------------------------

QT       += core gui xml


#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TransactionManager
TEMPLATE = app

DEFINES *= QT_USE_QSTRINGBUILDER

SOURCES += main.cpp\
        Account.cpp\
        BarGraph.cpp\
        Category.cpp\
        DisplayDialog.cpp\
        DisplayLabel.cpp\
        FileConfigDialog.cpp\
        Logger.cpp\
        Month.cpp\
        OverviewAccountListItem.cpp\
        Parser.cpp\
        PieView.cpp\
        ReportPieChart.cpp\
        ReportTableView.cpp\
        Transaction.cpp\
        TransactionList.cpp\
        TransactionManager.cpp\
        TripleRadioButton.cpp\
        qcustomplot.cpp

HEADERS  += Account.hpp\
        Category.hpp\
        BarGraph.hpp\
        DisplayDialog.hpp\
        DisplayLabel.hpp\
        FileConfigDialog.hpp\
        Logger.hpp\
        Month.hpp\
        OverviewAccountListItem.hpp\
        Parser.hpp\
        PieView.hpp\
        ReportPieChart.hpp\
        ReportTableView.hpp\
        Transaction.hpp\
        TransactionList.hpp\
        TransactionManager.hpp\
        TripleRadioButton.hpp\
        qcustomplot.hpp

FORMS    += transactionmanager.ui

RESOURCES += \
    TransactionManager.qrc
