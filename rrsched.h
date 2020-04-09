#ifndef RRSCHED_H
#define RRSCHED_H
#include "scheduler.h"

class RRSched : public Scheduler
{
private:
    float quantumTime;
public:
    RRSched();
    void schedule();
    float waitingTime();
    RRSched(QVector<SysProcess> processes,float qtime);
    float getQuantumTime() const;
    void setQuantumTime(float value);
};

#endif // RRSCHED_H
