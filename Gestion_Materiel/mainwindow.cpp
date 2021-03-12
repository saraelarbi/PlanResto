#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"materiel.h"
#include"fournisseur.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_mat->setModel(M.afficher());
    ui->tab_fou->setModel(F.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_ajouter_clicked()
{
    QString id=ui->id->text();
    QString nom=ui->nom->text();
    QString type=ui->type->text();
    QString marque=ui->marque->text();
    float prix=ui->prix->text().toFloat();


    Materiel M(id,type,nom,marque,prix);


    bool test2=M.ajouter();

    if(test2)
    {
        ui->tab_mat->setModel(M.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pb_supprimer_clicked()
{
    Materiel M1; M1.setid(ui->id_supp->text());
    bool test=M1.supprimer(M1.getid());
}

void MainWindow::on_ajout2_clicked()
{
    int cinf=ui->cinf->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString type=ui->type->text();
    int tel=ui->tel->text().toInt();
    QString email=ui->email->text();
    QString adresse=ui->adresse->text();


    Fournisseur F(cinf,nom,prenom,type,tel,email,adresse);


    bool test2=F.ajouter();

    if(test2)
    {
        ui->tab_fou->setModel(F.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_pb_spprimer2_clicked()
{
    Fournisseur F1; F1.setcinf(ui->cinf_supp->text().toInt());
    bool test=F1.supprimer(F1.getcinf());
}
