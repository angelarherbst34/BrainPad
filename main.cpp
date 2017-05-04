#include "mainwindow.h"
#include <QApplication>

/**
 * Creates main window
 * @param argc the argument count
 * @param argv the argument array
 * @return the QApplication (qt)
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
