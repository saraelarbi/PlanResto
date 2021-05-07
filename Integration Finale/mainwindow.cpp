#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mailing.h"
#include"music.h"
#include"materiel.h"
#include"remise.h"
#include"client.h"
#include"commande.h"
#include"calculatrice.h"
#include "smtp.h"
#include "fonction.h"
#include "emplyer.h"
#include "dialog.h"
#include "smtp.h"
#include "fonction.h"
#include "emplyer.h"
#include "dialog.h"



#include<QFileDialog>
#include<QTextDocument>
#include<QTextStream>
#include<QGraphicsView>
#include<QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QSystemTrayIcon>
#include<QMediaPlayer>
#include<QUrlQuery>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include <QDate>
#include <QTime>
#include<QMessageBox>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include <QtPrintSupport/QPrinter>
#include <QDesktopServices>
#include <QSound>
#include <QDesktopWidget>
#include <QCoreApplication>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->stackedWidget->setCurrentIndex(1);



    son=new QSound("C:/Users/ASUS/Desktop/Integration Finale/ss.wav");

    med = new QMediaPlayer(this);

        connect(med , &QMediaPlayer::positionChanged, [&](qint64 pos){

            ui->avancement_media->setValue(pos);

        });

        connect(med , &QMediaPlayer::durationChanged, [&](qint64 dur){

            ui->avancement_media->setMaximum(dur);

        });

    ui->affichage->setModel(supp.afficher());
    ui->tableView->setModel(sup.afficher());
    ui->affichage->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->affichage->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tabcommande_2->setModel(tmpcommande.afficher());
    ui->tabclient_2->setModel(tmpclient.afficher());
    ui->tabcommande_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabcommande_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tabclient_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabclient_2->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tab_mat->setModel(M.afficher());
    ui->tab_fou->setModel(F.afficher());
    ui->tab_mail->setModel(F.afficher());
    ui->tab_rem->setModel(R.afficher());
    ui->tab_mat->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_mat->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_fou->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_fou->setSelectionMode(QAbstractItemView::SingleSelection);


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

    ui->tel->setMaxLength(8);
    ui->id->setMaxLength(10);
    ui->cinf->setMaxLength(8);
    ui->prix->setValidator(new QIntValidator(0, 999999999, this));
    ui->tel->setValidator(new QIntValidator(0, 99999999, this));
    ui->ancien_prix->setValidator(new QIntValidator(0, 999999999, this));
    ui->nouveau_prix->setValidator(new QIntValidator(0, 999999999, this));
    ui->cinf->setValidator(new QIntValidator(0, 99999999, this));

    ui->tab_bloc->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_bloc->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_produit->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_produit->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_produit->setModel(P.afficher());
    ui->tab_bloc->setModel(B.afficher());
    ui->prixP->setValidator(new QIntValidator(0, 999999999, this));
    ui->numb->setValidator(new QIntValidator(0, 999999999, this));


    ui->tab_collab->setModel(C.afficher());
    ui->afficher_Contrat->setModel(T.afficher());
    ui->tableViewres->setModel(Re.afficher());
    ui->tab_collab->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_collab->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewres->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->afficher_Contrat->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->afficher_Contrat->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewres->setSelectionMode(QAbstractItemView::SingleSelection);


    ui->tableView_B->setModel(tmpBoisson.afficher());
    ui->tableView_P->setModel(tmpPlat.afficher());

    ui->tabhis->setModel(tmph.afficherhis()) ;

           current_user="";

         //Regex (pour contrôle de saisie)

            mail_regex=QRegExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");
            cin_regex=QRegExp("[0-9]{8}$");
            chaine_regex=QRegExp("[a-zA-Z]{2,20}$");
            tel_regex=QRegExp("[0-9]{8}$");
            salaire_regex=QRegExp("[0-9]+$");
            horaire_regex=QRegExp("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");


        //windows size
            initial_width=this->width()*0.8;
            initial_height=this->height();

            login_width=this->width()*0.84;
            login_height=this->height()*0.7;

            QRect screenGeometry = QApplication::desktop()->screenGeometry();
            center_main_x=(screenGeometry.width()-initial_width) / 2;
            center_main_y=(screenGeometry.height()-initial_height) / 2;
            center_login_x=(screenGeometry.width()-login_width) / 2;
            center_login_y=(screenGeometry.height()-login_height) / 2;

          QPixmap pic("C:/Users/ASUS/Desktop/Integration Finale/sd.png");
          ui->label_im->setPixmap(pic);

            this->setFixedSize(login_width,login_height);


            //Forgotten password hyperlink
                ui->mdp_oublie_label->setText(tr("<a href=\"whatever\">Mot de passe oublié?</a>"));
                ui->mdp_oublie_label->setTextInteractionFlags(Qt::TextBrowserInteraction);

                ui->passwordLineEdit_login->setEchoMode(QLineEdit::Password);
                ui->passwordLineEdit_signup->setEchoMode(QLineEdit::Password);
                ui->confimerMotDePasseLineEdit_signup->setEchoMode(QLineEdit::Password);


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

                                      int SB=ui->tab_collab->model()->rowCount();
                                                         ui->idcollaborateur_2->clear();

                                                         for (int i=0;i<SB;i++)
                                                         {
                                                             QString idcollaborateur = ui->tab_collab->model()->index(i, 0).data().toString();
                                                             ui->idcollaborateur_2->addItem(idcollaborateur);
                                                         }

                                                         ui->telephonecollab->setValidator(new QIntValidator(100, 99999999, this));
                                                         ui->nbtable->setValidator(new QIntValidator(100, 999, this));
                                                         ui->nbchaise->setValidator(new QIntValidator(100, 999, this));
                                                         ui->numres->setValidator(new QIntValidator(100, 9999, this));
                                                         ui->idcollaborateur->setValidator(new QIntValidator(100, 9999, this));

                                                         ui->tarifcnt->setMaxLength(5);
                                                         ui->tarifcnt->setValidator(new QIntValidator(100, 99999, this));

                                                         ui->numres->setMaxLength(4);
                                                         ui->idcollaborateur->setMaxLength(4);
                                                         ui->NumSMS->setMaxLength(12);
                                                         ui->adressecollab->setMaxLength(50);
                                                         ui->telephonecollab->setMaxLength(8);
                                                         ui->nomcolla->setMaxLength(15);
                                                         ui->prenomcollab->setMaxLength(15);
                                                         ui->prenomRES->setMaxLength(15);
                                                         ui->nom_2cnt->setMaxLength(15);
                                                         ui->nomRES->setMaxLength(15);


                                      //arduino
          /*      int ret=A.connect_arduino();
              switch(ret){
                case(0):qDebug()<< "arduino is availble and connected to :"<< A.getarduino_port_name();
                    break;
                case(1):qDebug()<< "arduino is availble but not connected to :"<< A.getarduino_port_name();
                    break;
                case(-1):qDebug()<< "arduino is not availble";
                }
                QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
*/




                   //moemen

                   son0=new QSound("C:/Users/ASUS/Desktop/Integration Finale/Ajout.wav");
                   son1=new QSound("C:/Users/ASUS/Desktop/Integration Finale/Modifier.wav");
                   son2=new QSound("C:/Users/ASUS/Desktop/Integration Finale/supprimer.wav");
                   son3=new QSound("C:/Users/ASUS/Desktop/Integration Finale/Ajout.wav");
                   son4=new QSound("C:/Users/ASUS/Desktop/Integration Finale/Modifier.wav");
                   son5=new QSound("C:/Users/ASUS/Desktop/Integration Finale/supprimer.wav");



                   timerr=new QTimer(this) ;

                   connect(timerr , SIGNAL(timeout()),this,SLOT(myfunctionn())) ;
                   timerr->start(1000) ;

                   // arduino
                    int ret=a.connect_arduino();
                    switch(ret){
                        case(0):qDebug()<< "arduino is availble and connected to :"<< a.getarduino_port_name();
                            break;
                        case(1):qDebug()<< "arduino is availble but not connected to :"<< a.getarduino_port_name();
                            break;
                        case(-1):qDebug()<< "arduino is not availble";
                    }





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


