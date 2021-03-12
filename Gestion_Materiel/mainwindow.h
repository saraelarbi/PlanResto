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

    void on_pb_supprimer_clicked();

    void on_ajout2_clicked();

    void on_pb_spprimer2_clicked();

private:
    Ui::MainWindow *ui;
    Materiel M;
    Fournisseur F;
};
#endif // MAINWINDOW_H
