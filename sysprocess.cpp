#include "sysprocess.h"

QString SysProcess::getName() const
{
    return name;
}

void SysProcess::setName(const QString &value)
{
    name = value;
}

QString SysProcess::getRPG() const
{
    return RPG;
}

void SysProcess::setRPG(const QString &value)
{
    RPG = value;
}

float SysProcess::getBurstTime() const
{
    return burstTime;
}

void SysProcess::setBurstTime(float value)
{
    burstTime = value;
}

float SysProcess::getArrivalTime() const
{
    return arrivalTime;
}

void SysProcess::setArrivalTime(float value)
{
    arrivalTime = value;
}

int SysProcess::getPriority() const
{
    return priority;
}

void SysProcess::setPriority(int value)
{
    priority = value;
}

SysProcess::SysProcess()
{

}

SysProcess::SysProcess(QString name)
{
    this->setName(name);
}

SysProcess::SysProcess(QString name, QString RPG, float burstTime, float arrivalTime, int priority)
{
    this->setName(name);
    this->setRPG(RPG);
    this->setBurstTime(burstTime);
    this->setArrivalTime(arrivalTime);
    this->setPriority(priority);
}
