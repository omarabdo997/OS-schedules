#include "answer.h"
#include <QTextEdit>
#include <QLabel>
#include <QScrollArea>
#include <vector>
#include <QHBoxLayout>
#include <QPushButton>
Answer::Answer(QWidget *parent) :
    QWidget(parent)
{
//        setMinimumSize(250,250);
//        QTextEdit *edit1=new QTextEdit(this);
}

Answer::~Answer()
{

}

void Answer::set_model()
{
    setMaximumHeight(100);
    setMinimumHeight(100);
    QPalette color1,color2;
    color1.setColor(QPalette::Window,Qt::red);
    color2.setColor(QPalette::Window,Qt::blue);
    std::vector<QLabel*>p_lister;
    std::vector<QLabel*>p_ruler;
//    QGridLayout *layout=new QGridLayout(this);

//    QWidget *holder=new QWidget(this);
    QVBoxLayout *main_layout=new QVBoxLayout(this);
    QHBoxLayout *layout2=new QHBoxLayout;
    QHBoxLayout *ruler=new QHBoxLayout;
    main_layout->addLayout(layout2);
    main_layout->addLayout(ruler);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0,50,0,0);
    layout2->setSpacing(0);
    ruler->setSpacing(0);
//    holder->setMinimumSize(200,200);
//    holder->move(500,500);

    for(int i=0;i<20;i++)
    {
        p_lister.push_back(new QLabel("P"+QString::number(i+1),this));
        p_lister[i]->setAutoFillBackground(true);
        if(i%2==0)
        {
            p_lister[i]->setPalette(color1);
        }
        else
        {
            p_lister[i]->setPalette(color2);
        }

//        p_lister[i]->setGeometry(i*100,0,100,100);
//        holder->addWidget(p_lister[i]);
        p_ruler.push_back(new QLabel(QString::number(i),this));
        p_lister[i]->setMinimumWidth(100*(i+1));
        p_ruler[i]->setMinimumWidth(100*(i+1));
        p_lister[i]->setMaximumHeight(50);
        p_lister[i]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        p_ruler[i]->setAlignment(Qt::AlignRight);
        layout2->addWidget(p_lister[i]);
        ruler->addWidget(p_ruler[i]);
//        p_lister[i]->setMinimumWidth(100);


//        p_lister[i]->setParent(holder);
    }




}
