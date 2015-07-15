#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include "bp.h"

using namespace std;

BPNeuralNetwork::BPNeuralNetwork(){}

//BPNeuralNetwork::BPNeuralNetwork(int d,int traindata,int testdata,int in,int neuron,int out,double alpha,int epo,double endaccuracy): Data(d), TrainData(traindata),TestData(testdata),In(in),Neuron(neuron),Out(out),LearningRate(alpha),Epochs(epo),EndAccuracy(endaccuracy){
BPNeuralNetwork::BPNeuralNetwork(Para para){
    //Para p -> input parameters

    Data = para.Data;

    TrainData = para.TrainData;

    TestData = para.TestData;

    In = para.In;

    Neuron = para.Neuron;

    Out = para.Out;

    LearningRate = para.LearningRate;

    Epochs = para.Epochs;

    EndAccuracy = para.EndAccuracy;

    Momentum = para.Momentum;

	int i,j;

	double rH = 1/sqrt( (double) In);
	double rO = 1/sqrt( (double) Neuron);

	data = new(double*[Data]);

	for(i=0;i<Data;i++){

		data[i] = new(double[In+Out]);

		for(j=0;j<In+Out;j++){

			data[i][j] = 0.0;
		}

	}


	d_in_train = new(double*[TrainData]);

	for(i=0;i<TrainData;i++){

		d_in_train[i] = new(double[In]);

		for(j=0;j<In;j++){

			d_in_train[i][j] = 0.0;
		}

	}


	d_out_train = new(double*[TrainData]);

	for(i=0;i<TrainData;i++){

		d_out_train[i] = new(double[Out]);

		for(j=0;j<Out;j++){

			d_out_train[i][j] = 0.0;
		}

	}

	d_in_test = new(double*[TestData]);

	for(i=0;i<TestData;i++){

		d_in_test[i] = new(double[In]);

		for(j=0;j<In;j++){

			d_in_test[i][j] = 0.0;
		}

	}

	d_out_test = new(double*[TestData]);

	for(i=0;i<TestData;i++){

		d_out_test[i] = new(double[Out]);

		for(j=0;j<Out;j++){

			d_out_test[i][j] = 0.0;
		}

	}

	w = new(double*[In]);

	for(i=0;i<In;i++){

		w[i] = new(double[Neuron]);

		for(j=0;j<Neuron;j++){

			w[i][j] = ( ( (double)(rand()%100)+1)/100  * 2 * rH ) - rH;

		}

	}

	v = new(double*[Neuron]);

	for(i=0;i<Neuron;i++){

		v[i] = new(double[Out]);

		for(j=0;j<Out;j++){

			v[i][j] = ( ( (double)(rand()%100)+1)/100  * 2 * rO ) - rO;

		}

	}

	dw = new(double*[In]);

	for(i=0;i<In;i++){

		dw[i] = new(double[Neuron]);

		for(j=0;j<Neuron;j++){

			dw[i][j] = 0.0;
		}

	}

	dv = new(double*[Neuron]);

	for(i=0;i<Neuron;i++){

		dv[i] = new(double[Out]);

		for(j=0;j<Out;j++){

			dv[i][j] = 0.0;
		}

	}


	o = new(double[Neuron]);

	for(i=0;i<Neuron;i++){

		o[i] = 0.0;

	}

	OutputData = new(double[TrainData]);

	for(i=0;i<TrainData;i++){

		OutputData[i] = 0.0;

	}

	Minin = new(double[In]);

	for(i=0;i<In;i++){

		Minin[i] = 0.0;

	}

	Maxin = new(double[In]);

	for(i=0;i<In;i++){

		Maxin[i] = 0.0;

	}

	Minout = new(double[Out]);

	for(i=0;i<Out;i++){

		Minout[i] = 0.0;

	}

	Maxout = new(double[Out]);

	for(i=0;i<Out;i++){

		Maxout[i] = 0.0;

	}


}


BPNeuralNetwork::~BPNeuralNetwork(){

	int i;

	delete[] o;
	delete[] OutputData;
	delete[] Minin;
	delete[] Maxin;
	delete[] Minout;
	delete[] Maxout;

	for(i=0;i<Data;i++){

		delete[] data[i];

	}

	delete[] data;


	for(i=0;i<TrainData;i++){

		delete[] d_in_train[i];
		delete[] d_out_train[i];

	}

	delete[] d_in_train;
	delete[] d_out_train;

	for(i=0;i<TestData;i++){

		delete[] d_in_test[i];
		delete[] d_out_test[i];

	}

	delete[] d_in_test;
	delete[] d_out_test;

	for(i=0;i<In;i++){

		delete[] w[i];
		delete[] dw[i];

	}

	delete[] w;
	delete[] dw;

	for(i=0;i<Neuron;i++){

		delete[] v[i];
		delete[] dv[i];

	}

	delete[] v;
	delete[] dv;


}

