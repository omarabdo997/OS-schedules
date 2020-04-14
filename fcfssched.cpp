#include "fcfssched.h"
#include <algorithm>
#include <QString>
bool FCFSSched::cmp(const SysProcess &p1,const SysProcess &p2)
{
    if(p1.getArrivalTime() < p2.getArrivalTime())
        return true;
    else if (p1.getArrivalTime() == p2.getArrivalTime())
    {
        QString p1name=p1.getName();
        QString p2name=p2.getName();
         p1name=p1name.remove(0,1);
         p2name=p2name.remove(0,1);
         return p1name.toInt()<p2name.toInt();
    }

    else return false;
}



FCFSSched::FCFSSched()
{

}

void FCFSSched::schedule()
{
    qSort(processes.begin(),processes.end(),cmp);
    float finish = 0;
    Interval interval = Interval();
    intervals.clear();
    for(int i = 0 ; i < processes.size() ; ++i)
    {
      if(processes[i].getArrivalTime() > finish)
        finish = processes[i].getArrivalTime();
      interval.setFrom(finish);
      finish += processes[i].getBurstTime();
      interval.setTo(finish);
      interval.setProcess(processes[i]);
      intervals.push_back(interval);
    }
}

float FCFSSched::waitingTime()
{
    float ans=0;
    for(int i = 0 ; i < intervals.size() ; i++)
      ans += intervals[i].getFrom()-intervals[i].getProcess().getArrivalTime();
    ans /= intervals.size();
    return ans;
}

FCFSSched::FCFSSched(QVector<SysProcess> processes)
{
    this->setProcesses(processes);
}
