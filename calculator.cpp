#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
double mem_pos = 0.0;
double mem_neg = 0.0;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){

        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()) ,this , SLOT(NumPressed()));

    }
    connect(ui->Button_add,SIGNAL(released()) ,this , SLOT(MathButtonPressed()));
    connect(ui->Button_sub,SIGNAL(released()) ,this , SLOT(MathButtonPressed()));
    connect(ui->Button_mul,SIGNAL(released()) ,this , SLOT(MathButtonPressed()));
    connect(ui->Button_div,SIGNAL(released()) ,this , SLOT(MathButtonPressed()));

    connect(ui->Button_eq,SIGNAL(released()) ,this , SLOT(EqualButton()));
    connect(ui->Button_sign,SIGNAL(released()) ,this , SLOT(ChangeSign()));
    connect(ui->Button_AC,SIGNAL(released()) ,this , SLOT(clear()));
    connect(ui->Button_Mp, SIGNAL(released()) , this , SLOT(memory_add()));
    connect(ui->Button_Mn, SIGNAL(released()) , this , SLOT(memory_sub()));
    connect(ui->Button_decimal, SIGNAL(released()) , this , SLOT(add_decimal()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){

    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayVal = ui->Display->text();

    QString newVal = displayVal + butval;
    ui->Display->setText(newVal);
    double dblNewVal = newVal.toDouble();
    double temp = 999999999999999;
    if(!((dblNewVal >((-1)*temp)) && (dblNewVal <(temp)))){
        clear();
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    mulTrigger = false;
    subTrigger = false;
    addTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive)==0){
        divTrigger = true;
    }
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive)==0){
        mulTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive)==0){
        addTrigger = true;
    }
    else if(QString::compare(butVal, "-", Qt::CaseInsensitive)==0){
        subTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButton(){

    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger){
        solution = calcVal + dblDisplayVal;
    }
    else if(subTrigger){
        solution = calcVal - dblDisplayVal;
    }
    else if(mulTrigger){
        solution = calcVal * dblDisplayVal;
    }
    else if(divTrigger){
        solution = calcVal / dblDisplayVal;
    }else{
        //Display (M+ val) - (M-val)
        solution = mem_pos - mem_neg;
        mem_pos = 0.0;
        mem_neg = 0.0;
    }

    ui->Display->setText(QString::number(solution));

}

void Calculator::ChangeSign(){

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal *= -1;
    ui->Display->setText(QString::number(dblDisplayVal,'g',16));
}

void Calculator::clear(){

    ui->Display->clear();
    double dblDisplayVal = 0;
    ui->Display->setText(QString::number(dblDisplayVal,'g',16));

    mem_pos = 0.0;
    mem_neg = 0.0;
}

void Calculator::memory_add(){

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    mem_pos+= dblDisplayVal;

    ui->Display->setText("0");
}

void Calculator::memory_sub(){

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    mem_neg+= dblDisplayVal;

    ui->Display->setText("0");

}

void Calculator::add_decimal(){

    QString temp = ui->Display->text();
    if(!(temp.contains(".",Qt::CaseInsensitive))){
        QString temp1 = temp + '.';
        ui->Display->setText(temp1);
    }
}





