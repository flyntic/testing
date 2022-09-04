#ifndef DEFTEST_H
#define DEFTEST_H
#include <QVector>
#include <QMessageBox>
#include <QFile>
typedef enum
{
    radiobut=1,
    checkbox=2,
    edit
}enTypeAnswer;

struct stQuestion
{
    QString text;
    enTypeAnswer typeAnswer;
    QVector<QString> answers;
    QString answer;

};

const QString strTopic="topic";
const QString strName="name";
const QString strType="type";
const QString strQuestion="question";
const QString strAnswer="answer";
const QString strRight="right";



struct stTest
{
    QString topic;
    QString name;
    QVector <stQuestion *> questions;

    QString findStr(QString str, QFile * file)
    {
      QString find(" ");
      QString line;

        line = file->readLine();
        if (!line.contains(str))
        {
            // do something
        }
        else
        {   find=line.remove(str);

        }

    return find;
   }
public:
    stTest(QString _file)
    {
        QFile *file=new QFile();
        if (!QFile::exists(_file))
        {
            QMessageBox msgBox;
            msgBox.setText("Невозможно открыть файл с тестом");
            msgBox.exec();

        }
        else
        {
        file->setFileName(_file);
        file->open( QFileDevice::ReadOnly);

        QString line;

        topic=findStr(strTopic,file);
        name=findStr(strName,file);

        do
        {
           stQuestion *q=new stQuestion();
           do{
           q->text=findStr(strQuestion,file);
           }while((q->text==" ")&&(!file->atEnd()));
           QString strtype =findStr(strType,file);
           if (strtype.contains('c')!=0) q->typeAnswer=checkbox;
           if (strtype.contains('r')!=0) q->typeAnswer=radiobut;
           if (strtype.contains('e')!=0) q->typeAnswer=edit;

           do
           {
               QString ans=findStr(strAnswer,file);
               if ((ans==" ")&&(q->answers.length()>0)) break;
               if(ans!=" ")
                 q->answers.push_back(ans);

           } while   (!file->atEnd() );

           q->answer=" ";//findStr(strRight,file);
           questions.push_back(q);
        }
        while   (!file->atEnd());


        }
        file->close();
    }
};

struct stTesting
{
    stTest test;
    QString name;
    int nCurrentQuestion;
  //  QVector<QString> answers;
public:
    stTesting(QString _name,QString _file):name(_name),test(_file)
    {
      nCurrentQuestion=0;
      //answers.clear();
    }
   /* void addAnswer(QString _answer)
    {
        answers[nCurrentQuestion]=_answer;
    }*/
    void next(){if(++nCurrentQuestion>=test.questions.length())nCurrentQuestion=test.questions.length()-1;}
    void prev(){if (nCurrentQuestion--<=0)nCurrentQuestion=0;}
    QString getQuestion(){return test.questions[nCurrentQuestion]->text;}
    enTypeAnswer getTypeAnswer(){return test.questions[nCurrentQuestion]->typeAnswer;}
    QVector<QString> getAnswers(){return test.questions[nCurrentQuestion]->answers;}
    void setAnswer(QString answer){ test.questions[nCurrentQuestion]->answer=answer;}

};

#endif // DEFTEST_H
