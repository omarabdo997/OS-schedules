#ifndef CENTERALWIDGET_H
#define CENTERALWIDGET_H

#include <QWidget>
#include "processesselector.h"
#include "scheduleselect.h"
#include <QGridLayout>
#include <QScrollArea>


class CenteralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CenteralWidget(QWidget *parent = nullptr);
    ~CenteralWidget();

private slots:
     void create_processess();
private:
     ScheduleSelect *scheduleselect;

     QGridLayout *layout;
     ProcessesSelector *ps;
     QScrollArea *bar;
     int FIRST_PROCESSES_CREATION;

};

#endif // CENTERALWIDGET_H
