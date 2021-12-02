#ifndef SETPOINTWINDOW_H
#define SETPOINTWINDOW_H

#include <QWidget>
#include <QTimer>

#include "configPLC.h"
#include "hmi_tag.h"

namespace Ui {
class SetPointwindow;
}

class SetPointwindow : public QWidget
{
    Q_OBJECT

public:
    explicit SetPointwindow(QWidget *parent = nullptr);
    ~SetPointwindow();

private:
    Ui::SetPointwindow *ui;

    QTimer *myTimer;

signals:
    void backToHomeScreen();

    void updateLevel1SP();
    void updateLevel2SP();
    void updateTimeSP();
    void updateTemperatureSP();

private slots:
    void backButton_clicked();

    void setLevel1Button_clicked();
    void setTimeButton_clicked();
    void setTemperatureButton_clicked();

    void update();
};

#endif // SETPOINTWINDOW_H
