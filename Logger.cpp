//******************************************************************************
// Author: Obi Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: Logger.cpp
//******************************************************************************

#include <QString>
#include <QStringList>
#include <QDebug>

#include "Logger.h"
#include "Category.h"

// Static variables
QStringList Logger::sLogList;

//----------------------------------------------------------------------------
// log String
//----------------------------------------------------------------------------
void Logger::logString
    (
    const QString& aString,
    LogType aLogType
    )
{
    // log string
    QString str;
    switch( aLogType )
    {
    case LOG_INFO:
        str = "Info   : ";
        break;
    case LOG_WARNING:
        str = "Warning: ";
        break;
    case LOG_ERROR:
        str = "Error  : ";
        break;
    }
    str.append( aString );
    sLogList.push_back( str );
    //qDebug() << str;
} // Logger::logString

//----------------------------------------------------------------------------
// clear String
//----------------------------------------------------------------------------
void Logger::clearLog()
{
    sLogList.clear();
} // Logger::clearLog
