#include "inputwindow.h"
#include "ui_inputwindow.h"

#include <QDebug>

#define LED_OFF(led) ui->led->setCheckState(Qt::Unchecked)
#define LED_ON(led) ui->led->setCheckState(Qt::Checked)

QString PLC_IP = "192.168.137.13";
int PLC_RACK = 0;
int PLC_SLOT = 1;

Inputwindow::Inputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inputwindow)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);

    /* Set default value */
    ui->inputIP->setText(PLC_IP);
    ui->inputRACK->setValue(PLC_RACK);
    ui->inputSLOT->setValue(PLC_SLOT);

    ui->disconnectButton->setEnabled(false);

    ui->connectionON_img->setVisible(false);
    ui->connectionOFF_img->setVisible(true);

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
    connect(ui->mainButton, SIGNAL(clicked()), this, SLOT(mainScreenButton_clicked()));
    connect(ui->infoButton, SIGNAL(clicked()), this, SLOT(infoScreenButton_clicked()));
    connect(ui->inputButton, SIGNAL(clicked()), this, SLOT(inputScreenButton_clicked()));
    connect(ui->outputButton, SIGNAL(clicked()), this, SLOT(outputScreenButton_clicked()));

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton_clicked()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(disconnectButton_clicked()));

    /* update */
    connect(myTimer, SIGNAL(timeout()), this, SLOT(update()));
    myTimer->start(300);
}

Inputwindow::~Inputwindow()
{
    delete ui;
}

void Inputwindow::backButton_clicked()
{
    emit exit();
}

void Inputwindow::mainScreenButton_clicked()
{
    emit goToMainScreen();
}

void Inputwindow::infoScreenButton_clicked()
{
    emit goToInfoScreen();
}
void Inputwindow::inputScreenButton_clicked()
{
    emit goToInputScreen();
}
void Inputwindow::outputScreenButton_clicked()
{
    emit goToOutputScreen();
}

void Inputwindow::update()
{
    //inputPLC.I0_0 ? LED_ON(switchInput0_0) : LED_OFF(switchInput0_0);
    I0_0.VALUE ? LED_ON(switchInput0_0) : LED_OFF(switchInput0_0);
    I0_1.VALUE ? LED_ON(switchInput0_1) : LED_OFF(switchInput0_1);
    I0_2.VALUE ? LED_ON(switchInput0_2) : LED_OFF(switchInput0_2);
    I0_3.VALUE ? LED_ON(switchInput0_3) : LED_OFF(switchInput0_3);
    I0_4.VALUE ? LED_ON(switchInput0_4) : LED_OFF(switchInput0_4);
    I0_5.VALUE ? LED_ON(switchInput0_5) : LED_OFF(switchInput0_5);
    I0_6.VALUE ? LED_ON(switchInput0_6) : LED_OFF(switchInput0_6);
    I0_7.VALUE ? LED_ON(switchInput0_7) : LED_OFF(switchInput0_7);

    ui->inputB1->setText(QString::number(IB1.VALUE));
    ui->inputB2->setText(QString::number(IB2.VALUE));
    ui->inputW3->setText(QString::number(IW3.VALUE));
    ui->inputW5->setText(QString::number(IW5.VALUE));
    ui->inputD7->setText(QString::number(static_cast<double>(ID7.VALUE),'f', 2));
    ui->inputD11->setText(QString::number(static_cast<double>(ID11.VALUE),'f', 2));

    infoPLC.IS_CONNECTED ? ui->connectionON_img->setVisible(true) : ui->connectionON_img->setVisible(false);
}

void Inputwindow::connectButton_clicked()
{
    PLC_IP = ui->inputIP->toPlainText();
    PLC_RACK = ui->inputRACK->value();
    PLC_SLOT = ui->inputSLOT->value();
    emit connectToPlc();
    ui->disconnectButton->setEnabled(true);
    ui->connectButton->setEnabled(false);
}

void Inputwindow::disconnectButton_clicked()
{
    emit disconnectFromPlc();
    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
}