// read data from dataset file
void BPNeuralNetwork::loadData(char* filename){

	int i,j;

    ifstream infile(filename);

    string line;

    for(i=0;i<Data;i++){

        getline(infile, line);

        istringstream stream(line);

        string field;

        for(j=0;j<(In+Out);j++){

            getline(stream,field,',');

            data[i][j] = atof(field.c_str());


        }

    }

    infile.close();

}

void BPNeuralNetwork::splitData(int dataNum){

    //split the data into train and test for cross validation

    //total 10 groups data

    //dataNum means the dataNum-th data, make the data to be test data,other data to be train data

    int DataUnit = Data / 10;//total 10 groups

    int TestLowerBoundIndex = DataUnit * (dataNum - 1); // the test dataset lower bound index

    int TestUpperBoundIndex = DataUnit * dataNum - 1;// the test dataset upper bound index

	int i,j;

    for(i=0;i<Data;i++){

        for(j=0;j<In+Out;j++){

            if(i<TestLowerBoundIndex){

                if(j<In){

                    d_in_train[i][j] = data[i][j];

                }else{

                    d_out_train[i][j-In] = data[i][j];

                }

            }

            if(i >= TestLowerBoundIndex && i <= TestUpperBoundIndex){

                // test dataset

                if(j < In){

                    d_in_test[i-TestLowerBoundIndex][j] = data[i][j];

                }else{

                    d_out_test[i-TestLowerBoundIndex][j-In] = data[i][j];

                }

            }

            if(i>TestUpperBoundIndex){

                if(j<In){

                    d_in_train[i-TestUpperBoundIndex-1][j] = data[i][j];

                }else{

                    d_out_train[i-TestUpperBoundIndex-1][j-In] = data[i][j];

                }


            }

        }
    }


}



// init BP network 
void BPNeuralNetwork::initBPNetwork(){

	int i,j;



	// Find the min and max value of input and output data(TrainData + TestData)

	for(i=0; i<In; i++){

		Minin[i]=Maxin[i]=data[0][i];
        
        for(j=0; j<Data; j++){

            Maxin[i]=Maxin[i]>data[j][i]?Maxin[i]:data[j][i];

            Minin[i]=Minin[i]<data[j][i]?Minin[i]:data[j][i];

        }

    }

    for(i=In; i<(In+Out); i++){

    	Minout[i-In]=Maxout[i-In]=data[0][i];

        for(j=0; j<Data; j++){

            Maxout[i-In]=Maxout[i-In]>data[j][i]?Maxout[i-In]:data[j][i];

            Minout[i-In]=Minout[i-In]<data[j][i]?Minout[i-In]:data[j][i];

        }

    }


    // train/test data input and output normalization 

    for (i = 0; i < In; i++){

    	for(j = 0; j < TrainData; j++){

    		d_in_train[j][i] = (d_in_train[j][i] - Minin[i] + 1) / (Maxin[i] - Minin[i] + 1);

    	}

    }
                  
    for (i = 0; i < Out; i++){

    	for(j = 0; j < TrainData; j++){

    		d_out_train[j][i] = (d_out_train[j][i] - Minout[i] + 1) / (Maxout[i] - Minout[i] + 1);


    	}

    }


    for (i = 0; i < In; i++){

    	for(j = 0; j < TestData; j++){

    		d_in_test[j][i] = (d_in_test[j][i] - Minin[i] + 1) / (Maxin[i] - Minin[i] + 1);

    	}

    }

            
}

//activation function(sigmoid function)
double BPNeuralNetwork::fnet(double net){

	return 1 / (1+exp(-net));

}

void BPNeuralNetwork::computeO(int var){

	int i,j;

    double sum;

	for(i = 0; i < Neuron; i++){

        sum = 0.0;

        for(j = 0; j < In; j++){

           	sum += w[j][i] * d_in_train[var][j];

        }

        o[i] = fnet(sum); // hidden neuron 

    }

    for(i = 0; i < Out; i++){

        sum = 0.0;

        for(j = 0; j < Neuron; j++){

            sum += o[j] * v[j][i];

        }

        OutputData[i] = fnet(sum);

    }

}

