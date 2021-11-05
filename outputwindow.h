#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QWidget>

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
};

#endif // OUTPUTWINDOW_H
