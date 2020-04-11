#include "rrsched.h"

float RRSched::getQuantumTime() const
{
    return quantumTime;
}

void RRSched::setQuantumTime(float value)
{
    quantumTime = value;
}

bool RRSched::cmp(const SysProcess &p1, const SysProcess &p2)
{
    return p1.getArrivalTime() < p2.getArrivalTime();
}

RRSched::RRSched()
{

}

void RRSched::schedule()
{
    qSort(processes.begin(),processes.end(),cmp);
    QQueue<SysProcess> processesQueue = new QQueue(processes);
    QQueue<SysProcess> runningProcessesQueue = new QQueue(processes[0]);
    Interval interval = Interval();
    intervals.clear();
    float finish = processesQueue.dequeue().getArrivalTime();
    SysProcess p;
    while(!ProcessesQueue.empty())
    {
        p = runningProcessesQueue.dequeue();
        interval.setFrom(finish);
        if(p.getBurstTime() > quantumTime)
        {
            finish+=quantumTime;
            p.setBurstTime(p.getBurstTime()-quantumTime);
            runningProcessesQueue.enqueue(p);
        }
        else
            finish+=p.getBurstTime();

        interval.setTo(finish);
        interval.setProcess(p);

        intervals.push_back(interval);

        if(processesQueue.head().getArrivalTime() <= finish)
            runningProcessesQueue.push_front(processesQueue.dequeue());

        if(runningProcessesQueue.empty())
        {
            if(!processesQueue.empty())
            {
                finish = processesQueue.head().getArrivalTime();
                runningProcessesQueue.enqueue(processesQueue.dequeue());
            }
        }
    }
}

float RRSched::waitingTime()
{
    float t = 0;
    for(int i = 0 ; i < processes.size() ; ++i)
    {
        float finish;
        float start = processes[i].getArrivalTime();
        for(int k = 0 ; k < intervals.size() ; ++k)
        {
            if(processes[i].getName() == intervals[k].getProcess().getName())
                finish = intervals[k].getTo();
        }
        t += finish - start - processes[i].getBurstTime();
    }
    return t/ processes.size();
}

RRSched::RRSched(QVector<SysProcess> processes, float qtime)
{
    this->setProcesses(processes);
    this->setQuantumTime(qtime);
}
