#include "worker.h"

infoPLC_t infoPLC;
outputPLC_t outputPLC;

Worker::Worker(QObject *parent) : QObject(parent)
{
    myTimer = new QTimer(this);
    //myPlc = new PlcS7(PLC_IP.toStdString().c_str(), PLC_RACK, PLC_SLOT);
    //myPlc = new PlcS7("192.168.137.10", 0 , 1);
    myPlc = new PlcS7();

    /* Set default value */
    strcpy(infoPLC.MODULE_TYPE_NAME, "");
    strcpy(infoPLC.SERIAL_NUMBER, "");
    strcpy(infoPLC.AS_NAME, "");
    strcpy(infoPLC.COPYRIGHT, "");
    strcpy(infoPLC.MODULE_NAME, "");
    infoPLC.IS_CONNECTED = false;

    connect(myTimer, SIGNAL(timeout()), this, SLOT(update()));

    myTimer->start(200);

    qDebug() << static_cast<int>(myPlc->isConnect());
}

Worker::~Worker()
{
    delete myPlc;
    delete myTimer;
}

void Worker::connectToPlc()
{
    if (myPlc->isConnect() == false)
    {
        myPlc->setParms(PLC_IP.toStdString().c_str(), PLC_RACK, PLC_SLOT);
        if(myPlc->connect() == 0)
        {
            qDebug("Connected successful");
            myPlc->getPlcInfo();
            strcpy(infoPLC.MODULE_TYPE_NAME, myPlc->plcInfo.ModuleTypeName);
            strcpy(infoPLC.SERIAL_NUMBER, myPlc->plcInfo.SerialNumber);
            strcpy(infoPLC.AS_NAME, myPlc->plcInfo.ASName);
            strcpy(infoPLC.COPYRIGHT, myPlc->plcInfo.Copyright);
            strcpy(infoPLC.MODULE_NAME, myPlc->plcInfo.ModuleName);
            infoPLC.IS_CONNECTED = true;
            emit updatePLCInfo();
        }
    }
    qDebug() << static_cast<int>(myPlc->isConnect());
}

void Worker::disconnectFromPlc()
{
    if (myPlc->isConnect())
    {
        if(myPlc->disconnect() == 0)
        {
            strcpy(infoPLC.MODULE_TYPE_NAME, "");
            strcpy(infoPLC.SERIAL_NUMBER, "");
            strcpy(infoPLC.AS_NAME, "");
            strcpy(infoPLC.COPYRIGHT, "");
            strcpy(infoPLC.MODULE_NAME, "");
            emit updatePLCInfo();
            infoPLC.IS_CONNECTED = false;
        }
    }
    qDebug() << static_cast<int>(myPlc->isConnect());
}

void Worker::update()
{
    /* Reading PLC output */
    // mutex ?!!!!!!!!!!!!
    if (myPlc->isConnect())
    {
        inputPLC.I0_0 = myPlc->readI(0, 0);
        inputPLC.I0_1 = myPlc->readI(0, 1);
        inputPLC.I0_2 = myPlc->readI(0, 2);
        inputPLC.I0_3 = myPlc->readI(0, 3);
        inputPLC.I0_4 = myPlc->readI(0, 4);
        inputPLC.I0_5 = myPlc->readI(0, 5);
        inputPLC.I0_6 = myPlc->readI(0, 6);
        inputPLC.I0_7 = myPlc->readI(0, 7);

        outputPLC.QB1 = myPlc->readQB_SInt(1);
        outputPLC.QB2 = myPlc->readQB_USInt(2);
        outputPLC.QW3 = myPlc->readQW_Int(3);
        outputPLC.QW5 = myPlc->readQW_UInt(5);
        outputPLC.QD7 = myPlc->readQD_Real(7);
        outputPLC.QD11 = myPlc->readQD_Real(11);
    }

}

void Worker::setOutput0_0()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_0, 0, 0);
    }
}
void Worker::setOutput0_1()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_1, 0, 1);
    }
}
void Worker::setOutput0_2()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_2, 0, 2);
    }
}
void Worker::setOutput0_3()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_3, 0, 3);
    }
}
void Worker::setOutput0_4()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_4, 0, 4);
    }
}
void Worker::setOutput0_5()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_5, 0, 5);
    }
}
void Worker::setOutput0_6()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_6, 0, 6);
    }
}
void Worker::setOutput0_7()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_7, 0, 7);
    }
}
void Worker::setOutputB1()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeIB_SInt(outputPLC.QB1, 1);
    }
}
void Worker::setOutputB2()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeIB_USInt(outputPLC.QB2, 2);
    }
}
void Worker::setOutputW3()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeIW_Int(outputPLC.QW3, 3);
    }
}
void Worker::setOutputW5()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeIW_UInt(outputPLC.QW5, 5);
    }
}
void Worker::setOutputD7()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeID_Real(outputPLC.QD7, 7);
    }
}
void Worker::setOutputD11()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeID_Real(outputPLC.QD11, 11);
    }
}
