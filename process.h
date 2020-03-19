#ifndef PROCESS_H
#define PROCESS_H
#include <QString>

class Process
{
private:
    QString name;
    QString RPG;
    float burstTime;
    float arrivalTime;
    int priority;


public:
    Process();
    Process(QString name);
    Process(QString name,QString RPG,float burstTime,
            float arrivalTime,int priority);
    QString getName() const;
    void setName(const QString &value);
    QString getRPG() const;
    void setRPG(const QString &value);
    float getBurstTime() const;
    void setBurstTime(float value);
    float getArrivalTime() const;
    void setArrivalTime(float value);
    int getPriority() const;
    void setPriority(int value);
};

#endif // PROCESS_H
