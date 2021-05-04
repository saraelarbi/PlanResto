#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mailing.h"
#include"music.h"
#include"materiel.h"
#include"remise.h"
#include"client.h"
#include"commande.h"
#include"calculatrice.h"
#include<QFileDialog>
#include"fournisseur.h"
#include<QTextDocument>
#include<QTextStream>
#include <QGraphicsView>
#include <QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QSystemTrayIcon>
#include<QMediaPlayer>
#include<QUrlQuery>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include "fonction.h"
#include "emplyer.h"
#include "emplyer.h"
#include "dialog.h"
#include <QDate>
#include <QTime>
#include<QMessageBox>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include <QtPrintSupport/QPrinter>
#include <QDesktopServices>
#include <QSound>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    son=new QSound("C:/Users/ASUS/Desktop/qt/SmartResto/ss.wav");

    mSystemTrayIcon = new QSystemTrayIcon(this);

    mSystemTrayIcon->setVisible(true);

    ui->affichage->setModel(supp.afficher());
    ui->tableView->setModel(sup.afficher());
    ui->affichage->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->affichage->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->CIN->setPlaceholderText("CIN ...");
    ui->nom->setPlaceholderText("Nom ...");
    ui->prenom->setPlaceholderText("Prenom ...");
    ui->Telephone->setPlaceholderText("Téléphone ...");
    ui->email->setPlaceholderText("Email ...");
    ui->Adress->setPlaceholderText("Adresse ...");

    ui->TypeFonction->setPlaceholderText("Type de fonction ...");
    ui->Salaire->setPlaceholderText("Salaire ...");
    ui->Jourdetravail->setPlaceholderText("Jour de travail ...");

    ui->heurededebut->setPlaceholderText("Heure de debut ...");
    ui->heuredefin->setPlaceholderText("Heure de fin ...");
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    ui->tab_mat->setModel(M.afficher());
    ui->tab_fou->setModel(F.afficher());
    ui->tab_mail->setModel(F.afficher());
    ui->tab_rem->setModel(R.afficher());
    ui->tel->setMaxLength(8);
    ui->id->setMaxLength(10);
    ui->cinf->setMaxLength(8);
    ui->prix->setValidator(new QIntValidator(0, 999999999, this));
    ui->tel->setValidator(new QIntValidator(0, 99999999, this));
    ui->ancien_prix->setValidator(new QIntValidator(0, 999999999, this));
    ui->nouveau_prix->setValidator(new QIntValidator(0, 999999999, this));
    ui->cinf->setValidator(new QIntValidator(0, 99999999, this));


    int nb=ui->affichage->model()->rowCount();
                   ui->TypeFonction_2->clear();

                   for (int i=0;i<nb;i++)
                   {
                       QString type_fonction = ui->affichage->model()->index(i, 0).data().toString();
                       ui->TypeFonction_2->addItem(type_fonction);
                   }








                  QPixmap pix("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/images/PRR");
                  ui->img->setPixmap(pix);
                  animation = new QPropertyAnimation(ui->img,"geometry");
                  animation->setDuration(10000);
                  animation->setStartValue(ui->img->geometry());
                  animation->setEndValue(QRect(610,0,100,100));
                  animation->start();
                   ui->tab_mat->setSelectionBehavior(QAbstractItemView::SelectRows);
                   ui->tab_mat->setSelectionMode(QAbstractItemView::SingleSelection);
                   ui->tab_fou->setSelectionBehavior(QAbstractItemView::SelectRows);
                   ui->tab_fou->setSelectionMode(QAbstractItemView::SingleSelection);

                   int cleR=ui->tab_mat->model()->rowCount();
                   ui->id_materiel->clear();
                   for (int i=0;i<cleR;i++)
                   {QString id = ui->tab_mat->model()->index(i, 0).data().toString();
                       ui->id_materiel->addItem(id);
               }

                   int nbb=ui->tab_fou->model()->rowCount();
                                      ui->cinfet->clear();

                                      for (int i=0;i<nbb;i++)
                                      {
                                          QString cinf = ui->tab_fou->model()->index(i, 0).data().toString();
                                          ui->cinfet->addItem(cinf);



               }
                                      //arduino
                int ret=A.connect_arduino();
                switch(ret){
                case(0):qDebug()<< "arduino is availble and connected to :"<< A.getarduino_port_name();
                    break;
                case(1):qDebug()<< "arduino is availble but not connected to :"<< A.getarduino_port_name();
                    break;
                case(-1):qDebug()<< "arduino is not availble";
                }
                QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


               }



