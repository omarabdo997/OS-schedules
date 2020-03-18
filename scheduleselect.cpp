#include "scheduleselect.h"
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QFont>
#include <QPalette>
#include <QHBoxLayout>

ScheduleSelect::ScheduleSelect(QWidget *parent) :
    QWidget(parent)
{
    //style
    QFont title("times",14,QFont::Bold,true);
    QFont radio_text("times",12);
    QFont radio_text_secondry("times",10);
    QPalette title_style;
    title_style.setColor(QPalette::WindowText,Qt::blue);
    setMinimumSize(250,250);

    //schedular_select label
    QLabel *schedular_select=new QLabel("Schedular select",this);
    schedular_select->setFont(title);
    schedular_select->setPalette(title_style);

    //radio buttons
    QRadioButton *fcfs=new QRadioButton("FCFS",this);
    fcfs->setFont(radio_text);
    QRadioButton *round_robin=new QRadioButton("Round Robin",this);
    round_robin->setFont(radio_text);
    QRadioButton *sjf=new QRadioButton("SJF",this);
    sjf->setFont(radio_text);
    QRadioButton *sjf_preemptive=new QRadioButton("Preemptive",this);
    sjf_preemptive->setFont(radio_text_secondry);
    QRadioButton *sjf_non_preemptive=new QRadioButton("Non Preemptive",this);
    sjf_non_preemptive->setFont(radio_text_secondry);
    QRadioButton *priority=new QRadioButton("Priority",this);
    priority->setFont(radio_text);
    QRadioButton *priority_preemptive=new QRadioButton("Preemptive",this);
    priority_preemptive->setFont(radio_text_secondry);
    QRadioButton *priority_non_preemptive=new QRadioButton("Non Preemptive",this);
    priority_non_preemptive->setFont(radio_text_secondry);


    //submit button
    QPushButton *submit=new QPushButton("Submit",this);

    //button grouping main radio buttons
    QButtonGroup *scheduals=new QButtonGroup(this);
    scheduals->addButton(fcfs);
    scheduals->addButton(round_robin);
    scheduals->addButton(sjf);
    scheduals->addButton(priority);

    //button grouping secondry radio buttons
        //sjf
    QButtonGroup *sjf_options=new QButtonGroup(this);
    sjf_options->addButton(sjf_preemptive);
    sjf_options->addButton(sjf_non_preemptive);
        //priority
    QButtonGroup *priority_options=new QButtonGroup(this);
    priority_options->addButton(priority_preemptive);
    priority_options->addButton(priority_non_preemptive);

    //layouts

        //secondry horizotnal layout
            //sjf
    QHBoxLayout *layout_sjf=new QHBoxLayout;
    layout_sjf->addWidget(sjf_preemptive);
    layout_sjf->addWidget(sjf_non_preemptive);
    layout_sjf->setContentsMargins(10,0,0,0);
            //priority
    QHBoxLayout *layout_priority=new QHBoxLayout;
    layout_priority->addWidget(priority_preemptive);
    layout_priority->addWidget(priority_non_preemptive);
    layout_priority->setContentsMargins(10,0,0,0);
    //main vertical layout
    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(schedular_select);
//    layout->setMargin(0);
//    layout->addSpacing(0);
    layout->addWidget(fcfs);
    layout->addWidget(round_robin);
    layout->addWidget(sjf);
    layout->addLayout(layout_sjf);
    layout->addWidget(priority);
    layout->addLayout(layout_priority);
    layout->addWidget(submit);
    layout->setContentsMargins(30,0,0,0);

















}

ScheduleSelect::~ScheduleSelect()
{

}
