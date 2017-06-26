//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: DisplayLabel.h
//******************************************************************************

#ifndef DisplayLabel_H
#define DisplayLabel_H

#include <QDate>
#include <QLabel>
#include <QString>
#include <QTimer>
#include <QWidget>

class DisplayLabel : public QLabel
{
    Q_OBJECT
public:
    DisplayLabel();
    virtual void mouseDoubleClickEvent( QMouseEvent* aEvent );
    virtual void mousePressEvent( QMouseEvent* aEvent );
    virtual void mouseReleaseEvent( QMouseEvent* aEvent );
    QDate getStartDate() const { return mStartDate; }
    QDate getEndDate() const { return mEndDate; }
    void  setDates( const QDate& aStartDate, const QDate& aEndDate );
    QString getString() const { return mString; }
    void  setString( const QString& aString ){ mString = aString; }
signals:
    void clicked();
private:
    QTimer mPressTimer;
    QTimer mReleaseTimer;
    QDate mStartDate;
    QDate mEndDate;
    QString mString;
};

#endif // DisplayLabel_H
