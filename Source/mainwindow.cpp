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
    connect(&inputTestScreen, SIGNAL(changeInput0_0()), &myWorker, SLOT(setInput0_0()));
    connect(&inputTestScreen, SIGNAL(changeInput0_1()), &myWorker, SLOT(setInput0_1()));
    connect(&inputTestScreen, SIGNAL(changeInput0_2()), &myWorker, SLOT(setInput0_2()));
    connect(&inputTestScreen, SIGNAL(changeInput0_3()), &myWorker, SLOT(setInput0_3()));
    connect(&inputTestScreen, SIGNAL(changeInput0_4()), &myWorker, SLOT(setInput0_4()));
    connect(&inputTestScreen, SIGNAL(changeInput0_5()), &myWorker, SLOT(setInput0_5()));
    connect(&inputTestScreen, SIGNAL(changeInput0_6()), &myWorker, SLOT(setInput0_6()));
    connect(&inputTestScreen, SIGNAL(changeInput0_7()), &myWorker, SLOT(setInput0_7()));
    /* Other inputs */
    connect(&inputTestScreen, SIGNAL(changeInputB1()), &myWorker, SLOT(setInputB1()));
    connect(&inputTestScreen, SIGNAL(changeInputB2()), &myWorker, SLOT(setInputB2()));
    connect(&inputTestScreen, SIGNAL(changeInputW3()), &myWorker, SLOT(setInputW3()));
    connect(&inputTestScreen, SIGNAL(changeInputW5()), &myWorker, SLOT(setInputW5()));
    connect(&inputTestScreen, SIGNAL(changeInputD7()), &myWorker, SLOT(setInputD7()));
    connect(&inputTestScreen, SIGNAL(changeInputD11()), &myWorker, SLOT(setInputD11()));
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
