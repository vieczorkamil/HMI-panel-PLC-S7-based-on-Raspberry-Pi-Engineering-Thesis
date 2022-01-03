#include "statisticwindow.h"
#include "ui_statisticwindow.h"

Statisticwindow::Statisticwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statisticwindow)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
    connect(ui->mainButton, SIGNAL(clicked()), this, SLOT(mainScreenButton_clicked()));
    connect(ui->infoButton, SIGNAL(clicked()), this, SLOT(infoScreenButton_clicked()));
    connect(ui->inputButton, SIGNAL(clicked()), this, SLOT(inputScreenButton_clicked()));
    connect(ui->outputButton, SIGNAL(clicked()), this, SLOT(outputScreenButton_clicked()));

    /* update */
    connect(myTimer, SIGNAL(timeout()), this, SLOT(update()));
    myTimer->start(300);
}

Statisticwindow::~Statisticwindow()
{
    delete ui;
}

void Statisticwindow::backButton_clicked()
{
    emit exit();
}

void Statisticwindow::mainScreenButton_clicked()
{
    emit goToMainScreen();
}

void Statisticwindow::infoScreenButton_clicked()
{
    emit goToInfoScreen();
}
void Statisticwindow::inputScreenButton_clicked()
{
    emit goToInputScreen();
}
void Statisticwindow::outputScreenButton_clicked()
{
    emit goToOutputScreen();
}

void Statisticwindow::update()
{
    ui->levelProggresBar1->setValue(static_cast<int>(LEVEL1.VALUE));
    ui->levelProggresBar2->setValue(static_cast<int>(LEVEL2.VALUE));
    ui->temperatureBar->setValue(static_cast<int>(TEMPERATURE.VALUE));
    ui->temperatureValue->setText(QString::number(static_cast<double>(TEMPERATURE.VALUE),'f', 2));
}
