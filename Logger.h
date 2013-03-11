//******************************************************************************
//
//  HEADER NAME: Logger.h
//******************************************************************************

#ifndef LOGGER_H
#define LOGGER_H

#include <QStringList>

class Logger
{
public:
    // Types
    enum LogType
    {
        LOG_INFO,
        LOG_WARNING,
        LOG_ERROR,

        LOG_ENTRY_CNT
    };

    // Functions
    static void logString
        (
        const QString& aString,
        LogType aLogType = LOG_INFO
        );
    static void clearLog();

    // Variable
    static QStringList sLogList;
};

#endif // LOGGER_H
