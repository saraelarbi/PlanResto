#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "plat.h"
#include "boisson.h"

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

private:
    Ui::MainWindow *ui;
    Plat tmpPlat;
    Boisson tmpBoisson;


};

#endif // MAINWINDOW_H
