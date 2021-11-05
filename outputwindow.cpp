#include "outputwindow.h"
#include "ui_outputwindow.h"

Outputwindow::Outputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outputwindow)
{
    ui->setupUi(this);
}

Outputwindow::~Outputwindow()
{
    delete ui;
}
