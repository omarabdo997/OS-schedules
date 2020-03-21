#include "scheduler.h"

void Scheduler::setProcesses(const QVector<SysProcess> &value)
{
    processes = value;
}

QVector<Interval> Scheduler::getIntervals() const
{
    return intervals;
}

Scheduler::Scheduler()
{

}
