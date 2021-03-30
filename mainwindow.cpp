#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "commande.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);


ui->tabclient_2->setModel(tmpclient.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{

    QString id= ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString adresse= ui->lineEdit_adresse->text();
    QString tel= ui->lineEdit_tel->text();
    QString email= ui->lineEdit_email->text();

  client c(id,nom,prenom,adresse,tel,email);
  bool test=c.ajouter();
  if(test)
{

      ui->tabclient_2->setModel(tmpclient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un client"),
                  QObject::tr("Client ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un client"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer_clicked()
{
 QString id= ui->lineEdit_id->text();
bool test=tmpclient.supprimer(id);
if(test)
{ui->tabclient_2->setModel(tmpclient.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                QObject::tr("Client supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un client"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}
void MainWindow::on_pb_ajouter2_clicked()
{

    QString id= ui->lineEdit_id2->text();
    QString nom= ui->lineEdit_nom2->text();
    QString type= ui->lineEdit_type->text();
    QString cinp= ui->lineEdit_cinp->currentText();
    float prix= ui->lineEdit_prix->text().toFloat();


  commande co(id,nom,type,cinp,prix);
  bool test=co.ajouter();
  if(test)
{

      ui->tabcommande_2->setModel(tmpcommande.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une commande"),
                  QObject::tr("Commande ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un commande"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  QItemSelectionModel *select = ui->tabcommande_2->selectionModel();
      QString typefonction = select->selectedRows(0).value(0).data().toString();

     if(tmpcommande.supprimer(cinp))
     {
         ui->tabcommande_2->setModel(tmpcommande.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("suppression effectué.\n"
                                 "Click ok to exit."), QMessageBox::Cancel);
         int nb=ui->tabcommande_2->model()->rowCount();
                        ui->lineEdit_cinp->clear();

                        for (int i=0;i<nb;i++)
                        {
                            QString type_fonction = ui->tabcommande_2->model()->index(i, 0).data().toString();
                            ui->lineEdit_cinp->addItem(type_fonction);
                        }
     }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("suppression non effectue.\n"
                                 "Click OK to exit."), QMessageBox::Cancel);
      }


}
void MainWindow::on_pb_supprimer2_clicked()
{
 QString id= ui->lineEdit_id2->text();
bool test=tmpcommande.supprimer(id);
if(test)
{ui->tabcommande_2->setModel(tmpcommande.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer une commande"),
                QObject::tr("Commande supprimée.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer une commande"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_modifier_clicked()
{
    QString id=ui->lineEdit_id->text();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString adresse=ui->lineEdit_adresse->text();
    QString tel=ui->lineEdit_tel->text();
    QString email=ui->lineEdit_email->text();
    client c(id,nom,prenom,adresse,tel,email);
    if(c.modifier(id))
    {
          ui->tabclient_2->setModel(tmpclient.afficher());
              QMessageBox::information(nullptr, QObject::tr("Modifier un Client"),
                          QObject::tr("Client modifié.\n"), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier une Client"),
                          QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
    }

}
void MainWindow::on_pb_modifier2_clicked()
{
    QString id=ui->lineEdit_id2->text();
    QString nom=ui->lineEdit_nom2->text();
    QString type=ui->lineEdit_type->text();
    QString cinp=ui->lineEdit_cinp->currentText();
    float prix=ui->lineEdit_prix->text().toFloat();
    commande co(id,nom,type,cinp,prix);
    if(co.modifier(id))
    {
          ui->tabcommande_2->setModel(tmpcommande.afficher());
              QMessageBox::information(nullptr, QObject::tr("Modifier une Commande"),
                          QObject::tr("Commande modifiée.\n"), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier une Commande"),
                          QObject::tr("Erreur !!!!!!!!\n"), QMessageBox::Cancel);
    }

}

void MainWindow::on_pb_rechercher_clicked()
{
    QString rech =ui->lineEditrech->text();
   ui->tabclient_2->setModel(tmpclient.rechercher(rech));
}

void MainWindow::on_pb_tri_clicked()
{
    ui->tabclient_2->setModel(tmpclient.tri());
}
void MainWindow::on_pb_rechercher2_clicked()
{
    QString rech =ui->lineEditrech2->text();
   ui->tabcommande_2->setModel(tmpcommande.rechercher(rech));
}

void MainWindow::on_pb_tri2_clicked()
{
    ui->tabcommande_2->setModel(tmpcommande.tri());
}
