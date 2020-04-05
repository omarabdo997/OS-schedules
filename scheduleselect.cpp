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
#include <QMessageBox>


ScheduleSelect::ScheduleSelect(QWidget *parent) :
    QWidget(parent)
{
    //style
    QFont title("times",18,QFont::Bold,true);
    QFont radio_text("times",12);
    QFont radio_text_secondry("times",10);
    QPalette title_style;
    title_style.setColor(QPalette::WindowText,Qt::blue);
    setMinimumSize(200,250);

    //schedular_select label
    QLabel *schedular_select=new QLabel("Scheduler Select",this);
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
    layout_sjf->setContentsMargins(10,0,70,0);

            //priority
    QHBoxLayout *layout_priority=new QHBoxLayout;
    layout_priority->addWidget(priority_preemptive);
    layout_priority->addWidget(priority_non_preemptive);
    layout_priority->setContentsMargins(10,0,70,0);

    //button layout
    QHBoxLayout *button_layout=new QHBoxLayout;
    submit->setMinimumWidth(50);
    button_layout->addSpacing(120);
    button_layout->addWidget(submit);
    button_layout->addSpacing(120);

    //main vertical layout
    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->addWidget(schedular_select);
//    layout->setMargin(0);
    layout->addSpacing(10);
    layout->addWidget(fcfs);
    layout->addWidget(round_robin);
    layout->addWidget(sjf);
    layout->addLayout(layout_sjf);
    layout->addWidget(priority);
    layout->addLayout(layout_priority);
    layout->addSpacing(30);
    layout->addLayout(form_layout);
    layout->addSpacing(10);
    layout->addLayout(button_layout);

    layout->setContentsMargins(30,0,0,0);


    //signals and slots
        //submit button
//    connect(submit,SIGNAL(clicked()),this,SLOT(emit_input_finished()));

    connect(submit,&QPushButton::clicked,[=](){
        if(fcfs->isChecked())
        {
            setOp(0);
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
        if(no_p>0 && op>=0 && op<=5)
            emit input_finished();
        else
        {
            QMessageBox::critical(this,"Wrong input","Please select a schedule and enter a valid process number");
        }
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
        if(sjf->isChecked())
        {
            sjf_preemptive->setChecked(true);
        }

    });
    connect(priority,&QRadioButton::toggled,[priority_options,priority_preemptive,priority_non_preemptive,priority]()
    {
        priority_preemptive->setEnabled(!priority_preemptive->isEnabled());
        priority_non_preemptive->setEnabled(!priority_non_preemptive->isEnabled());
        priority_options->setExclusive(false);
        priority_preemptive->setChecked(false);
        priority_non_preemptive->setChecked(false);
        priority_options->setExclusive(true);
        if(priority->isChecked())
        {
            priority_preemptive->setChecked(true);
        }

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



