#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    int inputTestScreen_INDEX = 1;
    int outputTestScreen_INDEX = 2;

private slots:
    void closeButton_clicked();
    void inputTestButton_clicked();
    void outputTestButton_clicked();
};

#endif // MAINWINDOW_H