void BPNeuralNetwork::backUpdate(int var){

	int i,j;

	double sum;

    //double Momentum = 0.4;

	for(i = 0; i < Neuron; i++){

		sum = 0.0;

		for(j = 0; j < Out; j++){


            sum += (OutputData[j] - d_out_train[var][j]) * v[i][j];

            dv[i][j] = LearningRate * (OutputData[j] - d_out_train[var][j]) * o[i] + Momentum * dv[i][j];

            v[i][j] -= dv[i][j];


		}


		for(j = 0; j < In; j++){

            dw[j][i] = LearningRate * sum * o[i] * (1 - o[i]) * d_in_train[var][j] + Momentum * dw[j][i];//momentum term;

            w[j][i] -= dw[j][i];

		}

	}
	


}


// train BP network
void BPNeuralNetwork::trainBPNetwork(char* filename){

    int i,count;

    int TestDataGroup; // test data group id

    double ProgramTime;

    clock_t start,end;

    start = clock();

    fstream logfile(filename,ios::out);

	double trainError,testError,error,accuracy,cost,precision,recall;

    double AverageTrainMSE = 0.0;
    double AverageTestMSE = 0.0;
    double AverageCost = 0.0;

    for(TestDataGroup = 1;TestDataGroup <= 10;TestDataGroup++){

        splitData(TestDataGroup); // split the data into train and test dataset

        initBPNetwork();//init the bp network

        count = 0;

        do{

            error = 0.0;

            for (i = 0; i < TrainData; i++){

                computeO(i);

                error += (OutputData[0] - d_out_train[i][0]) * (OutputData[0] - d_out_train[i][0]);

                backUpdate(i);
            
            }

            trainError = sqrt(error) / TrainData;//train dataset error / MSE

            testError = computeTestMSE();

            accuracy = computeTestAccuracy();

            cost = computeTestCost();

            recall = computeTestRecallAndPrecision("recall");

            precision = computeTestRecallAndPrecision("precision");

            if(!logfile){

                cout<<"file error"<<endl;

                exit(1);

            }else{

        /*        logfile<<"Test dataset is group " << TestDataGroup << endl;

                logfile<<"Train dataset MSE = "<< trainError << ",Step = "<< count + 1<<endl;

                logfile<<"Test dataset MSE = "<< testError << ",Step = "<< count + 1 <<endl;

                logfile<<"Test dataset Accuracy = "<< accuracy << ",Step = "<< count + 1 <<endl;

                logfile<<"Test dataset Cost = "<< cost << ",Step = "<< count + 1 <<endl;

                logfile<<"Test dataset Recall = "<< recall << ",Step = "<< count + 1 <<endl;

                logfile<<"Test dataset Precision = "<< precision << ",Step = "<< count + 1 <<endl;

                logfile<<"========================================================="<<endl;*/

            }

               // emit emitLog("Test dataset is group :");

                cout<<"Test dataset is group " << TestDataGroup << endl;

                cout<<"Train dataset MSE = "<< trainError << ",count = "<<count<<endl;

                cout<<"Test dataset MSE = "<< testError << ",count = "<<count<<endl;

                cout<<"Test dataset Accuracy = "<< accuracy << ",count = "<<count<<endl;

                cout<<"Test dataset Cost = "<< cost << ",count = "<<count<<endl;

                cout<<"Test dataset Recall = "<< recall << ",count = "<<count<<endl;

                cout<<"Test dataset Precision = "<< precision << ",count = "<<count<<endl;

                cout<<"========================================================="<<endl;

                count++;

            }while(count <=Epochs && accuracy < EndAccuracy);

            AverageTrainMSE += trainError;

            AverageTestMSE += testError;

            AverageCost += cost;

        }

        end = clock();

        ProgramTime = (double)(end - start) / CLOCKS_PER_SEC;

        AverageTrainMSE /= 10;

        AverageTestMSE /= 10;

        AverageCost /= 10;

        logfile << "Train and Test Results: " << endl;

        logfile << "Input Nodes : " << In << " Hidden Nodes : " << Neuron << " Output Nodes : " << Out << endl;

        logfile << "Learning Rate : " << LearningRate << endl;

        logfile << "Momentum : " << Momentum << endl;

        logfile << "Ending Epochs : " << Epochs << endl;

        logfile << "Ending Accuracy : " << EndAccuracy << endl;

        logfile << "Average Train MSE : " << AverageTrainMSE << endl;

        logfile << "Average Test MSE : " << AverageTestMSE << endl;

        logfile << "Average Cost : " << AverageCost << endl;

        logfile << "Program Cost Time : " << ProgramTime << " s" << endl;

        logfile.close();

}

