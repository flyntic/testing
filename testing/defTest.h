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
    QString rightAnswer;

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
      QString find(' ');
      QString line;
      do {
        line = file->readLine();
        if (!line.contains(str))
        {
            // do something
        }
        else
        {   find=line.remove(str);
            break;
        }
    } while (!file->atEnd());
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
        //if(!file->isOpen())
         //  MessageBox


       // }
       // else
       // {
        QString line;
        //


        topic=findStr(strTopic,file);
        name=findStr(strName,file);

        do
        {
           stQuestion *q=new stQuestion();
           q->text=findStr(strQuestion,file);
           QString strtype =findStr(strType,file);
           if (strtype.contains('c')!=0) q->typeAnswer=checkbox;
           if (strtype.contains('r')!=0) q->typeAnswer=radiobut;
           if (strtype.contains('e')!=0) q->typeAnswer=edit;


           do
           {
               QString ans=findStr(strAnswer,file);
               if (ans==' ') break;

               q->answers.push_back(ans);

           } while   (!file->atEnd() );

           q->rightAnswer=findStr(strRight,file);
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
    QVector<QString> answers;
public:
    stTesting(QString _name,QString _file):name(_name),test(_file)
    {
      nCurrentQuestion=0;
      answers.clear();
    }
    void addAnswer(QString _answer)
    {
        answers[nCurrentQuestion]=_answer;
    }
    void next(){}
    void prev(){}
    QString getQuestion(){return test.questions[nCurrentQuestion]->text;}
    enTypeAnswer getTypeAnswer(){return test.questions[nCurrentQuestion]->typeAnswer;}
    QVector<QString> getAnswers(){return test.questions[nCurrentQuestion]->answers;}

};

#endif // DEFTEST_H
