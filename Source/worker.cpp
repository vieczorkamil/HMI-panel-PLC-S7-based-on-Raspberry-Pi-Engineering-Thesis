#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    myTimer = new QTimer(this);
    myPlc = new PlcS7(PLC_IP.toStdString().c_str(), PLC_RACK, PLC_SLOT);

    connect(myTimer, SIGNAL(timeout()), this, SLOT(update()));

    myTimer->start(200);
}

Worker::~Worker()
{
    delete myPlc;
    delete myTimer;
}

void Worker::connectToPlc()
{
    if (myPlc->isConnect() == false)
        myPlc->connect();
}

void Worker::disconnectFromPlc()
{
    if (myPlc->connect())
        myPlc->disconnect();
}

void Worker::update()
{
    /* Reading PLC output */
    //emit updateResult();
}

void Worker::setInput0_0()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeI(inputPLC.I0_0, 0, 0);
    }
    qDebug() << inputPLC.I0_0;
}
void Worker::setInput0_1()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeI(inputPLC.I0_1, 0, 1);
    }
}
void Worker::setInput0_2()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeI(inputPLC.I0_2, 0, 2);
    }
}
void Worker::setInput0_3()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeI(inputPLC.I0_3, 0, 3);
    }
}
void Worker::setInput0_4()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeI(inputPLC.I0_4, 0, 4);
    }
}
void Worker::setInput0_5()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeI(inputPLC.I0_5, 0, 5);
    }
}
void Worker::setInput0_6()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeI(inputPLC.I0_6, 0, 6);
    }
}
void Worker::setInput0_7()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeI(inputPLC.I0_7, 0, 7);
    }
}
void Worker::setInputB1()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeIB_SInt(inputPLC.IB1, 1);
    }
}
void Worker::setInputB2()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeIB_USInt(inputPLC.IB2, 2);
    }
}
void Worker::setInputW3()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeIW_Int(inputPLC.IW3, 3);
    }
}
void Worker::setInputW5()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeIW_UInt(inputPLC.IW5, 5);
    }
}
void Worker::setInputD7()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeID_Real(inputPLC.ID7, 7);
    }
}
void Worker::setInputD11()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeID_Real(inputPLC.ID11, 11);
    }
    qDebug() << inputPLC.ID11;
}
