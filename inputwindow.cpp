#include "inputwindow.h"
#include "ui_inputwindow.h"

Inputwindow::Inputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inputwindow)
{
    ui->setupUi(this);
}

Inputwindow::~Inputwindow()
{
    delete ui;
}
