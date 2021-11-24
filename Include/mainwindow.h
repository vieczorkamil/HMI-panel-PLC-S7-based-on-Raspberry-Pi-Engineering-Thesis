#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>

#include "worker.h"
#include "inputwindow.h"
#include "outputwindow.h"

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
    QThread myThread;
    Worker myWorker;

    bool mixer;
    QTimer *animationTimer;

    int inputTestScreen_INDEX = 1;
    int outputTestScreen_INDEX = 2;

private slots:
    void closeButton_clicked();
    void backToHomeScreen();
    void inputTestButton_clicked();
    void outputTestButton_clicked();
    void on_V1Button_clicked();
    void on_V2Button_clicked();
    void on_V3Button_clicked();
    void on_V4Button_clicked();
    void on_mixerONButton_clicked();
    void on_heaterONButton_clicked();

    void updateAnimation();
};

#endif // MAINWINDOW_H
