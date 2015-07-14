#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "workerthread.h"
#include "para.h"
//#include "bp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_RunBtn_clicked();

    void updateStatus(QString);

    void updateBtnStatus();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

signals:
    void emitPara(Para);


private:

    Ui::MainWindow *ui;
    WorkerThread worker;
    Para para;
    QString ChooseFile(QString);


};

#endif // MAINWINDOW_H
