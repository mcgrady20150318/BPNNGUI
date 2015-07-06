#ifndef BP_H
#define BP_H

#include "para.h"

class BPNeuralNetwork{

private:

	/*Dataset Para*/
	int Data;
	int TrainData;
	int TestData;

	/*BP Para*/
	int In;
	int Neuron;
	int Out;
	double LearningRate;//learning rate
    double Momentum;

	/*End Para*/
	int Epochs;
	double EndAccuracy; //accuarcy

	/*Data Array*/
	double** data;
	double** d_in_train;
	double** d_out_train;
	double** d_in_test;
	double** d_out_test;

	double** w;
	double** v;
	double** dw;
	double** dv;

	double* o;
	double* OutputData;
	double* Minin;
	double* Maxin;
	double* Minout;
	double* Maxout;

    inline void splitData(int);

    inline double fnet(double);

    inline void computeO(int);

    inline void backUpdate(int);

    inline double predict(int);

    inline double computeTestMSE();

    inline double computeTestAccuracy();

    inline double computeTestCost();

    inline double computeTestRecallAndPrecision(char*);


public:

    //BPNeuralNetwork(int,int,int,int,int,int,double,int,double);
    BPNeuralNetwork();

    BPNeuralNetwork(Para);

	~BPNeuralNetwork();

    void loadData(char*);

	void initBPNetwork();

    void trainBPNetwork(char*);

    void writeNeuron(char*,char*);

//signals:

   // void emitLog(QString);




};

#endif // BP_H
