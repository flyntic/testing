#include "wTesting.h"
#include "ui_wTesting.h"

#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    testing= new stTesting("Иванов", "test.txt");
    ui->labelNameTopicText->setText(QString("Тема ")+ testing->test.topic+ "  Тест "+ testing->test.name+"  Тестируемый "+ testing->name);

    ui->labelQuestion->setText(testing->getQuestion());

    QCheckBox * r=new QCheckBox(ui->frame_Answer);
    QPoint p(r->geometry().x(),r->geometry().y());
    //ui->frame_Answer->children()
    delete(r);

    if (testing->getTypeAnswer()==checkbox)
    {
        QCheckBox *r;

        for(auto a:testing->getAnswers())
        {
            r=new QCheckBox(ui->frame_Answer);
            r->setText(a);
            r->setGeometry(p.x(),p.y(),r->geometry().width(),r->geometry().height());
            p.setY(p.y()+20);
        }

    }
    else
        if (testing->getTypeAnswer()==radiobut)
        {
            QRadioButton *r;

            for(auto a:testing->getAnswers())
            {
                r=new QRadioButton(ui->frame_Answer);
                r->setText(a);
                r->setGeometry(p.x(),p.y(),r->geometry().width(),r->geometry().height());
                p.setY(p.y()+20);
            }


        }
   else
        if (testing->getTypeAnswer()==edit)
            {
              QLineEdit *l;
              l=new QLineEdit(ui->frame_Answer);

            }

}

Widget::~Widget()
{
    delete ui;
}

