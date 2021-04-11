#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collaborateur.h"
#include "contrat.h"
#include <QMessageBox>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include<QSqlQueryModel>
#include<QTextDocument>
#include<QDesktopServices>
#include "smtp.h"
#include<QAbstractSocket>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));

        ui->tab_collab->setModel(C.afficher());
        ui->tableView_2->setModel(T.afficher());
        ui->tab_collab->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tab_collab->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);


        int nb=ui->tab_collab->model()->rowCount();
                           ui->idcollaborateur_2->clear();

                           for (int i=0;i<nb;i++)
                           {
                               QString idcollaborateur = ui->tab_collab->model()->index(i, 0).data().toString();
                               ui->idcollaborateur_2->addItem(idcollaborateur);
                           }



}
void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_collab_2_clicked()
{
   QString idcollaborateur=ui->idcollaborateur->text();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
     QString telephone=ui->telephone->text();
    QString adresse=ui->adresse->text();
    QString email=ui->email->text();




    Collaborateur C(idcollaborateur,nom,prenom,telephone,adresse,email);


     bool test2=C.ajouter();

     if(test2)
     {
         ui->tab_collab->setModel(C.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         int nb=ui->tab_collab->model()->rowCount();
         ui->idcollaborateur_2->clear();
         for (int i=0;i<nb;i++)
         {
             QString idcollaborateur = ui->tab_collab->model()->index(i,0).data().toString();
             ui-> idcollaborateur_2->addItem(idcollaborateur);
         }


 }
     else
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectue.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_supprimer_collab_clicked()
{
        QItemSelectionModel *select = ui->tab_collab->selectionModel();
        QString idcollaborateur = select->selectedRows(0).value(0).data().toString();

       if(C.supprimer(idcollaborateur))
       {
           ui->tab_collab->setModel(C.afficher());
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("suppression effectué.\n"
                                   "Click ok to exit."), QMessageBox::Cancel);
           int nb=ui->tab_collab->model()->rowCount();
                          ui->idcollaborateur_2->clear();

                          for (int i=0;i<nb;i++)
                          {
                              QString idcollaborateur = ui->tab_collab->model()->index(i, 0).data().toString();
                              ui->idcollaborateur_2->addItem(idcollaborateur);
                          }
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                       QObject::tr("suppression non effectue.\n"
                                   "Click OK to exit."), QMessageBox::Cancel);
        }
}


void MainWindow::on_ajouter_collab_clicked()
{
     QString type=ui->type->text();
     QString nom=ui->nom_2->text();
     QString duree=ui->duree->currentText();
     QString tarif=ui->tarif->text();
     QString idcollaborateur=ui->idcollaborateur_2->currentText();



    Contrat C(type,nom,duree,tarif,idcollaborateur);


     bool test2=C.ajouter();

     if(test2)
     {
         ui->tableView_2->setModel(T.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

 }
     else
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectue.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_modifier_collab_clicked()
{
    if (ui->modifier_collab->isChecked())
    {
        ui->modifier_collab->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("COLLABORATEUR");
        tableModel->select();
        ui->tab_collab->setModel(tableModel);
    }
    else
    {
        ui->modifier_collab->setText("Modifier");
        ui->tab_collab->setModel(C.afficher());
        QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                    QObject::tr("Fonction modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);

    }

}

void MainWindow::on_supprimer_collab_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_2->selectionModel();
            QString C = select->selectedRows(0).value(0).data().toString();

           if(T.supprimer(C))
           {
               ui->tableView_2->setModel(T.afficher());
               QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("suppression effectué.\n"
                                       "Click ok to exit."), QMessageBox::Cancel);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                           QObject::tr("suppression non effectue.\n"
                                       "Click OK to exit."), QMessageBox::Cancel);
           }
}

