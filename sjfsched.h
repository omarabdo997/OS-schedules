#ifndef SJFSCHED_H
#define SJFSCHED_H
#include "scheduler.h"
#include <QtAlgorithms>

class SJFSched : public Scheduler
{

private :
    bool isPreemtive ;
    static bool cmp(const SysProcess &p1 , const SysProcess &p2);

public:

    SJFSched();
    SJFSched(bool isPreemtive , QVector<SysProcess> processes );

    void set_isPreemptive(bool value);
    bool get_isPreemptive();

    void schedule() ;

   // float waitingTime();


};

#endif // SJFSCHED_H


