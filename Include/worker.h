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
