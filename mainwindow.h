#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fonction.h"
#include "emplyer.h"
#include <QPrinter>

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

private:
    Ui::MainWindow *ui;
    fonction supp;
    Employes sup;



};



#endif // MAINWINDOW_H
