#include "workerthread.h"

using namespace std;

WorkerThread::WorkerThread()
: QThread()
{


}

WorkerThread::~WorkerThread()
{
    terminate();
}


void WorkerThread::run(){

    char *inputFilePath;
    char *wFilePath;
    char *vFilePath;
    char *logFilePath;

    QByteArray f1 = para.inputFilename.toLatin1();
    inputFilePath = f1.data();

    QByteArray f2 = para.wFilename.toLatin1();
    wFilePath = f2.data();

    QByteArray f3 = para.vFilename.toLatin1();
    vFilePath = f3.data();

    QByteArray f4 = para.logFilename.toLatin1();
    logFilePath = f4.data();

    //BPNeuralNetwork bpnn(para.Data,para.TrainData,para.TestData,para.In,para.Neuron,para.Out,para.LearningRate,para.Epochs,para.EndAccuracy);
    BPNeuralNetwork bpnn(para);

    bpnn.loadData(inputFilePath);

    emit emitStatus("load data from " + para.inputFilename);

    QThread::sleep(2);

    emit emitStatus("BPNetowrk init!");

    QThread::sleep(2);

    bpnn.trainBPNetwork(logFilePath);

    emit emitStatus("BPNetwork Train successfully!Train Result is in file: " + para.logFilename);

    QThread::sleep(2);

    bpnn.writeNeuron(wFilePath,vFilePath);

    emit emitStatus("BPNetwork Model saved successfully!Model is in files: " + para.wFilename + " and " + para.vFilename);

    QThread::sleep(2);

    emit emitFinished();//make the run button works again

}


void WorkerThread::updatePara(Para p){

    para = p;

}

