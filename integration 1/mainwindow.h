#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "fonction.h"
#include "emplyer.h"
#include "historique.h"
#include <QPrinter>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>
#include <QSystemTrayIcon>

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

private:
    Ui::MainWindow *ui;

    fonction supp;
    Employes sup;
    QSound *son;
    QMediaPlayer musicAdd;
    QSystemTrayIcon *mSystemTrayIcon;
    historique histo;
};
#endif // MAINWINDOW_H
