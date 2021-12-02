#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>

#include "worker.h"
#include "inputwindow.h"
#include "outputwindow.h"
#include "statisticwindow.h"
#include "setpointwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Inputwindow inputTestScreen;
    Outputwindow outputTestScreen;
    Statisticwindow statisticScreen;
    SetPointwindow setPointScreen;

    QThread myThread;
    Worker myWorker;

    bool mixer;
    QTimer *animationTimer;

    int inputTestScreen_INDEX = 1;
    int outputTestScreen_INDEX = 2;
    int statisticScreen_INDEX = 3;
    int setPointScreen_INDEX = 4;
signals:
    void setBitSTART();
    void resetBitSTART();

    void setBitRESET();
    void resetBitRESET();

    void changeBitSTOP();

private slots:
    void closeButton_clicked();
    void backToHomeScreen();
    void inputTestButton_clicked();
    void outputTestButton_clicked();
    void statsButton_clicked();
    void setPointButton_clicked();

    void updateAnimation();
    void on_startButton_clicked();
    void on_startButton_released();
    void on_stopButton_clicked();
    void on_showButton_clicked();
};

#endif // MAINWINDOW_H
