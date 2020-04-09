#ifndef CENTERALWIDGET_H
#define CENTERALWIDGET_H

#include <QWidget>
#include "processesselector.h"
#include "scheduleselect.h"
#include <QGridLayout>
#include <QScrollArea>
#include <answer.h>
#include "fcfssched.h"
#include  <PrioritySched.h>
#include "sjfsched.h"
class CenteralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CenteralWidget(QWidget *parent = nullptr);
    ~CenteralWidget();

private slots:
     void create_processess();
     void create_answer();
private:
     ScheduleSelect *scheduleselect;

     QGridLayout *layout;
     ProcessesSelector *ps;
     Answer *answer;
     QScrollArea *bar;
     QScrollArea *bar2;
     QLabel *avg_waiting_time;
     QLabel *avg_waiting_time_answer;
     QVector<SysProcess>processes;
     Scheduler *scheduler;
     int FIRST_PROCESSES_CREATION=0;
     int FIRST_PROCESSES_ANSWER=0;

};

#endif // CENTERALWIDGET_H
