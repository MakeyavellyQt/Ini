#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("makeyavelly");
    QCoreApplication::setApplicationName("TestIni");

    MainWindow w;
    w.show();

    return a.exec();
}
