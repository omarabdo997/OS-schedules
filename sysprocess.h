#ifndef SYSPROCESS_H
#define SYSPROCESS_H
#include <QString>

class SysProcess
{
private:
    QString name;
    QString RPG;
    float burstTime;
    float arrivalTime;
    int priority;


public:
    SysProcess();
    SysProcess(QString name);
    SysProcess(QString name,QString RPG,float burstTime,
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

#endif // SYSPROCESS_H
