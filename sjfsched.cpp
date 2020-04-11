#include "sjfsched.h"
#include <algorithm>


float SJFSched :: finish = 0 ;

QVector <SysProcess> SJFSched :: copy_processes ;

int SJFSched::cmp(const SysProcess &p1,const SysProcess &p2)
{

    if ( p1.getArrivalTime() <= finish )

      {
        if (p2.getArrivalTime() <= finish)
        {
            if      ( p1.getBurstTime() < p2.getBurstTime() ) { return true  ;}
            else if ( p1.getBurstTime() < p2.getBurstTime() ) { return 0     ;}
            else                                              { return false ;}
        }

         else {return true ;}
      }

    else // p1.getArrivalTime() > finish

      {
        if (p2.getArrivalTime() <= finish )  { return false ;}

         else
          {
            if(p1.getArrivalTime() < p2.getArrivalTime())
                return true;
            else if (p1.getArrivalTime() == p2.getArrivalTime())
               {
                if      ( p1.getBurstTime() < p2.getBurstTime() ) { return true  ;}
                else if ( p1.getBurstTime() < p2.getBurstTime() ) { return 0     ;}
                else                                              { return false ;}
               }
            else return false;
          }

       }

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
        for (int i=0 ; i < processes.size() ; i++)
           { if (processes[i].getBurstTime()==0)
              {
                processes.remove(i);
                i++;
               }
           }

        for (int i=0 ; i < processes.size() ; i++)
           copy_processes.push_back(processes[i]);       

       float amount = 0 ;                                // to use it in time slice
       float first  = 0 ;                               // to use it in getTo
       int k = 0 ;                                     // to know index of process that will come soon after finsh
       SysProcess Old_pro , New_pro ;                 // for process itself
       qSort(processes.begin(),processes.end(),cmp); // for the first time only

       if(processes[0].getArrivalTime() > finish )  // handle problem of no processes in the first time only
        { first = processes[0].getArrivalTime();
          finish = processes[0].getArrivalTime();
        }

       float c = processes[processes.size()-1].getArrivalTime() ;

       // Before corner case

while ( finish < c &&  processes.size() != 0 )

{


     if (processes.size() != 1 )
       {
         for (int p = 0 ; p < processes.size() ; p++ )  { if ( processes[p].getArrivalTime() > finish ) { k = p ; break; }  }

         amount =  processes[k].getArrivalTime() - finish ;
       }

     else  { amount = processes[0].getBurstTime() ; } // if there is only last one in vector

     if ( amount > processes[0].getBurstTime() ) { amount = processes[0].getBurstTime() ; }  // if the available amout is over

     Old_pro =  processes[0]  ;

     interval.setFrom(first);

     finish = finish + amount  ;

     processes[0].setBurstTime( processes[0].getBurstTime()-amount) ;

     if ( processes[0].getBurstTime()==0 ) { processes.remove(0); }

     if (processes.size() != 0 )
         {
            qSort(processes.begin(),processes.end(),cmp);  // sort every finish of time slice " amount "

            New_pro = processes[0] ;
         }

        else
        {
            interval.setTo(finish);

            interval.setProcess(Old_pro);

            intervals.push_back(interval);
        }

     if (  New_pro.getName() != Old_pro.getName() )

         {
             interval.setTo(finish);

             interval.setProcess(Old_pro);

             intervals.push_back(interval);

             first = finish ;
          }

     if(processes[0].getArrivalTime() > finish )    // handle problem of no processes during running
            { first = processes[0].getArrivalTime();
              finish = processes[0].getArrivalTime();
            }

} // for while (finish < processes[processes.size()-1] )



     // After corner case   // After the last one is lager than or equal finish

if ( finish >= c &&  processes.size() != 0 )
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

              // we need handle time in between if the processor is not avaiable

               interval.setFrom(finish);
               finish += processes[0].getBurstTime();
               interval.setTo(finish);
               interval.setProcess(processes[0]);
               intervals.push_back(interval);
               processes.remove(0);

            }
   }

 } // for else

} // for schedule





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
      // search of waiting time for every one process

      float ans = 0 , one_wait = 0 , all_wait = 0  ;
      QVector <int> num ;

      for (int j =0 ; j < copy_processes.size() ; j++ )
        {
             QString pro = copy_processes[j].getName() ;

             for(int i = 0 ; i < intervals.size() ; i++)  { if (intervals[i].getProcess().getName()==pro) { num.push_back(i); } }

             if (num.size()>1)
                {
                   for(int i = 0 ; i < num.size()-1 ; i++) // -1 to exit before the exit the vector
                       {
                          float one_in =0 ;
                          one_in=intervals[num[i+1]].getFrom() - intervals[num[i]].getTo()   ;
                          one_wait += one_in ;
                       }
                }

             else { one_wait = intervals[num[0]].getFrom() - copy_processes[j].getArrivalTime(); }

             all_wait += one_wait ;
             num.clear();

        }


      ans = all_wait / copy_processes.size();
      return ans;

    }


}






