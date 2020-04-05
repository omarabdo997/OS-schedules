#ifndef PRIORITYSCHED_H
#define PRIORITYSCHED_H
#include "scheduler.h"
#include <QtAlgorithms>


class prioritysched : public Scheduler
{
private:

bool is_Preemptive;
float qtime;

static bool cmp(const SysProcess &p1 , const SysProcess &p2);

public:

prioritysched();
prioritysched(QVector<SysProcess> processes,bool is_Preemptive);
prioritysched(QVector<SysProcess> processes,bool is_Preemptive,float qtime);
void set_is_Preemptive(bool value);
bool get_is_preemptive();
void set_qtime(float value);
float get_qtime();

void schedule() ;
float waitingTime();



};

#endif // PRIORITYSCHED_H
