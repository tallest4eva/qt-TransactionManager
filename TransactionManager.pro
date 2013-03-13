#-------------------------------------------------
#
# Project created by QtCreator 2013-02-02T18:07:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TransactionManager
TEMPLATE = app


SOURCES += main.cpp\
        Account.cpp\
        Category.cpp\
        DisplayDialog.cpp\
        FileConfigDialog.cpp\
        GraphWidget.cpp\
        Logger.cpp\
        Month.cpp\
        OverviewAccountListItem.cpp\
        Parser.cpp\
        PieView.cpp\
        ReportTableView.cpp\
        Transaction.cpp\
        TransactionListModel.cpp\
        TransactionManager.cpp

HEADERS  += Account.h\
        Category.h\
        DisplayDialog.h\
        FileConfigDialog.h\
        GraphWidget.h\
        Logger.h\
        Month.h\
        OverviewAccountListItem.h\
        Parser.h\
        PieView.h\
        ReportTableView.h\
        Transaction.h\
        TransactionListModel.h\
        TransactionManager.h

FORMS    += transactionmanager.ui

RESOURCES += \
    TransactionManager.qrc

CONFIG += qwt

#QWT
QWT_LOCATION = C:/Qwt-6.0.2
 
INCLUDEPATH +=  $${QWT_LOCATION}/include/
LIBS =          -L$${QWT_LOCATION}/lib \
                -lqwt