void MainWindow::on_modifier_collab_2_clicked()
{

    if (ui->modifier_collab_2->isChecked())
    {
        ui->modifier_collab_2->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("contrat");
        tableModel->select();
        ui->tableView_2->setModel(tableModel);
    }
    else
    {
        ui->modifier_collab_2->setText("Modifier");
        ui->tableView_2->setModel(T.afficher());
        QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                    QObject::tr("Fonction modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);

    }
}



void MainWindow::on_pb_recherche_clicked()
{
    if (ui->checkBox_nom->isChecked())
   { QString nom=ui->rech_nom->text();
       QSqlQueryModel *verif=T.rechercher_nom(nom);
       if (verif!=nullptr)
       {
           ui->tableView_2->setModel(verif);

       }
    }

 if (ui->checkBox_type->isChecked())
   { QString type=ui->rech_type->text();
       QSqlQueryModel *verif=T.rechercher_type(type);
       if (verif!=nullptr)
       {

           ui->tableView_2->setModel(verif);

       }
    }
  if (ui->checkBox_tarif->isChecked())
   { QString tarif=ui->rech_tarif->text();
       QSqlQueryModel *verif=T.rechercher_tarif(tarif);
       if (verif!=nullptr)
       {

           ui->tableView_2->setModel(verif);

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
                   QSqlQueryModel *verif=T.rechercher_nom_type(nom,type);
                   if (verif!=nullptr)
                   {
                       ui->tableView_2->setModel(verif);

                   }
                       } else
                           QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
                   } else
                       QMessageBox::warning(this,"erreur","Champ salaire est vide");
   }
  if ((ui->checkBox_nom->isChecked())&&(ui->checkBox_tarif->isChecked()))
   {
       QString nom=ui->rech_nom->text();
      QString tarif=ui->rech_tarif->text();

                   if (nom!="")
                     {
                   QSqlQueryModel *verif=T.rechercher_nom_tarif(nom,tarif);
                   if (verif!=nullptr)
                   {
                       ui->tableView_2->setModel(verif);

                   }

                   } else
                       QMessageBox::warning(this,"erreur","Champ salaire est vide");
   }
   if ((ui->checkBox_type->isChecked())&&(ui->checkBox_tarif->isChecked()))
   {
      QString type=ui->rech_type->text();
      QString tarif=ui->rech_tarif->text();

                   if (type!="")
                     {
                   QSqlQueryModel *verif=T.rechercher_type_tarif(type,tarif);
                   if (verif!=nullptr)
                   {
                       ui->tableView_2->setModel(verif);

                   }

                   } else
                       QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
   }


if ((ui->checkBox_nom->isChecked())&&(ui->checkBox_tarif->isChecked())&&(ui->checkBox_type->isChecked()))
{

    QString tarif=ui->rech_tarif->text();
    QString nom=ui->rech_nom->text();
    QString type=ui->rech_type->text();

                if (nom!="")
                  {
                    if (type!="")
                       {
                QSqlQueryModel *verif=T.rechercher_tous(nom,type,tarif);
                if (verif!=nullptr)
                {

                    ui->tableView_2->setModel(verif);

                }
                    } else
                        QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
                } else
                    QMessageBox::warning(this,"erreur","Champ salaire est vide");

}
}

void MainWindow::on_re_afficher_clicked()
{
    ui->rech_nom->setText("");
        ui->rech_type->setText("");
        ui->tableView_2->setModel(T.afficher());
}



void MainWindow::on_reset_2_clicked()
{
    ui->type->setText("");
    ui->nom_2->setText("");
    ui->duree->setCurrentText("");
    ui->tarif->setText("");
    ui->idcollaborateur_2->setCurrentText("");
}

void MainWindow::on_reset_clicked()
{
    ui->idcollaborateur->setText("");
    ui->nom->setText("");
    ui->prenom->setText("");
    ui->telephone->setText("");
    ui->adresse->setText("");
    ui->email->setText("");
}
void MainWindow::on_radioButton_clicked()
{
    {QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();


               model->setQuery("select * from collaborateur order by id_collaborateur");

               model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_collaborateur"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
               model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

                        ui->tab_collab->setModel(model);
                        ui->tab_collab->show();
                        msgBox.setText("Tri avec succés.");
                        msgBox.exec();

        }
}

void MainWindow::on_radioButton_2_clicked()
{
    QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();



           model->setQuery("select * from collaborateur order by nom");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_collaborateur"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

                    ui->tab_collab->setModel(model);
                    ui->tab_collab->show();
                    msgBox.setText("Tri avec succés.");
                    msgBox.exec();
}

void MainWindow::on_radioButton_3_clicked()
{
    QMessageBox msgBox ;
        QSqlQueryModel * model= new QSqlQueryModel();



           model->setQuery("select * from collaborateur order by prenom");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_collaborateur"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

                    ui->tab_collab->setModel(model);
                    ui->tab_collab->show();
                    msgBox.setText("Tri avec succés.");
                    msgBox.exec();
}


void MainWindow::on_re_afficher2_clicked()
{
    ui->radioButton_3->setText("");
        ui->radioButton_2->setText("");
        ui->tab_collab->setModel(C.afficher());
}



