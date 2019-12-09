#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", "tgtsml");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
