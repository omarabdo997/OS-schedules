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
#include <QLineEdit>
#include <QFormLayout>
#include <QString>
#include <QDebug>

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
    sjf_preemptive->setEnabled(false);
    sjf_preemptive->setFont(radio_text_secondry);
    QRadioButton *sjf_non_preemptive=new QRadioButton("Non Preemptive",this);
    sjf_non_preemptive->setEnabled(false);
    sjf_non_preemptive->setFont(radio_text_secondry);

    QRadioButton *priority=new QRadioButton("Priority",this);
    priority->setFont(radio_text);
    QRadioButton *priority_preemptive=new QRadioButton("Preemptive",this);
    priority_preemptive->setEnabled(false);
    priority_preemptive->setFont(radio_text_secondry);
    QRadioButton *priority_non_preemptive=new QRadioButton("Non Preemptive",this);
    priority_non_preemptive->setEnabled(false);
    priority_non_preemptive->setFont(radio_text_secondry);




    //no of processes
    QLineEdit *number_processes=new QLineEdit(this);

    QLabel *number_label=new QLabel("Number of processes",this);
    number_label->setFont(radio_text);

    //submit button
    QPushButton *submit=new QPushButton("Submit",this);
    connect(submit,&QPushButton::clicked,[=](){
        if(fcfs->isChecked())
        {
            qDebug()<<"Hello";
        }
        else if(round_robin->isChecked())
        {
            setOp(1);
        }
        else if(sjf->isChecked())
        {
            if(sjf_non_preemptive->isChecked())
            {
                setOp(3);
            }
            else
            {
                setOp(2);
            }
        }
        else if(priority->isChecked())
        {
            if(priority_non_preemptive->isChecked())
            {
                setOp(5);
            }
            else
            {
                setOp(4);
            }
        }
        setNo_p(number_processes->text().toInt());
        qDebug()<<getOp();
        qDebug()<<getNo_p();
    });


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
    //Form layout
    QFormLayout *form_layout=new QFormLayout;
    form_layout->addRow(number_label,number_processes);
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
    layout->addSpacing(10);
    layout->addWidget(fcfs);
    layout->addWidget(round_robin);
    layout->addWidget(sjf);
    layout->addLayout(layout_sjf);
    layout->addWidget(priority);
    layout->addLayout(layout_priority);
    layout->addLayout(form_layout);
    layout->addWidget(submit);

    layout->setContentsMargins(30,0,0,0);


    //signals and slots
        //submit button
    connect(submit,&QPushButton::clicked,[=](){
        if(fcfs->isChecked())
        {
            qDebug()<<"Hello";
        }
        else if(round_robin->isChecked())
        {
            setOp(1);
        }
        else if(sjf->isChecked())
        {
            if(sjf_non_preemptive->isChecked())
            {
                setOp(3);
            }
            else
            {
                setOp(2);
            }
        }
        else if(priority->isChecked())
        {
            if(priority_non_preemptive->isChecked())
            {
                setOp(5);
            }
            else
            {
                setOp(4);
            }
        }
        setNo_p(number_processes->text().toInt());
        qDebug()<<getOp();
        qDebug()<<getNo_p();
    });
        //activate and deactivate radio buttons
    connect(sjf,&QRadioButton::toggled,[=]()
    {
        sjf_preemptive->setEnabled(!sjf_preemptive->isEnabled());
        sjf_non_preemptive->setEnabled(!sjf_non_preemptive->isEnabled());
        sjf_options->setExclusive(false);
        sjf_preemptive->setChecked(false);
        sjf_non_preemptive->setChecked(false);
        sjf_options->setExclusive(true);

    });
    connect(priority,&QRadioButton::toggled,[priority_options,priority_preemptive,priority_non_preemptive]()
    {
        priority_preemptive->setEnabled(!priority_preemptive->isEnabled());
        priority_non_preemptive->setEnabled(!priority_non_preemptive->isEnabled());
        priority_options->setExclusive(false);
        priority_preemptive->setChecked(false);
        priority_non_preemptive->setChecked(false);
        priority_options->setExclusive(true);

    });














}

ScheduleSelect::~ScheduleSelect()
{

}

int ScheduleSelect::getOp() const
{
    return op;
}

int ScheduleSelect::getNo_p() const
{
    return no_p;
}

void ScheduleSelect::setOp(int value)
{
    op = value;
}

void ScheduleSelect::setNo_p(int value)
{
    no_p = value;
}
