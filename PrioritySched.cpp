#include <PrioritySched.h>
#include <algorithm>

void prioritysched :: set_is_Preemptive(bool value){is_Preemptive = value; }

bool prioritysched :: get_is_preemptive(){  return is_Preemptive; }

void prioritysched :: set_qtime(float value) { qtime = value ;}

float prioritysched :: get_qtime(){return qtime; }


prioritysched ::prioritysched()
{

}


prioritysched :: prioritysched(QVector<SysProcess> processes,bool is_Preemptive)
{
    this->setProcesses(processes);
    this->set_is_Preemptive(is_Preemptive);
}

prioritysched :: prioritysched(QVector<SysProcess> processes,bool is_Preemptive,float qtime)
{
    this->setProcesses(processes);
    this->set_is_Preemptive(is_Preemptive);
    this->set_qtime(qtime);
}

bool prioritysched::cmp(const SysProcess &p1,const SysProcess &p2)
{
    if(p1.getArrivalTime() == p2.getArrivalTime())
        return  p1.getPriority() < p2.getPriority();
    else if((p1.getArrivalTime()==p2.getArrivalTime())&&(p1.getPriority()== p2.getPriority()))
        return p1.getBurstTime()<p2.getBurstTime();
    else if(p1.getPriority() == p2.getPriority())
        return p1.getArrivalTime()<p2.getArrivalTime();
    else
        return p1.getArrivalTime() < p2.getArrivalTime();
}

void prioritysched :: schedule()
{
    qSort(processes.begin(),processes.end(),cmp);

    if(get_is_preemptive())
    {

    }
    else // Priority non preemptive - so after sorting we act like it it FCFS.
    {
        float finish =0;
        Interval interval= Interval();
        intervals.clear();
        for(int i = 0 ;i<processes.size();i++)
        {
            if(processes[i].getArrivalTime()>finish)
            {
                finish = processes[i].getArrivalTime();
                interval.setFrom(finish);
                finish +=processes[i].getBurstTime();
                interval.setTo(finish);
                interval.setProcess(processes[i]);
                intervals.push_back(interval);
            }

        }

    }

}

float prioritysched :: waitingTime()
{
    if(get_is_preemptive())
    {

    }
    else
    {
        float ans = 0;
        for(int i =0;i<intervals.size();i++)
        {
            ans+=intervals[i].getFrom() - intervals[i].getProcess().getArrivalTime();

        }

        float waiting = ans/intervals.size();
        return waiting;
    }
}
