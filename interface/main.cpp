#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include<QWidget>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Connection c;
    bool test=c.createconnect();
    MainWindow w;

    w.show();




    return a.exec();
}
