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
    emit updateResult();
}
