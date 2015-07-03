#ifndef BP_H
#define BP_H

class BPNeuralNetwork{

private:
    //dsflfl

	/*Dataset Para*/
	int Data;
	int TrainData;
	int TestData;

	/*BP Para*/
	int In;
	int Neuron;
	int Out;
	double LearningRate;//learning rate

	/*End Para*/
	int Epochs;
	double EndAccuracy; //accuarcy

	/*Data Array*/
	//double data[Data][In+Out];
	//double d_in_train[TrainData][In],d_out_train[TrainData][Out],w[Neuron][In],v[Out][Neuron],dw[Neuron][In],dv[Out][Neuron];
	//double o[Neuron],OutputData[TrainData],Minin[In],Maxin[In],Minout[Out],Maxout[Out];
	//double d_in_test[TestData][In],d_out_test[TestData][Out];
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

    void splitData(int);

	double fnet(double);

	void computeO(int);

	void backUpdate(int);

	double predict(int);

	double computeTestMSE();

	double computeTestAccuracy();

	double computeTestCost();

	double computeTestRecallAndPrecision(char*);


public:

	BPNeuralNetwork(int,int,int,int,int,int,double,int,double);

	~BPNeuralNetwork();

    void loadData(char*);

	void initBPNetwork();

    void trainBPNetwork(char*);

    void writeNeuron(char*,char*);




};

#endif // BP_H
