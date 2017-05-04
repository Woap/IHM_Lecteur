/**
 * \file main.cpp
 * \author CHIBOUT Yanis et IBIS Ibrahim
 *
 * Aud.io lecteur audio pour mpv
 *
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
