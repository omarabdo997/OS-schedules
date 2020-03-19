#ifndef ANSWER_H
#define ANSWER_H

#include <QWidget>


class Answer : public QWidget
{
    Q_OBJECT

public:
    explicit Answer(QWidget *parent = nullptr);
    ~Answer();
    void set_model();
private:

};

#endif // ANSWER_H
