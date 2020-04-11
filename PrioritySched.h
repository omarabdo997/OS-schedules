#ifndef PRIORITYSCHED_H
#define PRIORITYSCHED_H
#include "scheduler.h"
#include <QtAlgorithms>
class prioritysched : public Scheduler
{
private:

bool is_Preemptive;
static bool cmp(const SysProcess &p1 , const SysProcess &p2);
static bool pcmp(const SysProcess &p1,const SysProcess &p2);
static bool arriv_cmp(QVector<SysProcess>&processes);
QVector<float>Burst_time_copy_preemptive;
QVector<float> get_burst_copy(QVector<SysProcess> &processes);
public:

prioritysched();
prioritysched(QVector<SysProcess> processes,bool is_Preemptive);
void set_is_Preemptive(bool value);
bool get_is_preemptive();

void schedule() ;
float waitingTime();

};

#endif // PRIORITYSCHED_H
