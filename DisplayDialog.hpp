//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: DisplayDialog.h
//******************************************************************************

#ifndef DisplayDialog_H
#define DisplayDialog_H

#include <QObject>
#include <QDialog>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>

class DisplayDialog : public QDialog
{
    Q_OBJECT

public:
    // Functions
    explicit DisplayDialog(QWidget* parent = 0);
    ~DisplayDialog();
    void setDisplay
        (
        const QStringList& aStringList,
        const QString& aEmptyDisplayString = QString( "No content to display" )
        );

private slots:
    void handleDoneButton();

private:
    // Functions

    // Variables
    QScrollArea mScrollable;
    QTextEdit mLabel;
    QPushButton mButton;
};

#endif // DisplayDialog_H
