#include "wTesting.h"
#include "ui_wTesting.h"

#include <QVector>
#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    testing= new stTesting("Тема","test.txt");

    connect(ui->pb_Next, SIGNAL(clicked()) ,this,SLOT(nextQuestion()));
    connect(ui->pb_Prev, SIGNAL(clicked()) ,this,SLOT(prevQuestion()));
    repaintTest();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::setAnswer()
{
      if (testing->getTypeAnswer()==checkbox)
        {
          QCheckBox *r=qobject_cast<QCheckBox*>(QObject::sender());
          answer=r->text();
         }
      else
      if (testing->getTypeAnswer()==radiobut)
        {
          QRadioButton *r=qobject_cast<QRadioButton*>(QObject::sender());
          answer=r->text();
         }
      else
          if (testing->getTypeAnswer()==edit)
            {
              QLineEdit *r=qobject_cast<QLineEdit*>(QObject::sender());
              answer=r->text();
             }


       // answer=QObject::sender().Text();

}

void Widget::repaintTest()
{  static QVector<QObject*> checkboxs;
    int n_l=checkboxs.length();
    for(int i=0;i<n_l;i++)
        delete(checkboxs[n_l-1-i]);
    checkboxs.clear();
    ui->labelNameTopicText->setText("Предмет " + testing->test.topic+ "  Тема "+ testing->test.name+"  Тестируемый"+ testing->name);

    ui->labelQuestion->setText(testing->getQuestion());
    QCheckBox * r=new QCheckBox(ui->frame_Answer);
    QPoint p(r->geometry().x(),r->geometry().y());
    delete(r);



    if (testing->getTypeAnswer()==checkbox)
    {
        QCheckBox *r;
        QVector<QString> answers=testing->getAnswers();
        for(auto a:answers)
        {
            r=new QCheckBox(ui->frame_Answer);
            connect(r,SIGNAL(clicked()),SLOT(setAnswer()));
            r->setText(a);
            r->setGeometry(p.x(),p.y(),r->geometry().width(),r->geometry().height());
            p.setY(p.y()+20);
            checkboxs.push_back(r);
        }

    }
    else
        if (testing->getTypeAnswer()==radiobut)
        {
            QRadioButton *r;
            QVector<QString> answers=testing->getAnswers();
            for(auto a:answers)
            {
                r=new QRadioButton(ui->frame_Answer);
                connect(r,SIGNAL(clicked()),SLOT(setAnswer()));
                r->setText(a);
                r->setGeometry(p.x(),p.y(),r->geometry().width(),r->geometry().height());
                p.setY(p.y()+20);
                checkboxs.push_back(r);
            }


        }
   else
        if (testing->getTypeAnswer()==edit)
            {
              QLineEdit *l;

              l=new QLineEdit(ui->frame_Answer);
              connect(l,SIGNAL(textChanged(QString)),SLOT(setAnswer()));
              checkboxs.push_back(l);
            }
}


