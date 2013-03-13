//******************************************************************************
//
//  HEADER NAME: ReportTableView.h
//******************************************************************************

#ifndef ReportTableView_H
#define ReportTableView_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

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
    void setDateRange( QDate aStartDate, QDate aEndDate );

private:
    // Functions

    // Variables
    QDate mStartDate;
    QDate mEndDate;
    QStandardItemModel* mModel;
};

#endif // ReportTableView_H
