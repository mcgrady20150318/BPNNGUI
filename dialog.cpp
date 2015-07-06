#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    model = new QStandardItemModel();

    model->setColumnCount(1);

    model->setHeaderData(0,Qt::Horizontal,"Attributes");

    ui->tableView->setModel(model);

    for(int i = 1; i < 20; i++){

         model->setItem(i-1,0,new QStandardItem(QString::fromLocal8Bit("哈哈")));

    }


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_generateBtn_clicked()
{

    close();

}

void Dialog::on_DeleteBtn_clicked()
{

    int curRow = ui->tableView->currentIndex().row();

    model->removeRow(curRow);

}
