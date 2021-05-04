#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "fonction.h"
#include"materiel.h"
#include"fournisseur.h"
#include"excel.h"
#include"mailing.h"
#include"client.h"
#include"commande.h"
#include"calculatrice.h"
#include"music.h"
#include"arduino.h"
#include"remise.h"
#include "emplyer.h"
#include "historique.h"
#include <QPrinter>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>
#include <QSystemTrayIcon>
#include<QNetworkReply>
#include<QPropertyAnimation>
#include<QMediaPlayer>
#include<QSound>

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
    void on_Aymen_clicked();

    void on_Moemen_clicked();

    void on_Salma_clicked();

    void on_Sara_clicked();

    void on_Taher_clicked();

    void on_Ghazi_clicked();

    void on_Configuration_clicked();

    void on_Aymen_2_clicked();

    void on_Moemen_2_clicked();

    void on_Salma_2_clicked();

    void on_Sara_2_clicked();

    void on_Taher_2_clicked();

    void on_Ghazi_2_clicked();

    void on_Configuration_2_clicked();

    void on_Aymen_3_clicked();

    void on_Moemen_3_clicked();

    void on_Salma_3_clicked();

    void on_Sara_3_clicked();

    void on_Taher_3_clicked();

    void on_Ghazi_3_clicked();

    void on_Configuration_3_clicked();

    void on_Aymen_4_clicked();

    void on_Moemen_4_clicked();

    void on_Salma_4_clicked();

    void on_Sara_4_clicked();

    void on_Taher_4_clicked();

    void on_Ghazi_4_clicked();

    void on_Configuration_4_clicked();

    void on_Aymen_5_clicked();

    void on_Moemen_5_clicked();

    void on_Salma_5_clicked();

    void on_Sara_5_clicked();

    void on_Taher_5_clicked();

    void on_Ghazi_5_clicked();

    void on_Configuration_5_clicked();

    void on_Aymen_6_clicked();

    void on_Moemen_6_clicked();

    void on_Salma_6_clicked();

    void on_Sara_6_clicked();

    void on_Taher_6_clicked();

    void on_Ghazi_6_clicked();

    void on_Configuration_6_clicked();

    void on_Aymen_7_clicked();

    void on_Moemen_7_clicked();

    void on_Salma_7_clicked();

    void on_Sara_7_clicked();

    void on_Taher_7_clicked();

    void on_Ghazi_7_clicked();

    void on_Configuration_7_clicked();

    void on_ajouter_fonction_clicked();

    void on_supprimer_fonction_clicked();

    void on_ajouter_emplye_clicked();

    void on_supprimer_emplye_clicked();

    void on_MFonction_clicked();

    void on_MEmploye_clicked();

    void on_resetf_clicked();

    void on_resetP_clicked();

    void on_rechercherf_clicked();

    void on_reafficherf_clicked();

    void on_radioButton_triNom_clicked();

    void on_radioButton_triPrenom_clicked();

    void on_radioButton_triTelephone_clicked();

    void on_exporter_employer_clicked();

    void on_web_clicked();

    void on_envoyer_mail_employe_clicked();

    void on_pb_ajouter_clicked();
    void on_ajout2_clicked();
    void on_modifier_M_clicked();
    void on_modifier_F_clicked();
    void on_rechercher_matirel_clicked();
    void on_pb_supp2_clicked();
    void on_pb_supp_clicked();
    void on_reaficher_rech_clicked();
    void on_reset_Mat_clicked();
    void on_reset_Fou_clicked();
    void on_pushButton_2_clicked();
    void sendMail();
    void mailSent(QString);
    void on_recherche_textChanged(const QString &arg1);
  /*  bool verifNOM();
    bool verifTYPE();
    bool verifMARQUE();
    bool verifNOMF();
    bool verifPRENOM();
    bool verifTYPE2();
    bool verifADRESSE();
    bool verifCHAMPVIDE();*/



    void on_imp_F_clicked();






    void on_refresh_clicked();



void replyFinished(QNetworkReply* reply);




    void on_envoyer_sms_clicked();

    void on_musique_materiel_clicked();

    void on_musique_fournisseur_clicked();

    void on_musique_mail_clicked();


    void on_musique_temp_clicked();


    void on_Ajout_remise_clicked();


    void on_Calculatrice_clicked();

    void on_Musique_rem_clicked();

    void on_Modif_rem_clicked();

    void on_exel_rem_clicked();

    void on_supp_rem_clicked();


    void on_rech_rem_textChanged(const QString &arg1);



    void on_pb_ajouter_2_clicked();

    void on_resetClient_clicked();

    void on_pb_rechercher_clicked();

    void on_reaficherClient_clicked();

    void on_pb_tri_clicked();

    void on_pb_excel_clicked();

    void on_pb_modifier_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_6_clicked();

    void on_pb_ajouter2_clicked();

    void on_resetCommande_clicked();

    void on_pb_rechercher2_clicked();

    void on_reaficherCommande_clicked();

    void on_pb_tri2_clicked();

    void on_imprimer_clicked();

    void on_pb_modifier2_clicked();

    void on_pb_supprimer2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_muet_clicked();

    void on_avance_valueChanged(int value);

    void on_pushButton_clicked();
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

    fonction supp;
    Employes sup;
    QSound *son;
    QMediaPlayer musicAdd;
    QSystemTrayIcon *mSystemTrayIcon;
    historique histo;
    Materiel M;
    Fournisseur F;
    Remise R;
    QPropertyAnimation* animation;
    QByteArray data;
    arduino A;
    client tmpclient;
    commande tmpcommande;
     commande tmph;
     QMediaPlayer *mMediaPlayer;
};
#endif // MAINWINDOW_H
