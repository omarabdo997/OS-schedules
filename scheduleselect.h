#ifndef SCHEDULESELECT_H
#define SCHEDULESELECT_H

#include <QWidget>

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

private:
    int op;
    int no_p;
};

#endif // SCHEDULESELECT_H
