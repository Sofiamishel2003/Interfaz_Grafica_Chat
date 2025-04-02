#include "mainwindow.h"
#include <QApplication>
extern "C" {
    #include "client.h"
    }
int main(int argc, char *argv[])
{
    hello_from_c();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
