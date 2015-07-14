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

    ui->MomentumEdit->setText("0.3");

    /*Train End Para*/

    ui->EpochsEdit->setText("1000");

    ui->AccuracyEdit->setText("0.90");

    /*File Para*/

    ui->InputFileEdit->setText("/Users/zhangjun/Documents/C++Work/BPNN/data/german.dat");

    ui->WEdit->setText("/Users/zhangjun/Documents/C++Work/BPNN/data/InputToHiddenWeights.dat");

    ui->VEdit->setText("/Users/zhangjun/Documents/C++Work/BPNN/data/HiddenToOutputWeights.dat");

    ui->LogEdit->setText("/Users/zhangjun/Documents/C++Work/BPNN/data/log.dat");

    /*Signals Slots Connect */

    connect(&worker,SIGNAL(emitStatus(QString)),this,SLOT(updateStatus(QString)));

    connect(this,SIGNAL(emitPara(Para)),&worker,SLOT(updatePara(Para)));

    connect(&worker,SIGNAL(emitFinished()),this,SLOT(updateBtnStatus()));

   // connect(&bp,SIGNAL(emitLog(QString)),this,SLOT(updateStatus(QString)));

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
    double Momentum = ui->MomentumEdit->text().toDouble();

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
    para.Momentum = Momentum;

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

QString MainWindow::ChooseFile(QString filename){

    QFileDialog *fd = new QFileDialog(this,tr("Choose Dataset File"), "/Users/Zhangjun/Documents/C++Work/BPNN/data","" );

    fd->setFileMode(QFileDialog::ExistingFile);

    fd->setViewMode(QFileDialog::Detail);

    QStringList filters;

    filters << "*.csv" << "*.dat" << "*.txt" << "*.*";

    fd->setNameFilters(filters);

    QStringList fileNamesList;

    if(fd->exec()) // ok
    {

            fileNamesList = fd->selectedFiles();

            QString fileName = fileNamesList.at(0).toLocal8Bit().constData();

            return fileName;

    }else{

        return filename;

    }


}

void MainWindow::updateStatus(QString str){

    ui->StatusOutput->setText(str);

}

void MainWindow::updateBtnStatus(){

    ui->RunBtn->setDisabled(0);//make the run button works again

}


void MainWindow::on_toolButton_clicked()
{

    ui->InputFileEdit->setText(ChooseFile(ui->InputFileEdit->text()));

}

void MainWindow::on_toolButton_2_clicked()
{

    ui->WEdit->setText(ChooseFile(ui->WEdit->text()));

}

void MainWindow::on_toolButton_3_clicked()
{
    ui->VEdit->setText(ChooseFile(ui->VEdit->text()));

}

void MainWindow::on_toolButton_4_clicked()
{
    ui->LogEdit->setText(ChooseFile(ui->LogEdit->text()));

}

