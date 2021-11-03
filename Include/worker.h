#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>

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
};

#endif // WORKER_H