void MainWindow::sendMail()
{
    Mailing* mailing = new Mailing(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(mailing, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    ui->tab_mail->setModel(F.afficher());

    mailing->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->message->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple Mailing fournisseur" ), tr( "Message envoyer!\n\n" ) );
}


/*bool MainWindow::verifCHAMPVIDE()
{

    if(ui->nom_3->text().isEmpty() || ui->id->text().isEmpty() || ui->type->text().isEmpty() || ui->marque->text().isEmpty() ||  ui->prix->text().isEmpty())
    {
         ui->nom_3->clear();
         ui->id->clear();
         ui->type->clear();
         ui->marque->clear();
         ui->cinfet->clear();
         ui->prix->clear();

         ui->nom->setPlaceholderText("VIDE") ;
         ui->id->setPlaceholderText("VIDE") ;
         ui->type->setPlaceholderText("VIDE") ;
         ui->marque->setPlaceholderText("VIDE") ;
         ui->prix->setPlaceholderText("VIDE") ;

         return false;


    }
    else
    {
        return true;
    }
}


bool MainWindow::verifNOM()
{
    if (ui->nom_3->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->nom_3->text().isEmpty())
    {
        ui->nom_3->clear();
        ui->nom_3->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::verifTYPE()
{
    if (ui->type->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->type->text().isEmpty())
    {
        ui->type->clear();
        ui->type->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::verifMARQUE()
{
    if (ui->marque->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->marque->text().isEmpty())
    {
        ui->marque->clear();
        ui->marque->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::verifNOMF()
{
    if (ui->nom_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->nom_2->text().isEmpty())
    {
        ui->nom_2->clear();
        ui->nom_2->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::verifPRENOM()
{
    if (ui->prenom_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->prenom_2->text().isEmpty())
    {
        ui->prenom_2->clear();
        ui->prenom_2->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::verifTYPE2()
{
    if (ui->type_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->type_2->text().isEmpty())
    {
        ui->type_2->clear();
        ui->type_2->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::verifADRESSE()
{
    if (ui->adresse->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->adresse->text().isEmpty())
    {
        ui->adresse->clear();
        ui->adresse->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}*/

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{     son->play();
    QString id=ui->id->text();
    QString nom=ui->nom->text();
    QString type=ui->type->text();
    QString marque=ui->marque->text();
    QString prix=ui->prix->text();
    QString cinf=ui->cinfet->currentText();



    Materiel M(id,nom,type,marque,prix,cinf);
        bool test2=M.ajouter();



          if( test2/*&&verifCHAMPVIDE() && verifNOM() && verifTYPE() && verifMARQUE()*/)
    {
        ui->tab_mat->setModel(M.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/ajout succe.mp3"));
                musicAdd.play();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION MATERIEL ","L'ajout du materiel est effectué",QSystemTrayIcon::Information,15000);

            QMessageBox::information(nullptr, QObject::tr("Ajouter Materiel"),
                                  QObject::tr("Materiel ajouté"),QMessageBox::Cancel);
            int cleR=ui->tab_mat->model()->rowCount();
                           ui->id_materiel->clear();

                           for (int i=0;i<cleR;i++)
                           {
                               QString id = ui->tab_mat->model()->index(i, 0).data().toString();
                               ui->id_materiel->addItem(id);
          }
            }

            else
                QMessageBox::critical(nullptr, QObject::tr("Ajouter Materiel"),
                                      QObject::tr("Erreur!"),QMessageBox::Cancel);


        }








void MainWindow::on_ajout2_clicked()
{
    QString cinf=ui->cinf->text();
    QString nom=ui->nom_2->text();
    QString prenom=ui->prenom_2->text();
    QString type=ui->type_2->text();
    QString tel=ui->tel->text();
    QString email=ui->email_2->text();
    QString adresse=ui->adresse->text();


    Fournisseur F(cinf,nom,prenom,type,tel,email,adresse);
    bool test2=F.ajouter();


    if(test2/* && verifNOMF()&&verifTYPE2()&&verifPRENOM()&&verifADRESSE()*/)
    {
        ui->tab_fou->setModel(F.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/ajout succe.mp3"));
                musicAdd.play();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION FOURNISSEUR ","L'ajout du fournisseur est effectué",QSystemTrayIcon::Information,15000);


                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué.\n"
                                            "Click ok to exit."), QMessageBox::Cancel);
                    int nbb=ui->tab_fou->model()->rowCount();
                                   ui->cinfet->clear();

                                   for (int i=0;i<nbb;i++)
                                   {
                                       QString cinf = ui->tab_fou->model()->index(i, 0).data().toString();
                                       ui->cinfet->addItem(cinf);
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
            musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/modif succe.mp3"));
                    musicAdd.play();
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
            musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/modif succe.mp3"));
                    musicAdd.play();
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
                                  QMessageBox::warning(this,"erreur","Champ vide");
                          } else
                              QMessageBox::warning(this,"erreur","Champ vide");
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
                              QMessageBox::warning(this,"erreur","Champ vide");
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
                              QMessageBox::warning(this,"erreur","Champ vide");
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
                               QMessageBox::warning(this,"erreur","Champ vide");
                       } else
                           QMessageBox::warning(this,"erreur","Champ vide");

       }
}



void MainWindow::on_pb_supp2_clicked()
{
    QItemSelectionModel *select = ui->tab_fou->selectionModel();
        QString cinf = select->selectedRows(0).value(0).data().toString();

       if(F.supprimer(cinf))
       {
           ui->tab_fou->setModel(F.afficher());
           musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/supp succe.mp3"));
                   musicAdd.play();
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();
                   notifyIcon->setIcon(QIcon("icone.png"));

                   notifyIcon->showMessage("GESTION MATERIEL ","La suppression du fournisseur est effectuée",QSystemTrayIcon::Information,15000);

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Suppression effectué.\n"
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
                       QObject::tr("Suppression non effectue.\n"
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
           musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/supp succe.mp3"));
                   musicAdd.play();
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();
                   notifyIcon->setIcon(QIcon("icone.png"));

                   notifyIcon->showMessage("GESTION MATERIEL ","La suppression du materiel est effectuée",QSystemTrayIcon::Information,15000);

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Suppression effectué.\n"
                                   "Click ok to exit."), QMessageBox::Cancel);
       }
       else
          {
              QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                          QObject::tr("Suppression non effectue.\n"
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
        ui->nom_2->setText("");
        ui->marque->setText("");
        ui->prix->setText("");
}


void MainWindow::on_reset_Fou_clicked()
{
    ui->cinf->setText("");
    ui->nom_3->setText("");
    ui->prenom_2->setText("");
    ui->type_2->setText("");
    ui->tel->setText("");
    ui->email_2->setText("");
    ui->adresse->setText("");

}

void MainWindow::on_pushButton_2_clicked()
{


                   QPdfWriter pdf("C:/PR/Materiel/sara/Pdf.pdf");
                   QPainter painter(&pdf);
                  int i = 4000;
                       painter.setPen(Qt::red);
                       painter.setFont(QFont("Comic Sans MS", 30));
                       painter.drawText(1100,1100,"Liste Des Matériels ");
                       painter.setPen(Qt::blue);
                       painter.setFont(QFont("Comic Sans MS", 50));
                       painter.drawRect(100,100,7300,1900);
                       painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/PR/Materiel/logo/PRR"));
                       painter.setPen(Qt::blue);

                       painter.drawRect(0,3000,9600,500);
                       painter.setPen(Qt::green);

                       painter.setFont(QFont("Comic Sans MS", 15));
                       painter.drawText(200,3300,"Identifiant");
                       painter.drawText(1800,3300,"Nom");
                       painter.drawText(3300,3300,"Type");
                       painter.drawText(5300,3300,"Marque");
                       painter.drawText(6800,3300,"Prix");

                       painter.drawText(8300,3300,"CinF");



                       QSqlQuery query;
                       query.prepare("select * from materiel");
                       query.exec();
                       while (query.next())
                       {
                           painter.setPen(Qt::red);
                           painter.drawText(200,i,query.value(0).toString());
                           painter.setPen(Qt::black);
                           painter.drawText(1800,i,query.value(1).toString());
                           painter.drawText(3300,i,query.value(2).toString());
                           painter.drawText(5300,i,query.value(3).toString());
                           painter.drawText(6800,i,query.value(4).toString());
                           painter.setPen(Qt::blue);

                           painter.drawText(8300,i,query.value(5).toString());



                          i = i + 500;
                       }
                       int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré! -Voulez-Vous Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                           if (reponse == QMessageBox::Yes)
                           {
                               QDesktopServices::openUrl(QUrl::fromLocalFile("C:/PR/Materiel/sara/Pdf.pdf"));
                               painter.end();
                           }
                           if (reponse == QMessageBox::No)
                           {
                                painter.end();
                           }
    }






void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    Fournisseur f;
        if(ui->recherche->text() == "")
            {
                ui->tab_fou->setModel(f.afficher());
            }
            else
            {
                 ui->tab_fou->setModel(f.rechercher(ui->recherche->text()));
            }
}


void MainWindow::on_imp_F_clicked()
{

    QPdfWriter pdf("C:/PR/Fournisseur/Pdf2.pdf");
    QPainter painter(&pdf);
   int i = 4000;
      int y =7200;
        painter.setPen(Qt::red);
        painter.setFont(QFont("Comic Sans MS", 30));
        painter.drawText(1100,1100,"Liste Des Matériels ");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Comic Sans MS", 50));
        painter.drawRect(100,100,7300,1900);
        painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/PR/Materiel/logo/PRR"));
        painter.setPen(Qt::blue);

        painter.drawRect(0,3000,9600,500);
        painter.drawRect(0,6000,4000,500);
        painter.setPen(Qt::green);

        painter.setFont(QFont("Comic Sans MS", 15));
        painter.drawText(200,3300,"CinF");
        painter.drawText(1700,3300,"Nom");
        painter.drawText(3200,3300,"Prenom");
        painter.drawText(5000,3300,"Type");
        painter.drawText(6500,3300,"Tel");
        painter.drawText(200,6300,"Email");
        painter.drawText(8000,3300,"Adresse");





        QSqlQuery query;
        query.prepare("select * from fournisseur");
        query.exec();
        while (query.next())
        {
            painter.setPen(Qt::red);
            painter.drawText(200,i,query.value(0).toString());
            painter.setPen(Qt::black);
            painter.drawText(1700,i,query.value(1).toString());
            painter.drawText(3200,i,query.value(2).toString());
            painter.drawText(5000,i,query.value(3).toString());
            painter.drawText(6500,i,query.value(4).toString());

            painter.drawText(200,y,query.value(5).toString());
            painter.drawText(8000,i,query.value(6).toString());




           i = i + 500;
           y = y + 500;
        }
        int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré! -Voulez-Vous Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/PR/Fournisseur/Pdf2.pdf"));
                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }
}