double BPNeuralNetwork::computeTestAccuracy(){

	int i;

	int count = 0;

	double output;

	int temp;

	for(i = 0 ; i < TestData ; i++){	

		temp = (int)(predict(i)+0.5);

		output = (double)temp;

		if(output == d_out_test[i][0]){

			//right result

			count++;
		}


	}

	return 1.0 * count / TestData;
}

double BPNeuralNetwork::computeTestMSE(){

	int i;

	double error = 0.0;

	double output;

	for (i = 0; i < TestData; i++){


		output = predict(i);

		error += (output - d_out_test[i][0]) * (output - d_out_test[i][0]);
            
    }

    return sqrt(error) / TestData;

}

double BPNeuralNetwork::computeTestCost(){

	int i;

	int TPCount = 0,FNCount = 0, FPCount = 0,TNCount = 0;

	double TPCost = 0.0,FNCost = 1.0,FPCost = 5.0,TNCost = 0.0;

	int temp;

	double output;

	for(i=0;i<TestData;i++){

		temp = (int)(predict(i)+0.5);

		output = (double)temp;

		if(output == 1 && d_out_test[i][0] == 1){

			TPCount ++;

		}

		if(output == 2 && d_out_test[i][0] == 1){

			FNCount ++;

		}

		if(output == 1 && d_out_test[i][0] == 2){

			FPCount ++;

		}

		if(output == 2 && d_out_test[i][0] == 2){

			TNCount ++;

		}

	}

	return TPCost * TPCount + FNCost * FNCount + FPCost * FPCount + TNCost * TNCount;

}

double BPNeuralNetwork::computeTestRecallAndPrecision(char* type){

	int i;

	int TPCount = 0,FNCount = 0, FPCount = 0,TNCount = 0;

	int temp;

	double output;

	for(i=0;i<TestData;i++){

		temp = (int)(predict(i)+0.5);

		output = (double)temp;

		if(output == 1 && d_out_test[i][0] == 1){

			TPCount ++;

		}

		if(output == 2 && d_out_test[i][0] == 1){

			FNCount ++;

		}

		if(output == 1 && d_out_test[i][0] == 2){

			FPCount ++;

		}

		if(output == 2 && d_out_test[i][0] == 2){

			TNCount ++;

		}

	}

	//cout<<TPCount<<" "<<FNCount<<" "<<FPCount<<" "<<TNCount<<endl;

	if(type == "recall"){

		return 1.0 * TPCount / (TPCount + FNCount);

	}

	if(type == "precision"){

		return 1.0 * TPCount / (TPCount + FPCount);
	}

	

}

//Predict the classfication
double BPNeuralNetwork::predict(int var){

	int i,j;

	double sum;

	double result;

	for(i = 0; i < Neuron; i++){

        sum = 0.0;

        for(j = 0; j < In; j++){

           	sum += w[i][j] * d_in_test[var][j];

        }

        o[i] = fnet(sum); // hidden neuron 

    }

    for(i = 0; i < Out; i++){

        sum = 0.0;

        for(j = 0; j < Neuron; j++){

            sum += o[j] * v[i][j];

        }

    }

    result = fnet(sum) * (Maxout[0] - Minout[0] + 1) + Minout[0] - 1;

    return result;


}


// write Neuron
void BPNeuralNetwork::writeNeuron(char* wname,char* vname){

	//write w

	int i,j;

	fstream outfile(wname,ios::out);

	if(! outfile){

		cout<<"file error"<<endl;
		exit(1);

	}else{

		for(i = 0; i < Neuron; i++){

			for(j = 0; j < In; j++){

				outfile << w[i][j] << " ";
			}

			outfile << endl;
		}

		cout<<"input layer to hidden layer weights file is generated!"<<endl;
	}

	outfile.close();


	fstream outfile1(vname,ios::out);

	if(! outfile1){

		cout<<"file error"<<endl;
		exit(1);

	}else{

		for(i = 0; i < Out; i++){

			for(j = 0; j < Neuron; j++){

				outfile1 << v[i][j] << " ";
			}

			outfile1 << endl;
		}

		cout<<"hidden layer to output layer weights file is generated!"<<endl;
	}

	outfile1.close();


}









