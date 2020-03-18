#include "mainwindow.h"
#include "scheduleselect.h"
#include <QApplication>
#include "processesselector.h"
#include "answer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
