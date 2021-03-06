#ifndef STATISTICWINDOW_H
#define STATISTICWINDOW_H

#include <QWidget>
#include <QTimer>

#include "configPLC.h"
#include "hmi_tag.h"

namespace Ui {
class Statisticwindow;
}

class Statisticwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Statisticwindow(QWidget *parent = nullptr);
    ~Statisticwindow();

private:
    Ui::Statisticwindow *ui;

    QTimer *myTimer;

signals:
    void backToHomeScreen();
    void exit();
    void goToMainScreen();
    void goToInfoScreen();
    void goToInputScreen();
    void goToOutputScreen();

private slots:
    void backButton_clicked();
    void mainScreenButton_clicked();
    void infoScreenButton_clicked();
    void inputScreenButton_clicked();
    void outputScreenButton_clicked();

    void update();
};

#endif // STATISTICWINDOW_H
