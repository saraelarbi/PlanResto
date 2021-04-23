#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"mailing.h"
#include"materiel.h"
#include"remise.h"
#include"arduino.h"
#include"fournisseur.h"
#include<QPropertyAnimation>
#include<QMediaPlayer>
#include<QSound>
#include"excel.h"

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


    void on_imp_F_clicked();



    void on_ajout_remise_clicked();

    void on_supp_remise_clicked();

    void on_modifier_remise_clicked();

    void on_excel_remise_clicked();


    void on_recherche2_textChanged(const QString &arg1);

    void on_refresh_clicked();

    void on_textEdit_copyAvailable(bool b);


private:

    Ui::MainWindow *ui;
    Materiel M;
    Fournisseur F;
    Remise R;
    QPropertyAnimation* animation;
    QMediaPlayer musicAdd;
    QSound *son;
    QByteArray data;
    arduino A;
};
#endif // MAINWINDOW_H
