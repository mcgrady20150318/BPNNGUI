#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workerthread.h"
#include "para.h"

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

signals:
    void emitPara(Para);


private:
    Ui::MainWindow *ui;
    WorkerThread worker;
    Para para;
};

#endif // MAINWINDOW_H
