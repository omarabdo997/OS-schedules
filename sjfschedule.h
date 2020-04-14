#ifndef SJFSCHEDULE_H
#define SJFSCHEDULE_H
#include "scheduler.h"

class SJFSchedule:public Scheduler
{
private:
    bool isPreemtive ;
public:
    SJFSchedule(bool isPreemtive , QVector<SysProcess> processes);
    static bool cmp(const SysProcess &p1,const SysProcess &p2);
    bool getIsPreemtive() const;
    void setIsPreemtive(bool value);
    void schedule() ;

    float waitingTime();
};

#endif // SJFSCHEDULE_H
