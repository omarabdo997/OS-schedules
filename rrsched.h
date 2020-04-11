#ifndef RRSCHED_H
#define RRSCHED_H
#include "scheduler.h"
#include <QQueue>
#include <QtAlgorithms>

class RRSched : public Scheduler
{
private:
    float quantumTime;
    static bool cmp(const SysProcess &p1 , const SysProcess &p2);
public:
    RRSched();
    void schedule();
    float waitingTime();
    RRSched(QVector<SysProcess> processes,float qtime);
    float getQuantumTime() const;
    void setQuantumTime(float value);
};

#endif // RRSCHED_H
