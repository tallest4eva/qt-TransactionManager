//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: OverviewAccountListItem.h
//******************************************************************************

#ifndef OverviewAccountListItem_HPP
#define OverviewAccountListItem_HPP

#include <QWidget>
#include <QFrame>
#include <QLabel>

#include "Account.hpp"

class OverviewAccountListItem : public QFrame
{

public:
    // Functions
    explicit OverviewAccountListItem(QWidget* parent = 0);
    ~OverviewAccountListItem();
    void setAccount( Account* aAccount );
    void setSelected( bool aSelected );
    Account* getAccount() const { return mAccount; }

private:
    // Functions
    void updateLabelColors();

    // Variables
    Account* mAccount;
    QLabel mNameLabel;
    QLabel mBalanceLabel;
    QLabel mTransactionLabel;
    QLabel mDateLabel;
    bool mSelected;
};

#endif // OverviewAccountListItem_HPP
