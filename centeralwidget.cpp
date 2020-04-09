#include "centeralwidget.h"
#include "scheduleselect.h"
#include "processesselector.h"
#include <QGridLayout>
#include "answer.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>


CenteralWidget::CenteralWidget(QWidget *parent) :
    QWidget(parent)

{
    //starting size
    setMinimumSize(500,400);

    //starting widget
    scheduleselect=new ScheduleSelect(this);

    //layout
    layout=new QGridLayout(this);
    layout->addWidget(scheduleselect,0,0);
    layout->setHorizontalSpacing(50);

    //connection
    connect(scheduleselect,SIGNAL(input_finished()),this,SLOT(create_processess()));
}

CenteralWidget::~CenteralWidget()
{
    delete scheduler;
}

void CenteralWidget::create_processess()
{
    //change width
    setMinimumWidth(1020);

    if(FIRST_PROCESSES_CREATION!=0)
    {
        delete  ps;
        delete bar;
    }

    //create process selector widget
    ps=new ProcessesSelector(this);
    ps->setModel(scheduleselect->getOp(),scheduleselect->getNo_p());



    //create vertical scroll bar and set it to process selector widget
    bar=new QScrollArea(this);
    bar->setWidget(ps);

    //vertical bar style
    bar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    bar->setFrameShape(QFrame::NoFrame);

    //vertical bar with process selector layout
    layout->addWidget(bar,0,1);

    FIRST_PROCESSES_CREATION=1;

    //connecting to result on submiting
    connect(ps,SIGNAL(input_finished()),this,SLOT(create_answer()));

}

void CenteralWidget::create_answer()
{

    if(FIRST_PROCESSES_ANSWER!=0)
    {
        delete answer;
        delete bar2;
        delete avg_waiting_time;
        delete avg_waiting_time_answer;
        delete scheduler;
    }

    //changing size with answer appearence
    setMinimumHeight(600);

    //get submited processes
    processes=ps->getProcesses();
    qDebug()<<"processes"<<processes.size();

    //dynamic bynding to scheduler class
    switch (scheduleselect->getOp())
    {
    case(0):
        scheduler=new FCFSSched(processes);
        break;
    case(1):
        scheduler=new RRSched(processes,ps->getBurst_time());
        break;
    case(2):
        scheduler=new SJFSched(1,processes);
        break;
    case(3):
        scheduler=new SJFSched(0,processes);
        break;
    case(4):
        scheduler=new prioritysched(processes,1);
        break;
    case(5):
        scheduler=new prioritysched(processes,0);
        break;

    }

    //call schedule
    scheduler->schedule();

    //create answer widget and send needed data
    answer=new Answer(this);
    answer->set_model(scheduler->getIntervals());

    //create horizontal scroll bar and set it to answer widget
    bar2=new QScrollArea(this);
    bar2->setWidget(answer);

    //horizontal scroll bar style
    bar2->setFrameShape(QFrame::NoFrame);
    bar2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //horizontal scroll bar and answer widget layout
    layout->addWidget(bar2,2,0,1,2);

    //waiting time font and color
    QColor veryDarkGrey(47,47,47);
    QColor veryDarkGreen(15,42,15);
    QFont waiting_time_label("times",18,QFont::Bold);
    QPalette waiting_time_palette;
    waiting_time_palette.setColor(QPalette::WindowText,veryDarkGrey);
    QPalette waiting_time_answer_palette;
    waiting_time_answer_palette.setColor(QPalette::WindowText,veryDarkGreen);

    //avg waiting time label and answer creation
    avg_waiting_time=new QLabel("Average Waiting Time: ",this);
    avg_waiting_time_answer=new QLabel(QString::number(scheduler->waitingTime()),this);

    //avg waiting time label styling
    avg_waiting_time->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
    avg_waiting_time->setFont(waiting_time_label);
    avg_waiting_time->setPalette(waiting_time_palette);

    //avg waiting time answer styling
    avg_waiting_time_answer->setFont(waiting_time_label);
    avg_waiting_time_answer->setPalette(waiting_time_answer_palette);


    //avg waiting time label and answer laying out
    QHBoxLayout *avg_waiting_time_layout=new QHBoxLayout;
    avg_waiting_time_layout->addWidget(avg_waiting_time);
    avg_waiting_time_layout->setContentsMargins(30,0,0,0);
    layout->addLayout(avg_waiting_time_layout,1,0);
    layout->addWidget(avg_waiting_time_answer,1,1);



    FIRST_PROCESSES_ANSWER=1;

}
