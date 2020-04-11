#include <PrioritySched.h>
#include <algorithm>
#include <queue>
#include <iterator>
#include <QDebug>

void prioritysched :: set_is_Preemptive(bool value){is_Preemptive = value; }

bool prioritysched :: get_is_preemptive(){  return is_Preemptive; }

QVector<float> prioritysched ::get_burst_copy(QVector<SysProcess> &processes)
{
    for(int i=0;i<processes.size();i++)
    {
        Burst_time_copy_preemptive.push_back(processes[i].getBurstTime());
    }
    return Burst_time_copy_preemptive;
}


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

class pq_pcmp{
public:
    bool operator()(const SysProcess &p1,const SysProcess &p2)
    {
        if(p1.getPriority()> p2.getPriority())
            return true;
        else if(p1.getPriority()<p2.getPriority())
            return false;
        else if(p1.getPriority()==p2.getPriority())
            return p1.getArrivalTime()>p2.getArrivalTime();
    }
};


void prioritysched :: schedule()
{


    if(get_is_preemptive())
    {
        qSort(processes.begin(),processes.end(),cmp);
        if(arriv_cmp(processes))
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
            get_burst_copy(processes); //copy burst times before missing with them
            float last = 0;
            std::priority_queue<SysProcess,QVector<SysProcess>,pq_pcmp> my_pq;
            Interval interval= Interval();
            intervals.clear();
            int executed_process = 0;
            int n = processes.size();
            int i = 0;
            while(executed_process<n)
            {
                if(i == n)
                {
                    int qsize=my_pq.size();
                    while(!my_pq.empty())
                    {  float finish=interval.getFrom();;
                       for(int j=0;j<qsize;j++)
                       {
                           if(j==0) //highest priority
                           {
                               interval.setTo(finish+my_pq.top().getBurstTime());
                               finish +=my_pq.top().getBurstTime();
                               my_pq.pop();
                               intervals.push_back(interval);
                               executed_process++;
                               continue;

                           }
                           else
                           {
                               interval.setFrom(finish);
                               interval.setTo(finish+my_pq.top().getBurstTime());
                               finish += my_pq.top().getBurstTime();
                               interval.setProcess(my_pq.top());
                               intervals.push_back(interval);
                               my_pq.pop();
                               executed_process++;
                               continue;

                           }

                       }

                    }



                }

                else if(i==0)
                {
                    interval.setFrom(processes[i].getArrivalTime());
                    interval.setProcess(processes[i]);
                    if(processes.size()==1)
                    {
                        interval.setTo(processes[i].getArrivalTime()+processes[i].getBurstTime());
                        intervals.push_back(interval);
                        executed_process++;
                        continue;
                    }
                    my_pq.push(processes[i]);
                    i++;
                    continue;
                }
                else
                {
                    SysProcess prev = my_pq.top();

                    my_pq.push(processes[i]);
                    if(my_pq.top().getName()==prev.getName()) //the old top didn't change as it has higher priority
                    {   SysProcess top = my_pq.top(); //the top didn't change


                        if(processes[i].getArrivalTime()>=last+top.getBurstTime())
                        {
                            while(processes[i].getArrivalTime()>=last+top.getBurstTime())
                            {
                                last+=top.getBurstTime();
                                interval.setTo(last);
                                intervals.push_back(interval);
                                executed_process++;
                                my_pq.pop();

                                top =my_pq.top();

                                if(my_pq.size()==1)
                                {

                                    break;
                                }
                                else if(top.getName()==processes[i].getName()&&my_pq.size()>1 &&top.getArrivalTime()!=last)
                                {
                                    top=my_pq.top();
                                    my_pq.pop();
                                    SysProcess p = my_pq.top();
                                    my_pq.pop();
                                    interval.setFrom(last);
                                    interval.setProcess(p);
                                    interval.setTo(top.getArrivalTime());
                                    intervals.push_back(interval);
                                    p.setBurstTime(p.getBurstTime()-(top.getArrivalTime()-last));
                                    last=top.getArrivalTime();
                                    if(p.getBurstTime()==0)
                                    {   executed_process++;
                                        my_pq.push(top);
                                        interval.setFrom(last);
                                        interval.setProcess(top);
                                        continue;
                                    }
                                    else
                                    {
                                        my_pq.push(p);
                                        my_pq.push(top);
                                        interval.setFrom(last);
                                        interval.setProcess(top);
                                        continue;

                                    }
                                }
                                interval.setFrom(last);
                                interval.setProcess(top);
                                if(i==n-1)
                                {   interval.setTo(last+top.getBurstTime());
                                    last = last+top.getBurstTime();
                                    intervals.push_back(interval);
                                    executed_process++;
                                    my_pq.pop();
                                    i++;
                                    break;
                                }
                                continue;

                            }

                            if(i==n)
                            {
                                interval.setFrom(last);
                                interval.setProcess(my_pq.top());
                                continue;
                            }


                            if(my_pq.size()==1)
                                last= my_pq.top().getArrivalTime();
                            else if(my_pq.size()>1)
                                ;
                            interval.setFrom(last);
                            interval.setProcess(my_pq.top());
                            i++;
                            continue;

                        }
                        else
                        {
                            i++;
                            continue;
                        }

                    }
                    else // has lower priority than the next
                    {
                        if(my_pq.top().getArrivalTime()>=last+prev.getBurstTime())
                        {   while(my_pq.top().getArrivalTime()>=last+prev.getBurstTime())
                            {
                                interval.setTo(last+prev.getBurstTime());
                                last+=prev.getBurstTime();
                                intervals.push_back(interval);
                                executed_process++;

                                SysProcess top = my_pq.top();
                                my_pq.pop();

                                my_pq.pop();
                                if(my_pq.empty())
                                {
                                    my_pq.push(top);
                                    break;
                                }
                                else
                                {
                                    prev = my_pq.top();
                                    my_pq.push(top);

                                    interval.setFrom(last);
                                    interval.setProcess(prev);
                                }

                            }
                            interval.setFrom(my_pq.top().getArrivalTime());
                            last=my_pq.top().getArrivalTime();
                            interval.setProcess(my_pq.top());
                            i++;
                            continue;
                        }
                        else
                        {
                            interval.setTo(my_pq.top().getArrivalTime());
                            intervals.push_back(interval);
                            SysProcess top = my_pq.top();
                            my_pq.pop();
                            SysProcess p = my_pq.top();
                            my_pq.pop();
                            p.setBurstTime(p.getBurstTime()-(top.getArrivalTime()-last));
                            last = top.getArrivalTime();
                            if(p.getBurstTime()==0)
                            {   executed_process++;
                                my_pq.push(top);
                                interval.setFrom(last);
                                interval.setProcess(my_pq.top());
                                i++;
                                continue;
                            }
                            else
                            {   my_pq.push(p);
                                my_pq.push(top);
                                interval.setFrom(last);
                                interval.setProcess(my_pq.top());
                                i++;
                                continue;
                            }

                        }

                    }


                }



            }

        }



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
        if(arriv_cmp(processes))
        {
            float ans = 0;
            for(int i =0;i<intervals.size();i++)
            {
                ans+=intervals[i].getFrom() - intervals[i].getProcess().getArrivalTime();
            }
            return ans/intervals.size();
        }
        else
        {

            float waiting_time[processes.size()];
            float finish_time[processes.size()];
            int interval_num;
            float total_waiting =0;
            for(int i=0;i<processes.size();i++)
            {
                for(int j=0;j<intervals.size();j++)
                {
                  if(intervals[j].getProcess().getName()==processes[i].getName())
                    interval_num=j;
                }
                finish_time[i]=intervals[interval_num].getTo();
            }

            for(int i=0;i<processes.size();i++)
            {
                waiting_time[i] = finish_time[i]-Burst_time_copy_preemptive[i]-processes[i].getArrivalTime();
            }
            for(int i=0;i<processes.size();i++)
            {
                total_waiting+=waiting_time[i];
            }

            return total_waiting/processes.size();
        }

    }
    else
    {
        float ans = 0;
        for(int i =0;i<intervals.size();i++)
        {
            ans+=intervals[i].getFrom() - intervals[i].getProcess().getArrivalTime();

        }

        return ans/intervals.size();
    }
}
