#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"blocs.h"
#include"produit.h"
#include<QMediaPlayer>
#include<QSound>
#include<QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:



    void on_pb_ajouter1_clicked();


    void on_pb_ajouter_clicked();


    void on_supprimer_P_clicked();

    void on_supprimer_B_clicked();

    void on_Modifier_B_clicked();

    void on_Modifier_P_clicked();

    void on_rechercher_produit_clicked();

    void on_Reafficher_clicked();

    void on_reset_produit_clicked();

    void on_pushButton_2_clicked();

    void on_le_stat_clicked();

    void on_idT_clicked();

    void on_numT_clicked();

    void on_etatT_clicked();

    void on_recherche_textChanged(const QString &arg1);

    void on_radioButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    bool verifCHAMPVIDE();
    bool  verifNOM();
    bool verifTYPE();
    bool verifMARQUE();
    bool verifNUMB();
    bool verifETAT();

    bool verifCHAMPVIDEbloc();


    void on_music_bloc_clicked();

    void on_music_his_clicked();


private:
    Ui::MainWindow *ui;
     Blocs B;
     Produit P;
     QPropertyAnimation* animation;
     QMediaPlayer musicAdd;
     QSound *son;
     projeth tmph;
};
#endif // MAINWINDOW_H
