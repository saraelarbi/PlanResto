#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "collaborateur.h"
#include "contrat.h"

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


private:
    Ui::MainWindow *ui;
    Collaborateur C;
    Contrat T;

};

#endif // MAINWINDOW_H
