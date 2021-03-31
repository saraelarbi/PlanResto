#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"materiel.h"
#include"fournisseur.h"
#include <QMessageBox>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_mat->setModel(M.afficher());
    ui->tab_fou->setModel(F.afficher());
    ui->tab_mat->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_mat->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_fou->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_fou->setSelectionMode(QAbstractItemView::SingleSelection);

    int nb=ui->tab_fou->model()->rowCount();
                       ui->cinfet->clear();

                       for (int i=0;i<nb;i++)
                       {
                           QString cinf = ui->tab_fou->model()->index(i, 0).data().toString();
                           ui->cinfet->addItem(cinf);
}
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
    QString prix=ui->prix->text();
    QString cinf=ui->cinfet->currentText();



    Materiel M(id,nom,type,marque,prix,cinf);


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




void MainWindow::on_ajout2_clicked()
{
    QString cinf=ui->cinf->text();
    QString nom=ui->nom_2->text();
    QString prenom=ui->prenom->text();
    QString type=ui->type_2->text();
    QString tel=ui->tel->text();
    QString email=ui->email->text();
    QString adresse=ui->adresse->text();


    Fournisseur F(cinf,nom,prenom,type,tel,email,adresse);


    bool test2=F.ajouter();

    if(test2)
    {
        ui->tab_fou->setModel(F.afficher());

                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué.\n"
                                            "Click ok to exit."), QMessageBox::Cancel);
                    int nb=ui->tab_fou->model()->rowCount();
                                   ui->cinfet->clear();

                                   for (int i=0;i<nb;i++)
                                   {
                                       QString type_fonction = ui->tab_fou->model()->index(i, 0).data().toString();
                                       ui->cinfet->addItem(type_fonction);
                  }
}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_modifier_M_clicked()
{
    if (ui->modifier_M->isChecked())
        {
            ui->modifier_M->setText("Modifiable");
            QSqlTableModel *tableModel= new QSqlTableModel();
            tableModel->setTable("MATERIEL");
            tableModel->select();
            ui->tab_mat->setModel(tableModel);
        }
        else
        {
            ui->modifier_M->setText("Modifier");
            ui->tab_mat->setModel(M.afficher());
            QMessageBox::information(nullptr, QObject::tr("modification materiel"),
                        QObject::tr("Materiel modifié.\n"

    "Click OK to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_modifier_F_clicked()
{
    if (ui->modifier_F->isChecked())
        {
            ui->modifier_F->setText("Modifiable");
            QSqlTableModel *tableModel= new QSqlTableModel();
            tableModel->setTable("FOURNISSEUR");
            tableModel->select();
            ui->tab_fou->setModel(tableModel);
        }
        else
        {
            ui->modifier_F->setText("Modifier");
            ui->tab_fou->setModel(F.afficher());
            QMessageBox::information(nullptr, QObject::tr("modification fournisseur"),
                        QObject::tr("Fournisseur modifié.\n"

    "Click OK to exit."), QMessageBox::Cancel);

        }
}


void MainWindow::on_rechercher_matirel_clicked()
{
           if (ui->checkBox_nom->isChecked())
          { QString nom=ui->rech_nom->text();
              QSqlQueryModel *verif=M.rechercher_nom(nom);
              if (verif!=nullptr)
              {
                  ui->tab_mat->setModel(verif);

              }
           }

        if (ui->checkBox_type->isChecked())
          { QString type=ui->rech_type->text();
              QSqlQueryModel *verif=M.rechercher_type(type);
              if (verif!=nullptr)
              {

                  ui->tab_mat->setModel(verif);

              }
           }
         if (ui->checkBox_marque->isChecked())
          { QString marque=ui->rech_marque->text();
              QSqlQueryModel *verif=M.rechercher_marque(marque);
              if (verif!=nullptr)
              {

                  ui->tab_mat->setModel(verif);

              }
           }
          if ((ui->checkBox_nom->isChecked())&&(ui->checkBox_type->isChecked()))
          {
              QString nom=ui->rech_nom->text();
              QString type=ui->rech_type->text();

                          if (nom!="")
                            {
                              if (type!="")
                                 {
                          QSqlQueryModel *verif=M.rechercher_nom_type(nom,type);
                          if (verif!=nullptr)
                          {
                              ui->tab_mat->setModel(verif);

                          }
                              } else
                                  QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
                          } else
                              QMessageBox::warning(this,"erreur","Champ salaire est vide");
          }
         if ((ui->checkBox_nom->isChecked())&&(ui->checkBox_marque->isChecked()))
          {
              QString nom=ui->rech_nom->text();
             QString marque=ui->rech_marque->text();

                          if (nom!="")
                            {
                          QSqlQueryModel *verif=M.rechercher_nom_marque(nom,marque);
                          if (verif!=nullptr)
                          {
                              ui->tab_mat->setModel(verif);

                          }

                          } else
                              QMessageBox::warning(this,"erreur","Champ salaire est vide");
          }
          if ((ui->checkBox_type->isChecked())&&(ui->checkBox_marque->isChecked()))
          {
             QString type=ui->rech_type->text();
             QString marque=ui->rech_marque->text();

                          if (type!="")
                            {
                          QSqlQueryModel *verif=M.rechercher_type_marque(type,marque);
                          if (verif!=nullptr)
                          {
                              ui->tab_mat->setModel(verif);

                          }

                          } else
                              QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
          }


       if ((ui->checkBox_nom->isChecked())&&(ui->checkBox_marque->isChecked())&&(ui->checkBox_type->isChecked()))
       {

           QString marque=ui->rech_marque->text();
           QString nom=ui->rech_nom->text();
           QString type=ui->rech_type->text();

                       if (nom!="")
                         {
                           if (type!="")
                              {
                       QSqlQueryModel *verif=M.rechercher_tous(nom,type,marque);
                       if (verif!=nullptr)
                       {

                           ui->tab_mat->setModel(verif);

                       }
                           } else
                               QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
                       } else
                           QMessageBox::warning(this,"erreur","Champ salaire est vide");

       }
}



void MainWindow::on_pb_supp2_clicked()
{
    QItemSelectionModel *select = ui->tab_fou->selectionModel();
        QString cinf = select->selectedRows(0).value(0).data().toString();

       if(F.supprimer(cinf))
       {
           ui->tab_fou->setModel(F.afficher());
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Mression effectué.\n"
                                   "Click ok to exit."), QMessageBox::Cancel);
           int nb=ui->tab_fou->model()->rowCount();
                          ui->cinfet->clear();

                          for (int i=0;i<nb;i++)
                          {
                              QString cinf = ui->tab_fou->model()->index(i, 0).data().toString();
                              ui->cinfet->addItem(cinf);
                          }
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                       QObject::tr("Mression non effectue.\n"
                                   "Click OK to exit."), QMessageBox::Cancel);
        }
}

void MainWindow::on_pb_supp_clicked()
{
    QItemSelectionModel *select = ui->tab_mat->selectionModel();
        QString C = select->selectedRows(0).value(0).data().toString();

       if(M.supprimer(C))
       {
           ui->tab_mat->setModel(M.afficher());
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Mression effectué.\n"
                                   "Click ok to exit."), QMessageBox::Cancel);
       }
       else
          {
              QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                          QObject::tr("Mression non effectue.\n"
                                      "Click OK to exit."), QMessageBox::Cancel);
          }
}

void MainWindow::on_reaficher_rech_clicked()
{
    ui->rech_nom->setText("");
    ui->rech_type->setText("");
    ui->tab_mat->setModel(M.afficher());
}

void MainWindow::on_reset_Mat_clicked()
{
        ui->id->setText("");
        ui->type->setText("");
        ui->nom->setText("");
        ui->marque->setText("");
        ui->prix->setText("");
}
