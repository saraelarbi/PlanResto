#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include "commande.h"
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
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_ajouter2_clicked();

    void on_pb_supprimer2_clicked();

    void on_pb_modifier_clicked();

    void on_pb_modifier2_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_tri_clicked();

    void on_pb_rechercher2_clicked();

    void on_pb_tri2_clicked();

private:
    Ui::MainWindow *ui;
    client tmpclient;
    commande tmpcommande;
};

#endif // MAINWINDOW_H
