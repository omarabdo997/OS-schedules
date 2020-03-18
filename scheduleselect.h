#ifndef SCHEDULESELECT_H
#define SCHEDULESELECT_H

#include <QWidget>
#include <QPushButton>

class ScheduleSelect : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleSelect(QWidget *parent = nullptr);
    ~ScheduleSelect();

    int getOp() const;

    int getNo_p() const;

    void setOp(int value);

    void setNo_p(int value);
signals:
    void input_finished();


private:
    int op;
    int no_p;
    QPushButton *submit=new QPushButton("Submit",this);
};

#endif // SCHEDULESELECT_H
