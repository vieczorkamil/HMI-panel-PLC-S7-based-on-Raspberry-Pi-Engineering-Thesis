#include "worker.h"
#include "hmi_tag.h"

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
        if (myPlc->connect() == 0)
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

            setOutput0_0();
            setOutput0_1();
            setOutput0_2();
            setOutput0_3();
            setOutput0_4();
            setOutput0_5();
            setOutput0_6();
            setOutput0_7();

            setOutputB1();
            setOutputB2();
            setOutputW3();
            setOutputW5();
            setOutputD7();
            setOutputD11();
        }
    }
    qDebug() << static_cast<int>(myPlc->isConnect());
}

void Worker::disconnectFromPlc()
{
    if (myPlc->isConnect())
    {
        if (myPlc->disconnect() == 0)
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
        //inputPLC.I0_0 = myPlc->readI(0, 0);
        //I0_0.VALUE = myPlc->readI(I0_0.BYTE_DBNUMBER, I0_0.BIT_OFFSET);
        //I0_0.VALUE = myPlc->readI(&I0_0);
        I0_0.VALUE = myPlc->readValue(&I0_0);
        I0_1.VALUE = myPlc->readValue(&I0_1);
        I0_2.VALUE = myPlc->readValue(&I0_2);
        I0_3.VALUE = myPlc->readValue(&I0_3);
        I0_4.VALUE = myPlc->readValue(&I0_4);
        I0_5.VALUE = myPlc->readValue(&I0_5);
        I0_6.VALUE = myPlc->readValue(&I0_6);
        //I0_7.VALUE = myPlc->readI(I0_7.BYTE_DBNUMBER, I0_7.BIT_OFFSET);
        I0_7.VALUE = myPlc->readValue(&I0_7);

        IB1.VALUE = myPlc->readValue(&IB1);
        IB2.VALUE = myPlc->readValue(&IB2);
        IW3.VALUE = myPlc->readValue(&IW3);
        IW5.VALUE = myPlc->readValue(&IW5);
        ID7.VALUE = myPlc->readValue(&ID7);
        ID11.VALUE = myPlc->readValue(&ID11);

        START.VALUE = myPlc->readValue(&START);
        SENSOR1.VALUE = myPlc->readValue(&SENSOR1);
        SENSOR2.VALUE = myPlc->readValue(&SENSOR2);
        SENSOR3.VALUE = myPlc->readValue(&SENSOR3);
        MIXER.VALUE = myPlc->readValue(&MIXER);
        HEATER.VALUE = myPlc->readValue(&HEATER);
        VALVE1.VALUE = myPlc->readValue(&VALVE1);
        VALVE2.VALUE = myPlc->readValue(&VALVE2);
        VALVE3.VALUE = myPlc->readValue(&VALVE3);
        VALVE4.VALUE = myPlc->readValue(&VALVE4);
        TEMPERATURE.VALUE = myPlc->readValue(&TEMPERATURE);
        LEVEL1.VALUE = myPlc->readValue(&LEVEL1);
        LEVEL2.VALUE = myPlc->readValue(&LEVEL2);
    }
}

void Worker::setOutput0_0()
{
    if (myPlc->isConnect())
    {
        // mutex?
        //myPlc->writeQ(Q0_0.VALUE, Q0_0.BYTE_DBNUMBER, Q0_0.BIT_OFFSET);
        myPlc->writeValue(&Q0_0);
    }
}
void Worker::setOutput0_1()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&Q0_1);
    }
}
void Worker::setOutput0_2()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&Q0_2);
    }
}
void Worker::setOutput0_3()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&Q0_3);
    }
}
void Worker::setOutput0_4()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&Q0_4);
    }
}
void Worker::setOutput0_5()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&Q0_5);
    }
}
void Worker::setOutput0_6()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&Q0_6);
    }
}
void Worker::setOutput0_7()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&Q0_7);
    }
}
void Worker::setOutputB1()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&QB1);
    }
}
void Worker::setOutputB2()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&QB2);
    }
}
void Worker::setOutputW3()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&QW3);
    }
}
void Worker::setOutputW5()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&QW5);
    }
}
void Worker::setOutputD7()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&QD7);
    }
}
void Worker::setOutputD11()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeValue(&QD11);
    }
}

void Worker::changeBitStart()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->toggleBit(&START);
    }
}
