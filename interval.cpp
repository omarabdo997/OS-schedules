#include "interval.h"

float Interval::getFrom() const
{
    return from;
}

void Interval::setFrom(float value)
{
    from = value;
}

float Interval::getTo() const
{
    return to;
}

void Interval::setTo(float value)
{
    to = value;
}

SysProcess Interval::getProcess() const
{
    return process;
}

void Interval::setProcess(const SysProcess &value)
{
    process = value;
}

Interval::Interval()
{

}

Interval::Interval(float from, float to)
{
    this->setFrom(from);
    this->setTo(to);
}

Interval::Interval(float from, float to, SysProcess process)
{
    this->setFrom(from);
    this->setTo(to);
    this->setProcess(process);
}