void MainWindow::on_refresh_clicked()
{
    QByteArray data=A.read_from_arduino();
      if(data.size()>10){
      QString temp =QString::fromStdString(data.toStdString());
      ui->textEdit->setText(temp);
}
}









void MainWindow::on_envoyer_sms_clicked()
{

   QNetworkAccessManager * manager = new QNetworkAccessManager(this);

        QUrl url("https://ACd77b28e4e747e4f825b5d0ce7b49bbb7:6fd6b9eb93804911729d62c59325433d@api.twilio.com/2010-04-01/Accounts/ACd77b28e4e747e4f825b5d0ce7b49bbb7/Messages.json");
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


        QUrlQuery params;
        params.addQueryItem("From", "+13305945433");
        params.addQueryItem("To",ui->num_sms->text() );//"+21693743474"
        params.addQueryItem("Body", ui->message_sms->toPlainText());
       // params.addQueryItem("Body", "test");

        // etc

        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply*)));

        manager->post(request, params.query().toUtf8());

    }
    void MainWindow::replyFinished(QNetworkReply* reply)
    {
        //QByteArray bts = rep->readAll();


        QByteArray buffer = reply->readAll();
        qDebug() << buffer;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
        QJsonObject jsonReply = jsonDoc.object();

        QJsonObject response = jsonReply["response"].toObject();
        QJsonArray  data     = jsonReply["data"].toArray();
        qDebug() << data;
        qDebug() << response;


    }

void MainWindow::on_musique_materiel_clicked()
{
    music music;
    music.setModal(true);
    music.exec();
}

void MainWindow::on_musique_fournisseur_clicked()
{
    music music;
    music.setModal(true);
    music.exec();
}

void MainWindow::on_musique_mail_clicked()
{
    music music;
    music.setModal(true);
    music.exec();
}



void MainWindow::on_musique_temp_clicked()
{
    music music;
    music.setModal(true);
    music.exec();
}


