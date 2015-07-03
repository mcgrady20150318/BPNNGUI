#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include "para.h"
#include "bp.h"


class WorkerThread : public QThread
{
Q_OBJECT

public:
    WorkerThread();
    ~WorkerThread();
    Para para;

protected:

    void run();

signals:

    void emitStatus(QString);
    void emitFinished();

private slots:

    void updatePara(Para);

};

#endif // WORKERTHREAD_H
