#include "sysprocess.h"

QString SysProcess::getName() const
{
    return name;
}

void SysProcess::setName(const QString &value)
{
    name = value;
}

QVector<int> SysProcess::getRGB() const
{
    return RGB;
}

void SysProcess::setRGB(const QVector<int> &value)
{
    RGB = value;
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
void SysProcess::setStatus(QString value)
{
    status = value;
}
QString SysProcess::getStatus()
{
    return status;
}
SysProcess::SysProcess()
{

}

SysProcess::SysProcess(QString name)
{
    this->setName(name);
}

SysProcess::SysProcess(QString name, QVector<int> RGB, float burstTime, float arrivalTime, int priority)
{
    this->setName(name);
    this->setRGB(RGB);
    this->setBurstTime(burstTime);
    this->setArrivalTime(arrivalTime);
    this->setPriority(priority);
}
