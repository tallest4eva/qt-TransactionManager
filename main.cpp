//******************************************************************************
//
//  HEADER NAME: main.cpp
//******************************************************************************

#include "transactionmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransactionManager w;
    w.show();
    
    return a.exec();
}
