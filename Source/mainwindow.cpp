#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainScreen->setCurrentIndex(ui->mainScreen->indexOf(ui->homeScreen)); // set homeScreen as default

    /* Add new screen */
    ui->mainScreen->insertWidget(inputTestScreen_INDEX, &inputTestScreen);
    ui->mainScreen->insertWidget(outputTestScreen_INDEX, &outputTestScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}
