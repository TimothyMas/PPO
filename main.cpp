#include "mainppo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPPO w;
    w.show();
    return a.exec();
}
