#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"materiel.h"
#include"fournisseur.h"
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

private:
    Ui::MainWindow *ui;
    Materiel M;
    Fournisseur F;
};
#endif // MAINWINDOW_H
