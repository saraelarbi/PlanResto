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

private:
    Ui::MainWindow *ui;
    Collaborateur C;
    Contrat T;
    QMediaPlayer musicAdd;
    QSound *son;
    QPropertyAnimation* animation;
    Arduino A;



};

#endif // MAINWINDOW_H
