#include "rrsched.h"

float RRSched::getQuantumTime() const
{
    return quantumTime;
}

void RRSched::setQuantumTime(float value)
{
    quantumTime = value;
}

RRSched::RRSched()
{

}

void RRSched::schedule()
{

}

float RRSched::waitingTime()
{

}

RRSched::RRSched(QVector<SysProcess> processes, float qtime)
{
    this->setProcesses(processes);
    this->setQuantumTime(qtime);
}
