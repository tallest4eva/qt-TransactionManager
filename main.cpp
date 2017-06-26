//******************************************************************************
// Author: Obinna Modum (tallest4eva)
// Disclaimer: This Software is provides "As Is". Use at your own risk.
//
//  FILE NAME: main.cpp
//******************************************************************************

#include "TransactionManager.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TransactionManager mgr;
    mgr.show();

    return app.exec();
}
