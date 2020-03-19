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
    std::vector<QPushButton*>color_text;
    std::vector<QPushButton*>color_background;

    QGridLayout *layout=new QGridLayout(this);
//    QHBoxLayout *layout_main=new QHBoxLayout(this);
////    layout_main->addSpacing(10);
//    layout_main->addLayout(layout);
////    layout_main->addSpacing(40);
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
          p_time[i]->setPlaceholderText("Time");

          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");
          color_text.push_back(new QPushButton("Text color",this));
          color_background.push_back(new QPushButton("BG color",this));


          connect(color_text[i],&QPushButton::clicked,this,[i,this,p_label]()
          {
              QPalette palette=p_label[i]->palette();
              QColor color=palette.color(QPalette::WindowText);
              qDebug()<<"color"<<color;
              QColor selected_color=QColorDialog::getColor(color,this,"Choose Text color");
              if(selected_color.isValid())
              {
                  palette.setColor(QPalette::WindowText,selected_color);
                  p_label[i]->setPalette(palette);
              }


          });
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
          layout->addWidget(color_text[i],i,3);
          layout->addWidget(color_background[i],i,4);
//

      }
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p,2,1,1);
      layout->setHorizontalSpacing(0);
  }
  else if(op==1)
  {
      for(int i=0;i<no_p;i++)
      {
          p_label.push_back(new QLabel("P"+QString::number(i+1),this));
          p_label[i]->setFont(label_text);
          p_label[i]->setAutoFillBackground(true);
          p_time.push_back(new QLineEdit(this));
          p_time[i]->setPlaceholderText("Time");
          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");
          color_text.push_back(new QPushButton("Text color",this));
          color_background.push_back(new QPushButton("BG color",this));


          connect(color_text[i],&QPushButton::clicked,this,[i,this,p_label]()
          {
              QPalette palette=p_label[i]->palette();
              QColor color=palette.color(QPalette::WindowText);
              qDebug()<<"color"<<color;
              QColor selected_color=QColorDialog::getColor(color,this,"Choose Text color");
              if(selected_color.isValid())
              {
                  palette.setColor(QPalette::WindowText,selected_color);
                  p_label[i]->setPalette(palette);
              }


          });
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
          layout->addWidget(color_text[i],i,3);
          layout->addWidget(color_background[i],i,4);

      }

      burst=new QLineEdit(this);

      burst->setPlaceholderText("Burst Time");



      layout->addWidget(burst,no_p,0,1,3);
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p+1,2,1,1);
      layout->setHorizontalSpacing(0);

  }
  else if(op==4 or op==5)
  {
      for(int i=0;i<no_p;i++)
      {
          p_label.push_back(new QLabel("P"+QString::number(i+1),this));
          p_label[i]->setFont(label_text);
          p_label[i]->setAutoFillBackground(true);

          p_time.push_back(new QLineEdit(this));
          p_time[i]->setPlaceholderText("Time");
          p_time[i]->setMaximumWidth(90);
          p_arrival_time.push_back(new QLineEdit(this));
          p_arrival_time[i]->setPlaceholderText("Arrival Time");
          p_arrival_time[i]->setMaximumWidth(90);
          p_priority.push_back(new QLineEdit(this));
          p_priority[i]->setPlaceholderText("Priority");
          p_priority[i]->setMaximumWidth(90);
          color_text.push_back(new QPushButton("Text color",this));
          color_background.push_back(new QPushButton("BG color",this));


          connect(color_text[i],&QPushButton::clicked,this,[i,this,p_label]()
          {
              QPalette palette=p_label[i]->palette();
              QColor color=palette.color(QPalette::WindowText);
              qDebug()<<"color"<<color;
              QColor selected_color=QColorDialog::getColor(color,this,"Choose Text color");
              if(selected_color.isValid())
              {
                  palette.setColor(QPalette::WindowText,selected_color);
                  p_label[i]->setPalette(palette);
              }


          });
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
          layout->addWidget(color_text[i],i,4);
          layout->addWidget(color_background[i],i,5);

      }
      layout->setHorizontalSpacing(0);
      submit=new QPushButton("Submit",this);
      layout->addWidget(submit,no_p,2,1,1);

  }



}
