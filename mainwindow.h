#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include "commande.h"
#include <QMainWindow>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>
#include <QSystemTrayIcon>

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

    void on_resetClient_clicked();

    void on_resetCommande_clicked();

    void on_reaficherClient_clicked();

    void on_reaficherCommande_clicked();

    void on_stat_Commande_clicked();

private:
    Ui::MainWindow *ui;
    client tmpclient;
    commande tmpcommande;
    QSound *son;
    QMediaPlayer musicAdd;
    QSystemTrayIcon *mSystemTrayIcon;
};

#endif // MAINWINDOW_H
