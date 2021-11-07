#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QWidget>
#include <QTimer>

#include "configPLC.h"

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

    QTimer *myTimer;

signals:
    void backToHomeScreen();

private slots:
    void backButton_clicked();
    void updatePLCInfo();
    void update();
};

#endif // OUTPUTWINDOW_H
