#include <iostream>
#include <assert.h>
#include "sysprocess.h"
using namespace std;
class Min_Heap
{
private:

public:



    int capacity;
    int size;
    SysProcess *data;
    Min_Heap(int c):capacity(c),size(0),data(new SysProcess[capacity])
    {

    }
    Min_Heap(int c,SysProcess d):capacity(c),size(1),data(new SysProcess[capacity])
    {
        data[0]=d;
    }
    int parent(int i)
    {
        return ((i+1)/2)-1;
    }
    int left_child(int i)
    {
        return (2*(i+1))-1;
    }
    int right_child(int i)
    {
        return 2*(i+1);
    }
    void sift_up(int i)
    {
        while(i>0 && data[parent(i)].getBurstTime()>data[i].getBurstTime())
        {
            SysProcess temp=data[parent(i)];
            data[parent(i)]=data[i];
            data[i]=temp;
            i=parent(i);
        }
    }
    void sift_down(int i)
    {
        while(left_child(i)<=(size-1))
        {
            if(right_child(i)<=(size-1))
            {
                int min=data[left_child(i)].getBurstTime()<data[right_child(i)].getBurstTime()?left_child(i):right_child(i);
                if(data[i].getBurstTime()>data[min].getBurstTime())
                {
                    SysProcess temp=data[min];
                    data[min]=data[i];
                    data[i]=temp;
                    i=min;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if(data[i].getBurstTime()>data[left_child(i)].getBurstTime())
                {
                    SysProcess temp=data[left_child(i)];
                    data[left_child(i)]=data[i];
                    data[i]=temp;
                    i=left_child(i);
                }
                else
                {
                    break;
                }
            }
        }
    }
    void insert(SysProcess p)
    {
        if(size==capacity)
        {
            delete [] data;
            assert(size==capacity);
        }
        size=size+1;
        data[size-1]=p;
        sift_up(size-1);
    }
    SysProcess extract_max()
    {
        SysProcess result=data[0];
        data[0]=data[size-1];
        size=size-1;
        sift_down(0);
        return result;
    }
    void remove(int i)
    {
        data[i].setBurstTime(data[0].getBurstTime()-1);
        sift_up(i);
        extract_max();
    }
    void change_priority(int i,int p)
    {
        int oldp=data[i].getBurstTime();
        data[i].setBurstTime(p);
        if(p<oldp)
        {
            sift_up(i);
        }
        else
        {
            sift_down(i);
        }
    }
    SysProcess peak_top()
    {
        return data[0];
    }
    ~Min_Heap()
    {
        delete [] data;
    }

};