void MainWindow::on_Ajout_remise_clicked()
{
    QString idmateriel=ui->id_materiel->currentText();
    QString remise=ui->remise->text();
    QDate dates=ui->date->date();
     QString ancienprix=ui->ancien_prix->text();
      QString nouveauprix=ui->nouveau_prix->text();

    Remise R(idmateriel,remise,dates,ancienprix,nouveauprix);


    bool test2=R.ajouter();
    /*if((idmateriel=="")&&(remise==""))
       {
        QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                              QObject::tr("Tous les champs sont vides"),QMessageBox::Ok);
    }
     else if((idmateriel==""))
    {
     QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                           QObject::tr("Le champ ID Materiel est vide"),QMessageBox::Ok);
 }
    else if((remise==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Remise est vide"),QMessageBox::Ok);
}
    else if((dates==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Dates est vide"),QMessageBox::Ok);
}
    else if((ancienprix==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Ancien prix est vide"),QMessageBox::Ok);
}
    else if((nouveauprix==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Nouveau prix est vide"),QMessageBox::Ok);
}

*/
     if(test2)
    {
        ui->tab_rem->setModel(R.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/ajout succe.mp3"));
                musicAdd.play();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION REMISE ","L'ajout de la remise est effectué",QSystemTrayIcon::Information,15000);

            QMessageBox::information(nullptr, QObject::tr("Ajouter Remise"),
                                  QObject::tr("Remise ajouté"),QMessageBox::Cancel);
            }

            else
                QMessageBox::critical(nullptr, QObject::tr("Ajouter Remise"),
                                      QObject::tr("Erreur!"),QMessageBox::Cancel);


}


void MainWindow::on_Calculatrice_clicked()
{
    Calculatrice calc;
    calc.setModal(true);
    calc.exec();
}

void MainWindow::on_Musique_rem_clicked()
{
    music music;
    music.setModal(true);
    music.exec();
}

void MainWindow::on_Modif_rem_clicked()
{
    if (ui->Modif_rem->isChecked())
        {
            ui->Modif_rem->setText("Modifiable");
            QSqlTableModel *tableModel= new QSqlTableModel();
            tableModel->setTable("REMISE");
            tableModel->select();
            ui->tab_rem->setModel(tableModel);
        }
        else
        {
            ui->Modif_rem->setText("Modifier");
            ui->tab_rem->setModel(R.afficher());
            musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/modif succe.mp3"));
                    musicAdd.play();
            QMessageBox::information(nullptr, QObject::tr("modification remise"),
                        QObject::tr("Remise modifiée.\n"

    "Click OK to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_exel_rem_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                           tr("Excel Files (*.xls)"));
           if (fileName.isEmpty())
               return;

           ExportExcelObject obj(fileName, "mydata", ui->tab_rem);

           //colums to export
           obj.addField(0, "IDMATERIEL", "char(20)");
           obj.addField(1, "REMISE", "char(20)");
           obj.addField(2, "DATES", "char(20)");
           obj.addField(2, "ANCIENPRIX", "char(20)");
           obj.addField(2, "NOUVEAUPRIX", "char(20)");




           int retVal = obj.export2Excel();
           if( retVal > 0)
           {
               QMessageBox::information(this, tr("Done"),
                                        QString(tr("%1 records exported!")).arg(retVal)
                                        );
           }
}

void MainWindow::on_supp_rem_clicked()
{
    QItemSelectionModel *select = ui->tab_rem->selectionModel();
        QString idmateriel = select->selectedRows(0).value(0).data().toString();

       if(R.supprimer(idmateriel))
       {
           ui->tab_rem->setModel(R.afficher());
           musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/supp succe.mp3"));
                   musicAdd.play();
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();
                   notifyIcon->setIcon(QIcon("icone.png"));

                   notifyIcon->showMessage("GESTION MATERIEL ","La suppression du materiel est effectuée",QSystemTrayIcon::Information,15000);

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Suppression effectué.\n"
                                   "Click ok to exit."), QMessageBox::Cancel);
       }
       else
          {
              QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                          QObject::tr("Suppression non effectue.\n"
                                      "Click OK to exit."), QMessageBox::Cancel);
          }

}


void MainWindow::on_rech_rem_textChanged(const QString &arg1)
{
    Remise R;
        if(ui->rech_rem->text() == "")
            {
                ui->tab_rem->setModel(R.afficher());
            }
            else
            {
                 ui->tab_rem->setModel(R.rechercher2(ui->rech_rem->text()));
            }
}



void MainWindow::on_Aymen_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Moemen_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_Salma_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_Sara_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_Taher_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_Ghazi_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_Configuration_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_Aymen_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Moemen_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_Salma_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_Sara_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_Taher_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_Ghazi_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_Configuration_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_Aymen_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Moemen_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_Salma_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_Sara_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_Taher_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_Ghazi_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_Configuration_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_Aymen_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Moemen_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_Salma_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_Sara_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_Taher_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_Ghazi_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_Configuration_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_Aymen_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Moemen_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_Salma_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_Sara_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_Taher_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_Ghazi_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_Configuration_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_Aymen_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Moemen_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_Salma_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_Sara_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_Taher_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_Ghazi_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_Configuration_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_Aymen_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_Moemen_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_Salma_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_Sara_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_Taher_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_Ghazi_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_Configuration_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_ajouter_fonction_clicked()
{
    son->play();
        QString typefonction=ui->TypeFonction->text();
        QString salaire=ui->Salaire->text();
        QString jourdetravail=ui->Jourdetravail->text();
        QString heurededebut=ui->heurededebut->text();
        QString heuredefin=ui->heuredefin->text();
        QDate debutdeconge=ui->debutdeconges->date();
        QDate findeconge=ui->findeconges->date();


        fonction M(typefonction,salaire,jourdetravail,heurededebut,heuredefin,debutdeconge,findeconge);


        bool test=M.ajouter();

        if(test)
        {
            ui->affichage->setModel(supp.afficher());
            musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/ajout succe.mp3"));
            musicAdd.play();

            mSystemTrayIcon->showMessage(tr("Notification"),
                                                tr("Ajout effectué"));

           /* QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Ajout effectué.\n"
                                    "Click ok to exit."), QMessageBox::Cancel);*/

            int nb=ui->affichage->model()->rowCount();
                           ui->TypeFonction_2->clear();

                           for (int i=0;i<nb;i++)
                           {
                               QString type_fonction = ui->affichage->model()->index(i, 0).data().toString();
                               ui->TypeFonction_2->addItem(type_fonction);
                           }


    }
        else

            mSystemTrayIcon->showMessage(tr("Notification"),
                                                tr("Ajout non effectué"));

           /* QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Ajout non effectue.\n"
                                    "Click OK to exit."), QMessageBox::Cancel);*/
}

void MainWindow::on_supprimer_fonction_clicked()
{
    son->play();
    QItemSelectionModel *select = ui->affichage->selectionModel();
    QString typefonction = select->selectedRows(0).value(0).data().toString();

   if(supp.supprimer(typefonction))
   {
       ui->affichage->setModel(supp.afficher());
       musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/supp succe.mp3"));
       musicAdd.play();

       mSystemTrayIcon->showMessage(tr("Notification"),
                                           tr("Suppression effectué"));

       /*QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("suppression effectué.\n"
                               "Click ok to exit."), QMessageBox::Cancel);*/

       int nb=ui->affichage->model()->rowCount();
                      ui->TypeFonction_2->clear();

                      for (int i=0;i<nb;i++)
                      {
                          QString type_fonction = ui->affichage->model()->index(i, 0).data().toString();
                          ui->TypeFonction_2->addItem(type_fonction);
                      }
   }
   else
   {
       mSystemTrayIcon->showMessage(tr("Notification"),
                                           tr("Suppression non effectué"));

       /*QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                   QObject::tr("suppression non effectue.\n"
                               "Click OK to exit."), QMessageBox::Cancel);*/
    }
}


void MainWindow::on_ajouter_emplye_clicked()
{
    son->play();

    QString CIN=ui->CIN->text();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString TypeFonction=ui->TypeFonction_2->currentText();
    QString Telephone=ui->Telephone->text();
    QString email=ui->email->text();
    QString Adress=ui->Adress->text();
histo.save("CIN:"+ui->CIN->text(),"Nom :"+ui->nom->text());


    Employes E(CIN,nom,prenom,TypeFonction,Telephone,email,Adress);


    bool test=E.ajouter();

    if(test)
    {
        ui->tableView->setModel(sup.afficher());

        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/ajout succe.mp3"));
        musicAdd.play();
        mSystemTrayIcon->showMessage(tr("Notification"),
                                            tr("Ajout effectué"));

        /*QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click ok to exit."), QMessageBox::Cancel);*/

}
    else
        mSystemTrayIcon->showMessage(tr("Notification"),
                                            tr("Ajout non effectué"));
        /*QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectue.\n"
                                "Click OK to exit."), QMessageBox::Cancel);*/


}

void MainWindow::on_supprimer_emplye_clicked()
{
    son->play();
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QString C = select->selectedRows(0).value(0).data().toString();

   if(sup.supprimer(C))
   {
       ui->tableView->setModel(sup.afficher());
       musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/supp succe.mp3"));
       musicAdd.play();

       mSystemTrayIcon->showMessage(tr("Notification"),
                                           tr("Suppression effectué"));

       /*QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("suppression effectué.\n"
                               "Click ok to exit."), QMessageBox::Cancel);*/
   }
   else
   {
       mSystemTrayIcon->showMessage(tr("Notification"),
                                           tr("Suppression non effectué"));

       /*QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                   QObject::tr("suppression non effectue.\n"
                               "Click OK to exit."), QMessageBox::Cancel);*/
   }
}

void MainWindow::on_MFonction_clicked()
{
    son->play();

if (ui->MFonction->isChecked())
{
    ui->MFonction->setText("Modifiable");
    QSqlTableModel *tableModel= new QSqlTableModel();
    tableModel->setTable("FC");
    tableModel->select();
    ui->affichage->setModel(tableModel);
}
else
{
    ui->MFonction->setText("Modifier");
    ui->affichage->setModel(supp.afficher());
    musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/modif succe.mp3"));
    musicAdd.play();

    mSystemTrayIcon->showMessage(tr("Notification"),
                                        tr("Modification effectué"));

    /*QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                QObject::tr("Fonction modifié.\n"
                            "Click OK to exit."), QMessageBox::Cancel);*/

}
}

void MainWindow::on_MEmploye_clicked()
{
    son->play();
    if (ui->MEmploye->isChecked())
    {
        ui->MEmploye->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("EM");
        tableModel->select();
        ui->tableView->setModel(tableModel);
    }
    else
    {
        ui->MEmploye->setText("Modifier");
        ui->tableView->setModel(sup.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/modif succe.mp3"));
        musicAdd.play();

        mSystemTrayIcon->showMessage(tr("Notification"),
                                            tr("Modification non effectué"));

        /*QMessageBox::information(nullptr, QObject::tr("modification employe"),
                    QObject::tr("Employe modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);*/

    }
}

void MainWindow::on_resetf_clicked()
{
    son->play();
    ui->TypeFonction->setText("");
    ui->Salaire->setText("");
    ui->Jourdetravail->setText("");
    ui->heurededebut->setText("");
    ui->heuredefin->setText("");

}

void MainWindow::on_resetP_clicked()
{
    son->play();
    ui->CIN->setText("");
    ui->nom->setText("");
    ui->prenom->setText("");
    ui->Telephone->setText("");
    ui->email->setText("");
    ui->Adress->setText("");
}

void MainWindow::on_rechercherf_clicked()
{
    if (ui->checkBox_salaire->isChecked())
       { QString salaire=ui->rech_salaire->text();
           QSqlQueryModel *verif=supp.rechercher_salaire(salaire);
           if (verif!=nullptr)
           {
               ui->affichage->setModel(verif);

           }
        }

     if (ui->checkBox_jourdetravail->isChecked())
       { QString jourdetravail=ui->rech_jourdetravail->text();
           QSqlQueryModel *verif=supp.rechercher_jourdetravail(jourdetravail);
           if (verif!=nullptr)
           {

               ui->affichage->setModel(verif);

           }
        }
      if (ui->checkBox_findeconge->isChecked())
       { QDate findeconge=ui->rech_findeconge->date();
           QSqlQueryModel *verif=supp.rechercher_findeconge(findeconge);
           if (verif!=nullptr)
           {

               ui->affichage->setModel(verif);

           }
        }
       if ((ui->checkBox_salaire->isChecked())&&(ui->checkBox_jourdetravail->isChecked()))
       {
           QString salaire=ui->rech_salaire->text();
           QString jourdetravail=ui->rech_jourdetravail->text();

                       if (salaire!="")
                         {
                           if (jourdetravail!="")
                              {
                       QSqlQueryModel *verif=supp.rechercher_salaire_jourdetravail(salaire,jourdetravail);
                       if (verif!=nullptr)
                       {
                           ui->affichage->setModel(verif);

                       }
                           } else
                               QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
                       } else
                           QMessageBox::warning(this,"erreur","Champ salaire est vide");
       }
      if ((ui->checkBox_salaire->isChecked())&&(ui->checkBox_findeconge->isChecked()))
       {
           QString salaire=ui->rech_salaire->text();
          QDate findeconge=ui->rech_findeconge->date();

                       if (salaire!="")
                         {
                       QSqlQueryModel *verif=supp.rechercher_salaire_findeconge(salaire,findeconge);
                       if (verif!=nullptr)
                       {
                           ui->affichage->setModel(verif);

                       }

                       } else
                           QMessageBox::warning(this,"erreur","Champ salaire est vide");
       }
       if ((ui->checkBox_jourdetravail->isChecked())&&(ui->checkBox_findeconge->isChecked()))
       {
          QString jourdetravail=ui->rech_jourdetravail->text();
          QDate findeconge=ui->rech_findeconge->date();

                       if (jourdetravail!="")
                         {
                       QSqlQueryModel *verif=supp.rechercher_jourdetravail_findeconge(jourdetravail,findeconge);
                       if (verif!=nullptr)
                       {
                           ui->affichage->setModel(verif);

                       }

                       } else
                           QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
       }


    if ((ui->checkBox_salaire->isChecked())&&(ui->checkBox_findeconge->isChecked())&&(ui->checkBox_jourdetravail->isChecked()))
    {

        QDate findeconge=ui->rech_findeconge->date();
        QString salaire=ui->rech_salaire->text();
        QString jourdetravail=ui->rech_jourdetravail->text();

                    if (salaire!="")
                      {
                        if (jourdetravail!="")
                           {
                    QSqlQueryModel *verif=supp.rechercher_tous(salaire,jourdetravail,findeconge);
                    if (verif!=nullptr)
                    {

                        ui->affichage->setModel(verif);

                    }
                        } else
                            QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
                    } else
                        QMessageBox::warning(this,"erreur","Champ salaire est vide");

    } //else QMessageBox::warning(this,"erreur","Aucun critére n'est coché");

}

void MainWindow::on_reafficherf_clicked()
{
    son->play();

    ui->rech_salaire->setText("");
    ui->rech_jourdetravail->setText("");
    ui->affichage->setModel(supp.afficher());

}

void MainWindow::on_radioButton_triNom_clicked()
{
    {QMessageBox msgBox ;
           QSqlQueryModel * model= new QSqlQueryModel();


              model->setQuery("select * from EM order by nom");

              model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("TypeFonction"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("Telephone"));
              model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
              model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adress"));

                       ui->tableView->setModel(model);
                       ui->tableView->show();
                       msgBox.setText("Tri affecté sur le nom.");
                       msgBox.exec();

       }
}

void MainWindow::on_radioButton_triPrenom_clicked()
{
    {QMessageBox msgBox ;
           QSqlQueryModel * model= new QSqlQueryModel();


              model->setQuery("select * from EM order by prenom");

              model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("TypeFonction"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("Telephone"));
              model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
              model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adress"));

                       ui->tableView->setModel(model);
                       ui->tableView->show();
                       msgBox.setText("Tri affecté sur le prenom.");
                       msgBox.exec();

       }
}

void MainWindow::on_radioButton_triTelephone_clicked()
{
    {QMessageBox msgBox ;
           QSqlQueryModel * model= new QSqlQueryModel();


              model->setQuery("select * from EM order by Telephone asc");

              model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("TypeFonction"));
              model->setHeaderData(4, Qt::Horizontal, QObject::tr("Telephone"));
              model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
              model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adress"));

                       ui->tableView->setModel(model);
                       ui->tableView->show();
                       msgBox.setText("Tri affecté sur le téléphone.");
                       msgBox.exec();

       }
}

void MainWindow::on_exporter_employer_clicked()
{
    son->play();
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("liste_employers.pdf"); }

           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);

           QTextDocument doc;
           QSqlQuery q;
           q.prepare("SELECT * FROM EM ");
           q.exec();
           QString pdf="<br> <img src='C:/Users/ASUS/Desktop/qt/SmartResto/logo.png' height='50' width='150'/> <h1  style='color:red'>       LISTE DES EMPLOYES  <br></h1>\n <br> <table>  <tr>  <th> CIN </th> <th> Nom </th> <th> Prenom </th> <th> Typefonction  </th> <th> Téléphone </th> <th> Email </th> <th> Adresse </th> </tr>" ;


           while ( q.next()) {

               pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"</td>  <td>" +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"--------"+"</td>       <td>"+q.value(4).toString()+"       </td>   <td>"+ q.value(5).toString()+"    </td>       <td>"+ q.value(6).toString()+"    </td>" ;

           }
           doc.setHtml(pdf);
           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);
}

