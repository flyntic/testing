#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "deftest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    stTesting *testing;
    QString answer;
public slots:
   void nextQuestion()
    {
        testing->setAnswer(answer);
        testing->next();
        repaintTest();

    };
   void prevQuestion()
    {
        testing->prev();
        repaintTest();

    };
   void setAnswer();

public:
   void repaintTest();

};
#endif // WIDGET_H
