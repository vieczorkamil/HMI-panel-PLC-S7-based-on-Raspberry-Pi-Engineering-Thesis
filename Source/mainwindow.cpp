#include "mainwindow.h"
#include "ui_mainwindow.h"

#define ACTIVE_SCREEN(name)     ui->mainScreen->setCurrentIndex(ui->mainScreen->indexOf(ui->name))

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myWorker.moveToThread(&myThread);
    myThread.start();

    ui->mainScreen->setCurrentIndex(ui->mainScreen->indexOf(ui->homeScreen)); // set homeScreen as default

    /* ---------------------------------------------Add new screen--------------------------------------------- */
    ui->mainScreen->insertWidget(inputTestScreen_INDEX, &inputTestScreen);
    ui->mainScreen->insertWidget(outputTestScreen_INDEX, &outputTestScreen);
    ui->mainScreen->insertWidget(statisticScreen_INDEX, &statisticScreen);
    ui->mainScreen->insertWidget(setPointScreen_INDEX, &setPointScreen);

    /* Init UI value */
    ui->valveON1_img->setVisible(false);
    ui->valveON2_img->setVisible(false);
    ui->valveON3_img->setVisible(false);
    ui->valveON4_img->setVisible(false);
    ui->sensorON1_img->setVisible(false); //sensor 1
    ui->sensorON2_img->setVisible(false); //sensor 2
    ui->sensorON3_img->setVisible(false); //sensor 3

    {
        mixer = false;
        animationTimer = new QTimer(this);
        connect(animationTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
        animationTimer->start(300);
        ui->mixerON1_img->setVisible(false);
        ui->mixerON2_img->setVisible(false);
        ui->mixerON3_img->setVisible(false);
        ui->mixerON4_img->setVisible(false);
    }
    ui->heaterON_img->setVisible(false);
    ui->V1label->setVisible(false);
    ui->V2label->setVisible(false);
    ui->V3label->setVisible(false);
    ui->V4label->setVisible(false);
    ui->S1label->setVisible(false);
    ui->S2label->setVisible(false);
    ui->S3label->setVisible(false);

    /* ---------------------------------------------Other Screens SIGNAL - SLOT connection------------------------------------------ */
    connect(&inputTestScreen, SIGNAL(exit()), this, SLOT(closeApp()));
    connect(&inputTestScreen, SIGNAL(goToMainScreen()), this, SLOT(activeMainScreen()));
    connect(&inputTestScreen, SIGNAL(goToInfoScreen()), this, SLOT(activeInfoScreen()));
    connect(&inputTestScreen, SIGNAL(goToInputScreen()), this, SLOT(activeInputScreen()));
    connect(&inputTestScreen, SIGNAL(goToOutputScreen()), this, SLOT(activeOutputScreen()));

    connect(&outputTestScreen, SIGNAL(exit()), this, SLOT(closeApp()));
    connect(&outputTestScreen, SIGNAL(goToMainScreen()), this, SLOT(activeMainScreen()));
    connect(&outputTestScreen, SIGNAL(goToInfoScreen()), this, SLOT(activeInfoScreen()));
    connect(&outputTestScreen, SIGNAL(goToInputScreen()), this, SLOT(activeInputScreen()));
    connect(&outputTestScreen, SIGNAL(goToOutputScreen()), this, SLOT(activeOutputScreen()));

    connect(&statisticScreen, SIGNAL(exit()), this, SLOT(closeApp()));
    connect(&statisticScreen, SIGNAL(goToMainScreen()), this, SLOT(activeMainScreen()));
    connect(&statisticScreen, SIGNAL(goToInfoScreen()), this, SLOT(activeInfoScreen()));
    connect(&statisticScreen, SIGNAL(goToInputScreen()), this, SLOT(activeInputScreen()));
    connect(&statisticScreen, SIGNAL(goToOutputScreen()), this, SLOT(activeOutputScreen()));

    connect(&setPointScreen, SIGNAL(backToHomeScreen()), this, SLOT(backToHomeScreen()));

    /* ---------------------------------------------Button's SIGNAL - SLOT connection------------------------------------------------- */
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(closeApp()));
    connect(ui->mainButton, SIGNAL(clicked()), this, SLOT(activeMainScreen()));
    connect(ui->infoButton, SIGNAL(clicked()), this, SLOT(activeInfoScreen()));
    connect(ui->inputButton, SIGNAL(clicked()), this, SLOT(activeInputScreen()));
    connect(ui->outputButton, SIGNAL(clicked()), this, SLOT(activeOutputScreen()));

    /* ---------------------------------------------Thread SIGNAL - SLOT connection---------------------------------------------------- */
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
    /* Visulisation button */
    connect(this, SIGNAL(setBitSTART()), &myWorker, SLOT(setBitStart()));
    connect(this, SIGNAL(resetBitSTART()), &myWorker, SLOT(resetBitStart()));
    connect(this, SIGNAL(setBitRESET()), &myWorker, SLOT(setBitReset()));
    connect(this, SIGNAL(resetBitRESET()), &myWorker, SLOT(resetBitReset()));
    connect(this, SIGNAL(changeBitSTOP()), &myWorker, SLOT(changeBitStop()));
    /* Set points button */
    connect(&setPointScreen, SIGNAL(updateLevel1SP()), &myWorker, SLOT(updateLevel1SP()));
    connect(&setPointScreen, SIGNAL(updateLevel2SP()), &myWorker, SLOT(updateLevel2SP()));
    connect(&setPointScreen, SIGNAL(updateTimeSP()), &myWorker, SLOT(updateTimeSP()));
    connect(&setPointScreen, SIGNAL(updateTemperatureSP()), &myWorker, SLOT(updateTemperatureSP()));
    /* Update PLC info */
    connect(&myWorker, SIGNAL(updatePLCInfo()), &outputTestScreen, SLOT(updatePLCInfo()));
}

