#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <QVector>
#include "interval.h"
#include "sysprocess.h"

class Scheduler
{
private:
    QVector<SysProcess> processes;
    QVector<Interval> intervals;
public:
    Scheduler();
    void setProcesses(const QVector<SysProcess> &value);
    QVector<Interval> getIntervals() const;

    virtual void schedule() = 0;
    virtual float waitingTime() = 0;
};

#endif // SCHEDULER_H
