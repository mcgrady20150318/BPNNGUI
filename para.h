#ifndef PARA_H
#define PARA_H

#include <QString>


class Para
{
public:
    Para();

    /*Dataset Para*/
    int Data;
    int TrainData;
    int TestData;

    /*BP Para*/
    int In;
    int Neuron;
    int Out;
    double LearningRate;//learning rate
    double Momentum;//Momentum Term

    /*End Para*/
    int Epochs;
    double EndAccuracy; //accuarcy

    /*File Para*/
    QString inputFilename;
    QString wFilename;
    QString vFilename;
    QString logFilename;

private:

};

#endif // PARA_H
