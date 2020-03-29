#ifndef FCFSSCHED_H
#define FCFSSCHED_H
#include "scheduler.h"

class FCFSSched : public Scheduler
{
private:
    bool cmp(SysProcess p1 , SysProcess p2);
public:
    FCFSSched();
    void schedule();
    float waitingTime();
    FCFSSched(vector<SysProcess> processes);
};

#endif // FCFSSCHED_H
