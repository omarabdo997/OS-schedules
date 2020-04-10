#include "sjfsched.h"
#include <algorithm>

float SJFSched :: finish = 0 ;

bool SJFSched::cmp(const SysProcess &p1,const SysProcess &p2)
{

    if( p1.getArrivalTime() <= finish && p1.getBurstTime() < p2.getBurstTime() )
        return true ;
    else return false;
}

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

void SJFSched::schedule()
{
    finish = 0;
    Interval interval = Interval();
    intervals.clear();


    if (!isPreemtive)  // for non preemtive case
   {

     for(int i = 0 ; i < processes.size() ;i++)  // Why ++i ??
       {

          qSort(processes.begin()+i,processes.end(),cmp);  // use i to make the finished process not use in the sorting

          if(processes[i].getArrivalTime() > finish)    // handle problem of no processes
              finish = processes[i].getArrivalTime();

          interval.setFrom(finish);
          finish += processes[i].getBurstTime();
          interval.setTo(finish);
          interval.setProcess(processes[i]);
          intervals.push_back(interval);
       }

   }


else  // for preemtive case

 {

     float time_all = 0 ; // end of time line

     for (int i = 0 ; i < processes.size() ; i++) { time_all += processes[i].getBurstTime() ; }

  //  qDebug() <<time_all ; // const and static explaining

    float decrease = 0 ;
    for (int i = 0 ; i < time_all ; i++ )  // ++i  // check every time slice
    {

      interval.setFrom(finish);
      finish++ ;
      interval.setTo(finish);
      interval.setProcess(processes[0]);
      intervals.push_back(interval);
      // may check till the Burst time is less 1

      if  ( (interval.getTo() - interval.getFrom()) >= 1 )
          processes[0].getBurstTime() < 1 // we will make a change in finish
               if processes[0].getArrivalTime()

      processes[0].setBurstTime( processes[0].getBurstTime()-1) ; // decrease time from every finish in time slice

       processes[0].setBurstTime( processes[0].getBurstTime()-1) ;

      qSort(processes.begin(),processes.end(),cmp); // sort every finish of time slice

      if (processes[0].getBurstTime()==0) { processes.remove(0);}

    }

 }


}



float SJFSched::waitingTime()
{
   if (!isPreemtive)   // waiting for non preemitive
    {
      float ans=0;
      for(int i = 0 ; i < intervals.size() ; i++)
         ans += intervals[i].getFrom()-intervals[i].getProcess().getArrivalTime();
      ans /= intervals.size();
      return ans;
    }

  else   // waiting for preemitive
    {
       float ans=0;
       for(int i = 0 ; i < intervals.size() ; i++)
          ans += intervals[i].getFrom()-intervals[i].getProcess().getArrivalTime();
       ans /= intervals.size();
       return ans;
     }

}





