#include "setpointwindow.h"
#include "ui_setpointwindow.h"

SetPointwindow::SetPointwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetPointwindow)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
    connect(ui->setLevel1Button, SIGNAL(clicked()), this, SLOT(setLevel1Button_clicked()));
    connect(ui->setTimeButton, SIGNAL(clicked()), this, SLOT(setTimeButton_clicked()));
    connect(ui->setTemperatureButton, SIGNAL(clicked()), this, SLOT(setTemperatureButton_clicked()));

    /* update */
    connect(myTimer, SIGNAL(timeout()), this, SLOT(update()));
    myTimer->start(300);
}

SetPointwindow::~SetPointwindow()
{
    delete ui;
}

void SetPointwindow::backButton_clicked()
{
    emit backToHomeScreen();
}

void SetPointwindow::update()
{
    ui->level1->setNum(ui->level1Slider->value());
}

void SetPointwindow::setLevel1Button_clicked()
{
    LEVEL1SETPOINT.VALUE = ui->level1Slider->value();
    emit updateLevel1SP();
}

void SetPointwindow::setTimeButton_clicked()
{
    //TIMESETPOINT.VALUE = ui->timeSetPoint->value();
    emit updateTimeSP();
}

void SetPointwindow::setTemperatureButton_clicked()
{
    TEMPERATURESETPOINT.VALUE = ui->temperatureSetPoint->value();
    emit updateTemperatureSP();
}
