#include "fcfssched.h"

bool FCFSSched::cmp(SysProcess p1, SysProcess p2)
{
    if(p1.getArrivalTime() < p2.getArrivalTime())
        return true;
    else if (p1.getArrivalTime() == p2.getArrivalTime())
        return p1.getBurstTime() < p2.getBurstTime();
    else return false;
}

FCFSSched::FCFSSched()
{

}

void FCFSSched::schedule()
{
    sort(processes.begin(),processes.end(),cmp);
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

FCFSSched::FCFSSched(vector<SysProcess> processes)
{
    this->setProcesses(processes);
}
