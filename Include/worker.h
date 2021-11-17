#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <cstring>

#include "configPLC.h"
#include "plcS7.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    QTimer *myTimer;
    PlcS7 *myPlc;

    explicit Worker(QObject *parent = nullptr);
    ~Worker();

signals:
    void updateResult();
    void updatePLCInfo();

public slots:
    void connectToPlc();
    void disconnectFromPlc();

    void update();

    void setOutput0_0();
    void setOutput0_1();
    void setOutput0_2();
    void setOutput0_3();
    void setOutput0_4();
    void setOutput0_5();
    void setOutput0_6();
    void setOutput0_7();

    void setOutputB1();
    void setOutputB2();
    void setOutputW3();
    void setOutputW5();
    void setOutputD7();
    void setOutputD11();
};

#endif // WORKER_H
