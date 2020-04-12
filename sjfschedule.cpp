#include "sjfschedule.h"

bool SJFSchedule::getIsPreemtive() const
{
    return isPreemtive;
}

void SJFSchedule::setIsPreemtive(bool value)
{
    isPreemtive = value;
}

void SJFSchedule::schedule()
{
    if(isPreemtive)
    {

    }
    else
    {

    }
}

float SJFSchedule::waitingTime()
{

}

SJFSchedule::SJFSchedule(bool isPreemtive, QVector<SysProcess> processes)
{
    this->setIsPreemtive(isPreemtive);
    this->setProcesses(processes);

}

