#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpixmap.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/abdelmomen medhioub/Desktop/projet c++/design/pic") ;
    ui->labelimg->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
