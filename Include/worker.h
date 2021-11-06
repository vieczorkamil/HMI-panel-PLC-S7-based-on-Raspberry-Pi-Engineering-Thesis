#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>

#include "configPLC.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    QTimer *myTimer;

    explicit Worker(QObject *parent = nullptr);
    ~Worker();

signals:
    void updateResult();

public slots:
    void update();

    void setInput0_0();
    void setInput0_1();
    void setInput0_2();
    void setInput0_3();
    void setInput0_4();
    void setInput0_5();
    void setInput0_6();
    void setInput0_7();

    void setInputB1();
    void setInputB2();
    void setInputW3();
    void setInputW5();
    void setInputD7();
    void setInputD11();
};

#endif // WORKER_H
