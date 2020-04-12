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
        int points=0;
        std::string::const_iterator it = s.begin();
        while (it != s.end() && (std::isdigit(*it) or ((*it)=='.')))
        {
            if((*it)=='.')
            {
                points++;
            }
            ++it;
        }
        return !s.empty() && it == s.end() && points<=1 && s.back()!='.';
    }




};

#endif // PROCESSESSELECTOR_H
