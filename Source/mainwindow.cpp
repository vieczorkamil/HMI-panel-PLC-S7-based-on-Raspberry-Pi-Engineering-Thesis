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

    /* Back to homeScreen SIGNAL - SLOT connection */
    connect(&inputTestScreen, SIGNAL(backToHomeScreen()), this, SLOT(backToHomeScreen()));
    connect(&outputTestScreen, SIGNAL(backToHomeScreen()), this, SLOT(backToHomeScreen()));

    /* Button's SIGNAL - SLOT connection */
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeButton_clicked()));
    connect(ui->inputTestButton, SIGNAL(clicked()), this, SLOT(inputTestButton_clicked()));
    connect(ui->outputTestButton, SIGNAL(clicked()), this, SLOT(outputTestButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeButton_clicked()
{
    this->close();
}

void MainWindow::backToHomeScreen()
{
    ui->mainScreen->setCurrentIndex(ui->mainScreen->indexOf(ui->homeScreen)); // set homeScreen as default
}

void MainWindow::inputTestButton_clicked()
{
    ui->mainScreen->setCurrentIndex(inputTestScreen_INDEX);
}

void MainWindow::outputTestButton_clicked()
{
    ui->mainScreen->setCurrentIndex(inputTestScreen_INDEX);
}
