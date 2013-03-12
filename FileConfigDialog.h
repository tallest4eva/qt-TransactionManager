//******************************************************************************
//
//  HEADER NAME: FileConfigDialog.h
//******************************************************************************

#ifndef FileConfigDialog_H
#define FileConfigDialog_H

#include <QObject>
#include <QComboBox>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

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
    void handleCancelButton();
    void handleRestoreButton();
    void handleDoneButton();

private:
    // Functions
    void updateComboBoxes();
    
    // Variables
    QGroupBox mFileBox;
    QGroupBox mAccountBox;
    QGroupBox mTransactionBox;
    QComboBox mTransactionDate;
    QComboBox mTransactionName;
    QComboBox mTransactionDescription;
    QComboBox mTransactionType;
    QComboBox mTransactionAmount;
    QComboBox mTransactionBalance;
    QComboBox mTransactionCategory;
    QComboBox mTransactionLabels;
    QComboBox mFileSeperator;
    QComboBox mDateFormat;
    QComboBox mAccountName;
    QComboBox mAccountStatus;
    QComboBox mAccountState;
    QComboBox mAccountAltName;
    
    QPushButton mCancelButton;
    QPushButton mRestoreButton;
    QPushButton mDoneButton;
};

#endif // FileConfigDialog_H
