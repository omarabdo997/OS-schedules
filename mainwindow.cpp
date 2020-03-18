#include "mainwindow.h"
#include "scheduleselect.h"
#include <QHBoxLayout>
#include "centeralwidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("OS Scheduler");
    setMinimumSize(800,400);
    CenteralWidget *centerwidget=new CenteralWidget(this);
    setCentralWidget(centerwidget);


//    QHBoxLayout *layout=new QHBoxLayout(this);
//    layout->addWidget(scheduleselect);




}

MainWindow::~MainWindow()
{
}

