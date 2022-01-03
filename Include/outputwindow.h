#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QWidget>

#include "configPLC.h"
#include "hmi_tag.h"

namespace Ui {
class Outputwindow;
}

class Outputwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Outputwindow(QWidget *parent = nullptr);
    ~Outputwindow();

private:
    Ui::Outputwindow *ui;

signals:
    void backToHomeScreen();
    void exit();
    void goToMainScreen();
    void goToInfoScreen();
    void goToInputScreen();
    void goToOutputScreen();

    void changeOutput0_0();
    void changeOutput0_1();
    void changeOutput0_2();
    void changeOutput0_3();
    void changeOutput0_4();
    void changeOutput0_5();
    void changeOutput0_6();
    void changeOutput0_7();

    void changeOutputB1();
    void changeOutputB2();
    void changeOutputW3();
    void changeOutputW5();
    void changeOutputD7();
    void changeOutputD11();

private slots:
    void backButton_clicked();
    void mainScreenButton_clicked();
    void infoScreenButton_clicked();
    void inputScreenButton_clicked();
    void outputScreenButton_clicked();
    void updatePLCInfo();

    void switchOutput0_0_changed(int);
    void switchOutput0_1_changed(int);
    void switchOutput0_2_changed(int);
    void switchOutput0_3_changed(int);
    void switchOutput0_4_changed(int);
    void switchOutput0_5_changed(int);
    void switchOutput0_6_changed(int);
    void switchOutput0_7_changed(int);

    void outputB1Button_clicked();
    void outputB2Button_clicked();
    void outputW3Button_clicked();
    void outputW5Button_clicked();
    void outputD7Button_clicked();
    void outputD11Button_clicked();
};

#endif // OUTPUTWINDOW_H
