#ifndef PROCESSESSELECTOR_H
#define PROCESSESSELECTOR_H
#include <vector>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "sysprocess.h"
#include <string>

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
//    bool isNumber (QString line)
//    {

//        if (std::isdigit((line.toStdString().c_str())))
//            return true;

//        return false;
//    }
    bool is_number(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }




};

#endif // PROCESSESSELECTOR_H
