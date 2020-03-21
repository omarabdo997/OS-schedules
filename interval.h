#ifndef INTERVAL_H
#define INTERVAL_H
#include "sysprocess.h"

class Interval
{
private:
    float from;
    float to;
    SysProcess process;
public:
    Interval();
    Interval(float from,float to);
    Interval(float from,float to, SysProcess process);
    float getFrom() const;
    void setFrom(float value);
    float getTo() const;
    void setTo(float value);
    SysProcess getProcess() const;
    void setProcess(const SysProcess &value);
};

#endif // INTERVAL_H
