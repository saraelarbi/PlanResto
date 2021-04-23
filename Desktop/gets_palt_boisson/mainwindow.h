#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "plat.h"
#include "boisson.h"
#include "arduino.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_tableView_B_activated(const QModelIndex &index);

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_17_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_18_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    bool verifID();
    bool verifNOM();
    bool verifTYPE();
    bool verifPRIX();

    bool verifIDb();
    bool verifNOMb();
    bool verifTYPEb();
    bool verifPRIXb();

private:
    Ui::MainWindow *ui;
    Plat tmpPlat;
    Boisson tmpBoisson;


};

#endif // MAINWINDOW_H
