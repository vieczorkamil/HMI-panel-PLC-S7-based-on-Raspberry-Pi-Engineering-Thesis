#include "inputwindow.h"
#include "ui_inputwindow.h"

#include <QDebug>

Inputwindow::Inputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inputwindow)
{
    ui->setupUi(this);

    /* Set default value */
    ui->inputIP->setText(PLC_IP);
    ui->inputRACK->setValue(PLC_RACK);
    ui->inputSLOT->setValue(PLC_SLOT);

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));

    connect(ui->switchInput0_0, SIGNAL(stateChanged(int)), this, SLOT(switchInput0_0_changed(int)));
    connect(ui->switchInput0_1, SIGNAL(stateChanged(int)), this, SLOT(switchInput0_1_changed(int)));
    connect(ui->switchInput0_2, SIGNAL(stateChanged(int)), this, SLOT(switchInput0_2_changed(int)));
    connect(ui->switchInput0_3, SIGNAL(stateChanged(int)), this, SLOT(switchInput0_3_changed(int)));
    connect(ui->switchInput0_4, SIGNAL(stateChanged(int)), this, SLOT(switchInput0_4_changed(int)));
    connect(ui->switchInput0_5, SIGNAL(stateChanged(int)), this, SLOT(switchInput0_5_changed(int)));
    connect(ui->switchInput0_6, SIGNAL(stateChanged(int)), this, SLOT(switchInput0_6_changed(int)));
    connect(ui->switchInput0_7, SIGNAL(stateChanged(int)), this, SLOT(switchInput0_7_changed(int)));

    connect(ui->inputB1Button, SIGNAL(clicked()), this, SLOT(inputB1Button_clicked()));
    connect(ui->inputB2Button, SIGNAL(clicked()), this, SLOT(inputB2Button_clicked()));
    connect(ui->inputW3Button, SIGNAL(clicked()), this, SLOT(inputW3Button_clicked()));
    connect(ui->inputW5Button, SIGNAL(clicked()), this, SLOT(inputW5Button_clicked()));
    connect(ui->inputD7Button, SIGNAL(clicked()), this, SLOT(inputD7Button_clicked()));
    connect(ui->inputD11Button, SIGNAL(clicked()), this, SLOT(inputD11Button_clicked()));

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton_clicked()));
}

Inputwindow::~Inputwindow()
{
    delete ui;
}

void Inputwindow::backButton_clicked()
{
    emit backToHomeScreen();
}

void Inputwindow::switchInput0_0_changed(int arg)
{
    // mutex !?
    if(arg)
        I0_0 = true;
    else
        I0_0 = false;
    emit changeInput0_0();
}

void Inputwindow::switchInput0_1_changed(int arg)
{
    // mutex !?
    if(arg)
        I0_1 = true;
    else
        I0_1 = false;
    emit changeInput0_1();
}

void Inputwindow::switchInput0_2_changed(int arg)
{
    // mutex !?
    if(arg)
        I0_2 = true;
    else
        I0_2 = false;
    emit changeInput0_2();
}

void Inputwindow::switchInput0_3_changed(int arg)
{
    // mutex !?
    if(arg)
        I0_3 = true;
    else
        I0_3 = false;
    emit changeInput0_3();
}

void Inputwindow::switchInput0_4_changed(int arg)
{
    // mutex !?
    if(arg)
        I0_4 = true;
    else
        I0_4 = false;
    emit changeInput0_4();
}

void Inputwindow::switchInput0_5_changed(int arg)
{
    // mutex !?
    if(arg)
        I0_5 = true;
    else
        I0_5 = false;
    emit changeInput0_5();
}

void Inputwindow::switchInput0_6_changed(int arg)
{
    // mutex !?
    if(arg)
        I0_6 = true;
    else
        I0_6 = false;
    emit changeInput0_6();
}

void Inputwindow::switchInput0_7_changed(int arg)
{
    // mutex !?
    if(arg)
        I0_7 = true;
    else
        I0_7 = false;
    emit changeInput0_7();
}

void Inputwindow::inputB1Button_clicked()
{
    //mutex !?
    IB1 = static_cast<int8_t>(ui->inputB1->value());
    emit changeInputB1();
}

void Inputwindow::inputB2Button_clicked()
{
    //mutex !?
    IB2 = static_cast<uint8_t>(ui->inputB2->value());
    emit changeInputB2();
}

void Inputwindow::inputW3Button_clicked()
{
    //mutex !?
    IW3 = static_cast<int16_t>(ui->inputW3->value());
    emit changeInputW3();
}

void Inputwindow::inputW5Button_clicked()
{
    //mutex !?
    IW5 = static_cast<uint16_t>(ui->inputW5->value());
    emit changeInputW5();
}

void Inputwindow::inputD7Button_clicked()
{
    //mutex !?
    ID7 = static_cast<float>(ui->inputD7->value());
    emit changeInputD7();
}

void Inputwindow::inputD11Button_clicked()
{
    //mutex !?
    ID11 = static_cast<float>(ui->inputD11->value());
    emit changeInputD11();
}

void Inputwindow::connectButton_clicked()
{
    PLC_IP = ui->inputIP->toPlainText();
    PLC_RACK = ui->inputRACK->value();
    PLC_SLOT = ui->inputSLOT->value();

    if(ui->connectButton->text() == "CONNECT")
    {
        ui->connectButton->setText("DISCONNECT");
        emit connectToPlc();
    }
    else
    {
        ui->connectButton->setText("CONNECT");
        emit disconnectFromPlc();
    }
}


