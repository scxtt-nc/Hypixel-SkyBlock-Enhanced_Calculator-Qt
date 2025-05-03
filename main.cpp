#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Enhanced Item Cost Calculator"); // Set window title in English
    w.show();
    return a.exec();
}
