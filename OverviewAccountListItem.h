//******************************************************************************
//
//  HEADER NAME: OverviewAccountListItem.h
//******************************************************************************

#ifndef OverviewAccountListItem_H
#define OverviewAccountListItem_H

#include <QWidget>
#include <QFrame>
#include <QLabel>

#include "Account.h"

class OverviewAccountListItem : public QFrame
{

public:
    // Functions
    explicit OverviewAccountListItem(QWidget* parent = 0);
    ~OverviewAccountListItem();
    void setAccount( Account* aAccount );

private:
    // Functions

    // Variables
    Account* mAccount;
    QLabel mNameLabel;
    QLabel mBalanceLabel;
    QLabel mStatusLabel;
    QLabel mDateLabel;
};

#endif // OverviewAccountListItem_H
