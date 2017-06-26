//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: TripleRadioButton.h
//******************************************************************************

#ifndef TripleRadioButton_HPP
#define TripleRadioButton_HPP

#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QString>

#include "Transaction.hpp"

class TripleRadioButton : public QWidget
{
    Q_OBJECT

public:
    // Functions
    TripleRadioButton( const QString& aLabelText, QWidget* aParent = 0);
    ~TripleRadioButton();
    void setMatchType( Transaction::MatchType aMatchType );
    Transaction::MatchType getMatchType() const;

signals:
    void buttonClicked();

private:

    // Variables
    QLabel mNameLabel;
    QRadioButton mMatchButton;
    QRadioButton mDoNotMatchButton;
    QRadioButton mExcludeButton;
};

#endif // TripleRadioButton_HPP
