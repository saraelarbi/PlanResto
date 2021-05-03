#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include "commande.h"
#include <QMainWindow>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>
#include <QSystemTrayIcon>
#include<QMediaPlayer>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QMouseEvent>
#include <QtWidgets/QMessageBox>

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

   /* void on_stat_Commande_clicked();*/

    void on_imprimer_clicked();

    void on_pb_excel_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_muet_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void replyFinished(QNetworkReply* reply);

       bool verifID();

       bool verifID2();

       bool verifNOM();

       bool verifNOM2();

       bool verifprenom();

       bool verifTYPE();

       bool verifPRIX();

        bool verifIDb();

        bool verifemail();

        bool veriftel();

        bool verifcinp();

private:
    Ui::MainWindow *ui;
    client tmpclient;
    commande tmpcommande;
    QSound *son;
    QMediaPlayer musicAdd;
    QSystemTrayIcon *mSystemTrayIcon;
    QMediaPlayer *mMediaPlayer;
    commande tmph;
};

#endif // MAINWINDOW_H
