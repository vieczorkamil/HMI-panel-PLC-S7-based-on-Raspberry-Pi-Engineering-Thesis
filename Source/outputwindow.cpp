#include "outputwindow.h"
#include "ui_outputwindow.h"

#define LED_OFF(led) ui->led->setCheckState(Qt::Unchecked)
#define LED_ON(led) ui->led->setCheckState(Qt::Checked)

Outputwindow::Outputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outputwindow)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    /* Set default value */
    ui->ModuleTypeName->setText(QString::fromUtf8(infoPLC.MODULE_TYPE_NAME));
    ui->SerialNumber->setText(QString::fromUtf8(infoPLC.SERIAL_NUMBER));
    ui->ASName->setText(QString::fromUtf8(infoPLC.AS_NAME));
    ui->Copyright->setText(QString::fromUtf8(infoPLC.COPYRIGHT));
    ui->ModuleName->setText(QString::fromUtf8(infoPLC.MODULE_NAME));

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));

    /* update */
    connect(myTimer, SIGNAL(timeout()), this, SLOT(update()));
    myTimer->start(300);
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

void Outputwindow::update()
{
    if(outputPLC.Q0_0)
        LED_ON(switchOutput0_0);
    else
        LED_OFF(switchOutput0_0);

    if(outputPLC.Q0_1)
        LED_ON(switchOutput0_1);
    else
        LED_OFF(switchOutput0_1);

    if(outputPLC.Q0_2)
        LED_ON(switchOutput0_2);
    else
        LED_OFF(switchOutput0_2);

    if(outputPLC.Q0_3)
        LED_ON(switchOutput0_3);
    else
        LED_OFF(switchOutput0_3);

    if(outputPLC.Q0_4)
        LED_ON(switchOutput0_4);
    else
        LED_OFF(switchOutput0_4);

    if(outputPLC.Q0_5)
        LED_ON(switchOutput0_5);
    else
        LED_OFF(switchOutput0_5);

    if(outputPLC.Q0_6)
        LED_ON(switchOutput0_6);
    else
        LED_OFF(switchOutput0_6);

    if(outputPLC.Q0_7)
        LED_ON(switchOutput0_7);
    else
        LED_OFF(switchOutput0_7);

    ui->outputB1->setText(QString::number(outputPLC.QB1));
    ui->outputB2->setText(QString::number(outputPLC.QB2));
    ui->outputW3->setText(QString::number(outputPLC.QW3));
    ui->outputW5->setText(QString::number(outputPLC.QW5));
    ui->outputD7->setText(QString::number(static_cast<double>(outputPLC.QD7),'f', 2));
    ui->outputD11->setText(QString::number(static_cast<double>(outputPLC.QD11),'f', 2));

}
