#ifndef ANSWER_H
#define ANSWER_H

#include <QWidget>
#include "interval.h"

class Answer : public QWidget
{
    Q_OBJECT

public:
    explicit Answer(QWidget *parent = nullptr);
    ~Answer();
    void set_model(QVector<Interval> intervals);
private:

};

#endif // ANSWER_H
