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

Process Interval::getProcess() const
{
    return process;
}

void Interval::setProcess(const Process &value)
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

Interval::Interval(float from, float to, Process process)
{
    this->setFrom(from);
    this->setTo(to);
    this->setProcess(process);
}
