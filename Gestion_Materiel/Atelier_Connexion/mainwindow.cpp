#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mailing.h"
#include"materiel.h"
#include<QFileDialog>
#include"fournisseur.h"
#include <QMessageBox>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include<QTextDocument>
#include<QTextStream>
#include <QGraphicsView>
#include <QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDesktopServices>
#include<QSystemTrayIcon>
#include <QtPrintSupport/QPrinter>
#include <QSound>
#include<QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    son=new QSound("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/ss.wav");
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    ui->tab_mat->setModel(M.afficher());
    ui->tab_fou->setModel(F.afficher());
    ui->tab_mail->setModel(F.afficher());
    ui->tab_rem->setModel(R.afficher());

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

    int nb=ui->tab_fou->model()->rowCount();
                       ui->cinfet->clear();

                       for (int i=0;i<nb;i++)
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
 if((id=="")&&(nom=="")&&(type=="")&&(marque=="")&&(prix=="")&&(cinf==""))
    {
     QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                           QObject::tr("Tous les champs sont vides"),QMessageBox::Ok);
 }

 else if((id==""))
{
 QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le champ ID est vide"),QMessageBox::Ok);
}
 else if((type==""))
{
 QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le champ Type est vide"),QMessageBox::Ok);
}
 else if((nom==""))
{
 QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le champ Nom est vide"),QMessageBox::Ok);
}
 else if((marque==""))
{
 QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le champ Marque est vide"),QMessageBox::Ok);
}
 else if((prix==""))
{
 QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le champ Prix est vide"),QMessageBox::Ok);
}
 else if((cinf==""))
{
 QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le champ CINF est vide"),QMessageBox::Ok);
}
  else if(test2)
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
    QString prenom=ui->prenom->text();
    QString type=ui->type_2->text();
    QString tel=ui->tel->text();
    QString email=ui->email->text();
    QString adresse=ui->adresse->text();


    Fournisseur F(cinf,nom,prenom,type,tel,email,adresse);
    bool test2=F.ajouter();

    if((cinf=="")&&(nom=="")&&(prenom=="")&&(type=="")&&(tel=="")&&(email=="")&&(adresse==""))
       {
        QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                              QObject::tr("Tous les champs sont vides"),QMessageBox::Ok);

}
    else if((cinf==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ CINF est vide"),QMessageBox::Ok);
}
    else if((nom==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Nom est vide"),QMessageBox::Ok);
}
    else if((prenom==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Prenom est vide"),QMessageBox::Ok);
}
    else if((type==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Type est vide"),QMessageBox::Ok);
}
    else if((tel==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Telephone est vide"),QMessageBox::Ok);
}
    else if((email==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Email est vide"),QMessageBox::Ok);
}
    else if((adresse==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ Adresse est vide"),QMessageBox::Ok);
}
   else if(test2)
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
                    int nb=ui->tab_fou->model()->rowCount();
                                   ui->cinfet->clear();

                                   for (int i=0;i<nb;i++)
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
        ui->nom->setText("");
        ui->marque->setText("");
        ui->prix->setText("");
}


void MainWindow::on_reset_Fou_clicked()
{
    ui->cinf->setText("");
    ui->nom_2->setText("");
    ui->prenom->setText("");
    ui->type_2->setText("");
    ui->tel->setText("");
    ui->email->setText("");
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


void MainWindow::on_ajout_remise_clicked()
{
    QString idmateriel=ui->id_materiel->currentText();
    QString remise=ui->remise->text();
    QString dates=ui->date->text();

    Remise R(idmateriel,remise,dates);


    bool test2=R.ajouter();
    if((idmateriel=="")&&(remise==""))
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


    else if(test2)
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



void MainWindow::on_supp_remise_clicked()
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

void MainWindow::on_modifier_remise_clicked()
{
    if (ui->modifier_remise->isChecked())
        {
            ui->modifier_remise->setText("Modifiable");
            QSqlTableModel *tableModel= new QSqlTableModel();
            tableModel->setTable("REMISE");
            tableModel->select();
            ui->tab_rem->setModel(tableModel);
        }
        else
        {
            ui->modifier_remise->setText("Modifier");
            ui->tab_rem->setModel(R.afficher());
            musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/modif succe.mp3"));
                    musicAdd.play();
            QMessageBox::information(nullptr, QObject::tr("modification remise"),
                        QObject::tr("Remise modifiée.\n"

    "Click OK to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_excel_remise_clicked()
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



           int retVal = obj.export2Excel();
           if( retVal > 0)
           {
               QMessageBox::information(this, tr("Done"),
                                        QString(tr("%1 records exported!")).arg(retVal)
                                        );
           }
}


void MainWindow::on_recherche2_textChanged(const QString &arg1)
{
    Remise R;
        if(ui->recherche2->text() == "")
            {
                ui->tab_rem->setModel(R.afficher());
            }
            else
            {
                 ui->tab_rem->setModel(R.rechercher2(ui->recherche2->text()));
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



