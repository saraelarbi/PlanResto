#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "plat.h"
#include "boisson.h"
#include "arduino.h"
#include "notifications.h"
#include <QSound>
#include <QTimer>


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


    void on_pushButton_ajouter_Plat_clicked();

    void on_pushButton_afficher_Plat_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_supprimer_Plat_clicked();

    void on_pushButton_modifier_Plat_clicked();

    void on_pushButton_ajouter_Boisson_clicked();

    void on_pushButton_afficher_Boisson_clicked();

    void on_pushButton_modifier_Boisson_clicked();

    void on_pushButton_supprimer_Boisson_clicked();

    void on_tableView_B_activated(const QModelIndex &index);

    void on_tri_prix_Plat_clicked();

    void on_tri_nom_Plat_clicked();

    void on_fermer_porte_clicked();

    void on_imprimer_pdf_Plat_clicked();

    void on_ouvrir_prote_clicked();

    void on_tri_prix_Boisson_clicked();

    void on_tri_nom_Boisson_clicked();

    void on_imprimer_pdf_Boisson_clicked();

    void on_tri_id_Plat_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tri_id_Boisson_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void myfunctionn();



    bool verifID();
    bool verifNOM();
    bool verifPRIX();
    bool verifingredients();

    bool verifID_3();
    bool verifNOM_3();
    bool verifPRIX_3();
    bool verifingredients_3();

    bool verifIDb();
    bool verifNOMb();
    bool verifPRIXb();

    bool verifIDb_2();
    bool verifNOMb_2();
    bool verifPRIXb_2();





  //  void on_stat_clicked();





private:
    Ui::MainWindow *ui;
    Plat tmpPlat;
    Boisson tmpBoisson;
    Arduino a ;
    notifications N;
    QSound *son;
    QSound *son1;
    QSound *son2;
    QSound *son3;
    QSound *son4;
    QSound *son5;
    QTimer *timerr;






};

#endif // MAINWINDOW_H
