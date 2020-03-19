#include "processesselector.h"
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QGridLayout>
#include <QString>
#include <QScrollArea>
#include <QPushButton>
#include <QDebug>


ProcessesSelector::ProcessesSelector(QWidget *parent) :
    QWidget(parent)
{

//    setMinimumSize(200,500);



//    QLabel *p1=new QLabel("P1",this);
//    QLabel *p2=new QLabel("P2",this);
//    QLabel *p3=new QLabel("P3",this);
//    QLineEdit *l1=new QLineEdit(this);
//    QLineEdit *l2=new QLineEdit(this);
//    QLineEdit *l3=new QLineEdit(this);
//    QFormLayout *layout=new QFormLayout(this);
//    layout->addRow(p1,l1);
//    layout->addRow(p2,l2);
//    layout->addRow(p3,l3);

}
ProcessesSelector::~ProcessesSelector()
{

}

void ProcessesSelector::setModel(int op, int no_p)
{

    std::vector<QLabel*>p_label;
    std::vector<QLineEdit*>p_time;
    std::vector<QLineEdit*>p_arrival_time;
    std::vector<QLineEdit*>p_priority;
    QLineEdit *burst;
    QGridLayout *layout=new QGridLayout(this);
    QPushButton * submit ;
    QFont label_text("times",12);
    layout->setContentsMargins(10,20,0,20);
    layout->setVerticalSpacing(20);




  if(op==0 or op==2 or op==3)
  {
      for(int i=0;i<no_p;i++)
      {
          p_label.push_back(new QLabel("P"+QString::number(i+1),this));
          p_label[i]->setFont(label_text);
          p_time.push_back(new QLineEdit(this));
          p_time[i]->setPlaceholderText("Time");
          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");
          layout->addWidget(p_label[i],i,0);
          layout->addWidget(p_time[i],i,1);
          layout->addWidget(p_arrival_time[i],i,2);

      }
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p,2,1,1);
  }
  else if(op==1)
  {
      for(int i=0;i<no_p;i++)
      {
          p_label.push_back(new QLabel("P"+QString::number(i+1),this));
          p_label[i]->setFont(label_text);
          p_time.push_back(new QLineEdit(this));
          p_time[i]->setPlaceholderText("Time");
          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");
          layout->addWidget(p_label[i],i,0);
          layout->addWidget(p_time[i],i,1);
          layout->addWidget(p_arrival_time[i],i,2);

      }

      burst=new QLineEdit(this);

      burst->setPlaceholderText("Burst Time");



      layout->addWidget(burst,no_p,0,1,3);
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p+1,2,1,1);
  }
  else if(op==4 or op==5)
  {
      for(int i=0;i<no_p;i++)
      {
          p_label.push_back(new QLabel("P"+QString::number(i+1),this));
          p_label[i]->setFont(label_text);
          p_time.push_back(new QLineEdit(this));
          p_time[i]->setPlaceholderText("Time");
          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");
          p_priority.push_back(new QLineEdit(this));
          p_priority[i]->setPlaceholderText("Priority");
          layout->addWidget(p_label[i],i,0);
          layout->addWidget(p_time[i],i,1);
          layout->addWidget(p_arrival_time[i],i,2);
          layout->addWidget(p_priority[i],i,3);

      }
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p,2,1,1);
  }


}
