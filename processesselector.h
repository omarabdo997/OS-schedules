#ifndef PROCESSESSELECTOR_H
#define PROCESSESSELECTOR_H
#include <vector>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "sysprocess.h"

class ProcessesSelector : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessesSelector(QWidget *parent = nullptr);
    ~ProcessesSelector();
    void setModel(int op,int no_p);
    QVector<SysProcess> getProcesses() const;

    float getBurst_time() const;

public slots:
signals:
    void input_finished();
private:
    QVector<SysProcess>processes;
    float burst_time;





};

#endif // PROCESSESSELECTOR_H
