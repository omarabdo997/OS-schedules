#ifndef PROCESSESSELECTOR_H
#define PROCESSESSELECTOR_H
#include <vector>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>


class ProcessesSelector : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessesSelector(QWidget *parent = nullptr);
    ~ProcessesSelector();
    void setModel(int op,int no_p);

private:





};

#endif // PROCESSESSELECTOR_H
