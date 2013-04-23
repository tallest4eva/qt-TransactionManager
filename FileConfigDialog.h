//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: FileConfigDialog.h
//******************************************************************************

#ifndef FileConfigDialog_H
#define FileConfigDialog_H

#include <QObject>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QGroupBox>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

#include "Parser.h"

class FileConfigDialog : public QDialog
{
    Q_OBJECT

public:
    // Types
    enum ButtonType
    {
        CANCEL_BUTTON,
        RESTORE_BUTTON,
        OK_BUTTON,

        BUTTON_CNT
    };
    
    // Functions
    explicit FileConfigDialog(QWidget* parent = 0);
    ~FileConfigDialog();

private slots:
    void handlePresetSelected();
    void handleTransactionClicked( bool aChecked );
    void handleCancelButton();
    void handleDoneButton();

private:
    // Functions
    void updateData();
    
    // Variables
    int mSelected;
    Parser::ConfigType mConfig;
    QGroupBox mConfigBox;
    QList<QRadioButton*> mRadioButtonList;

    QGroupBox mFileBox;
    QComboBox mFileSeperator;
    QComboBox mDateFormat;

    QGroupBox mAccountBox;
    QCheckBox mAccountCheckBox;
    QLineEdit mAccountDescriptor;
    QComboBox mAccountName;
    QComboBox mAccountStatus;
    QComboBox mAccountState;
    QComboBox mAccountAltName;

    QGroupBox mTransactionBox;
    QCheckBox mTransactionCheckBox;
    QLineEdit mTransactionDescriptor;
    QComboBox mTransactionDate;
    QComboBox mTransactionName;
    QComboBox mTransactionDescription;
    QComboBox mTransactionType;
    QComboBox mTransactionAmount;
    QComboBox mTransactionBalance;
    QComboBox mTransactionCategory;
    QComboBox mTransactionLabels;
    
    QPushButton mCancelButton;
    QPushButton mDoneButton;
};

#endif // FileConfigDialog_H
