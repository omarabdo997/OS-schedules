#include "mainwindow.h"
#include "scheduleselect.h"
#include <QHBoxLayout>
#include "centeralwidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("OS Scheduler");
//    setMinimumSize(1020,600);
    CenteralWidget *centerwidget=new CenteralWidget(this);
    setCentralWidget(centerwidget);
    setMaximumSize(1100,600);


//    QHBoxLayout *layout=new QHBoxLayout(this);
//    layout->addWidget(scheduleselect);




}

MainWindow::~MainWindow()
{
}

