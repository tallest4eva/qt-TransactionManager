//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: FileConfigDialog.h
//******************************************************************************

#ifndef FileConfigDialog_H
#define FileConfigDialog_H

#include <QObject>
#include <QComboBox>
#include <QDialog>
#include <QGroupBox>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

class TextEdit : public QTextEdit
{
public:
    TextEdit()
    {
        setTabChangesFocus(true);
        setWordWrapMode(QTextOption::NoWrap);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        QFontMetrics fm(font());
        setFixedHeight(fm.height() + 6);
    }
    void keyPressEvent( QKeyEvent* aEvent )
    {
        if( aEvent->key() == Qt::Key_Return || aEvent->key() == Qt::Key_Enter ){ aEvent->accept(); }
        else{ QTextEdit::keyPressEvent(aEvent); }
    }
};

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
    void updateData();
    
    // Variables
    QGroupBox mFileBox;
    QGroupBox mAccountBox;
    QGroupBox mTransactionBox;
    TextEdit mTransactionDescriptor;
    TextEdit mAccountDescriptor;
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
