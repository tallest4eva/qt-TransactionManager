//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: ReportTableView.h
//******************************************************************************

#ifndef ReportTableView_H
#define ReportTableView_H

#include <QDate>
#include <QList>
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

#include "Transaction.h"

class Month;

class ReportTableView : public QTableView
{
    Q_OBJECT

public:
    // Types
    enum HeaderType
    {
        HDR_DATE,
        HDR_INCOME,
        HDR_EXPENSE,
        HDR_NET_INCOME,
        HDR_NET_WORTH,

        HDR_CNT
    };
    
    // Functions
    explicit ReportTableView(QWidget* parent = 0);
    ~ReportTableView();
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void clear();

signals:
    void transactionFilterSelected( const Transaction::FilterType& aFilter );

private slots:
    void handleItemDoubleClicked( const QModelIndex& aIndex );

private:
    // Functions

    // Variables
    Transaction::FilterType mFilter;
    QStandardItemModel* mModel;
    QList<Month*> mMonthList;
};

#endif // ReportTableView_H
