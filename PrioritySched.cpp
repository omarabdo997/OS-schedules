#include <PrioritySched.h>
#include <algorithm>
#include <queue>
#include <vector>

void prioritysched :: set_is_Preemptive(bool value){is_Preemptive = value; }

bool prioritysched :: get_is_preemptive(){  return is_Preemptive; }


prioritysched ::prioritysched()
{

}


prioritysched :: prioritysched(QVector<SysProcess> processes,bool is_Preemptive)
{
    this->setProcesses(processes);
    this->set_is_Preemptive(is_Preemptive);
}

bool prioritysched::cmp(const SysProcess &p1,const SysProcess &p2)
{
    if(p1.getArrivalTime() == p2.getArrivalTime())
        return  p1.getPriority() < p2.getPriority();
    else
        return p1.getArrivalTime()<p2.getArrivalTime();
}

bool prioritysched ::pcmp(const SysProcess &p1,const SysProcess &p2)
{
    if(p1.getPriority()<p2.getPriority())
        return true;
    else if(p1.getPriority()==p2.getPriority())
        return p1.getArrivalTime()<p2.getArrivalTime();
}

bool prioritysched :: arriv_cmp(QVector<SysProcess> &processes)
{
    bool equal;
    for(int i=1;i<processes.size();i++)
    {
        if(processes[i].getArrivalTime()==processes[i-1].getArrivalTime())
            equal = true;
        else
        {   equal = false;
            break;
        }


    }
    return equal;
}



void prioritysched :: schedule()
{


    if(get_is_preemptive())
    {

    }
    else
    {
        qSort(processes.begin(),processes.end(),cmp);
        if(arriv_cmp(processes)) //if arrival time is the same ,we sort it according to the priority and deal with it like fcfs.
        {
            float finish =0;
            Interval interval= Interval();
            intervals.clear();
            for(int i = 0 ;i<processes.size();i++)
            {
                if(processes[i].getArrivalTime()>finish)
                    finish = processes[i].getArrivalTime();

                    interval.setFrom(finish);
                    finish +=processes[i].getBurstTime();
                    interval.setTo(finish);
                    interval.setProcess(processes[i]);
                    intervals.push_back(interval);

            }
        }
        else
        {
            float finish = 0;
            Interval interval= Interval();
            intervals.clear();
            if(processes[0].getArrivalTime()>finish)
                finish = processes[0].getArrivalTime();
            interval.setFrom(finish);
            finish+=processes[0].getBurstTime();
            interval.setTo(finish);
            interval.setProcess(processes[0]);
            intervals.push_back(interval);
            processes[0].setStatus("finished");
            int executed_process = 1;
            int n = processes.size();
            processes.erase(processes.begin());//deleted the first process which arrived first and finished.
            while(executed_process< n )
            {

                for(int j=0;j<processes.size();j++) //check if process is ready
                {
                    if(processes[j].getArrivalTime()<=finish)
                    {
                        processes[j].setStatus("ready");
                    }
                    else
                    {
                        continue;
                    }
                }

                qSort(processes.begin(),processes.end(),pcmp); //sort accoring to priority
                int best_process ;
                bool to_be_used;
                for(int i=0;i<processes.size();i++)
                {   to_be_used = false; //indicates that one of the highest priority is ready
                    if(processes[i].getStatus()=="ready")
                    {
                        to_be_used = true;
                        best_process = i;
                    }
                    else
                    {
                        continue;
                    }

                    if(to_be_used==true)
                        break;

                }
                if(to_be_used == true)
                {
                    if(processes[best_process].getArrivalTime()>finish)
                        finish = processes[best_process].getArrivalTime();
                    interval.setFrom(finish);
                    finish +=processes[best_process].getBurstTime();
                    interval.setTo(finish);
                    interval.setProcess(processes[best_process]);
                    intervals.push_back(interval);
                    executed_process++;
                    processes[best_process].setStatus("finished");
                    processes.erase(processes.begin()+best_process);
                }
                else //there's a gap between two processes
                {   qSort(processes.begin(),processes.end(),cmp); //sort according to arrival time again
                    if(processes[0].getArrivalTime()>finish)
                        finish = processes[0].getArrivalTime();
                    interval.setFrom(finish);
                    finish +=processes[0].getBurstTime();
                    interval.setTo(finish);
                    interval.setProcess(processes[0]);
                    intervals.push_back(interval);
                    executed_process++;
                    processes[0].setStatus("finished");
                    processes.erase(processes.begin());

                }

            }

        }
    }

}

float prioritysched :: waitingTime() //calculating waitingtime
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

        return ans/intervals.size();;
    }
}
