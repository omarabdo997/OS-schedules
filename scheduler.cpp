#include "scheduler.h"

void Scheduler::setProcesses(const QVector<SysProcess> &value)
{
    processes = value;
}

void Scheduler::setIntervals(const QVector<Interval> &value)
{
    intervals = value;
}

QVector<Interval> Scheduler::getIntervals() const
{
    return intervals;
}

Scheduler::Scheduler()
{

}
