#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myWorker.moveToThread(&myThread);
    myThread.start();

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

    /* Thread SIGNAL - SLOT connection */
    connect(&myThread, SIGNAL(finished()), myWorker.myTimer, SLOT(stop())); //zatrzymanie timera po zakończeniu wątku
    /* Connect and disconnect PLC */
    connect(&inputTestScreen, SIGNAL(connectToPlc()), &myWorker, SLOT(connectToPlc()));
    connect(&inputTestScreen, SIGNAL(disconnectFromPlc()), &myWorker, SLOT(disconnectFromPlc()));
    /* Input bite 0 */
    connect(&outputTestScreen, SIGNAL(changeOutput0_0()), &myWorker, SLOT(setOutput0_0()));
    connect(&outputTestScreen, SIGNAL(changeOutput0_1()), &myWorker, SLOT(setOutput0_1()));
    connect(&outputTestScreen, SIGNAL(changeOutput0_2()), &myWorker, SLOT(setOutput0_2()));
    connect(&outputTestScreen, SIGNAL(changeOutput0_3()), &myWorker, SLOT(setOutput0_3()));
    connect(&outputTestScreen, SIGNAL(changeOutput0_4()), &myWorker, SLOT(setOutput0_4()));
    connect(&outputTestScreen, SIGNAL(changeOutput0_5()), &myWorker, SLOT(setOutput0_5()));
    connect(&outputTestScreen, SIGNAL(changeOutput0_6()), &myWorker, SLOT(setOutput0_6()));
    connect(&outputTestScreen, SIGNAL(changeOutput0_7()), &myWorker, SLOT(setOutput0_7()));
    /* Other inputs */
    connect(&outputTestScreen, SIGNAL(changeOutputB1()), &myWorker, SLOT(setOutputB1()));
    connect(&outputTestScreen, SIGNAL(changeOutputB2()), &myWorker, SLOT(setOutputB2()));
    connect(&outputTestScreen, SIGNAL(changeOutputW3()), &myWorker, SLOT(setOutputW3()));
    connect(&outputTestScreen, SIGNAL(changeOutputW5()), &myWorker, SLOT(setOutputW5()));
    connect(&outputTestScreen, SIGNAL(changeOutputD7()), &myWorker, SLOT(setOutputD7()));
    connect(&outputTestScreen, SIGNAL(changeOutputD11()), &myWorker, SLOT(setOutputD11()));
    /* Update PLC info */
    connect(&myWorker, SIGNAL(updatePLCInfo()), &outputTestScreen, SLOT(updatePLCInfo()));
}

MainWindow::~MainWindow()
{
    myThread.quit();
    myThread.wait();
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
    ui->mainScreen->setCurrentIndex(outputTestScreen_INDEX);
}
