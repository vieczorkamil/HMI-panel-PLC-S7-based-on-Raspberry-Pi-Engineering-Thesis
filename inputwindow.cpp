#include "inputwindow.h"
#include "ui_inputwindow.h"

Inputwindow::Inputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inputwindow)
{
    ui->setupUi(this);

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
}

Inputwindow::~Inputwindow()
{
    delete ui;
}

void Inputwindow::backButton_clicked()
{
    emit backToHomeScreen();
}
