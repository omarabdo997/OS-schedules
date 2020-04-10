#include "sjfsched.h"
#include <algorithm>

float SJFSched :: finish = 0 ;

bool SJFSched::cmp(const SysProcess &p1,const SysProcess &p2)
{

    if( p1.getArrivalTime() <= finish && p1.getBurstTime() < p2.getBurstTime() )
        return true ;

    else if (p1.getArrivalTime() > finish && p2.getArrivalTime() > finish )
        if (  p1.getArrivalTime() == p2.getArrivalTime() ) {return p1.getBurstTime() < p2.getBurstTime() ; }
             else return p1.getArrivalTime() < p2.getArrivalTime() ;

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

    float amount = 0 ; // to use it in time slice
    float first = 0 ; // to use it in getTo
    int k = 0 ;  // to know index of process that will come soon after finsh

     qSort(processes.begin(),processes.end(),cmp); // for the first time only

while ( finish != time_all )
    {

// Before corner case


      for (int p = 0 ; p < processes.size() ; p++ )  { if (processes[p].getArrivalTime()> finish ) { k = p ; p=time_all ; }    }

       amount =  processes[k].getArrivalTime() - finish ;

       if ( amount > processes[0].getBurstTime() ) { amount = processes[0].getBurstTime() ; }  // if the available amout is over

       QString Old_process , New_process ;

       Old_process = processes[0].getName() ;

      interval.setFrom(first);

      finish = finish + amount  ;

      processes[0].setBurstTime( processes[0].getBurstTime()-amount) ;

      if (processes[0].getBurstTime()==0) { processes.remove(0);}

      qSort(processes.begin(),processes.end(),cmp); // sort every finish of time slice " amount "

      New_process = processes[0].getName () ;

      if ( Old_process != New_process )
      {

          interval.setTo(finish);

          interval.setProcess(processes[0]);

          intervals.push_back(interval);

          first = finish ;
       }




  // After corner case   // After the last one is lager than or equal finish


   if ( processes[processes.size()-1].getArrivalTime() > finish  )

     {
       // handle the current case before the data were lost
      interval.setFrom(first);

      finish = finish + processes[0].getBurstTime() ;
      interval.setTo(finish);
      interval.setProcess(processes[0]);
      intervals.push_back(interval);
      processes.remove(0);

      // the process will be like non preemtive

        while ( processes.size() != 0 )
          {

            interval.setFrom(finish);
            finish += processes[0].getBurstTime();
            interval.setTo(finish);
            interval.setProcess(processes[0]);
            intervals.push_back(interval);
            processes.remove(0);

          }



      }


} // for while finish != time_all



} // for else


} // for schedule





float SJFSched::waitingTime()

{
    return 1 ;
    /*
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
*/

}





