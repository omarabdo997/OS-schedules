#include "processesselector.h"
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QGridLayout>
#include <QString>
#include <QScrollArea>
#include <QPushButton>
#include <QDebug>
#include <QColorDialog>
#include <QMessageBox>


ProcessesSelector::ProcessesSelector(QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(250);
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
//    std::vector<QPushButton*>color_text;
    std::vector<QPushButton*>color_background;
    QGridLayout *layout=new QGridLayout(this);
    QPushButton * submit ;


    QFont label_text("times",12);
    layout->setContentsMargins(5,20,0,20);

    layout->setVerticalSpacing(20);




  if(op==0 or op==2 or op==3)
  {
      for(int i=0;i<no_p;i++)
      {
          p_label.push_back(new QLabel("P"+QString::number(i+1),this));
          p_label[i]->setFont(label_text);
          p_label[i]->setAutoFillBackground(true);
          p_time.push_back(new QLineEdit(this));
          p_time[i]->setPlaceholderText("Burst Time");

          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");

          color_background.push_back(new QPushButton("Color",this));



          connect(color_background[i],&QPushButton::clicked,this,[i,this,p_label]()
          {
              QPalette palette=p_label[i]->palette();
              QColor color=palette.color(QPalette::Window);
              qDebug()<<"color"<<color;
              QColor selected_color=QColorDialog::getColor(color,this,"Choose back ground color");
              if(selected_color.isValid())
              {
                  palette.setColor(QPalette::Window,selected_color);
                  p_label[i]->setPalette(palette);
              }


          });
          layout->addWidget(p_label[i],i,0);
          layout->addWidget(p_time[i],i,1);
          layout->addWidget(p_arrival_time[i],i,2);

          layout->addWidget(color_background[i],i,3);


      }
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p,2,1,1);
      layout->setHorizontalSpacing(15);
      connect(submit,&QPushButton::clicked,this,[=]()
      {
          processes.clear();
          for(int i=0;i<no_p;i++)
          {
              QColor color=p_label[i]->palette().color(QPalette::Window);
              QVector<int>rgb={color.red(),color.green(),color.blue()};
              if(p_arrival_time[i]->text().toFloat()<0 or p_arrival_time[i]->text()=="" or !is_number(p_arrival_time[i]->text().toStdString()))
              {
                  QMessageBox::critical(this,"Wrong burst time","Please submit valid arrival times!");
                  return;
              }
              if(p_time[i]->text().toFloat()<0 or p_time[i]->text()=="" or !is_number(p_time[i]->text().toStdString()))
              {
                  QMessageBox::critical(this,"Wrong burst time","Please submit valid burst times!");
                  return;
              }
              if(rgb==QVector<int>{240,240,240})
              {
                  rgb[0]=rand()%256;
                  rgb[1]=rand()%256;
                  rgb[2]=rand()%256;
                  QPalette palete;
                  QColor color(rgb[0],rgb[1],rgb[2]);
                  palete.setColor(QPalette::Window,color);
                  p_label[i]->setPalette(palete);
              }
              processes.push_back(SysProcess(p_label[i]->text(),rgb,p_time[i]->text().toFloat(),p_arrival_time[i]->text().toFloat(),0));
          }
          emit input_finished();
      });
  }
  else if(op==1)
  {
      for(int i=0;i<no_p;i++)
      {
          p_label.push_back(new QLabel("P"+QString::number(i+1),this));
          p_label[i]->setFont(label_text);
          p_label[i]->setAutoFillBackground(true);
          p_time.push_back(new QLineEdit(this));
          p_time[i]->setPlaceholderText("Burst Time");
          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");

          color_background.push_back(new QPushButton("Color",this));



          connect(color_background[i],&QPushButton::clicked,this,[i,this,p_label]()
          {
              QPalette palette=p_label[i]->palette();
              QColor color=palette.color(QPalette::Window);
              qDebug()<<"color"<<color;
              QColor selected_color=QColorDialog::getColor(color,this,"Choose back ground color");
              if(selected_color.isValid())
              {
                  palette.setColor(QPalette::Window,selected_color);
                  p_label[i]->setPalette(palette);
              }


          });
          layout->addWidget(p_label[i],i,0);
          layout->addWidget(p_time[i],i,1);
          layout->addWidget(p_arrival_time[i],i,2);

          layout->addWidget(color_background[i],i,3);

      }

      burst=new QLineEdit(this);

      burst->setPlaceholderText("Quantum Time");



      layout->addWidget(burst,no_p,0,1,3);
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p+1,2,1,1);
      layout->setHorizontalSpacing(15);
      connect(submit,&QPushButton::clicked,this,[=]()
      {
          processes.clear();
          if(!is_number(burst->text().toStdString()) or burst->text()=="" or burst->text().toFloat()<=0)
          {
              QMessageBox::critical(this,"Wrong quantum time","Please submit a valid quantum time!");
              return ;
          }
          for(int i=0;i<no_p;i++)
          {
              QColor color=p_label[i]->palette().color(QPalette::Window);
              QVector<int>rgb={color.red(),color.green(),color.blue()};

              if(p_arrival_time[i]->text().toFloat()<0 or p_arrival_time[i]->text()=="" or !is_number(p_arrival_time[i]->text().toStdString()))
              {
                  QMessageBox::critical(this,"Wrong burst time","Please submit valid arrival times!");
                  return;
              }
              if(p_time[i]->text().toFloat()<0 or p_time[i]->text()=="" or !is_number(p_time[i]->text().toStdString()))
              {
                  QMessageBox::critical(this,"Wrong burst time","Please submit valid burst times!");
                  return;
              }
              if(rgb==QVector<int>{240,240,240})
              {
                  rgb[0]=rand()%256;
                  rgb[1]=rand()%256;
                  rgb[2]=rand()%256;
                  QPalette palete;
                  QColor color(rgb[0],rgb[1],rgb[2]);
                  palete.setColor(QPalette::Window,color);
                  p_label[i]->setPalette(palete);
              }
              processes.push_back(SysProcess(p_label[i]->text(),rgb,p_time[i]->text().toFloat(),p_arrival_time[i]->text().toFloat(),0));
          }
          burst_time=burst->text().toFloat();
          emit input_finished();
      });

  }
  else if(op==4 or op==5)
  {
      for(int i=0;i<no_p;i++)
      {
          p_label.push_back(new QLabel("P"+QString::number(i+1),this));
          p_label[i]->setFont(label_text);
          p_label[i]->setAutoFillBackground(true);

          p_time.push_back(new QLineEdit(this));
          p_time[i]->setPlaceholderText("Burst Time");
          p_time[i]->setMaximumWidth(90);
          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");
          p_arrival_time[i]->setMaximumWidth(90);
          p_priority.push_back(new QLineEdit(this));
          p_priority[i]->setPlaceholderText("Priority");
          p_priority[i]->setMaximumWidth(90);

          color_background.push_back(new QPushButton("Color",this));



          connect(color_background[i],&QPushButton::clicked,this,[i,this,p_label]()
          {
              QPalette palette=p_label[i]->palette();
              QColor color=palette.color(QPalette::Window);
              qDebug()<<"color"<<color;
              QColor selected_color=QColorDialog::getColor(color,this,"Choose back ground color");
              if(selected_color.isValid())
              {
                  palette.setColor(QPalette::Window,selected_color);
                  p_label[i]->setPalette(palette);
              }


          });

          layout->addWidget(p_label[i],i,0);
          layout->addWidget(p_time[i],i,1);
          layout->addWidget(p_arrival_time[i],i,2);
          layout->addWidget(p_priority[i],i,3);
          layout->addWidget(color_background[i],i,4);

      }
      layout->setHorizontalSpacing(15);
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p,2,1,1);
      connect(submit,&QPushButton::clicked,this,[=]()
      {
          processes.clear();
          for(int i=0;i<no_p;i++)
          {
              QColor color=p_label[i]->palette().color(QPalette::Window);
              QVector<int>rgb={color.red(),color.green(),color.blue()};
              if(p_priority[i]->text().toFloat()<0 or p_priority[i]->text()=="" or !is_number(p_priority[i]->text().toStdString()))
              {
                  QMessageBox::critical(this,"Wrong priority","Please submit valid priority values!");
                  return;
              }
              if(p_arrival_time[i]->text().toFloat()<0 or p_arrival_time[i]->text()=="" or !is_number(p_arrival_time[i]->text().toStdString()))
              {
                  QMessageBox::critical(this,"Wrong burst time","Please submit valid arrival times!");
                  return;
              }
              if(p_time[i]->text().toFloat()<0 or p_time[i]->text()=="" or !is_number(p_time[i]->text().toStdString()))
              {
                  QMessageBox::critical(this,"Wrong burst time","Please submit valid burst times!");
                  return;
              }
              if(rgb==QVector<int>{240,240,240})
              {
                  rgb[0]=rand()%256;
                  rgb[1]=rand()%256;
                  rgb[2]=rand()%256;
                  QPalette palete;
                  QColor color(rgb[0],rgb[1],rgb[2]);
                  palete.setColor(QPalette::Window,color);
                  p_label[i]->setPalette(palete);
              }
              processes.push_back(SysProcess(p_label[i]->text(),rgb,p_time[i]->text().toFloat(),p_arrival_time[i]->text().toFloat(),p_priority[i]->text().toFloat()));
          }
          emit input_finished();
      });

  }



}

QVector<SysProcess> ProcessesSelector::getProcesses() const
{
    return processes;
}

float ProcessesSelector::getBurst_time() const
{
    return burst_time;
}
