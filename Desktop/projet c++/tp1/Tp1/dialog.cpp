#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::setClient(client c)
{
    QString cin = QString::number(c.getCIN());
    ui->lineEdit->setText(cin);
    ui->lineEdit_2->setText(c.getPrenom());
    ui->lineEdit_3->setText(c.getNom());
}
