#include "outputwindow.h"
#include "ui_outputwindow.h"

#define LED_OFF(led) ui->led->setCheckState(Qt::Unchecked)
#define LED_ON(led) ui->led->setCheckState(Qt::Checked)

Outputwindow::Outputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outputwindow)
{
    ui->setupUi(this);

    /* Set default value */
    ui->ModuleTypeName->setText(QString::fromUtf8(infoPLC.MODULE_TYPE_NAME));
    ui->SerialNumber->setText(QString::fromUtf8(infoPLC.SERIAL_NUMBER));
    ui->ASName->setText(QString::fromUtf8(infoPLC.AS_NAME));
    ui->Copyright->setText(QString::fromUtf8(infoPLC.COPYRIGHT));
    ui->ModuleName->setText(QString::fromUtf8(infoPLC.MODULE_NAME));

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));

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
    emit backToHomeScreen();
}

void Outputwindow::updatePLCInfo()
{
    ui->ModuleTypeName->setText(QString::fromUtf8(infoPLC.MODULE_TYPE_NAME));
    ui->SerialNumber->setText(QString::fromUtf8(infoPLC.SERIAL_NUMBER));
    ui->ASName->setText(QString::fromUtf8(infoPLC.AS_NAME));
    ui->Copyright->setText(QString::fromUtf8(infoPLC.COPYRIGHT));
    ui->ModuleName->setText(QString::fromUtf8(infoPLC.MODULE_NAME));
}

void Outputwindow::switchOutput0_0_changed(int arg)
{
    // mutex !?
    outputPLC.Q0_0 = arg;
    emit changeOutput0_0();
}

void Outputwindow::switchOutput0_1_changed(int arg)
{
    // mutex !?
    outputPLC.Q0_1 = arg;
    emit changeOutput0_1();
}

void Outputwindow::switchOutput0_2_changed(int arg)
{
    // mutex !?
    outputPLC.Q0_2 = arg;
    emit changeOutput0_2();
}

void Outputwindow::switchOutput0_3_changed(int arg)
{
    // mutex !?
    outputPLC.Q0_3 = arg;
    emit changeOutput0_3();
}

void Outputwindow::switchOutput0_4_changed(int arg)
{
    // mutex !?
    outputPLC.Q0_4 = arg;
    emit changeOutput0_4();
}

void Outputwindow::switchOutput0_5_changed(int arg)
{
    // mutex !?
    outputPLC.Q0_5 = arg;
    emit changeOutput0_5();
}

void Outputwindow::switchOutput0_6_changed(int arg)
{
    // mutex !?
    outputPLC.Q0_6 = arg;
    emit changeOutput0_6();
}

void Outputwindow::switchOutput0_7_changed(int arg)
{
    // mutex !?
    outputPLC.Q0_7 = arg;
    emit changeOutput0_7();
}

void Outputwindow::outputB1Button_clicked()
{
    //mutex !?
    outputPLC.QB1 = static_cast<int8_t>(ui->outputB1->value());
    emit changeOutputB1();
}

void Outputwindow::outputB2Button_clicked()
{
    //mutex !?
    outputPLC.QB2 = static_cast<uint8_t>(ui->outputB2->value());
    emit changeOutputB2();
}

void Outputwindow::outputW3Button_clicked()
{
    //mutex !?
    outputPLC.QW3 = static_cast<int16_t>(ui->outputW3->value());
    emit changeOutputW3();
}

void Outputwindow::outputW5Button_clicked()
{
    //mutex !?
    outputPLC.QW5 = static_cast<uint16_t>(ui->outputW5->value());
    emit changeOutputW5();
}

void Outputwindow::outputD7Button_clicked()
{
    //mutex !?
    outputPLC.QD7 = static_cast<float>(ui->outputD7->value());
    emit changeOutputD7();
}

void Outputwindow::outputD11Button_clicked()
{
    //mutex !?
    outputPLC.QD11 = static_cast<float>(ui->outputD11->value());
    emit changeOutputD11();
}

