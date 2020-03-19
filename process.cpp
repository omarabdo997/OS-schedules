#include "process.h"

QString Process::getName() const
{
    return name;
}

void Process::setName(const QString &value)
{
    name = value;
}

QString Process::getRPG() const
{
    return RPG;
}

void Process::setRPG(const QString &value)
{
    RPG = value;
}

float Process::getBurstTime() const
{
    return burstTime;
}

void Process::setBurstTime(float value)
{
    burstTime = value;
}

float Process::getArrivalTime() const
{
    return arrivalTime;
}

void Process::setArrivalTime(float value)
{
    arrivalTime = value;
}

int Process::getPriority() const
{
    return priority;
}

void Process::setPriority(int value)
{
    priority = value;
}

Process::Process()
{

}

Process::Process(QString name)
{
    this->setName(name);
}

Process::Process(QString name, QString RPG, float burstTime, float arrivalTime, int priority)
{
    this->setName(name);
    this->setRPG(RPG);
    this->setBurstTime(burstTime);
    this->setArrivalTime(arrivalTime);
    this->setPriority(priority);
}
