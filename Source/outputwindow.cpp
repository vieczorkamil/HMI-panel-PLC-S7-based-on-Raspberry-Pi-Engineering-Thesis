#include "outputwindow.h"
#include "ui_outputwindow.h"

Outputwindow::Outputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outputwindow)
{
    ui->setupUi(this);
    ui->label->setText(QString::fromUtf8(infoPLC.MODULE_TYPE_NAME));

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
    connect(ui->showButton, SIGNAL(clicked()), this, SLOT(showButton_clicked()));
}

Outputwindow::~Outputwindow()
{
    delete ui;
}

void Outputwindow::backButton_clicked()
{
    emit backToHomeScreen();
}

void Outputwindow::showButton_clicked()
{
    ui->label->setText(QString::fromUtf8(infoPLC.MODULE_TYPE_NAME));
}

void Outputwindow::updatePLCInfo()
{
    ui->label->setText(QString::fromUtf8(infoPLC.MODULE_TYPE_NAME));
}

