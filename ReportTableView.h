//******************************************************************************
//
//  HEADER NAME: ReportTableView.h
//******************************************************************************

#ifndef ReportTableView_H
#define ReportTableView_H

#include <QDate>
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

#include "Transaction.h"

class ReportTableView : public QTableView
{

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

private:
    // Functions

    // Variables
    QStandardItemModel* mModel;
};

#endif // ReportTableView_H
