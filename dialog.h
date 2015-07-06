#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_generateBtn_clicked();

    void on_DeleteBtn_clicked();

private:
    Ui::Dialog *ui;
    QStandardItemModel *model;
};

#endif // DIALOG_H
