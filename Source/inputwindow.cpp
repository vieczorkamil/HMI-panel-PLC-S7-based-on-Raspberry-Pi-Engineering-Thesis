#include "inputwindow.h"
#include "ui_inputwindow.h"

#include <QDebug>

#include "hmi_tag.h"

#define LED_OFF(led) ui->led->setCheckState(Qt::Unchecked)
#define LED_ON(led) ui->led->setCheckState(Qt::Checked)

inputPLC_t inputPLC; // extern typedef struct of PLC input

QString PLC_IP = "192.168.137.10";
int PLC_RACK = 0;
int PLC_SLOT = 1;
/*
QString PLC_IP = "";
int PLC_RACK = 0;
int PLC_SLOT = 0;
*/

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

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));

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
    emit backToHomeScreen();
}

void Inputwindow::update()
{
    //inputPLC.I0_0 ? LED_ON(switchInput0_0) : LED_OFF(switchInput0_0);
    I0_0.VALUE ? LED_ON(switchInput0_0) : LED_OFF(switchInput0_0);
    inputPLC.I0_1 ? LED_ON(switchInput0_1) : LED_OFF(switchInput0_1);
    inputPLC.I0_2 ? LED_ON(switchInput0_2) : LED_OFF(switchInput0_2);
    inputPLC.I0_3 ? LED_ON(switchInput0_3) : LED_OFF(switchInput0_3);
    inputPLC.I0_4 ? LED_ON(switchInput0_4) : LED_OFF(switchInput0_4);
    inputPLC.I0_5 ? LED_ON(switchInput0_5) : LED_OFF(switchInput0_5);
    inputPLC.I0_6 ? LED_ON(switchInput0_6) : LED_OFF(switchInput0_6);
    inputPLC.I0_7 ? LED_ON(switchInput0_7) : LED_OFF(switchInput0_7);

    ui->inputB1->setText(QString::number(inputPLC.IB1));
    ui->inputB2->setText(QString::number(inputPLC.IB2));
    ui->inputW3->setText(QString::number(inputPLC.IW3));
    ui->inputW5->setText(QString::number(inputPLC.IW5));
    ui->inputD7->setText(QString::number(static_cast<double>(inputPLC.ID7),'f', 2));
    ui->inputD11->setText(QString::number(static_cast<double>(inputPLC.ID11),'f', 2));
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