bool MainWindow::verifCHAMPVIDE()
{

    if(ui->nom_2->text().isEmpty() || ui->id->text().isEmpty() || ui->type->text().isEmpty() || ui->marque->text().isEmpty() ||  ui->prix->text().isEmpty())
    {
         ui->nom_2->clear();
         ui->id->clear();
         ui->type->clear();
         ui->marque->clear();
         ui->cinfet->clear();
         ui->prix->clear();

         ui->nom_2->setPlaceholderText("VIDE") ;
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


bool MainWindow::verifNOMm()
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

bool MainWindow::verifTYPEE()
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

bool MainWindow::verifPRENOMC()
{
    if (ui->prenomcollab->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->prenomcollab->text().isEmpty())
    {
        ui->prenomcollab->clear();
        ui->prenomcollab->setPlaceholderText("contient que des caracteres") ;
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
}

MainWindow::~MainWindow()
{

    ui->tableView_P->setModel(tmpPlat.afficher());//refresh
    ui->tableView_B->setModel(tmpBoisson.afficher());//refresh
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{     son->play();
    QString id=ui->id->text();
    QString nom=ui->nom_2->text();
    QString type=ui->type->text();
    QString marque=ui->marque->text();
    QString prix=ui->prix->text();
    QString cinf=ui->cinfet->currentText();



    Materiel M(id,nom,type,marque,prix,cinf);
        bool test2=M.ajouter();



          if( test2 &&verifCHAMPVIDE() && verifNOMm() && verifTYPEE() && verifMARQUE())
    {
        ui->tab_mat->setModel(M.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/ajout succe.mp3"));
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
    QString nom=ui->nom_3->text();
    QString prenom=ui->prenom_2->text();
    QString type=ui->type_2->text();
    QString tel=ui->tel->text();
    QString email=ui->email_2->text();
    QString adresse=ui->adresse->text();


    Fournisseur F(cinf,nom,prenom,type,tel,email,adresse);
    bool test2=F.ajouter();


    if(test2 && verifNOMF()&&verifTYPE2()&&verifPRENOM()&&verifADRESSE())
    {
        ui->tab_fou->setModel(F.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/ajout succe.mp3"));
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


                   QPdfWriter pdf("C:/Users/ASUS/Desktop/Integration Finale/PDF/mat.pdf");
                   QPainter painter(&pdf);
                  int i = 4000;
                       painter.setPen(Qt::red);
                       painter.setFont(QFont("Comic Sans MS", 30));
                       painter.drawText(1100,1100,"Liste Des Matériels ");
                       painter.setPen(Qt::blue);
                       painter.setFont(QFont("Comic Sans MS", 50));
                       painter.drawRect(100,100,7300,1900);
                       painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/ASUS/Desktop/Integration Finale/sd.png"));
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
                               QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Desktop/Integration Finale/PDF/mat.pdf"));
                               painter.end();
                           }
                           if (reponse == QMessageBox::No)
                           {
                                painter.end();
                           }
    }






void MainWindow::on_recherche_textChanged(const QString &)
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

    QPdfWriter pdf("C:/Users/ASUS/Desktop/Integration Finale/PDF/fou.pdf");
    QPainter painter(&pdf);
   int i = 4000;
      int y =7200;
        painter.setPen(Qt::red);
        painter.setFont(QFont("Comic Sans MS", 30));
        painter.drawText(1100,1100,"Liste Des Matériels ");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Comic Sans MS", 50));
        painter.drawRect(100,100,7300,1900);
        painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/ASUS/Desktop/Integration Finale/sd.png"));
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
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Desktop/Integration Finale/PDF/fou.pdf"));
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

     if(test2)
    {
        ui->tab_rem->setModel(R.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/ajout succe.mp3"));
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
            musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/modif succe.mp3"));
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
           musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/sound/supp succe.mp3"));
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


void MainWindow::on_rech_rem_textChanged(const QString &)
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

            bool typefonction_verif = chaine_regex.exactMatch(ui->TypeFonction->text());
            bool salaire_verif=salaire_regex.exactMatch(ui->Salaire->text());
            bool jourdetravail_verif=chaine_regex.exactMatch(ui->Jourdetravail->text());
            bool heurededebut_verif=horaire_regex.exactMatch(ui->heurededebut->text());
            bool heuredefin_verif=horaire_regex.exactMatch(ui->heuredefin->text());


            QString typefonction=ui->TypeFonction->text();
            QString salaire=ui->Salaire->text();
            QString jourdetravail=ui->Jourdetravail->text();
            QString heurededebut=ui->heurededebut->text();
            QString heuredefin=ui->heuredefin->text();
            QDate debutdeconge=ui->debutdeconges->date();
            QDate findeconge=ui->findeconges->date();





            if(typefonction_verif && salaire_verif && jourdetravail_verif && heurededebut_verif && heuredefin_verif)
            {
                fonction M(typefonction,salaire,jourdetravail,heurededebut,heuredefin,debutdeconge,findeconge);
                bool test=M.ajouter();
                if(test)
                {
                ui->affichage->setModel(supp.afficher());
                musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/ajout succe.mp3"));
                musicAdd.play();
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->setIcon(QIcon("icone.png"));

                        notifyIcon->showMessage("GESTION Fonction ","L'ajout du fonction est effectué",QSystemTrayIcon::Information,15000);


                int nb=ui->affichage->model()->rowCount();
                               ui->TypeFonction_2->clear();

                               for (int i=0;i<nb;i++)
                               {
                                   QString type_fonction = ui->affichage->model()->index(i, 0).data().toString();
                                   ui->TypeFonction_2->addItem(type_fonction);
                               }



            ui->TypeFonction->setText("");
            ui->Salaire->setText("");
            ui->Jourdetravail->setText("");
            ui->heurededebut->setText("");
            ui->heuredefin->setText("");


            ui->TypeFonction->setStyleSheet("color: black");
            ui->Salaire->setStyleSheet("color: black");
            ui->Jourdetravail->setStyleSheet("color: black");
            ui->heurededebut->setStyleSheet("color: black");
            ui->heuredefin->setStyleSheet("color: black");

        }}

        else
          {

            if (!typefonction_verif)
            {

                ui->TypeFonction->setStyleSheet("color: red");
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->setIcon(QIcon("icone.png"));

                        notifyIcon->showMessage("GESTION Fonction ","L'ajout du TypeFonction NON effectué",QSystemTrayIcon::Information,15000);

}
            if (!salaire_verif)
             {
                ui->Salaire->setStyleSheet("color: red");
                    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                    notifyIcon->show();
                    notifyIcon->setIcon(QIcon("icone.png"));

                    notifyIcon->showMessage("GESTION Fonction ","L'ajout du Salaire NON effectué",QSystemTrayIcon::Information,15000);
            }
            if (!jourdetravail_verif)
            {

                ui->Jourdetravail->setStyleSheet("color: red");
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->setIcon(QIcon("icone.png"));

                        notifyIcon->showMessage("GESTION Fonction ","L'ajout du Jourdetravail NON effectué",QSystemTrayIcon::Information,15000);
            }

            if (!heurededebut_verif)
            {

                ui->heurededebut->setStyleSheet("color: red");
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->setIcon(QIcon("icone.png"));

                        notifyIcon->showMessage("GESTION Fonction ","L'ajout du heurededebut NON effectué",QSystemTrayIcon::Information,15000);
            }

            if (!heuredefin_verif)
            {

                ui->heuredefin->setStyleSheet("color: red");
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->setIcon(QIcon("icone.png"));

                        notifyIcon->showMessage("GESTION Fonction ","L'ajout du heuredefin NON effectué",QSystemTrayIcon::Information,15000);
            }



           }



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

       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
               notifyIcon->show();
               notifyIcon->setIcon(QIcon("icone.png"));

               notifyIcon->showMessage("GESTION Fonction ","Fonction supprimé",QSystemTrayIcon::Information,15000);

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
       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
               notifyIcon->show();
               notifyIcon->setIcon(QIcon("icone.png"));

               notifyIcon->showMessage("GESTION Fonction ","Fonction NON supprimé",QSystemTrayIcon::Information,15000);
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

            bool mail_verif = mail_regex.exactMatch(ui->email->text());
            bool cin_verif=cin_regex.exactMatch(ui->CIN->text());
            bool nom_verif=chaine_regex.exactMatch(ui->nom->text());
            bool prenom_verif=chaine_regex.exactMatch(ui->prenom->text());
            bool telephone_verif=tel_regex.exactMatch(ui->Telephone->text());
            bool adresse_verif=chaine_regex.exactMatch(ui->Adress->text());




       if(cin_verif && nom_verif && prenom_verif && telephone_verif && adresse_verif && mail_verif)
        {

           Employes E(CIN,nom,prenom,TypeFonction,Telephone,email,Adress);

           bool test=E.ajouter();

           if(test){

            ui->tableView->setModel(sup.afficher());

            musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/qt/SmartResto/ajout succe.mp3"));
            musicAdd.play();
            QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                    notifyIcon->show();
                    notifyIcon->setIcon(QIcon("icone.png"));

                    notifyIcon->showMessage("GESTION Emplyes ","L'ajout d'emplye est effectué",QSystemTrayIcon::Information,15000);



                    ui->CIN->setText("");
                    ui->nom->setText("");
                    ui->prenom->setText("");
                    ui->Telephone->setText("");
                    ui->email->setText("");
                    ui->Adress->setText("");

                    ui->CIN->setStyleSheet("color: black");
                    ui->nom->setStyleSheet("color: black");
                    ui->prenom->setStyleSheet("color: black");
                    ui->Telephone->setStyleSheet("color: black");
                    ui->email->setStyleSheet("color: black");
                    ui->Adress->setStyleSheet("color: black");
                }}





                 else
                  {

                    if (!mail_verif){

                        ui->email->setStyleSheet("color: red");
                        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                notifyIcon->show();
                                notifyIcon->setIcon(QIcon("icone.png"));

                                notifyIcon->showMessage("GESTION Emplyes ","L'Email d'emplye NON validé",QSystemTrayIcon::Information,15000);
                    }

                    if (!cin_verif){

                        ui->CIN->setStyleSheet("color: red");
                        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                notifyIcon->show();
                                notifyIcon->setIcon(QIcon("icone.png"));

                                notifyIcon->showMessage("GESTION Emplyes ","Le CIN d'emplye NON validé",QSystemTrayIcon::Information,15000);
                    }

                    if (!telephone_verif){

                        ui->Telephone->setStyleSheet("color: red");
                        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                notifyIcon->show();
                                notifyIcon->setIcon(QIcon("icone.png"));

                                notifyIcon->showMessage("GESTION Emplyes ","Le NUM TELEPHONE d'emplye NON validé",QSystemTrayIcon::Information,15000);
                    }

                    if (!nom_verif){

                        ui->nom->setStyleSheet("color: red");
                        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                notifyIcon->show();
                                notifyIcon->setIcon(QIcon("icone.png"));

                                notifyIcon->showMessage("GESTION Emplyes ","Le NOM d'emplye NON validé",QSystemTrayIcon::Information,15000);
                    }

                    if (!prenom_verif){

                        ui->prenom->setStyleSheet("color: red");
                        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                notifyIcon->show();
                                notifyIcon->setIcon(QIcon("icone.png"));

                                notifyIcon->showMessage("GESTION Emplyes ","Le Prenom d'emplye NON validé",QSystemTrayIcon::Information,15000);
                    }

                    if (!adresse_verif){

                        ui->Adress->setStyleSheet("color: red");
                        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                notifyIcon->show();
                                notifyIcon->setIcon(QIcon("icone.png"));

                                notifyIcon->showMessage("GESTION Emplyes ","L'ADRESSE d'emplye NON validé",QSystemTrayIcon::Information,15000);
                          }

                        }

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

       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
               notifyIcon->show();
               notifyIcon->setIcon(QIcon("icone.png"));

               notifyIcon->showMessage("GESTION emplyes ","Employé supprimé",QSystemTrayIcon::Information,15000);

   }
   else
   {
       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
               notifyIcon->show();
               notifyIcon->setIcon(QIcon("icone.png"));

               notifyIcon->showMessage("GESTION Employe ","Employé NON supprimé",QSystemTrayIcon::Information,15000);
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

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->setIcon(QIcon("icone.png"));

            notifyIcon->showMessage("GESTION Fonctions ","Fonction Modifié",QSystemTrayIcon::Information,15000);

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

        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION Employes ","Employe Modifié",QSystemTrayIcon::Information,15000);

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

    ui->TypeFonction->setStyleSheet("color: black");
    ui->Salaire->setStyleSheet("color: black");
    ui->Jourdetravail->setStyleSheet("color: black");
    ui->heurededebut->setStyleSheet("color: black");
    ui->heuredefin->setStyleSheet("color: black");


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

    ui->CIN->setStyleSheet("color: black");
    ui->nom->setStyleSheet("color: black");
    ui->prenom->setStyleSheet("color: black");
    ui->Telephone->setStyleSheet("color: black");
    ui->email->setStyleSheet("color: black");
    ui->Adress->setStyleSheet("color: black");
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
    QString link="http://www.expat.com";
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
   if(verifID()&&verifNOMCl()&&verifprenom()&&veriftel()&&verifemail()){
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

   srand (time(NULL));
   QDate g = QDate::currentDate() ;
   QString dateee =g.toString("dd / MM / yyyy ") ;
   QString fn="ajouter" ;
   QString nom5 = ui->lineEdit_nom2->text();
   QString type5 = ui->lineEdit_type->text();
   QString prix5 = ui->lineEdit_prix->text();
   histogh GH(nom5,type5,dateee,prix5,fn) ;
    bool test1=GH.ajoutehis() ;

 commande co(id,nom,type,cinp,prix);
 if(verifID2()&&verifNOM2()&&verifTYPE()&&verifPRIXghazi()&&verifcinp()){

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
    QPdfWriter pdf("C:/Users/ASUS/Desktop/Integration Finale/PDF/ghazi.pdf");
                       QPainter painter(&pdf);
                      int i = 4000;
                           painter.setPen(Qt::red);
                           painter.setFont(QFont("Comic Sans MS", 30));
                           painter.drawText(1100,1100,"Liste Des Commandes");
                           painter.setPen(Qt::blue);
                           painter.setFont(QFont("Comic Sans MS", 50));
                           painter.drawRect(100,100,7300,1900);
                           painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/ASUS/Desktop/Integration Finale/sd.png"));
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
                                   QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Desktop/Integration Finale/PDF/ghazi.pdf"));
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






void MainWindow::on_pushButton_clicked()
{
    ui->tabhis->setModel(tmph.afficherhis());
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
    if (ui->lineEdit_nom_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_nom_2->text().isEmpty())
    {
        ui->lineEdit_nom_2->clear();
        ui->lineEdit_nom_2->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}


bool MainWindow::verifNOMCl()
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

bool MainWindow::verifNOMC()
{
    if (ui->nomcolla->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->nomcolla->text().isEmpty())
    {
        ui->nomcolla->clear();
        ui->nomcolla->setPlaceholderText("contient que des caracteres") ;
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


bool MainWindow::verifNOMR()
{
    if (ui->nomRES->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->nomRES->text().isEmpty())
    {
        ui->nomRES->clear();
        ui->nomRES->setPlaceholderText("contient que des caracteres") ;
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
    if (ui->lineEdit_prix_2->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_prix_2->text().isEmpty())
    {
        ui->lineEdit_prix_2->clear();

        ui->lineEdit_prix_2->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifPRIXghazi()
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


void MainWindow::on_signup_button_clicked()
{
     bool email_verif=mail_regex.exactMatch(ui->eMailLineEdit_signup->text());

        bool confirm_pwd=ui->confimerMotDePasseLineEdit_signup->text()==ui->passwordLineEdit_signup->text();

        if (log->sign_up(ui->usernameLineEdit_signup->text(),ui->passwordLineEdit_signup->text(),ui->eMailLineEdit_signup->text()) && confirm_pwd && email_verif)
        {
            ui->stackedWidget->setCurrentIndex(1);
            current_user=ui->usernameLineEdit_signup->text();

            ui->confimerMotDePasseLineEdit_signup->text().clear();
            ui->passwordLineEdit_signup->text().clear();
            ui->eMailLineEdit_signup->text().clear();
            ui->usernameLineEdit_signup->text().clear();
            this->setFixedSize(initial_width,initial_height);

            this->move(center_main_x, center_main_y);
            ui->eMailLineEdit_signup->setStyleSheet("color: black");

        }

        else
        {
            if (!email_verif)
                ui->eMailLineEdit_signup->setStyleSheet("color: red");
            if (!confirm_pwd)
                QMessageBox::warning(this,tr("Inscription"),tr("Les deux mots de passe ne sont pas identiques"));
        }

}

void MainWindow::on_login_button_clicked()
{
    if (ui->passwordLabel->text()=="Code")
        {

            if (log->sign_in_code(ui->usernameLineEdit_login->text(),ui->passwordLineEdit_login->text()))
            {
                QString pref=log->fetch_preferences(ui->usernameLineEdit_login->text());

                qDebug()<< pref;

                current_user=ui->usernameLineEdit_login->text();
                ui->stackedWidget->setCurrentIndex(0);



                if (current_user=="taher")
                    ui->stackedWidget_2->setCurrentIndex(4);
                else if (current_user=="aymen")
                    ui->stackedWidget_2->setCurrentIndex(0);
                else if (current_user=="momen")
                    ui->stackedWidget_2->setCurrentIndex(1);
                else if (current_user=="salma")
                    ui->stackedWidget_2->setCurrentIndex(2);
                else if (current_user=="sara")
                    ui->stackedWidget_2->setCurrentIndex(3);
                else if (current_user=="ghazi")
                    ui->stackedWidget_2->setCurrentIndex(5);
                else
                    ui->stackedWidget->setCurrentIndex(3);


                ui->usernameLineEdit_login->clear();
                ui->passwordLineEdit_login->clear();
                this->setFixedSize(initial_width,initial_height);
                this->move(center_main_x, center_main_y);

                QPixmap outPixmap = QPixmap();
                outPixmap.loadFromData(log->fetch_image(current_user),"PNG");
                outPixmap = outPixmap.scaledToWidth(ui->image_pos->width(),Qt::SmoothTransformation);
                ui->image_pos->setPixmap(outPixmap.scaled(outPixmap.width(),outPixmap.height(),Qt::KeepAspectRatio));

                ui->uname_label->setText(current_user);

            }
            else
                QMessageBox::warning(this,tr("Connexion"),tr("Erreur de connexion"));
        }
        else if (ui->passwordLabel->text()=="Mot de Passe")
        {
            if (log->sign_in(ui->usernameLineEdit_login->text(),ui->passwordLineEdit_login->text()))
            {
                QString pref=log->fetch_preferences(ui->usernameLineEdit_login->text());

                qDebug()<< pref;

                current_user=ui->usernameLineEdit_login->text();
                ui->stackedWidget->setCurrentIndex(0);



                if (current_user=="taher")
                    ui->stackedWidget_2->setCurrentIndex(4);
                else if (current_user=="aymen")
                    ui->stackedWidget_2->setCurrentIndex(0);
                else if (current_user=="momen")
                    ui->stackedWidget_2->setCurrentIndex(1);
                else if (current_user=="salma")
                    ui->stackedWidget_2->setCurrentIndex(2);
                else if (current_user=="sara")
                    ui->stackedWidget_2->setCurrentIndex(3);
                else if (current_user=="ghazi")
                    ui->stackedWidget_2->setCurrentIndex(5);
                else

                    ui->stackedWidget->setCurrentIndex(6);
                ui->usernameLineEdit_login->clear();
                ui->passwordLineEdit_login->clear();
                this->setFixedSize(initial_width,initial_height);

                this->move(center_main_x, center_main_y);

                ui->uname_label->setText(current_user);

                QPixmap outPixmap = QPixmap();
                outPixmap.loadFromData(log->fetch_image(current_user),"PNG");
                outPixmap = outPixmap.scaledToWidth(ui->image_pos->width(),Qt::SmoothTransformation);
                ui->image_pos->setPixmap(outPixmap.scaled(outPixmap.width(),outPixmap.height(),Qt::KeepAspectRatio));
            }
            else
            {
                QMessageBox::warning(this,tr("Connexion"),tr("Erreur de connexion"));
                test=false;
            }

        }
}



void MainWindow::on_logout_button_clicked()
{
    this->setFixedSize(login_width,login_height);
        this->move(center_login_x,center_login_y);
        ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_mdp_oublie_label_linkActivated(const QString &)
{
    if (ui->usernameLineEdit_login->text()!="")
        {
            login login;
            QString code=login.code_generator();
            QString email=login.fetch_email(ui->usernameLineEdit_login->text());
            login.update_mpd_reset(ui->usernameLineEdit_login->text(),code);

            QMessageBox::information(this, tr("Mot de passe oublié"), tr("Un code de vérification a été envoyé à votre adresse e-mail."));


            ui->passwordLabel->setText("Code");

            Mailing* ml = new Mailing("aymen.abid@esprit.tn", "191JMT2058", "smtp.gmail.com", 465);
            ml->sendMail("aymen.abid@esprit.tn", email , "Mot de Passe oublié" ,code);

            ui->usernameLineEdit_login->text().clear();
            ui->passwordLineEdit_login->text().clear();

        }
}

void MainWindow::on_ajouter_image_clicked()
{
    login login;
       login.ajouter_image(current_user);



       QPixmap outPixmap = QPixmap();
       outPixmap.loadFromData(log->fetch_image(current_user),"PNG");
       outPixmap = outPixmap.scaledToWidth(ui->image_pos->width(),Qt::SmoothTransformation);

       // ui->image_pos->setPixmap(outPixmap);

       ui->image_pos->setPixmap(outPixmap.scaled(outPixmap.width(),outPixmap.height(),Qt::KeepAspectRatio));
}

void MainWindow::on_ouvrir_media_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "ouvrir");

        if (filename.isEmpty())

        {

            return;

        }

        med->setMedia(QUrl::fromLocalFile(filename));

        med->setVolume(ui->volume_media->value());

        on_play_media_clicked();
}

void MainWindow::on_play_media_clicked()
{
    med->play();
}

void MainWindow::on_pause_media_clicked()
{
    med->pause();
}

void MainWindow::on_stop_media_clicked()
{
    med->stop();
}

void MainWindow::on_mute_media_clicked()
{
    if (ui->mute_media->text() == "Mute")

        {

            med->setMuted(true);

            ui->mute_media->setText("Unmute");

        }

        else {

            med->setMuted(false);

            ui->mute_media->setText("Mute");

        }
}

void MainWindow::on_volume_media_valueChanged(int value)
{
    med->setVolume(value);
}

void MainWindow::on_pushButton_15_clicked()
{
    Mailing* ml = new Mailing("aymen.abid@esprit.tn", "191JMT2058", "smtp.gmail.com", 465);
        ml->sendMail("abid.aimen21@gmail.com", "abid.aimen21@gmail.com" , "Signalisation Problème" ,ui->plainTextEdit_probleme->toPlainText());
        ui->plainTextEdit_probleme->clear();
}

void MainWindow::on_confirmer_chan_mdp_clicked()
{
    if (ui->confirmerNouveauMotDePasseLineEdit->text()==ui->nouveauMotDePasseLineEdit->text())
        {
            if (ui->ancienMotDePasseLineEdit->text()!="" && ui->confirmerNouveauMotDePasseLineEdit->text()!="")
            {
                bool test=log->modifier_mdp(current_user,ui->ancienMotDePasseLineEdit->text(),ui->nouveauMotDePasseLineEdit->text());

                if (!test)
                    QMessageBox::warning(this,tr("Changement du MDP"),tr("Erreur lors du changement du MDP"));
                else
                {
                    ui->ancienMotDePasseLineEdit->clear();
                    ui->nouveauMotDePasseLineEdit->clear();
                    ui->confirmerNouveauMotDePasseLineEdit->clear();
                }
            }
            else
                QMessageBox::warning(this,tr("Changement du MDP"),tr("Veuillez remplir tous les champs"));
        }
        else
            QMessageBox::warning(this,tr("Changement du MDP"),tr("Les deux mots de passe ne sont pas identiques"));
}

void MainWindow::on_annuler_chan_mdp_clicked()
{
        ui->ancienMotDePasseLineEdit->clear();
        ui->nouveauMotDePasseLineEdit->clear();
        ui->confirmerNouveauMotDePasseLineEdit->clear();
}

void MainWindow::on_radioButton_nuit_toggled(bool )
{
    login login;
        QString pref=login.fetch_preferences(current_user);



        pref[0]='N';
        this->setStyleSheet("font: 8pt \"Pacifico\";"
                            "background-color: rgb(43, 40, 38);"
                            "color: rgb(255, 255, 255);");



        QList<QPushButton *> butts = this->findChildren<QPushButton *>();

        for (int i=0; i<butts.size();i++)
        {
            butts.at(i)->setStyleSheet("QPushButton { background-color: #444444; }");
        }


        QList<QTabWidget *> tabs = this->findChildren<QTabWidget *>();

        for (int i=0; i<tabs.size();i++)
        {
            tabs.at(i)->setStyleSheet("QTabBar::tab { background-color: rgb(68, 68, 68);}");
        }

        //        QList<QTableView *> tabviews = this->findChildren<QTableView *>();

        //        for (int i=0; i<tabviews.size();i++)
        //        {
        //            tabs.at(i)->setStyleSheet("QTableView::tab { background-color: rgb(68, 68, 68);}");
        //       }

}

void MainWindow::on_radioButton_jour_toggled(bool )
{
    this->setStyleSheet("font: 8pt \"Pacifico\";");


        QList<QPushButton *> butts = this->findChildren<QPushButton *>();

        for (int i=0; i<butts.size();i++)
        {
            butts.at(i)->setStyleSheet("QPushButton { background-color: grey; }");
        }
        QList<QTabWidget *> tabs = this->findChildren<QTabWidget *>();

        for (int i=0; i<tabs.size();i++)
        {
            tabs.at(i)->setStyleSheet("QTabBar::tab { background-color: grey;}");
        }
}

void MainWindow::on_confirmer_langue_clicked()
{
    if (ui->comboBox_langue->currentText()=="Français")
       {
           translator->load(QDir::currentPath().append("C:/Users/ASUS/Desktop/Integration ghazi/bikou.qm"));
           qApp->installTranslator(translator);
           ui->retranslateUi(this);
           ui->comboBox_langue->setCurrentText("Français");
       }
       else if (ui->comboBox_langue->currentText()=="English")
       {
           translator->load("C:/Users/ASUS/Desktop/Integration ghazi/bikou.qm");
           qApp->installTranslator(translator);
           ui->retranslateUi(this);
           ui->comboBox_langue->setCurrentText("English");
       }
}


bool MainWindow::verifCHAMPVIDE_taher()

{



    if(ui->nomP->text().isEmpty() && ui->idP->text().isEmpty() && ui->typeP->text().isEmpty() && ui->marque->text().isEmpty() &&  ui->prixP->text().isEmpty())

    {

         ui->nomP->clear();

         ui->idP->clear();

         ui->typeP->clear();

         ui->marque->clear();


         ui->prixP->clear();



         ui->nomP->setPlaceholderText("VIDE") ;

         ui->idP->setPlaceholderText("VIDE") ;

         ui->typeP->setPlaceholderText("VIDE") ;

         ui->marque->setPlaceholderText("VIDE") ;

         ui->prixP->setPlaceholderText("VIDE") ;



         return false;
    }

    else

    {
        return true;
    }

}

bool MainWindow::verifCHAMPVIDEbloc_taher()

{



    if(ui->numb->text().isEmpty() || ui->idblocs->text().isEmpty() || ui->etat->text().isEmpty() )

    {

         ui->numb->clear();

         ui->idblocs->clear();

         ui->etat->clear();

         ui->numb->setPlaceholderText("VIDE") ;

         ui->idblocs->setPlaceholderText("VIDE") ;

         ui->etat->setPlaceholderText("VIDE") ;



         return false;
    }

    else

    {
        return true;
    }

}

bool MainWindow::verifTYPE_taher()

{

    if (ui->typeP->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->typeP->text().isEmpty())

    {

        ui->typeP->clear();

        ui->typeP->setPlaceholderText("contient que des caracteres") ;

        return false;

    }

    else

    {

        return true;

    }

}

bool MainWindow::verifNOM_taher()

{

    if (ui->nomP->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->nomP->text().isEmpty())

    {

        ui->nomP->clear();

        ui->nomP->setPlaceholderText("contient que des caracteres") ;

        return false;

    }

    else

    {

        return true;

    }

}

bool MainWindow::verifMARQUE_taher()

{

    if (ui->marque_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->marque_2->text().isEmpty())

    {

        ui->marque_2->clear();

        ui->marque_2->setPlaceholderText("contient que des caracteres") ;

        return false;

    }

    else

    {

        return true;

    }

}





bool MainWindow::verifETAT_taher()

{

    if (ui->etat->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->etat->text().isEmpty())

    {

        ui->etat->clear();

        ui->etat->setPlaceholderText("contient que des caracteres") ;

        return false;

    }

    else

    {

        return true;

    }

}


void MainWindow::on_supprimer_P_clicked()
{
    QItemSelectionModel *select = ui->tab_produit->selectionModel();
        QString C = select->selectedRows(0).value(0).data().toString();

       if(P.supprimer(C))
       {
           ui->tab_produit->setModel(P.afficher());
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();
                   notifyIcon->setIcon(QIcon("icone.png"));

                   notifyIcon->showMessage("GESTION PRODUIT  PRODUIT ","produit supprimer",QSystemTrayIcon::Information,15000);
           musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/supp succe.mp3"));
                           musicAdd.play();
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("suppression effectué.\n"
                                   "Click ok to exit."), QMessageBox::Cancel);srand (time(NULL));

       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                       QObject::tr("suppression non effectue.\n"
                                   "Click OK to exit."), QMessageBox::Cancel);
       }
}

void MainWindow::on_supprimer_B_clicked()
{
    QItemSelectionModel *select = ui->tab_bloc->selectionModel();
        QString C = select->selectedRows(0).value(0).data().toString();

       if(B.supprimer(C))
       {
           ui->tab_bloc->setModel(B.afficher());
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();
                   notifyIcon->setIcon(QIcon("icone.png"));

                   notifyIcon->showMessage("GESTION BLOCS  BLOCS ","bloc supprimer",QSystemTrayIcon::Information,15000);
           musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/supp succe.mp3"));
                           musicAdd.play();
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

void MainWindow::on_Modifier_B_clicked()
{
    if (ui->Modifier_B->isChecked())
    {
        ui->Modifier_B->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("BLOCS");
        tableModel->select();
        ui->tab_bloc->setModel(tableModel);
    }
    else
    {
        ui->Modifier_B->setText("Modifier");
        ui->tab_bloc->setModel(B.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION BLOCS  BLOCS ","bloc modifié",QSystemTrayIcon::Information,15000);
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/modif succe.mp3"));
                        musicAdd.play();
        QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                    QObject::tr("Fonction modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);

    }

}

void MainWindow::on_Modifier_P_clicked()
{
    if (ui->Modifier_P->isChecked())
    {
        ui->Modifier_P->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("PRODUIT");
        tableModel->select();
        ui->tab_produit->setModel(tableModel);

    }
    else
    {
        ui->Modifier_P->setText("Modifier");
        ui->tab_produit->setModel(P.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION PRODUIT  PRODUIT ","produit modifié",QSystemTrayIcon::Information,15000);
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/modif succe.mp3"));
                        musicAdd.play();
        QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                    QObject::tr("Fonction modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);
        srand (time(NULL));
                                  QDate d = QDate::currentDate() ;
                                   QString datee =d.toString("dd / MM / yyyy ") ;
                                   QString fn="modifier" ;
                                  QString nom1 = ui->nomP->text();
                                projeth pp(nom1,datee,fn) ;
                                bool test1=pp.modifierhis() ;

    }
}

void MainWindow::on_rechercher_produit_clicked()
{
    if (ui->checkBox_nom_2->isChecked())
              { QString nom=ui->rech_nom_2->text();
                  QSqlQueryModel *verif=P.rechercher_nom(nom);
                  if (verif!=nullptr)
                  {
                      ui->tab_produit->setModel(verif);

                  }
               }

            if (ui->checkBox_type_2->isChecked())
              { QString type=ui->rech_type_2->text();
                  QSqlQueryModel *verif=P.rechercher_type(type);
                  if (verif!=nullptr)
                  {

                      ui->tab_produit->setModel(verif);

                  }
               }
             if (ui->checkBox_marque_2->isChecked())
              { QString marque=ui->rech_marque_2->text();
                  QSqlQueryModel *verif=P.rechercher_marque(marque);
                  if (verif!=nullptr)
                  {

                      ui->tab_produit->setModel(verif);

                  }
               }
              if ((ui->checkBox_nom_2->isChecked())&&(ui->checkBox_type_2->isChecked()))
              {
                  QString nom=ui->rech_nom_2->text();
                  QString type=ui->rech_type_2->text();

                              if (nom!="")
                                {
                                  if (type!="")
                                     {
                              QSqlQueryModel *verif=P.rechercher_nom_type(nom,type);
                              if (verif!=nullptr)
                              {
                                  ui->tab_produit->setModel(verif);

                              }
                                  } else
                                      QMessageBox::warning(this,"erreur","Champ vide");
                              } else
                                  QMessageBox::warning(this,"erreur","Champ vide");
              }
             if ((ui->checkBox_nom_2->isChecked())&&(ui->checkBox_marque_2->isChecked()))
              {
                  QString nom=ui->rech_nom_2->text();
                 QString marque=ui->rech_marque_2->text();

                              if (nom!="")
                                {
                              QSqlQueryModel *verif=P.rechercher_nom_marque(nom,marque);
                              if (verif!=nullptr)
                              {
                                  ui->tab_produit->setModel(verif);

                              }

                              } else
                                  QMessageBox::warning(this,"erreur","Champ vide");
              }
              if ((ui->checkBox_type_2->isChecked())&&(ui->checkBox_marque_2->isChecked()))
              {
                 QString type=ui->rech_type_2->text();
                 QString marque=ui->rech_marque_2->text();

                              if (type!="")
                                {
                              QSqlQueryModel *verif=P.rechercher_type_marque(type,marque);
                              if (verif!=nullptr)
                              {
                                  ui->tab_produit->setModel(verif);

                              }

                              } else
                                  QMessageBox::warning(this,"erreur","Champ vide");
              }


           if ((ui->checkBox_nom_2->isChecked())&&(ui->checkBox_marque_2->isChecked())&&(ui->checkBox_type_2->isChecked()))
           {

               QString marque=ui->rech_marque_2->text();
               QString nom=ui->rech_nom_2->text();
               QString type=ui->rech_type_2->text();

                           if (nom!="")
                             {
                               if (type!="")
                                  {
                           QSqlQueryModel *verif=P.rechercher_tous(nom,type,marque);
                           if (verif!=nullptr)
                           {

                               ui->tab_produit->setModel(verif);

                           }
                               } else
                                   QMessageBox::warning(this,"erreur","Champ vide");
                           } else
                               QMessageBox::warning(this,"erreur","Champ vide");

           }
}


void MainWindow::on_Reafficher_clicked()
{
    ui->rech_nom->setText("");
    ui->rech_type->setText("");
    ui->rech_marque->setText("");
    ui->tab_produit->setModel(P.afficher());
}

void MainWindow::on_reset_produit_clicked()
{
        ui->idP->setText("");
        ui->typeP->setText("");
        ui->nomP->setText("");
        ui->marque_2->setText("");
        ui->prixP->setText("");
}



void MainWindow::on_le_stat_clicked()
{

        statis *w=new statis();
        w->make();
        w->show();

}

void MainWindow::on_idT_clicked()
{
        {QMessageBox msgBox ;
                QSqlQueryModel * model= new QSqlQueryModel();


                   model->setQuery("select * from blocs order by idblocs");

                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));

                            ui->tab_bloc->setModel(model);
                            ui->tab_bloc->show();
                            msgBox.setText("Tri avec succés.");
                            msgBox.exec();

            }
    }

void MainWindow::on_numT_clicked()
{
    QMessageBox msgBox ;
           QSqlQueryModel * model= new QSqlQueryModel();



              model->setQuery("select * from blocs order by numb");

              model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));

                       ui->tab_bloc->setModel(model);
                       ui->tab_bloc->show();
                       msgBox.setText("Tri avec succés.");
                       msgBox.exec();
}

void MainWindow::on_etatT_clicked()
{
    QMessageBox msgBox ;
           QSqlQueryModel * model= new QSqlQueryModel();



              model->setQuery("select * from blocs order by etat");

              model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));

                       ui->tab_bloc->setModel(model);
                       ui->tab_bloc->show();
                       msgBox.setText("Tri avec succés.");
                       msgBox.exec();
}




void MainWindow::on_radioButton_clicked()
{

    ui->tab_bloc->setModel(B.afficher());
}


void MainWindow::on_prec_clicked()
{
    if(ar.write_arduino("2")){
        ui->lcd->display(ui->lcd->intValue()-1);
        qDebug()<<"ok";

 }
}

void MainWindow::on_entrer_clicked()
{
    QByteArray d=QByteArray::fromStdString(ui->lineEntrer->text().toStdString());
            if(ar.write_arduino(d)){
            ui->lcd->display(ui->lineEntrer->text());
            qDebug()<<"ok";
            }
}

void MainWindow::on_pb_ajouterblocs_clicked()
{
    QString idblocs=ui->idblocs->text();
    QString numb=ui->numb->text();
     QString etat=ui->etat->text();

    Blocs B(idblocs,numb,etat);


     bool test2=B.ajouter();

     if(test2 && verifCHAMPVIDEbloc_taher()  && verifETAT_taher())
     {
         ui->tab_bloc->setModel(B.afficher());
         QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                 notifyIcon->show();
                 notifyIcon->setIcon(QIcon("icone.png"));

                 notifyIcon->showMessage("GESTION BLOCS  BLOCS ","bloc Ajouté",QSystemTrayIcon::Information,15000);
         musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/ajout succe.mp3"));
                         musicAdd.play();
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

 }
     else
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectue.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_ajouterProduit_clicked()
{
    QString id=ui->idP->text();
    QString nom=ui->nomP->text();
    QString type=ui->typeP->text();
    QString marque=ui->marque_2->text();
    QString prix=ui->prixP->text();
        srand (time(NULL));
        QDate d = QDate::currentDate() ;
         QString datee =d.toString("dd / MM / yyyy ") ;
         QString fn="ajouter" ;
        QString nom1 = ui->nomP->text();
      projeth pp(nom1,datee,fn) ;
      bool test1=pp.ajoutehis() ;


    Produit P(id,type,nom,marque,prix);


    bool test2=P.ajouter();

    if(test2 && verifCHAMPVIDE_taher() && verifNOM_taher() && verifTYPE_taher() && verifMARQUE_taher() )
    {
        ui->tab_produit->setModel(P.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION PRODUIT  PRODUIT ","produit Ajouté",QSystemTrayIcon::Information,15000);
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/ajout succe.mp3"));
                        musicAdd.play();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_PDFP_clicked()
{
    QPdfWriter pdf("C:/Users/ASUS/Desktop/Integration Finale/PDF/taher.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::red);
        painter.setFont(QFont("Comic Sans MS", 30));
        painter.drawText(1100,1100,"Liste Des Produits ");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Comic Sans MS", 50));
        painter.drawRect(100,100,7300,1900);
        painter.setPen(Qt::blue);
        painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/ASUS/Desktop/Integration Finale/sd.png"));
        painter.drawRect(0,3000,9600,500);
        painter.setPen(Qt::blue);

        painter.setFont(QFont("Comic Sans MS", 15));
        painter.drawText(200,3300,"Identifiant");
        painter.drawText(1800,3300,"Nom");
        painter.drawText(3300,3300,"Type");
        painter.drawText(5300,3300,"Marque");
        painter.drawText(6800,3300,"Prix");




        QSqlQuery query;
        query.prepare("select * from produit");
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




           i = i + 500;
        }
        int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Desktop/Integration Finale/PDF/taher.pdf"));
                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }

}

void MainWindow::on_suivantaHER_clicked()
{
    if(ar.write_arduino("1")){
    ui->lcd->display(ui->lcd->intValue()+1);
    qDebug()<<"ok";

 }
}

void MainWindow::on_imprimerProduits_clicked()
{
    QPrinter printer;
         printer.setPrinterName("imprimer");
         QPrintDialog dialog(&printer, this);
         if (dialog.exec() == QDialog::Rejected) return;
         ui->tab_bloc->render(&printer);
}

void MainWindow::on_HistoriqueTaher_clicked()
{
    ui->tabhis_2->setModel(tmp.afficherhis()) ;
    ui->tabhis_2->setModel(tmp.afficherhis());//refresh
}



void MainWindow::on_recherche_2_textChanged(const QString &arg1)
{
    Blocs B;
            if(ui->recherche_2->text() == "")
                {
                    ui->tab_bloc->setModel(B.afficher());
                }
                else
                {
                     ui->tab_bloc->setModel(B.rechercher(ui->recherche_2->text()));
                }
}






void MainWindow::on_ajouter_collab_2_clicked()
{
    QString idcollaborateur=ui->idcollaborateur->text();
     QString nom=ui->nomcolla->text();
     QString prenom=ui->prenomcollab->text();
      QString telephone=ui->telephonecollab->text();
     QString adresse=ui->adressecollab->text();
     QString email=ui->emailcollab->text();
     srand (time(NULL));
     QDate d = QDate::currentDate() ;
      QString datee =d.toString("dd / MM / yyyy ") ;
      QString fn="ajouter" ;
     QString nom1 = ui->nomcolla->text();
    histoS pp(nom1,datee,fn) ;
   bool test1=pp.ajoutehis() ;
     Collaborateur C(idcollaborateur,nom,prenom,telephone,adresse,email);


      bool test2=C.ajouter();


     if((test2)&&(verifNOMC())&&(verifPRENOMC()))
      {
          ui->tab_collab->setModel(C.afficher());
          musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/ajout succe.mp3"));
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
       musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/supp succe.mp3"));
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
                      srand (time(NULL));
                      QDate d = QDate::currentDate() ;
                       QString datee =d.toString("dd / MM / yyyy ") ;
                       QString fn="supprimer" ;
                      QString nom1 = ui->nomcolla->text();
                    projeth pp(nom1,datee,fn) ;
                    bool test1=pp.modifierhis() ;
   }

   else
   {
       QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                   QObject::tr("suppression non effectue.\n"
                               "Click OK to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_ajouter_contrat_clicked()
{
    QString type=ui->typecnt->text();
    QString nom=ui->nom_2cnt->text();
    QString duree=ui->duree->currentText();
    QString tarif=ui->tarifcnt->text();
    QString idcollaborateur=ui->idcollaborateur_2->currentText();
   Contrat C(type,nom,duree,tarif,idcollaborateur);
bool test2=C.ajouter();

    if((test2)&&(verifNOM1()))
    {
        ui->afficher_Contrat->setModel(T.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/ajout succe.mp3"));
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


bool MainWindow::verifNOM1()
{
    if (ui->nom_2cnt->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->nom_2cnt->text().isEmpty())
    {
        ui->nom_2cnt->clear();
        ui->nom_2cnt->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

bool MainWindow::verifPRENOM1()
{
    if (ui->prenomRES->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->prenomRES->text().isEmpty())
    {
        ui->prenomRES->clear();
        ui->prenomRES->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
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
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/modif succe.mp3"));
                musicAdd.play();
        ui->tab_collab->setModel(C.afficher());
        srand (time(NULL));
        QDate d = QDate::currentDate() ;
         QString datee =d.toString("dd / MM / yyyy ") ;
         QString fn="modifier" ;
        QString nom1 = ui->nomcolla->text();
      histoS pp(nom1,datee,fn) ;
      bool test1=pp.modifierhis() ;

        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION COLLABORATEURS  COLLABORATEUR ","collaborateur Modifié",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                    QObject::tr("Fonction modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);

    }
}


void MainWindow::on_reset_collab_clicked()
{
    ui->idcollaborateur->setText("");
    ui->nomcolla->setText("");
    ui->prenomcollab->setText("");
    ui->telephonecollab->setText("");
    ui->adressecollab->setText("");
    ui->emailcollab->setText("");
}

void MainWindow::on_re_afficher_collab_clicked()
{

        ui->tab_collab->setModel(C.afficher());
}



void MainWindow::on_radioButton_2_clicked()
{
    {QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();


               model->setQuery("select * from collaborateur order by idcollaborateur");

               model->setHeaderData(0, Qt::Horizontal, QObject::tr("idcollaborateur"));
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




void MainWindow::on_radioButton_3_clicked()
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



void MainWindow::on_radioButton_4_clicked()
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

void MainWindow::on_reset_Contrat_clicked()
{
    ui->typecnt->setText("");
    ui->nom_2cnt->setText("");
    ui->duree->setCurrentText("");
    ui->tarifcnt->setText("");
    ui->idcollaborateur_2->setCurrentText("");
}


void MainWindow::on_modifier_Contrat_clicked()
{
    if (ui->modifier_Contrat->isChecked())
    {
        ui->modifier_Contrat->setText("Modifiable");

        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("contrat");
        tableModel->select();
        ui->afficher_Contrat->setModel(tableModel);
    }
    else
    {
        ui->modifier_Contrat->setText("Modifier");
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/modif succe.mp3"));
                musicAdd.play();
        ui->afficher_Contrat->setModel(T.afficher());

                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->setIcon(QIcon("icone.png"));

                        notifyIcon->showMessage("GESTION COLLABORATEURS  CONTRAT ","contrat Modifié",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                    QObject::tr("Fonction modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_supprimer_Contrat_clicked()
{
    QItemSelectionModel *select = ui->afficher_Contrat->selectionModel();
            QString C = select->selectedRows(0).value(0).data().toString();

           if(T.supprimer(C))
           {
               ui->afficher_Contrat->setModel(T.afficher());
               musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/supp succe.mp3"));
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


void MainWindow::on_re_afficherContrat_clicked()
{
    ui->typecnt->setText("");
    ui->nom_2cnt->setText("");
    ui->duree->setCurrentText("");
    ui->tarifcnt->setText("");
    ui->idcollaborateur_2->setCurrentText("");
}

void MainWindow::on_pb_rechercheContrat_clicked()
{
    if (ui->checkBox_nom_3->isChecked())
   { QString nom=ui->rech_nom_3->text();
       QSqlQueryModel *verif=T.rechercher_nom(nom);
       if (verif!=nullptr)
       {
           ui->afficher_Contrat->setModel(verif);

       }
    }

 if (ui->checkBox_type_3->isChecked())
   { QString type=ui->rech_type_3->text();
       QSqlQueryModel *verif=T.rechercher_type(type);
       if (verif!=nullptr)
       {

           ui->afficher_Contrat->setModel(verif);

       }
    }
  if (ui->checkBox_tarif->isChecked())
   { QString tarif=ui->rech_tarif->text();
       QSqlQueryModel *verif=T.rechercher_tarif(tarif);
       if (verif!=nullptr)
       {

           ui->afficher_Contrat->setModel(verif);

       }
    }
   if ((ui->checkBox_nom_3->isChecked())&&(ui->checkBox_type_3->isChecked()))
   {
       QString nom=ui->rech_nom_3->text();
       QString type=ui->rech_type_3->text();

                   if (nom!="")
                     {
                       if (type!="")
                          {
                   QSqlQueryModel *verif=T.rechercher_nom_type(nom,type);
                   if (verif!=nullptr)
                   {
                       ui->afficher_Contrat->setModel(verif);

                   }
                       } else
                           QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
                   } else
                       QMessageBox::warning(this,"erreur","Champ salaire est vide");
   }
  if ((ui->checkBox_nom_3->isChecked())&&(ui->checkBox_tarif->isChecked()))
   {
       QString nom=ui->rech_nom_3->text();
      QString tarif=ui->rech_tarif->text();

                   if (nom!="")
                     {
                   QSqlQueryModel *verif=T.rechercher_nom_tarif(nom,tarif);
                   if (verif!=nullptr)
                   {
                       ui->afficher_Contrat->setModel(verif);

                   }

                   } else
                       QMessageBox::warning(this,"erreur","Champ salaire est vide");
   }
   if ((ui->checkBox_type_3->isChecked())&&(ui->checkBox_tarif->isChecked()))
   {
      QString type=ui->rech_type_3->text();
      QString tarif=ui->rech_tarif->text();

                   if (type!="")
                     {
                   QSqlQueryModel *verif=T.rechercher_type_tarif(type,tarif);
                   if (verif!=nullptr)
                   {
                       ui->afficher_Contrat->setModel(verif);

                   }

                   } else
                       QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
   }


if ((ui->checkBox_nom_3->isChecked())&&(ui->checkBox_tarif->isChecked())&&(ui->checkBox_type_3->isChecked()))
{

    QString tarif=ui->rech_tarif->text();
    QString nom=ui->rech_nom_3->text();
    QString type=ui->rech_type_3->text();

                if (nom!="")
                  {
                    if (type!="")
                       {
                QSqlQueryModel *verif=T.rechercher_tous(nom,type,tarif);
                if (verif!=nullptr)
                {

                    ui->afficher_Contrat->setModel(verif);

                }
                    } else
                        QMessageBox::warning(this,"erreur","Champ jour de travail est vide");
                } else
                    QMessageBox::warning(this,"erreur","Champ salaire est vide");

}
}




void MainWindow::on_imprimer_Contrat_clicked()
{
    QPdfWriter pdf("C:/Users/ASUS/Desktop/Integration Finale/PDF/salma.pdf");
                       QPainter painter(&pdf);
                      int i = 4000;
                           painter.setPen(Qt::red);
                           painter.setFont(QFont("Comic Sans MS", 30));
                           painter.drawText(1100,1100,"Liste Des Contrats ");
                           painter.setPen(Qt::blue);
                           painter.setFont(QFont("Comic Sans MS", 50));
                           painter.drawRect(100,100,7300,1900);
                           painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/ASUS/Desktop/Integration Finale/sd.png"));
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
                                   QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Desktop/Integration Finale/PDF/salma.pdf"));
                                   painter.end();
                               }
                               if (reponse == QMessageBox::No)
                               {
                                    painter.end();
                               }
}


void MainWindow::on_le_stat_Contrat_clicked()
{
    statis *w=new statis();
    w->make();
    w->show();
}

void MainWindow::on_resetReservation_clicked()
{
    ui->numres->setText("");
    ui->nomRES->setText("");
    ui->prenomRES->setText("");
    ui->dateres->setText("");
    ui->typeres->setCurrentText("");
    ui->nbtable->setText("");
    ui->nbchaise->setText("");
}


void MainWindow::on_ajouter_REServation_clicked()
{
    QString numres=ui->numres->text();
    QString nom=ui->nomRES->text();
    QString prenom=ui->prenomRES->text();
    QString dateres=ui->dateres->text();
    QString typeres=ui->typeres->currentText();
    QString nbtable=ui->nbtable->text();
    QString nbchaise=ui->nbchaise->text();
Reservation R(numres,nom,prenom,dateres,typeres,nbtable,nbchaise);
    bool test2=R.ajouter();

    if((test2)&&(verifNOMR())&&(verifPRENOM1()))
    {
        ui->tableViewres->setModel(Re.afficher());
        musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/ajout succe.mp3"));
                musicAdd.play();
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->setIcon(QIcon("icone.png"));

                        notifyIcon->showMessage("GESTION COLLABORATEURS  RESERVATION","reservation Ajoutée",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_modifReservation_clicked()
{
    if (ui->modifReservation->isChecked())
        {
            ui->modifReservation->setText("Modifiable");

            QSqlTableModel *tableModel= new QSqlTableModel();
            tableModel->setTable("reservation");
            tableModel->select();
            ui->tableViewres->setModel(tableModel);
        }
        else
        {
            ui->modifReservation->setText("Modifier");
            musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/modif succe.mp3"));
                    musicAdd.play();
            ui->tableViewres->setModel(Re.afficher());

                    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                            notifyIcon->show();
                            notifyIcon->setIcon(QIcon("icone.png"));

                            notifyIcon->showMessage("GESTION COLLABORATEURS  RESERVATION ","reservation Modifié",QSystemTrayIcon::Information,15000);
            QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                        QObject::tr("Fonction modifié.\n"
                                    "Click OK to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_supprimerReservation_clicked()
{
    QItemSelectionModel *select = ui->tableViewres->selectionModel();
            QString numres = select->selectedRows(0).value(0).data().toString();

           if(Re.supprimer(numres))
           {
               ui->tableViewres->setModel(Re.afficher());
               musicAdd.setMedia(QUrl("C:/Users/ASUS/Desktop/Integration Finale/supp succe.mp3"));
                       musicAdd.play();
               QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                       notifyIcon->show();
                       notifyIcon->setIcon(QIcon("icone.png"));

                       notifyIcon->showMessage("GESTION COLLABORATION ","La suppression du reservation est effectuée",QSystemTrayIcon::Information,15000);

               QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("Suppression effectué.\n"
                                       "Click ok to exit."), QMessageBox::Cancel);
               int nb=ui->tableViewres->model()->rowCount();
                              ui->numres->clear();

                              for (int i=0;i<nb;i++)
                              {
                                  QString cinf = ui->tableViewres->model()->index(i, 0).data().toString();
                                 // ui->numres->addItem();
                              }
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                           QObject::tr("Suppression non effectue.\n"
                                       "Click OK to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_historiqueSALMA_clicked()
{
    ui->tabhis_3->setModel(tm.afficherhis()) ;
    ui->tabhis_3->setModel(tm.afficherhis());//refresh
}



void MainWindow::on_envoyerSMS_clicked()
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);

        QUrl url("https://ACfdf6442c496b28eda58ab1a0470c3873:131b59ad2d99808f7d6cf598488cb5ae@api.twilio.com/2010-04-01/Accounts/ACfdf6442c496b28eda58ab1a0470c3873/Messages.json");
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


        QUrlQuery params;
        params.addQueryItem("From", "+17179253091");
        params.addQueryItem("To",ui->NumSMS->text() );//"+21627198506"
        params.addQueryItem("Body", ui->msgSMS->toPlainText());
       // params.addQueryItem("Body", "test");

        // etc

        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply*)));

        manager->post(request, params.query().toUtf8());

}





void MainWindow::on_pushButton_ajouter_Plat_clicked()
{
    int Id=ui->lineEdit_id_2->text().toInt();
    int prix=ui->lineEdit_prix_2->text().toInt();
    QString nom=ui->lineEdit_nom_2->text();
    QString type;
    if( ui->comboBox_type->currentIndex()==1 )
        type="Entree";

                else if( ui->comboBox_type->currentIndex()==2 ) {

                type="Plat principal";
                }
    else if( ui->comboBox_type->currentIndex()==3 )   {

    type="Dessert";
    }

    QString ingredients=ui->lineEdit_ing->text();
    Plat P(Id,prix,nom,type,ingredients);


     if(verifID1()&&verifNOM()&&verifPRIX()&&verifingredients())
     {

         bool test=P.ajouter();


    if(test)
  {ui->tableView_P->setModel(tmpPlat.afficher());//refresh
        ui->lineEdit_id_3->clear();
        ui->comboBox_type_2->setCurrentIndex(0);
        ui->lineEdit_ing_3->clear();
        ui->lineEdit_nom_3->clear();
        ui->lineEdit_prix_3->clear();
        N.notifications_ajouterPlat();
 son->play();
            Mailing* m = new Mailing("omarnouri9999@gmail.com","selimanouri14","smtp.gmail.com",465);
           // connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            m->sendMail("omarnouri9999@gmail.com","abdelmoomen.medhioub@esprit.tn","add plat"," plat ajouté avec succès");


  QMessageBox::information(nullptr, QObject::tr("Ajouter un Plat"),
                    QObject::tr("Plat ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }


    else
     {

        QMessageBox::critical(nullptr, QObject::tr("Ajouter un Plat"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        }
     } else
     {
         QMessageBox msgBox ;
         msgBox.setText("fournisseur non ajouté ");
     }

    }


void MainWindow::on_pushButton_afficher_Plat_clicked()
{
    ui->tableView_P->setModel(tmpPlat.afficher());//refresh
    ui->lineEdit_id->clear();
    ui->comboBox_type->setCurrentIndex(0);
    ui->lineEdit_ing->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prix->clear();
}

void MainWindow::on_tableView_P_activated(const QModelIndex &index)
{
    QString val=ui->tableView_P->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from PLAT where ID='"+val+"' or NOM='"+val+"' or TYPE='"+val+"' or PRIX='"+val+"' or INGREDIENTS='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_id_3->setText(qry.value(0).toString());
            ui->lineEdit_prix_3->setText(qry.value(1).toString());
            ui->lineEdit_nom_3->setText(qry.value(2).toString());
            ui->comboBox_type_2->setCurrentText(qry.value(3).toString());
            ui->lineEdit_ing_3->setText(qry.value(4).toString());
        }
    }

}

void MainWindow::on_pushButton_supprimer_Plat_clicked()
{
    int id = ui->lineEdit_id_3->text().toInt();
    bool test=tmpPlat.supprimer(id);

    if(test)
    {ui->tableView_P->setModel(tmpPlat.afficher());//refresh
        N.notifications_supprimerPlat();
        son2->play();
        ui->lineEdit_id_3->clear();
        ui->comboBox_type_2->setCurrentIndex(0);
        ui->lineEdit_ing_3->clear();
        ui->lineEdit_nom_3->clear();
        ui->lineEdit_prix_3->clear();
       QMessageBox::information(nullptr, QObject::tr("Supprimer un Plat"),
                    QObject::tr("Plat supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
       {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un Plat"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_pushButton_modifier_Plat_clicked()
{
    int id = ui->lineEdit_id_3->text().toInt();
    int prix = ui->lineEdit_prix_3->text().toInt();
    QString nom = ui->lineEdit_nom_3->text();
    QString type;
    if( ui->comboBox_type_2->currentIndex()==1 )
        type="Entree";

                else if( ui->comboBox_type_2->currentIndex()==2 )   {

                type="Plat principal";
                }
    else if( ui->comboBox_type_2->currentIndex()==3 )   {

    type="Dessert";
    }
    QString ingredients = ui->lineEdit_ing_3->text();
    Plat P(id,prix,nom,type,ingredients);
    if(verifID_3()&&verifNOM_3()&&verifPRIX_3()&&verifingredients_3())
    {

    bool test=P.modifier(id);


    if(test)
    {
        N.notifications_modifierPlat();
        son1->play();
        ui->lineEdit_id_3->clear();
        ui->comboBox_type_2->setCurrentIndex(0);
        ui->lineEdit_ing_3->clear();
        ui->lineEdit_nom_3->clear();
        ui->lineEdit_prix_3->clear();
        ui->tableView_P->setModel(tmpPlat.afficher());


        QMessageBox::information(nullptr, QObject::tr("modifier un Plat"),

                    QObject::tr("Plat modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
   } else

    {
        QMessageBox::critical(nullptr, QObject::tr("modifier un Plat"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_ajouter_Boisson_clicked()
{
    int Id=ui->lineEdit_idB->text().toInt();
    int prix=ui->lineEdit_prixB->text().toInt();
    QString nom=ui->lineEdit_nomB->text();
    QString type;
    if( ui->comboBox_typeB->currentIndex()==1 )
        type="Eau minerale";

                else if( ui->comboBox_typeB->currentIndex()==2 )   {

                type="Boisson gazeuse";
                }
    else if( ui->comboBox_typeB->currentIndex()==3 )   {

    type="Boisson alcoolisee";
    }
    else if( ui->comboBox_typeB->currentIndex()==4 )   {

    type="Jus";
    }
   //=ui->lineEdit_typeB->text();
    Boisson B(Id,prix,nom,type);


    if(verifIDb()&&verifNOMb()&&verifPRIXb())
    {
    bool test=B.ajouter();

    if(test)
  {
        N.notifications_ajouterBoisson();
        son3->play();
        ui->lineEdit_idB->clear();
        ui->comboBox_typeB->setCurrentIndex(0);
        ui->lineEdit_nomB->clear();
        ui->lineEdit_prixB->clear();
        ui->tableView_B->setModel(tmpBoisson.afficher());//refresh

  QMessageBox::information(nullptr, QObject::tr("Ajouter boisson"),
                    QObject::tr("boisson ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }

    else {
        QMessageBox msgBox ;
        msgBox.setText("fournisseur non ajouté ");
         }

    }

}

void MainWindow::on_pushButton_modifier_Boisson_clicked()
{
    int id = ui->lineEdit_idB_2->text().toInt();
    int prix = ui->lineEdit_prixB_2->text().toInt();
    QString nom = ui->lineEdit_nomB_2->text();
    QString type;
    if( ui->comboBox_type_3->currentIndex()==1 )
        type="Eau minérale";

                else if( ui->comboBox_type_3->currentIndex()==2 )   {

                type="Boisson gazeuse";
                }
    else if( ui->comboBox_type_3->currentIndex()==3 )   {

    type="Boisson alcoolisee";
    }
    else if( ui->comboBox_type_3->currentIndex()==4 )   {

    type="Jus";
    }


    if(verifIDb_2()&&verifNOMb_2()&&verifPRIXb_2())
    {
        Boisson B(id,prix,nom,type);

    bool test=B.modifier(id);


    if(test)
    {
        N.notifications_modifierBoisson();
        son4->play();
        ui->lineEdit_idB_2->clear();
        ui->comboBox_type_3->setCurrentIndex(0);

        ui->lineEdit_nomB_2->clear();
        ui->lineEdit_prixB_2->clear();
        ui->tableView_B->setModel(tmpBoisson.afficher());//refresh


        QMessageBox::information(nullptr, QObject::tr("modifier boisson"),

                    QObject::tr("boisson modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
  } else

    {
        QMessageBox::critical(nullptr, QObject::tr("modifier un boisson"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

void MainWindow::on_pushButton_supprimer_Boisson_clicked()
{
    int id = ui->lineEdit_idB_2->text().toInt();

    bool test=tmpBoisson.supprimer(id);

    if(test){
        N.notifications_supprimerBoisson();
        son5->play();
        ui->lineEdit_idB_2->clear();
        ui->comboBox_type_3->setCurrentIndex(0);
        ui->lineEdit_nomB_2->clear();
        ui->lineEdit_prixB_2->clear();
        ui->tableView_B->setModel(tmpBoisson.afficher());//refresh

       QMessageBox::information(nullptr, QObject::tr("Supprimer un boisson"),
                    QObject::tr("boisson supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
       {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un boisson"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_afficher_Boisson_clicked()
{
    ui->tableView_B->setModel(tmpBoisson.afficher());//refresh
    ui->lineEdit_idB->clear();
    ui->comboBox_typeB->clear();

    ui->lineEdit_nomB->clear();
    ui->lineEdit_prixB->clear();

}

void MainWindow::on_tableView_B_activated(const QModelIndex &index)
{
    QString val=ui->tableView_B->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from BOISSON where ID='"+val+"' or NOM='"+val+"' or TYPE='"+val+"' or PRIX='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_idB_2->setText(qry.value(0).toString());
            ui->lineEdit_prixB_2->setText(qry.value(1).toString());
            ui->lineEdit_nomB_2->setText(qry.value(2).toString());
            ui->comboBox_type_3->setCurrentText(qry.value(3).toString());
        }
    }
}

void MainWindow::on_tri_prix_Plat_clicked()
{
    ui->tableView_P->setModel(tmpPlat.trier());//refresh
}

void MainWindow::on_tri_nom_Plat_clicked()
{
      ui->tableView_P->setModel(tmpPlat.trierN());//refresh
}

void MainWindow::on_fermer_porte_clicked()
{
    a.write_to_arduino("0");

}

void MainWindow::on_imprimer_pdf_Plat_clicked()
{

        QPdfWriter pdf("C:/Users/ASUS/Desktop/Integration Finale/PDF/plat.pdf");
        QPainter painter(&pdf);
        int i = 4000;
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(1100,1200,"Liste Des Plats ");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 50));
        painter.drawRect(100,100,7300,2600);
        painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/ASUS/Desktop/Integration Finale/sd.png"));
        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(200,3300,"ID");
        painter.drawText(1700,3300,"PRIX");
        painter.drawText(3200,3300,"NOM");
        painter.drawText(4900,3300,"TYPE");
        painter.drawText(6600,3300,"INGREDIENTS");


        QSqlQuery query;
        query.prepare("select * from PLAT");
        query.exec();
        while (query.next())
        {
            painter.drawText(200,i,query.value(0).toString());
            painter.drawText(1700,i,query.value(1).toString());
            painter.drawText(3200,i,query.value(2).toString());
            painter.drawText(4900,i,query.value(3).toString());
            painter.drawText(6600,i,query.value(4).toString());
            painter.drawText(8100,i,query.value(5).toString());

            i = i + 500;
        }
        int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Desktop/Integration Finale/PDF/plat.pdf"));
            painter.end();
        }
        if (reponse == QMessageBox::No)
        {
            painter.end();
        }

}

void MainWindow::on_ouvrir_prote_clicked()
{
    a.write_to_arduino("1");

}

void MainWindow::on_tri_prix_Boisson_clicked()
{
     ui->tableView_B->setModel(tmpBoisson.trier());//refresh
}

void MainWindow::on_tri_nom_Boisson_clicked()
{
    ui->tableView_B->setModel(tmpBoisson.trierN());//refresh
}

void MainWindow::on_imprimer_pdf_Boisson_clicked()
{
    QPdfWriter pdf("C:/Users/ASUS/Desktop/Integration Finale/PDF/boi.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(1100,1200,"Liste Des Boissons ");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(100,100,7300,2600);
    painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/ASUS/Desktop/Integration Finale/sd.png"));
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(200,3300,"ID");
    painter.drawText(1700,3300,"PRIX");
    painter.drawText(3200,3300,"NOM");
    painter.drawText(4900,3300,"TYPE");



    QSqlQuery query;
    query.prepare("select * from BOISSON");
    query.exec();
    while (query.next())
    {
        painter.drawText(200,i,query.value(0).toString());
        painter.drawText(1700,i,query.value(1).toString());
        painter.drawText(3200,i,query.value(2).toString());
        painter.drawText(4900,i,query.value(3).toString());
        painter.drawText(6600,i,query.value(4).toString());
        painter.drawText(8100,i,query.value(5).toString());

        i = i + 500;
    }
    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Desktop/Integration Finale/PDF/boi.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }

}

void MainWindow::on_tri_id_Plat_clicked()
{

    ui->tableView_P->setModel(tmpPlat.trierI());//refresh
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableView->setModel(tmpPlat.recherche(ui->lineEdit->text()));
}

void MainWindow::on_tri_id_Boisson_clicked()
{

    ui->tableView_B->setModel(tmpBoisson.trierI());//refresh
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
   ui->tableView_B->setModel(tmpBoisson.recherche(ui->lineEdit_2->text()));
}

bool MainWindow::verifID1()
{
    if (ui->lineEdit_id_2->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_id_2->text().isEmpty())
    {
        ui->lineEdit_id_2->clear();

        ui->lineEdit_id_2->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifNOMM()
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

/*bool MainWindow::verifTYPE()
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
}*/

bool MainWindow::verifPRIX1()
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

bool MainWindow::verifingredients()
{
    if (ui->lineEdit_ing->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_ing->text().isEmpty())
    {
        ui->lineEdit_ing->clear();
        ui->lineEdit_ing->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}




bool MainWindow::verifIDb()
{
    if (ui->lineEdit_idB->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_idB->text().isEmpty())
    {
        ui->lineEdit_idB->clear();

        ui->lineEdit_idB->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifNOMb()
{
    if (ui->lineEdit_nomB->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_nomB->text().isEmpty())
    {
        ui->lineEdit_nomB->clear();
        ui->lineEdit_nomB->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}

/*bool MainWindow::verifTYPEb()
{
    if (ui->lineEdit_typeB->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_typeB->text().isEmpty())
    {
        ui->lineEdit_typeB->clear();
        ui->lineEdit_typeB->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}*/

bool MainWindow::verifPRIXb()
{
    if (ui->lineEdit_prixB->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_prixB->text().isEmpty())
    {
        ui->lineEdit_prixB->clear();

        ui->lineEdit_prixB->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

void MainWindow::myfunctionn()
{
    QTime time = QTime::currentTime() ;
        QString time_text=time.toString("hh : mm : ss")  ;

        ui->label_date_time->setText(time_text) ;
        ui->label_date_time2->setText(time_text) ;
        ui->label_date_time3->setText(time_text) ;
}



bool MainWindow::verifIDb_2()
{
    if (ui->lineEdit_idB_2->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_idB_2->text().isEmpty())
    {
        ui->lineEdit_idB_2->clear();

        ui->lineEdit_idB_2->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifNOMb_2()
{
    if (ui->lineEdit_nomB_2->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_nomB_2->text().isEmpty())
    {
        ui->lineEdit_nomB_2->clear();
        ui->lineEdit_nomB_2->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}



bool MainWindow::verifPRIXb_2()
{
    if (ui->lineEdit_prixB_2->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_prixB_2->text().isEmpty())
    {
        ui->lineEdit_prixB_2->clear();

        ui->lineEdit_prixB_2->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}


bool MainWindow::verifID_3()
{
    if (ui->lineEdit_id_3->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_id_3->text().isEmpty())
    {
        ui->lineEdit_id_3->clear();

        ui->lineEdit_id_3->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifNOM_3()
{
    if (ui->lineEdit_nom_3->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_nom_3->text().isEmpty())
    {
        ui->lineEdit_nom_3->clear();
        ui->lineEdit_nom_3->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}



bool MainWindow::verifPRIX_3()
{
    if (ui->lineEdit_prix_3->text().contains(QRegExp("[^0-9 ]") ) || ui->lineEdit_prix_3->text().isEmpty())
    {
        ui->lineEdit_prix_3->clear();

        ui->lineEdit_prix_3->setPlaceholderText("contient que des chiffres") ;
        return false;
    }
    else
    {
        return true;
    }

}

bool MainWindow::verifingredients_3()
{
    if (ui->lineEdit_ing_3->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->lineEdit_ing_3->text().isEmpty())
    {
        ui->lineEdit_ing_3->clear();
        ui->lineEdit_ing_3->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

/*void MainWindow::on_stat_clicked()
{
    //![1]
        QBarSet *set0 = new QBarSet("Plat");
        QBarSet *set1 = new QBarSet("Boisson");


        *set0 << 1 << 2 << 3 << 4 << 5 << 6;
        *set1 << 5 << 0 << 0 << 4 << 0 << 7;

    //![1]

    //![2]
        QPercentBarSeries *series = new QPercentBarSeries();
        series->append(set0);
        series->append(set1);

    //![2]

    //![3]
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statestique de gestion des Plats et Boissons");
        chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
        QStringList categories;
        categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        QValueAxis *axisY = new QValueAxis();
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    //![4]

    //![5]
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    //![6]

    //![7]

        window=new MainWindow(this);

        window->setCentralWidget(chartView);
        window->resize(420, 300);
        window->show();
    //![7]
}*/


/*
void MainWindow::on_stat_clicked()
{

}*/

void MainWindow::on_pushButton_10_clicked()
{
    ui->idblocs->setText("");
    ui->numb->setText("");
    ui->etat->setText("");

}
