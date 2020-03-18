#ifndef PROCESSESSELECTOR_H
#define PROCESSESSELECTOR_H
#include <vector>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QGridLayout>


class ProcessesSelector : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessesSelector(QWidget *parent = nullptr);
    ~ProcessesSelector();
    void setModel(int op,int no_p);

private:
    std::vector<QLabel*>p_label;
    std::vector<QLineEdit*>p_time;
    std::vector<QLineEdit*>p_arrival_time;
    std::vector<QLineEdit*>p_priority;

    QGridLayout *layout=new QGridLayout(this);

};

#endif // PROCESSESSELECTOR_H