void MainWindow::on_web_clicked()
{
    son->play();
    QString link="http://www.expat.com/fr/emploi/hotel-bar-restaurant-tourisme.html";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_envoyer_mail_employe_clicked()
{
    son->play();
    QItemSelectionModel *select = ui->tableView->selectionModel();

    QString email_recipient = select->selectedRows(5).value(0).data().toString();
    QString nom_recipient = select->selectedRows(1).value(0).data().toString();
    QString prenom_recipient = select->selectedRows(2).value(0).data().toString();

    QDialog *d=new Dialog(email_recipient,nom_recipient,prenom_recipient,this);
    d->show();
    d->exec();
}



void MainWindow::on_pb_ajouter_2_clicked()
{
    son->play();


    QString id= ui->lineEdit_id->text();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString adresse= ui->lineEdit_adresse->text();
    QString tel= ui->lineEdit_tel->text();
    QString email= ui->lineEdit_email->text();

  client c(id,nom,prenom,adresse,tel,email);
   if(verifID()&&verifNOM()&&verifprenom()&&veriftel()&&verifemail()){
  bool test=c.ajouter();
  if(test)
{

      ui->tabclient_2->setModel(tmpclient.afficher());
      musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/ajout succe.mp3"));
      musicAdd.play();

      QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
              notifyIcon->show();
              notifyIcon->setIcon(QIcon("icone.png"));

              notifyIcon->showMessage("GESTION CLIENT  CLIENTS ","client Ajouté",QSystemTrayIcon::Information,15000);

QMessageBox::information(nullptr, QObject::tr("Ajouter un client"),
                  QObject::tr("Client ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
   }
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un client"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}


void MainWindow::on_resetClient_clicked()
{
    ui->lineEdit_id->setText("");
    ui->lineEdit_nom->setText("");
    ui->lineEdit_prenom->setText("");
    ui->lineEdit_tel->setText("");
    ui->lineEdit_adresse->setText("");
    ui->lineEdit_email->setText("");
}

void MainWindow::on_pb_rechercher_clicked()
{
    QString rech =ui->lineEditrech->text();
   ui->tabclient_2->setModel(tmpclient.rechercher(rech));
}

void MainWindow::on_reaficherClient_clicked()
{
    ui->lineEditrech->setText("");
    ui->tabclient_2->setModel(tmpclient.afficher());
}


void MainWindow::on_pb_tri_clicked()
{
    ui->tabclient_2->setModel(tmpclient.tri());
}


void MainWindow::on_pb_excel_clicked()
{
    QTableView *table;
        table = ui->tabclient_2;
        QString filters("CSV files (.csv);;All files (.*)");
        QString defaultFilter("CSV files (*.csv)");
        QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                           filters, &defaultFilter);
        QFile file(fileName);
        QAbstractItemModel *model =  table->model();
        if (file.open(QFile::WriteOnly | QFile::Truncate)) {
            QTextStream data(&file);
            QStringList strList;
            for (int i = 0; i < model->columnCount(); i++) {
                if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                    strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") << "\n";
            for (int i = 0; i < model->rowCount(); i++) {
                strList.clear();
                for (int j = 0; j < model->columnCount(); j++) {
                    if (model->data(model->index(i, j)).toString().length() > 0)
                        strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                    else
                        strList.append("");
                }
                data << strList.join(";") + "\n";
            }
            file.close();
            //QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
}
}

void MainWindow::on_pb_modifier_clicked()
{
    son->play();

    if (ui->pb_modifier->isChecked())
    {
        ui->pb_modifier->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("CLIENT");
        tableModel->select();
        ui->tabclient_2->setModel(tableModel);

    }
    else
    {
        ui->pb_modifier->setText("Modifier");
        ui->tabclient_2->setModel(tmpclient.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/modif succe.mp3"));
        musicAdd.play();

        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));
                notifyIcon->showMessage("GESTION Clients  CLIENTS ","Client Modifié",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("modification employe"),
                    QObject::tr("Employe modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_pb_supprimer_clicked()
{
    son->play();

    QItemSelectionModel *select = ui->tabclient_2->selectionModel();
    QString C = select->selectedRows(0).value(0).data().toString();

   if(tmpclient.supprimer(C))
   {
       ui->tabclient_2->setModel(tmpclient.afficher());
       musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/supp succe.mp3"));
       musicAdd.play();


       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
               notifyIcon->show();
               notifyIcon->setIcon(QIcon("icone.png"));

               notifyIcon->showMessage("GESTION Clients  CLIENTS ","Client suuprimé",QSystemTrayIcon::Information,15000);

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


void MainWindow::on_pushButton_6_clicked()
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);

        QUrl url("https://AC8471caf30a264b62b427dd7533503d3a:2f7569c904bd50c76c487d60faa31423@api.twilio.com/2010-04-01/Accounts/AC8471caf30a264b62b427dd7533503d3a/Messages.json");
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


        QUrlQuery params;
        params.addQueryItem("From", "+18327302656");
        params.addQueryItem("To",ui->num->text() );//"+21699419180"
        params.addQueryItem("Body", ui->textEdit->toPlainText());
       // params.addQueryItem("Body", "test");

        // etc

        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply*)));

        manager->post(request, params.query().toUtf8());

}

void MainWindow::on_pb_ajouter2_clicked()
{
    son->play();

   QString id= ui->lineEdit_id2->text();
   QString nom= ui->lineEdit_nom2->text();
   QString type= ui->lineEdit_type->text();
   QString prix= ui->lineEdit_prix->text();
   QString cinp= ui->lineEdit_cinp->text();



 commande co(id,nom,type,cinp,prix);
 if(verifID2()&&verifNOM2()&&verifTYPE()&&verifPRIX()&&verifcinp()){

 bool test=co.ajouter();
 if(test)
{
     ui->tabcommande_2->setModel(tmpcommande.afficher());
     musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/ajout succe.mp3"));
     musicAdd.play();

     QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
             notifyIcon->show();
             notifyIcon->setIcon(QIcon("icone.png"));

             notifyIcon->showMessage("GESTION Commandes  COMMANDE ","commande Ajouté",QSystemTrayIcon::Information,15000);

QMessageBox::information(nullptr, QObject::tr("Ajouter une commande"),
                 QObject::tr("Commande ajoutée.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}
 }
 else
     QMessageBox::critical(nullptr, QObject::tr("Ajouter un commande"),
                 QObject::tr("Erreur !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_resetCommande_clicked()
{
    ui->lineEdit_id2->setText("");
    ui->lineEdit_nom2->setText("");
    ui->lineEdit_type->setText("");
    ui->lineEdit_cinp->setText("");
    ui->lineEdit_prix->setText("");
}


void MainWindow::on_pb_rechercher2_clicked()
{
    QString rech =ui->lineEditrech2->text();
   ui->tabcommande_2->setModel(tmpcommande.rechercher(rech));
}

void MainWindow::on_reaficherCommande_clicked()
{
    ui->lineEditrech2->setText("");
    ui->tabcommande_2->setModel(tmpcommande.afficher());


}

void MainWindow::on_pb_tri2_clicked()
{
    ui->tabcommande_2->setModel(tmpcommande.tri());

}


void MainWindow::on_imprimer_clicked()
{
    QPdfWriter pdf("C:/commande/Pdf.pdf");
                       QPainter painter(&pdf);
                      int i = 4000;
                           painter.setPen(Qt::red);
                           painter.setFont(QFont("Comic Sans MS", 30));
                           painter.drawText(1100,1100,"Liste Des Commandes");
                           painter.setPen(Qt::blue);
                           painter.setFont(QFont("Comic Sans MS", 50));
                           painter.drawRect(100,100,7300,1900);
                           painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/commande/logo"));
                           painter.setPen(Qt::blue);

                           painter.drawRect(0,3000,9600,500);
                           painter.setPen(Qt::darkGreen);

                           painter.setFont(QFont("Calibri", 15));
                           painter.drawText(200,3300,"id");
                           painter.drawText(1800,3300,"nom");
                           painter.drawText(3300,3300,"type");
                           painter.drawText(5300,3300,"prix");
                           painter.drawText(6800,3300,"cinp");




                           QSqlQuery query;
                           query.prepare("select * from commande");
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
                                   QDesktopServices::openUrl(QUrl::fromLocalFile("C:/commande/Pdf.pdf"));
                                   painter.end();
                               }
                               if (reponse == QMessageBox::No)
                               {
                                    painter.end();
                               }
}

void MainWindow::on_pb_modifier2_clicked()
{
    son->play();

    if (ui->pb_modifier2->isChecked())
    {
        ui->pb_modifier2->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("COMMANDE");
        tableModel->select();
        ui->tabcommande_2->setModel(tableModel);

    }
    else
    {
        ui->pb_modifier2->setText("Modifier");
        ui->tabcommande_2->setModel(tmpcommande.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/modif succe.mp3"));
        musicAdd.play();

        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION Commande  COMMANDES ","Commande Modifié",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("modification employe"),
                    QObject::tr("Employe modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);

    }

}

void MainWindow::on_pb_supprimer2_clicked()
{
    son->play();

    QItemSelectionModel *select = ui->tabcommande_2->selectionModel();
    QString C = select->selectedRows(0).value(0).data().toString();

   if(tmpcommande.supprimer(C))
   {
       ui->tabcommande_2->setModel(tmpcommande.afficher());
       musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/supp succe.mp3"));
       musicAdd.play();


       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
               notifyIcon->show();
               notifyIcon->setIcon(QIcon("icone.png"));

               notifyIcon->showMessage("GESTION Commandes  COMMANDE ","commande supprimé",QSystemTrayIcon::Information,15000);

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

void MainWindow::on_pushButton_3_clicked()
{
     mMediaPlayer->play();
}

void MainWindow::on_pushButton_8_clicked()
{
    mMediaPlayer->pause();
}


void MainWindow::on_pushButton_9_clicked()
{
     mMediaPlayer->stop();
}


void MainWindow::on_muet_clicked()
{
    if(ui->muet->text()=="muet"){
         mMediaPlayer->setMuted(true);
        ui->muet->setText("unmuet");}
        else{ mMediaPlayer->setMuted(false);
            ui->muet->setText("muet");}
}

void MainWindow::on_avance_valueChanged(int value)
{
     ui->avance->setValue(value);
}

void MainWindow::on_pushButton_clicked()
{
    ui->tabhis->setModel(tmph.afficherhis()) ;
    ui->tabhis->setModel(tmph.afficherhis());//refresh
}
bool MainWindow::verifID()
{
    if (ui->lineEdit_id->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_id->text().isEmpty())
    {
        ui->lineEdit_id->clear();

        ui->lineEdit_id->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}
bool MainWindow::verifID2()
{
    if (ui->lineEdit_id2->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_id2->text().isEmpty())
    {
        ui->lineEdit_id2->clear();

        ui->lineEdit_id2->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifNOM()
{
    if (ui->lineEdit_nom->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_nom->text().isEmpty())
    {
        ui->lineEdit_nom->clear();
        ui->lineEdit_nom->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}
bool MainWindow::verifNOM2()
{
    if (ui->lineEdit_nom2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_nom2->text().isEmpty())
    {
        ui->lineEdit_nom2->clear();
        ui->lineEdit_nom2->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}
bool MainWindow::verifprenom()
{
    if (ui->lineEdit_prenom->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_prenom->text().isEmpty())
    {
        ui->lineEdit_prenom->clear();
        ui->lineEdit_prenom->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifTYPE()
{
    if (ui->lineEdit_type->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_type->text().isEmpty())
    {
        ui->lineEdit_type->clear();
        ui->lineEdit_type->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::verifPRIX()
{
    if (ui->lineEdit_prix->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_prix->text().isEmpty())
    {
        ui->lineEdit_prix->clear();

        ui->lineEdit_prix->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}


bool MainWindow::verifemail()
{
    if (ui->lineEdit_email->text().contains(QRegExp("[^a-zA-Z0-9@. ]") ) || ui->lineEdit_email->text().isEmpty())
    {
        ui->lineEdit_email->clear();
        ui->lineEdit_email->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::veriftel()
{
    if (ui->lineEdit_tel->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_tel->text().isEmpty())
    {
        ui->lineEdit_tel->clear();

        ui->lineEdit_tel->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifcinp()
{
    if (ui->lineEdit_cinp->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_cinp->text().isEmpty())
    {
        ui->lineEdit_cinp->clear();

        ui->lineEdit_cinp->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

