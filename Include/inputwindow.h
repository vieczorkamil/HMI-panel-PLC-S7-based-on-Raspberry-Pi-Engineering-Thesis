#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QWidget>
#include <QString>
#include <QTimer>

#include "configPLC.h"
#include "hmi_tag.h"

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

    QTimer *myTimer;

signals:
    void backToHomeScreen();

    void connectToPlc();
    void disconnectFromPlc();

private slots:
    void backButton_clicked();

    void connectButton_clicked();
    void disconnectButton_clicked();

    void update();
};

#endif // INPUTWINDOW_H
