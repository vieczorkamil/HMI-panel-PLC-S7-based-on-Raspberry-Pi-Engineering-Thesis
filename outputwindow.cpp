#include "outputwindow.h"
#include "ui_outputwindow.h"

Outputwindow::Outputwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Outputwindow)
{
    ui->setupUi(this);

    /* Button's SIGNAL - SLOT connection */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
}

Outputwindow::~Outputwindow()
{
    delete ui;
}

void Outputwindow::backButton_clicked()
{
    emit backToHomeScreen();
}
