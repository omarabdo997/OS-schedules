#ifndef SYSPROCESS_H
#define SYSPROCESS_H
#include <QString>
#include <QVector>

class SysProcess
{
private:
    QString name;
    QVector<int> RPG={0,0,0};
    float burstTime;
    float arrivalTime;
    int priority;


public:
    SysProcess();
    SysProcess(QString name);
    SysProcess(QString name,QVector<int> RPG,float burstTime,
            float arrivalTime,int priority);
    QString getName() const;
    void setName(const QString &value);
    QVector<int> getRPG() const;
    void setRPG(const QVector<int> &value);
    float getBurstTime() const;
    void setBurstTime(float value);
    float getArrivalTime() const;
    void setArrivalTime(float value);
    int getPriority() const;
    void setPriority(int value);
};

#endif // SYSPROCESS_H
