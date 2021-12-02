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

private slots:
    void backButton_clicked();

    void update();
};

#endif // STATISTICWINDOW_H
