#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*UI Para Init*/

    /*Data Para*/

    ui->DataPatternsEdit->setText("1000");

    ui->DataPatternsEdit->setDisabled(1);

    ui->TrainDataPatternsEdit->setText("900");

    ui->TrainDataPatternsEdit->setDisabled(1);

    ui->TestDataPattensEdit->setText("100");

    ui->TestDataPattensEdit->setDisabled(1);

    /*Network Para*/

    ui->InEdit->setText("20");

    ui->InEdit->setDisabled(1);

    ui->NeuronEdit->setText("10");

    ui->OutEdit->setText("1");

    ui->OutEdit->setDisabled(1);

    ui->LREdit->setText("0.3");

    /*Train End Para*/

    ui->EpochsEdit->setText("1000");

    ui->AccuracyEdit->setText("0.95");

    /*File Para*/

    ui->InputFileEdit->setText("/Users/zhangjun/Documents/C++Work/BPNN/data/german.dat");

    ui->WEdit->setText("/Users/zhangjun/Documents/C++Work/BPNN/data/InputToHiddenWeights.dat");

    ui->VEdit->setText("/Users/zhangjun/Documents/C++Work/BPNN/data/HiddenToOutputWeights.dat");

    ui->LogEdit->setText("/Users/zhangjun/Documents/C++Work/BPNN/data/log.dat");

    /*Signals Slots Connect */

    connect(&worker,SIGNAL(emitStatus(QString)),this,SLOT(updateStatus(QString)));

    connect(this,SIGNAL(emitPara(Para)),&worker,SLOT(updatePara(Para)));

    connect(&worker,SIGNAL(emitFinished()),this,SLOT(updateBtnStatus()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RunBtn_clicked()
{
    /*Data Para*/

    int Data = ui->DataPatternsEdit->text().toInt();
    int TrainData = ui->TrainDataPatternsEdit->text().toInt();
    int TestData = ui->TestDataPattensEdit->text().toInt();

    /*Network Para*/

    int In = ui->InEdit->text().toInt();
    int Neuron = ui->NeuronEdit->text().toInt();
    int Out = ui->OutEdit->text().toInt();
    double LearningRate = ui->LREdit->text().toDouble();

    /*Train End Para*/

    int Epochs = ui->EpochsEdit->text().toInt();
    double EndAccuracy = ui->AccuracyEdit->text().toDouble();

    /*File Para*/

    QString inputFilename = ui->InputFileEdit->text();
    QString wFilename = ui->WEdit->text();
    QString vFilename = ui->VEdit->text();
    QString logFilename = ui->LogEdit->text();

    para.Data = Data;
    para.TrainData = TrainData;
    para.TestData = TestData;

    para.In = In;
    para.Neuron = Neuron;
    para.Out = Out;
    para.LearningRate = LearningRate;

    para.Epochs = Epochs;
    para.EndAccuracy = EndAccuracy;

    para.inputFilename = inputFilename;
    para.wFilename = wFilename;
    para.vFilename = vFilename;
    para.logFilename = logFilename;

    emit emitPara(para);

    worker.start();

    ui->RunBtn->setDisabled(1);//make the run button disabled

}

void MainWindow::updateStatus(QString str){

    ui->StatusOutput->setText(str);

}

void MainWindow::updateBtnStatus(){

    ui->RunBtn->setDisabled(0);//make the run button works again

}

