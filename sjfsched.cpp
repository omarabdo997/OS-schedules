#include "sjfsched.h"
#include <algorithm>

SJFSched::SJFSched()
{

}

 SJFSched::SJFSched(bool isPreemtive , QVector<SysProcess> processes )
{
 this->set_isPreemptive(isPreemtive);
 this->setProcesses(processes);
}


void SJFSched :: set_isPreemptive(bool value) { isPreemtive = value ; }

bool SJFSched :: get_isPreemptive() {return isPreemtive ; }


float finish = 0;   // I neeed make this var global and func cmp and loop in schedule modify in it


bool SJFSched::cmp(const SysProcess &p1,const SysProcess &p2)
{
    if( p1.getArrivalTime() <= finish && p1.getBurstTime() < p2.getBurstTime() )
        return true ;
    else return false;
}


 // problem with const and static

void SJFSched::schedule()
{

    Interval interval = Interval();
    intervals.clear();

  // if (!isPreemtive)
 // {
     for(int i = 0 ; i < processes.size() ; ++i)  // Why ++i ??
         {
             qSort(processes.begin()+i,processes.end(),cmp); // make the finished process not use in the sorting


      if(processes[i].getArrivalTime() > finish)    // handle problem of no processes
        finish = processes[i].getArrivalTime();

      interval.setFrom(finish);
      finish += processes[i].getBurstTime();
      interval.setTo(finish);
      interval.setProcess(processes[i]);
      intervals.push_back(interval);
         }
 }


/*
    else
    {
         finish = 0 ;

    float time_all = 0 ; // end of time line
    for (int i = 0 ; i < processes.size() ; i++)
    {
       time_all += processes[i].getBurstTime() ;
    }

    for (int i = 0 ; i < time_all ; ++i)  // ++i  // check every time slice
    {
     qSort(processes.begin(),processes.end(),cmp);

      interval.setFrom(finish);
      interval.setProcess(processes[i]);
      intervals.push_back(interval);
      finish ++ ;
      interval.setTo(finish);
    }

    }



}

*/