MainWindow::~MainWindow()
{
    myThread.quit();
    myThread.wait();
    delete ui;
}

void MainWindow::closeApp()
{
    this->close();
}
void MainWindow::activeMainScreen()
{
    ui->mainScreen->setCurrentIndex(ui->mainScreen->indexOf(ui->homeScreen));
}

void MainWindow::activeInfoScreen()
{
    ui->mainScreen->setCurrentIndex(statisticScreen_INDEX);
}

void MainWindow::activeInputScreen()
{
    ui->mainScreen->setCurrentIndex(inputTestScreen_INDEX);
}
void MainWindow::activeOutputScreen()
{
    ui->mainScreen->setCurrentIndex(outputTestScreen_INDEX);
}

void MainWindow::updateAnimation()
{
    static int mixerAnimation = 0;
    mixerAnimation++;
    if(mixerAnimation > 3)
        mixerAnimation = 0;
    if(MIXER.VALUE)
    {
        ui->mixerOFF_img->setVisible(false);
        if(mixerAnimation == 0)
        {
            ui->mixerON1_img->setVisible(true);
            ui->mixerON2_img->setVisible(false);
            ui->mixerON3_img->setVisible(false);
            ui->mixerON4_img->setVisible(false);
        }
        else if(mixerAnimation == 1)
        {
            ui->mixerON1_img->setVisible(false);
            ui->mixerON2_img->setVisible(true);
            ui->mixerON3_img->setVisible(false);
            ui->mixerON4_img->setVisible(false);
        }
        else if(mixerAnimation == 2)
        {
            ui->mixerON1_img->setVisible(false);
            ui->mixerON2_img->setVisible(false);
            ui->mixerON3_img->setVisible(true);
            ui->mixerON4_img->setVisible(false);
        }
        else if(mixerAnimation == 3)
        {
            ui->mixerON1_img->setVisible(false);
            ui->mixerON2_img->setVisible(false);
            ui->mixerON3_img->setVisible(false);
            ui->mixerON4_img->setVisible(true);
        }
    }
    else
    {
        ui->mixerOFF_img->setVisible(true);
        ui->mixerON1_img->setVisible(false);
        ui->mixerON2_img->setVisible(false);
        ui->mixerON3_img->setVisible(false);
        ui->mixerON4_img->setVisible(false);
    }

    ui->sensorON1_img->setVisible(SENSOR1.VALUE); //sensor 1
    ui->sensorON2_img->setVisible(SENSOR2.VALUE); //sensor 2
    ui->sensorON3_img->setVisible(SENSOR3.VALUE); //sensor 3
    ui->heaterON_img->setVisible(HEATER.VALUE); //heater
    ui->valveON1_img->setVisible(VALVE1.VALUE); //valve 1
    ui->valveON2_img->setVisible(VALVE2.VALUE); //valve 2
    ui->valveON3_img->setVisible(VALVE3.VALUE); //valve 3
    ui->valveON4_img->setVisible(VALVE4.VALUE); //valve 4
}

void MainWindow::on_startButton_clicked()
{
    emit setBitSTART();
}

void MainWindow::on_startButton_released()
{
    emit resetBitSTART();
}

void MainWindow::on_stopButton_clicked()
{
    emit changeBitSTOP();
}

void MainWindow::on_showButton_clicked()
{
    static bool state = false;
    state = !state;
    ui->V1label->setVisible(state);
    ui->V2label->setVisible(state);
    ui->V3label->setVisible(state);
    ui->V4label->setVisible(state);
    ui->S1label->setVisible(state);
    ui->S2label->setVisible(state);
    ui->S3label->setVisible(state);
    if(state)
        ui->showButton->setText("Hide index");
    else {
        ui->showButton->setText("Show index");
    }
}
