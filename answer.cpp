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

void Answer::set_model(QVector<Interval>intervals)
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
    float from=0;
    for(int i=0;i<intervals.size();i++)
    {
        if(from!=intervals[i].getFrom())
        {

             QLabel *label=new QLabel("",this);
             QLabel *rulerr=new QLabel(QString::number(intervals[i].getFrom()),this);
             label->setMinimumWidth(100*(intervals[i].getFrom()-from));
             rulerr->setMinimumWidth(100*(intervals[i].getFrom()-from));
             label->setMaximumWidth(100*(intervals[i].getFrom()-from));
             rulerr->setMaximumWidth(100*(intervals[i].getFrom()-from));
             label->setMaximumHeight(50);
             label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
             rulerr->setAlignment(Qt::AlignRight);
             layout2->addWidget(label);
             ruler->addWidget(rulerr);


        }
        p_lister.push_back(new QLabel(intervals[i].getProcess().getName(),this));
        p_lister[i]->setAutoFillBackground(true);

        QPalette palette;
        QColor color(intervals[i].getProcess().getRGB()[0],intervals[i].getProcess().getRGB()[1],intervals[i].getProcess().getRGB()[2]);
        palette.setColor(QPalette::Window,color);
//        p_lister[i]->setGeometry(i*100,0,100,100);
//        holder->addWidget(p_lister[i]);
        p_ruler.push_back(new QLabel(QString::number(intervals[i].getTo()),this));
        p_lister[i]->setPalette(palette);

        p_lister[i]->setMinimumWidth(100*(intervals[i].getTo()-intervals[i].getFrom()));
        p_ruler[i]->setMinimumWidth(100*(intervals[i].getTo()-intervals[i].getFrom()));
        p_lister[i]->setMaximumWidth(100*(intervals[i].getTo()-intervals[i].getFrom()));
        p_ruler[i]->setMaximumWidth(100*(intervals[i].getTo()-intervals[i].getFrom()));
        p_lister[i]->setMaximumHeight(50);
        p_lister[i]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        p_ruler[i]->setAlignment(Qt::AlignRight);
        layout2->addWidget(p_lister[i]);
        ruler->addWidget(p_ruler[i]);
        from=intervals[i].getTo();
//        p_lister[i]->setMinimumWidth(100);


//        p_lister[i]->setParent(holder);
    }




}
