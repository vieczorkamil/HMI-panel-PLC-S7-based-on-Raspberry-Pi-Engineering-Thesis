#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QWidget>

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

signals:
    void backToHomeScreen();

private slots:
    void backButton_clicked();
    void showButton_clicked();
    void updatePLCInfo();
};

#endif // OUTPUTWINDOW_H
