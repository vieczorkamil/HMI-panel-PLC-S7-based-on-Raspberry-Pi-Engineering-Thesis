#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QWidget>
#include <QString>

#include "configPLC.h"

namespace Ui {
class Inputwindow;
}

class Inputwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Inputwindow(QWidget *parent = nullptr);
    ~Inputwindow();

private:
    Ui::Inputwindow *ui;

signals:
    void backToHomeScreen();

    void connectToPlc();
    void disconnectFromPlc();

    void changeInput0_0();
    void changeInput0_1();
    void changeInput0_2();
    void changeInput0_3();
    void changeInput0_4();
    void changeInput0_5();
    void changeInput0_6();
    void changeInput0_7();

    void changeInputB1();
    void changeInputB2();
    void changeInputW3();
    void changeInputW5();
    void changeInputD7();
    void changeInputD11();


private slots:
    void backButton_clicked();

    void switchInput0_0_changed(int);
    void switchInput0_1_changed(int);
    void switchInput0_2_changed(int);
    void switchInput0_3_changed(int);
    void switchInput0_4_changed(int);
    void switchInput0_5_changed(int);
    void switchInput0_6_changed(int);
    void switchInput0_7_changed(int);

    void inputB1Button_clicked();
    void inputB2Button_clicked();
    void inputW3Button_clicked();
    void inputW5Button_clicked();
    void inputD7Button_clicked();
    void inputD11Button_clicked();

    void connectButton_clicked();
    void disconnectButton_clicked();
};

#endif // INPUTWINDOW_H
