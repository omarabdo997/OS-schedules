#ifndef INTERVAL_H
#define INTERVAL_H
#include "process.h"

class Interval
{
private:
    float from;
    float to;
    Process process;
public:
    Interval();
    Interval(float from,float to);
    Interval(float from,float to,Process process);
    float getFrom() const;
    void setFrom(float value);
    float getTo() const;
    void setTo(float value);
    Process getProcess() const;
    void setProcess(const Process &value);
};

#endif // INTERVAL_H
