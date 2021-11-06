#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    myTimer = new QTimer(this);

    connect(myTimer, SIGNAL(timeout()), this, SLOT(update()));

    myTimer->start(200);
}

Worker::~Worker()
{
}

void Worker::update()
{
    /* Reading PLC output */
    //emit updateResult();
}

void Worker::setInput0_0()
{
    qDebug() << inputPLC.I0_0;
}
void Worker::setInput0_1()
{

}
void Worker::setInput0_2()
{

}
void Worker::setInput0_3()
{

}
void Worker::setInput0_4()
{

}
void Worker::setInput0_5()
{

}
void Worker::setInput0_6()
{

}
void Worker::setInput0_7()
{

}
void Worker::setInputB1()
{

}
void Worker::setInputB2()
{

}
void Worker::setInputW3()
{

}
void Worker::setInputW5()
{

}
void Worker::setInputD7()
{

}
void Worker::setInputD11()
{
    qDebug() << inputPLC.ID11;
}
