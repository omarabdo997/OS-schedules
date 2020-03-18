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
    ScheduleSelect *scheduleselect=new ScheduleSelect(this);
    QGridLayout *layout=new QGridLayout(this);
    layout->addWidget(scheduleselect,0,0);
    layout->setSpacing(50);


    connect(scheduleselect,&ScheduleSelect::input_finished,[scheduleselect,this,layout]()
    {
        ProcessesSelector *ps=new ProcessesSelector(this);

        ps->setModel(scheduleselect->getOp(),scheduleselect->getNo_p());
        QScrollArea *bar=new QScrollArea(this);
        bar->setWidget(ps);

        layout->addWidget(bar,0,1);

    });



}

CenteralWidget::~CenteralWidget()
{

}
