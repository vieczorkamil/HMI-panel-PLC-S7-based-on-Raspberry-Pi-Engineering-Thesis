#include "outputwindow.h"
#include "ui_outputwindow.h"

infoPLC_t infoPLC;

#define LED_OFF(led) ui->led->setCheckState(Qt::Unchecked)
#define LED_ON(led) ui->led->setCheckState(Qt::Checked)

Outputwindow::Outputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outputwindow)
{
    ui->setupUi(this);

    /* Set default value */

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
    connect(ui->mainButton, SIGNAL(clicked()), this, SLOT(mainScreenButton_clicked()));
    connect(ui->infoButton, SIGNAL(clicked()), this, SLOT(infoScreenButton_clicked()));
    connect(ui->inputButton, SIGNAL(clicked()), this, SLOT(inputScreenButton_clicked()));
    connect(ui->outputButton, SIGNAL(clicked()), this, SLOT(outputScreenButton_clicked()));

    connect(ui->switchOutput0_0, SIGNAL(stateChanged(int)), this, SLOT(switchOutput0_0_changed(int)));
    connect(ui->switchOutput0_1, SIGNAL(stateChanged(int)), this, SLOT(switchOutput0_1_changed(int)));
    connect(ui->switchOutput0_2, SIGNAL(stateChanged(int)), this, SLOT(switchOutput0_2_changed(int)));
    connect(ui->switchOutput0_3, SIGNAL(stateChanged(int)), this, SLOT(switchOutput0_3_changed(int)));
    connect(ui->switchOutput0_4, SIGNAL(stateChanged(int)), this, SLOT(switchOutput0_4_changed(int)));
    connect(ui->switchOutput0_5, SIGNAL(stateChanged(int)), this, SLOT(switchOutput0_5_changed(int)));
    connect(ui->switchOutput0_6, SIGNAL(stateChanged(int)), this, SLOT(switchOutput0_6_changed(int)));
    connect(ui->switchOutput0_7, SIGNAL(stateChanged(int)), this, SLOT(switchOutput0_7_changed(int)));

    connect(ui->outputB1Button, SIGNAL(clicked()), this, SLOT(outputB1Button_clicked()));
    connect(ui->outputB2Button, SIGNAL(clicked()), this, SLOT(outputB2Button_clicked()));
    connect(ui->outputW3Button, SIGNAL(clicked()), this, SLOT(outputW3Button_clicked()));
    connect(ui->outputW5Button, SIGNAL(clicked()), this, SLOT(outputW5Button_clicked()));
    connect(ui->outputD7Button, SIGNAL(clicked()), this, SLOT(outputD7Button_clicked()));
    connect(ui->outputD11Button, SIGNAL(clicked()), this, SLOT(outputD11Button_clicked()));
}

Outputwindow::~Outputwindow()
{
    delete ui;
}

void Outputwindow::backButton_clicked()
{
    emit exit();
}

void Outputwindow::mainScreenButton_clicked()
{
    emit goToMainScreen();
}

void Outputwindow::infoScreenButton_clicked()
{
    emit goToInfoScreen();
}
void Outputwindow::inputScreenButton_clicked()
{
    emit goToInputScreen();
}
void Outputwindow::outputScreenButton_clicked()
{
    emit goToOutputScreen();
}

void Outputwindow::updatePLCInfo()
{
}

void Outputwindow::switchOutput0_0_changed(int arg)
{
    // mutex !?
    Q0_0.VALUE = arg;
    emit changeOutput0_0();
}

void Outputwindow::switchOutput0_1_changed(int arg)
{
    // mutex !?
    Q0_1.VALUE = arg;
    emit changeOutput0_1();
}

void Outputwindow::switchOutput0_2_changed(int arg)
{
    // mutex !?
    Q0_2.VALUE = arg;
    emit changeOutput0_2();
}

void Outputwindow::switchOutput0_3_changed(int arg)
{
    // mutex !?
    Q0_3.VALUE = arg;
    emit changeOutput0_3();
}

void Outputwindow::switchOutput0_4_changed(int arg)
{
    // mutex !?
    Q0_4.VALUE = arg;
    emit changeOutput0_4();
}

void Outputwindow::switchOutput0_5_changed(int arg)
{
    // mutex !?
    Q0_5.VALUE = arg;
    emit changeOutput0_5();
}

void Outputwindow::switchOutput0_6_changed(int arg)
{
    // mutex !?
    Q0_6.VALUE = arg;
    emit changeOutput0_6();
}

void Outputwindow::switchOutput0_7_changed(int arg)
{
    // mutex !?
    Q0_7.VALUE = arg;
    emit changeOutput0_7();
}

void Outputwindow::outputB1Button_clicked()
{
    //mutex !?
    QB1.VALUE = static_cast<int8_t>(ui->outputB1->value());
    emit changeOutputB1();
}

void Outputwindow::outputB2Button_clicked()
{
    //mutex !?
    QB2.VALUE = static_cast<uint8_t>(ui->outputB2->value());
    emit changeOutputB2();
}

void Outputwindow::outputW3Button_clicked()
{
    //mutex !?
    QW3.VALUE = static_cast<int16_t>(ui->outputW3->value());
    emit changeOutputW3();
}

void Outputwindow::outputW5Button_clicked()
{
    //mutex !?
    QW5.VALUE = static_cast<uint16_t>(ui->outputW5->value());
    emit changeOutputW5();
}

void Outputwindow::outputD7Button_clicked()
{
    //mutex !?
    QD7.VALUE = static_cast<float>(ui->outputD7->value());
    emit changeOutputD7();
}

void Outputwindow::outputD11Button_clicked()
{
    //mutex !?
    QD11.VALUE = static_cast<float>(ui->outputD11->value());
    emit changeOutputD11();
}

