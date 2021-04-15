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
#include<QtPrintSupport/QPrintDialog>
#include<QPainter>
#include<QPdfWriter>
#include<QSqlError>
#include<QtWidgets>
#include<QTextStream>
#include<QGraphicsView>
#include<QSystemTrayIcon>
#include<QSqlQuery>
#include <QSound>
#include<QMediaPlayer>
#include<statis.h>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        QPixmap pix("C:/Users/ASUS I7/Desktop/Atelier_Connexion/logo");
           ui->img->setPixmap(pix);
           animation = new QPropertyAnimation(ui->img,"geometry");
           animation->setDuration(10000);
           animation->setStartValue(ui->img->geometry());
           animation->setEndValue(QRect(610,0,100,100));
           animation->start();
        son=new QSound("C:/Users/ASUS I7/Desktop/Atelier_Connexion/ss.wav");


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
         musicAdd.setMedia(QUrl("C:/Users/ASUS I7/Desktop/Atelier_Connexion/ajout succe.mp3"));
                 musicAdd.play();
                 QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                         notifyIcon->show();
                         notifyIcon->setIcon(QIcon("icone.png"));

                         notifyIcon->showMessage("GESTION COLLABORATEURS  COLLABORATEUR ","collaborateur Ajouté",QSystemTrayIcon::Information,15000);
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
           musicAdd.setMedia(QUrl("C:/Users/ASUS I7/Desktop/Atelier_Connexion/supp succe.mp3"));
                   musicAdd.play();
                   QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                           notifyIcon->show();
                           notifyIcon->setIcon(QIcon("icone.png"));

                           notifyIcon->showMessage("GESTION COLLABORATEURS  COLLABORATEUR ","collaborateur Supprimé",QSystemTrayIcon::Information,15000);
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
         musicAdd.setMedia(QUrl("C:/Users/ASUS I7/Desktop/Atelier_Connexion/ajout succe.mp3"));
                 musicAdd.play();
                 QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                         notifyIcon->show();
                         notifyIcon->setIcon(QIcon("icone.png"));

                         notifyIcon->showMessage("GESTION COLLABORATEURS  CONTRAT ","contrat Ajouté",QSystemTrayIcon::Information,15000);
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
        musicAdd.setMedia(QUrl("C:/Users/ASUS I7/Desktop/Atelier_Connexion/modif succe.mp3"));
                musicAdd.play();
        ui->tab_collab->setModel(C.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION COLLABORATEURS  COLLABPRATEUR ","collaborateur Modifié",QSystemTrayIcon::Information,15000);

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
               musicAdd.setMedia(QUrl("C:/Users/ASUS I7/Desktop/Atelier_Connexion/supp succe.mp3"));
                       musicAdd.play();
                       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                               notifyIcon->show();
                               notifyIcon->setIcon(QIcon("icone.png"));

                               notifyIcon->showMessage("GESTION COLLABORATEURS  CONTRAT ","Contrat Supprimé",QSystemTrayIcon::Information,15000);
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
        musicAdd.setMedia(QUrl("C:/Users/ASUS I7/Desktop/Atelier_Connexion/modif succe.mp3"));
                musicAdd.play();
        ui->tableView_2->setModel(T.afficher());

                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->setIcon(QIcon("icone.png"));

                        notifyIcon->showMessage("GESTION COLLABORATEURS  CONTRAT ","contrat Modifié",QSystemTrayIcon::Information,15000);
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




void MainWindow::on_imprimer_clicked()
{
QPdfWriter pdf("C:/collaboration/Pdf.pdf");
                   QPainter painter(&pdf);
                  int i = 4000;
                       painter.setPen(Qt::red);
                       painter.setFont(QFont("Comic Sans MS", 30));
                       painter.drawText(1100,1100,"Liste Des Contrats ");
                       painter.setPen(Qt::blue);
                       painter.setFont(QFont("Comic Sans MS", 50));
                       painter.drawRect(100,100,7300,1900);
                       painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/collaboration/logo"));
                       painter.setPen(Qt::blue);

                       painter.drawRect(0,3000,9600,500);
                       painter.setPen(Qt::darkGreen);

                       painter.setFont(QFont("Calibri", 15));
                       painter.drawText(200,3300,"Type");
                       painter.drawText(1800,3300,"Nom");
                       painter.drawText(3300,3300,"duree");
                       painter.drawText(5300,3300,"Tarif");
                       painter.drawText(6800,3300,"Idcollaborateur");




                       QSqlQuery query;
                       query.prepare("select * from contrat");
                       query.exec();
                       while (query.next())
                       {
                           painter.setPen(Qt::blue);
                           painter.drawText(200,i,query.value(0).toString());
                           painter.setPen(Qt::black);
                           painter.drawText(1800,i,query.value(1).toString());
                           painter.drawText(3300,i,query.value(2).toString());
                           painter.drawText(5300,i,query.value(3).toString());
                           painter.drawText(6800,i,query.value(4).toString());
                           painter.setPen(Qt::red);

                           painter.drawText(8300,i,query.value(5).toString());



                          i = i + 500;
                       }
                       int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré! -Voulez-Vous Affichez Le PDF ?",QMessageBox::Yes |  QMessageBox::No);
                           if (reponse == QMessageBox::Yes)
                           {
                               QDesktopServices::openUrl(QUrl::fromLocalFile("C:/collaboration/Pdf.pdf"));
                               painter.end();
                           }
                           if (reponse == QMessageBox::No)
                           {
                                painter.end();
                           }
    }

void MainWindow::on_le_stat_clicked()
{

        statis *w=new statis();
        w->make();
        w->show();

}
