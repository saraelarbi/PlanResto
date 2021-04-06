#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_clicked()
{
    client  c ;

    c.setCIN(ui->lineEdit->text().toInt());
    c.setPrenom(ui->lineEdit_2->text());
    c.setNom(ui->lineEdit_3->text());

    Dialog d ;
    d.setClient(c);
    d.exec();


}
