#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QWidget>

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
};

#endif // INPUTWINDOW_H
