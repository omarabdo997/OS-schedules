#include "sjfschedule.h"
#include "MinHeap.h"
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
        int timer;
        int start;
        int finish;
        intervals.clear();
        Interval interval;
        Min_Heap heap(processes.size());
        qSort(processes.begin(),processes.end(),cmp);
        timer=processes[0].getArrivalTime();
        heap.insert(processes[0]);
        start=processes[0].getArrivalTime();
        for(int i=1;i<processes.size();i++)
        {
            timer=processes[i].getArrivalTime();
            if(timer>=(heap.peak_top().getBurstTime()+start))
            {
                while(heap.size!=0 && timer>=(heap.peak_top().getBurstTime()+start))
                {
                    finish=heap.peak_top().getBurstTime()+start;
                    interval.setFrom(start);
                    interval.setTo(finish);
                    interval.setProcess(heap.peak_top());
                    heap.extract_max();
                    intervals.push_back(interval);
                    heap.insert(processes[i]);
                    if(heap.peak_top().getArrivalTime()<=timer)
                    {
                        start=heap.peak_top().getArrivalTime();
                    }
                    else
                    {
                        start=timer;
                    }
                }
            }
            else
            {
                if((heap.peak_top().getBurstTime()-(timer-start))>processes[i].getBurstTime())
                {
                    finish=timer-start;
                    interval.setFrom(start);
                    interval.setTo(finish);
                    interval.setProcess(heap.peak_top());
                    intervals.push_back(interval);
                    heap.change_priority(0,(heap.peak_top().getBurstTime()-(timer-start)));
                    heap.insert(processes[i]);
                    start=finish;
                }
                else
                {
                    heap.insert(processes[i]);
                }
            }

        }
        while(heap.size!=0)
        {
            finish=heap.peak_top().getBurstTime()+start;
            interval.setFrom(start);
            interval.setTo(finish);
            interval.setProcess(heap.peak_top());
            intervals.push_back(interval);
            heap.extract_max();
            start=finish;
        }
    }
    else
    {

    }
}

float SJFSchedule::waitingTime()
{
    return 2;
}

SJFSchedule::SJFSchedule(bool isPreemtive, QVector<SysProcess> processes)
{
    this->setIsPreemtive(isPreemtive);
    this->setProcesses(processes);

}

bool SJFSchedule::cmp(const SysProcess &p1, const SysProcess &p2)
{
    if(p1.getArrivalTime()==p2.getArrivalTime())
    {
        if(p1.getBurstTime()==p2.getBurstTime())
        {
            QString p1name=p1.getName();
            QString p2name=p2.getName();
             p1name=p1name.remove(0,1);
             p2name=p2name.remove(0,1);
             return p1name.toInt()<p2name.toInt();
        }
        else
        {
            return p1.getBurstTime()<p2.getBurstTime();
        }
    }
    else
    {
        return p1.getArrivalTime()<p2.getArrivalTime();
    }
}

