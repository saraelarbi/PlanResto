#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "collaborateur.h"
#include "contrat.h"
#include "statis.h"
#include <QSound>
#include<QMediaPlayer>
#include<QPropertyAnimation>
#include "arduino.h"
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QMouseEvent>
#include <QtWidgets/QMessageBox>
#include "reservation.h"
#include"arduino.h"





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
    void on_ajouter_collab_2_clicked();
    void on_supprimer_collab_clicked();
    void on_ajouter_collab_clicked();
    void on_modifier_collab_clicked();
    void on_supprimer_collab_2_clicked();
    void on_modifier_collab_2_clicked();
    void on_pb_recherche_clicked();
    void on_re_afficher_clicked();
    void on_reset_2_clicked();
    void on_reset_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_re_afficher2_clicked();
    void on_imprimer_clicked();
    void on_le_stat_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_2_clicked();
    void replyFinished(QNetworkReply* reply);
    void on_ajouter_3_clicked();
    void on_supprimer3_clicked();
    void on_modif3_clicked();
    void on_reset3_clicked();
    bool verifNOM();
    bool verifPRENOM();
    bool verifNOM1();
    bool verifNOM2();
    bool verifPRENOM1();
    void on_buzz_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Collaborateur C;
    Contrat T;
    Reservation R;
    QMediaPlayer musicAdd;
    QSound *son;
    QPropertyAnimation* animation;
    projeth tmph;
    Arduino ar;
    QPixmap *pix;
    QMediaPlayer musicc;



};

#endif // MAINWINDOW_H
