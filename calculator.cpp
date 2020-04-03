#include "calculator.h"
#include "ui_calculator.h"

double calcValue = 0.0;
bool divTrigerred = false;
bool mulTrigerred = false;
bool addTrigerred = false;
bool subTrigerred = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcValue));

    QPushButton *numButtons[10];

    for(int i=0; i<10; ++i){
        QString butName = "Button_" + QString::number(i);

        numButtons[i] = Calculator::findChild<QPushButton *>(butName);

        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Decimal_Point, SIGNAL(released()), this, SLOT(DecimalPressed()));

    connect(ui->Addition, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Subtraction, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Multiplication, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Division, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualPressed()));

    connect(ui->Change_Sign, SIGNAL(released()), this, SLOT(ChangeSignPressed()));

    connect(ui->All_Clear, SIGNAL(released()), this, SLOT(AllClearPressed()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator :: NumPressed(){

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    QString displayValue = ui->Display->text();

    if((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0)){

        ui->Display->setText(butVal);

    }
    else{

        QString newVal = displayValue + butVal;

        double dblNewVal = newVal.toDouble();

        ui->Display->setText(QString::number(dblNewVal, 'g',16));

    }
}

void Calculator :: DecimalPressed(){

    static int countDec =0;

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    countDec++;

    QString displayValue = ui->Display->text();

    if(countDec==1){
        ui->Display->setText(displayValue+butVal);
    }
    else{
        ui->Display->setText(displayValue);
    }
}

void Calculator :: OperatorPressed(){

    divTrigerred = false;
    mulTrigerred = false;
    addTrigerred = false;
    subTrigerred = false;

    QString displayValue = ui->Display->text();

    calcValue = displayValue.toDouble();

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    if(QString :: compare( butVal, "/", Qt :: CaseInsensitive)==0){

        divTrigerred=true;

    }
    else if(QString :: compare( butVal, "*", Qt :: CaseInsensitive)==0){

        mulTrigerred=true;

    }
    else if(QString :: compare( butVal, "+", Qt :: CaseInsensitive)==0){

        addTrigerred=true;

    }
    else if(QString :: compare( butVal, "-", Qt :: CaseInsensitive)==0){

        subTrigerred=true;

    }

    ui->Display->setText("");

}

void Calculator :: EqualPressed(){

    double solution = 0.0;

    int flag = 0;

    QString displayValue = ui->Display->text();

    double dblDisplayVal = displayValue.toDouble();

    if(divTrigerred || mulTrigerred || addTrigerred || subTrigerred){

        if(divTrigerred && (dblDisplayVal != 0 || dblDisplayVal != 0.0)){

            solution = calcValue / dblDisplayVal;

        }
        else if(divTrigerred && (dblDisplayVal == 0 || dblDisplayVal == 0.0)){

            flag = 1;

        }
        else if(mulTrigerred){

            solution = calcValue * dblDisplayVal;

        }
        else if(addTrigerred){

            solution = calcValue + dblDisplayVal;

        }
        else if(subTrigerred){

            solution = calcValue - dblDisplayVal;

        }
    }

    if(flag == 1){

        ui->Display->setText("Division by zero ERROR");

    }
    else{
        ui->Display->setText(QString :: number(solution));
    }
}

void Calculator :: ChangeSignPressed(){

    QString displayVal = ui->Display->text();

    QRegExp reg("[-]?[0-9.]*");

    if(reg.exactMatch(displayVal)){

        double dblDisplayVal = displayVal.toDouble();

        double dblDisplayValSign = (-1) * dblDisplayVal;

        ui->Display->setText(QString :: number(dblDisplayValSign));

    }

}

void Calculator :: AllClearPressed(){

    ui->Display->setText("0");

}

void Calculator :: ClearPressed(){

    QString displayVal = ui->Display->text();

    if(displayVal.length() == 0 || displayVal.length() == 1 ){

        ui->Display->setText("0");

    }
    else{

        QString displayStr = displayVal.left(displayVal.length()-1);

        ui->Display->setText(displayStr);

    }
}
