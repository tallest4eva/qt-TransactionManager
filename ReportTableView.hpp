//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: ReportTableView.h
//******************************************************************************

#ifndef ReportTableView_HPP
#define ReportTableView_HPP

#include <QDate>
#include <QList>
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

#include "Month.hpp"
#include "Transaction.hpp"

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
        HDR_NET_TRANSFERS,
        HDR_NET_WORTH,

        HDR_CNT
    };

    // Functions
public:
    explicit ReportTableView(QWidget* parent = 0);
    ~ReportTableView();
    void setMonthInterval( int aMonthInterval );
    void setTransactionFilter( const Transaction::FilterType& aFilter );
    void clear();

signals:
    void transactionFilterSelected( const Transaction::FilterType& aFilter );

private slots:
    void handleItemPressed( const QModelIndex& aIndex );
    void handleItemDoubleClicked( const QModelIndex& aIndex );

private:
    // Functions

    // Variables
    Transaction::FilterType mFilter;
    QStandardItemModel* mModel;
    QList<Month::DateIntervalType> mRowIntervalList;
    int mMonthInterval;
};

#endif // ReportTableView_HPP
