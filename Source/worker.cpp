#include "worker.h"
#include "hmi_tag.h"

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
        //inputPLC.I0_0 = myPlc->readI(0, 0);
        //I0_0.VALUE = myPlc->readI(I0_0.BYTE_DBNUMBER, I0_0.BIT_OFFSET);
        I0_0.VALUE = myPlc->readI(&I0_0);
        I0_1.VALUE = myPlc->readI(I0_1.BYTE_DBNUMBER, I0_1.BIT_OFFSET);
        I0_2.VALUE = myPlc->readI(I0_2.BYTE_DBNUMBER, I0_2.BIT_OFFSET);
        I0_3.VALUE = myPlc->readI(I0_3.BYTE_DBNUMBER, I0_3.BIT_OFFSET);
        I0_4.VALUE = myPlc->readI(I0_4.BYTE_DBNUMBER, I0_4.BIT_OFFSET);
        I0_5.VALUE = myPlc->readI(I0_5.BYTE_DBNUMBER, I0_5.BIT_OFFSET);
        I0_6.VALUE = myPlc->readI(I0_6.BYTE_DBNUMBER, I0_6.BIT_OFFSET);
        I0_7.VALUE = myPlc->readI(I0_7.BYTE_DBNUMBER, I0_7.BIT_OFFSET);
        //inputPLC.I0_1 = myPlc->readI(0, 1);
        //inputPLC.I0_2 = myPlc->readI(0, 2);
        //inputPLC.I0_3 = myPlc->readI(0, 3);
        //inputPLC.I0_4 = myPlc->readI(0, 4);
        //inputPLC.I0_5 = myPlc->readI(0, 5);
        //inputPLC.I0_6 = myPlc->readI(0, 6);
        //inputPLC.I0_7 = myPlc->readI(0, 7);

        IB1.VALUE = myPlc->readQB_SInt(IB1.BYTE_DBNUMBER);
        IB2.VALUE = myPlc->readIB_USInt(IB2.BYTE_DBNUMBER);
        IW3.VALUE = myPlc->readIW_Int(IW3.BYTE_DBNUMBER);
        IW5.VALUE = myPlc->readIW_UInt(IW5.BYTE_DBNUMBER);
        ID7.VALUE = myPlc->readID_Real(ID7.BYTE_DBNUMBER);
        ID11.VALUE = myPlc->readID_Real(ID11.BYTE_DBNUMBER);
    }

}

void Worker::setOutput0_0()
{
    if (myPlc->isConnect())
    {
        // mutex?
        myPlc->writeQ(outputPLC.Q0_0, 0, 0);
        myPlc->writeQ(Q0_0.VALUE, Q0_0.BYTE_DBNUMBER, Q0_0.BIT_OFFSET);
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
