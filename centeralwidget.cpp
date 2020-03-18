#include "centeralwidget.h"
#include "scheduleselect.h"
#include "processesselector.h"
#include <QGridLayout>
#include "answer.h"


CenteralWidget::CenteralWidget(QWidget *parent) :
    QWidget(parent)

{
    ScheduleSelect *scheduleselect=new ScheduleSelect(this);
    ProcessesSelector *ps=new ProcessesSelector(this);
    Answer *ans=new Answer(this);
    QGridLayout *layout=new QGridLayout(this);
    layout->addWidget(scheduleselect,0,0);
    layout->setSpacing(200);
    layout->addWidget(ps,0,1);
    layout->addWidget(ans,1,0,1,2);

}

CenteralWidget::~CenteralWidget()
{

}
