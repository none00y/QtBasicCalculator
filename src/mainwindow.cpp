#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
static double calcVal = 0.0f;
static double memory = 0.0f;
static bool isSaved = false;
enum operation {
    none,add,substract,divide,multiply
};
char opTrigger = operation::none;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* numButtons[10];
    for(int  i = 0; i < 10; i++ )
    {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        connect(numButtons[i],SIGNAL(released()),this,SLOT(NumButtonPressed()));
    }
    connect(ui->Add,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Substract,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Equals,SIGNAL(released()),this,SLOT(EqualsButtonPressed()));
    connect(ui->SignChange,SIGNAL(released()),this,SLOT(SignButtonPressed()));
    connect(ui->MemAdd,SIGNAL(released()),this,SLOT(MemoryButtonPressed()));
    connect(ui->MemClear,SIGNAL(released()),this,SLOT(MemoryButtonPressed()));
    connect(ui->MemRead,SIGNAL(released()),this,SLOT(MemoryButtonPressed()));
    connect(ui->Clear,SIGNAL(released()),this,SLOT(ClearButtonPressed()));
}
void MainWindow::NumButtonPressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0)||(displayVal.toDouble() == 0.0 ))
    {
        ui->Display->setText(buttonVal);
    }
    else
    {
        QString newVal = displayVal + buttonVal;
        double newdblVal = newVal.toDouble();
        ui->Display->setText(QString::number(newdblVal,'G',10));
    }
}
void MainWindow::MathButtonPressed()
{
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton* button = (QPushButton*)sender();
    QString buttonVal = button->text();
    if(QString::compare(buttonVal,"/",Qt::CaseInsensitive) == 0)
        opTrigger = operation::divide;
    else if(QString::compare(buttonVal,"*",Qt::CaseInsensitive) == 0)
        opTrigger = operation::multiply;
    else if(QString::compare(buttonVal,"+",Qt::CaseInsensitive) == 0)
        opTrigger = operation::add;
    else if(QString::compare(buttonVal,"-",Qt::CaseInsensitive) == 0)
        opTrigger = operation::substract;
    ui->Display->setText("");
}
void MainWindow::EqualsButtonPressed()
{
    QString displayVal = ui->Display->text();
    double disVal = displayVal.toDouble();
    double solution = 0;
    switch(opTrigger)
    {
       case operation::add:
           solution = calcVal + disVal;
        break;
        case operation::multiply:
            solution = calcVal * disVal;
         break;
        case operation::divide:
        if(disVal!= 0)
            solution = calcVal / disVal;
        else
        {
            solution = 0;
        }
         break;
        case operation::substract:
            solution = calcVal - disVal;
         break;
        case operation::none:
            solution = disVal;
    }
    calcVal = solution;
    ui->Display->setText(QString::number(solution));
}
void MainWindow::SignButtonPressed()
{
    QString displayVal = ui->Display->text();
   static QRegularExpression reg("[-]?[0-9.]*");
   QRegularExpressionMatch match = reg.match(displayVal);
   if(match.hasMatch())
   {
       double dblDisplayValSign = -1 * displayVal.toDouble();
       ui->Display->setText(QString::number(dblDisplayValSign));
   }

}
void MainWindow::MemoryButtonPressed()
{
    QPushButton* button = (QPushButton*)sender();
    QString buttonVal = button->text();
    if(QString::compare(buttonVal,"M+",Qt::CaseInsensitive)==0)
    {
        memory = ui->Display->text().toDouble();
        isSaved = true;
    }
    else if(isSaved && QString::compare(buttonVal,"M",Qt::CaseInsensitive)==0)
    {
        ui->Display->setText(QString::number(memory));
    }
    else if(isSaved && QString::compare(buttonVal,"M-",Qt::CaseInsensitive)==0)
    {
        memory = 0.0;
        isSaved = false;
    }
}
void MainWindow::ClearButtonPressed()
{
    ui->Display->setText("0");
    calcVal = 0.0;
    memory = 0.0;
    isSaved = false;
}
MainWindow::~MainWindow()
{
    delete ui;
}

