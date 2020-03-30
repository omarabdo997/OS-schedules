#ifndef FCFSSCHED_H
#define FCFSSCHED_H
#include "scheduler.h"
#include <QtAlgorithms>
class FCFSSched : public Scheduler
{
private:
    static bool cmp(const SysProcess &p1 , const SysProcess &p2);
public:
    FCFSSched();
    void schedule();
    float waitingTime();
    FCFSSched(QVector<SysProcess> processes);
};

#endif // FCFSSCHED_H
