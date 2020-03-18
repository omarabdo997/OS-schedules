#include "processesselector.h"
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>


ProcessesSelector::ProcessesSelector(QWidget *parent) :
    QWidget(parent)
{
    QLabel *p1=new QLabel("P1",this);
    QLabel *p2=new QLabel("P2",this);
    QLabel *p3=new QLabel("P3",this);
    QLineEdit *l1=new QLineEdit(this);
    QLineEdit *l2=new QLineEdit(this);
    QLineEdit *l3=new QLineEdit(this);
    QFormLayout *layout=new QFormLayout(this);
    layout->addRow(p1,l1);
    layout->addRow(p2,l2);
    layout->addRow(p3,l3);

}
ProcessesSelector::~ProcessesSelector()
{

}
