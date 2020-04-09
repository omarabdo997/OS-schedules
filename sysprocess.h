#ifndef SYSPROCESS_H
#define SYSPROCESS_H
#include <QString>
#include <QVector>
class SysProcess
{
private:
    QString name;
    QVector<int> RGB={0,0,0};
    float burstTime;
    float arrivalTime;
    int priority;
    QString status;

public:
    SysProcess();
    SysProcess(QString name);
    SysProcess(QString name,QVector<int> RGP,float burstTime,
            float arrivalTime,int priority);
    QString getName() const;
    void setName(const QString &value);
    QVector<int> getRGB() const;
    void setRGB(const QVector<int> &value);
    float getBurstTime() const;
    void setBurstTime(float value);
    float getArrivalTime() const;
    void setArrivalTime(float value);
    int getPriority() const;
    void setPriority(int value);
    QString getStatus();
    void setStatus(QString value);
};

#endif // SYSPROCESS_H
