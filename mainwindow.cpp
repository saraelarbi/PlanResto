#include "mainwindow.h"
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
#include "ui_mainwindow.h"
#include "arduino.h"
#include<QComboBox>
#include "reservation.h"

#include <iostream>

#include<QDate>

#include <QNetworkAccessManager>

#include <QUrlQuery>

#include <QNetworkReply>
#include <QJsonValue>
#include <QJsonValueRef>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QModelIndex>
#include <QGridLayout>
#include <QApplication>
#include <QIntValidator>
#include <QDateTime>
#include <QMediaPlayer>
#include <QRadioButton>



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

ui->telephone->setValidator(new QIntValidator(100, 99999999, this));
ui->nbtable->setValidator(new QIntValidator(100, 999, this));
ui->nbchaise->setValidator(new QIntValidator(100, 999, this));
ui->numres->setValidator(new QIntValidator(100, 9999, this));

ui->tarif->setMaxLength(5);
ui->tarif->setValidator(new QIntValidator(100, 99999, this));

ui->telephone->setMaxLength(8);
ui->numres->setMaxLength(4);
ui->idcollaborateur->setMaxLength(4);
ui->lineEdit->setMaxLength(12);
ui->adresse->setMaxLength(50);







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
    srand (time(NULL));
    QDate d = QDate::currentDate() ;
     QString datee =d.toString("dd / MM / yyyy ") ;
     QString fn="ajouter" ;
    QString nom1 = ui->nom->text();
  projeth pp(nom1,datee,fn) ;
  bool test1=pp.ajoutehis() ;




    Collaborateur C(idcollaborateur,nom,prenom,telephone,adresse,email);


     bool test2=C.ajouter();


     /*if((idcollaborateur=="")&&(nom=="")&&(prenom=="")&&(telephone=="")&&(adresse=="")&&(email==""))
        {

         QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                               QObject::tr("Tous les champs sont vides"),QMessageBox::Ok);
     }

     else if((idcollaborateur==""))
    {
     QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                           QObject::tr("Le champ ID est vide"),QMessageBox::Ok);
    }
     else if((nom=="")and (verifNOM()))
    {
     QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                           QObject::tr("Le champ nom est vide"),QMessageBox::Ok);
    }
     else if((prenom==""))
    {
     QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                           QObject::tr("Le champ prenom est vide"),QMessageBox::Ok);
    }
     else if((telephone==""))
    {
     QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                           QObject::tr("Le champ telephone est vide"),QMessageBox::Ok);
    }
     else if((adresse==""))
    {
     QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                           QObject::tr("Le champ adresse est vide"),QMessageBox::Ok);
    }
     else if((email==""))
    {
     QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                           QObject::tr("Le champ email est vide"),QMessageBox::Ok);
    }

 else*/  if((test2)&&(verifNOM())&&(verifPRENOM()))
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
                          srand (time(NULL));
                          QDate d = QDate::currentDate() ;
                           QString datee =d.toString("dd / MM / yyyy ") ;
                           QString fn="supprimer" ;
                          QString nom1 = ui->nom->text();
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


void MainWindow::on_ajouter_collab_clicked()
{
     QString type=ui->type->text();
     QString nom=ui->nom_2->text();
     QString duree=ui->duree->currentText();
     QString tarif=ui->tarif->text();
     QString idcollaborateur=ui->idcollaborateur_2->currentText();
    Contrat C(type,nom,duree,tarif,idcollaborateur);
 bool test2=C.ajouter();

     if((test2)&&(verifNOM1()))
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
        srand (time(NULL));
        QDate d = QDate::currentDate() ;
         QString datee =d.toString("dd / MM / yyyy ") ;
         QString fn="modifier" ;
        QString nom1 = ui->nom->text();
      projeth pp(nom1,datee,fn) ;
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

void MainWindow::on_pushButton_6_clicked()
{
    ui->tabhis->setModel(tmph.afficherhis()) ;
    ui->tabhis->setModel(tmph.afficherhis());//refresh
}


void MainWindow::on_pushButton_2_clicked()
{

    QNetworkAccessManager * manager = new QNetworkAccessManager(this);

        QUrl url("https://ACfdf6442c496b28eda58ab1a0470c3873:131b59ad2d99808f7d6cf598488cb5ae@api.twilio.com/2010-04-01/Accounts/ACfdf6442c496b28eda58ab1a0470c3873/Messages.json");
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


        QUrlQuery params;
        params.addQueryItem("From", "+17179253091");
        params.addQueryItem("To",ui->lineEdit->text() );//"+21627198506"
        params.addQueryItem("Body", ui->textEdit->toPlainText());
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
  /*  bool MainWindow::verifID()
    {
        if (ui->idcollaborateur->text().contains(QRegExp("[^0-9 ]") ) || ui->idcollaborateur->text().isEmpty())
        {
            ui->idcollaborateur->clear();

            ui->idcollaborateur->setPlaceholderText("contient que des chiffres") ;
            return false;
        }
        else
        {
            return true;
        }

    }

    bool MainWindow::verifNOM()
    {
        if (ui->nom->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->nom->text().isEmpty())
        {
            ui->nom->clear();
            ui->nom->setPlaceholderText("contient que des caracteres") ;
            return false;
        }
        else
        {
            return true;
        }

    }
    bool MainWindow::verifPRENOM()
    {
        if (ui->prenom->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->prenom->text().isEmpty())
        {
            ui->prenom->clear();
            ui->prenom->setPlaceholderText("contient que des caracteres") ;
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

    bool MainWindow::verifTYPEb()
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
    }

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

    }*/



void MainWindow::on_ajouter_3_clicked()
{
       QString numres=ui->numres->text();
       QString nom=ui->nom_3->text();
       QString prenom=ui->prenom1->text();
       QString dateres=ui->dateres->text();
       QString typeres=ui->typeres->currentText();
       QString nbtable=ui->nbtable->text();
       QString nbchaise=ui->nbchaise->text();
 Reservation R(numres,nom,prenom,dateres,typeres,nbtable,nbchaise);
       bool test2=R.ajouter();

       if((test2)&&(verifNOM2())&&(verifPRENOM1()))
       {
           ui->tableView->setModel(R.afficher());
           musicAdd.setMedia(QUrl("C:/Users/ASUS I7/Desktop/Atelier_Connexion/ajout succe.mp3"));
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

void MainWindow::on_supprimer3_clicked()
{
QItemSelectionModel *select = ui->tableView->selectionModel();
        QString numres = select->selectedRows(0).value(0).data().toString();

       if(R.supprimer(numres))
       {
           ui->tableView->setModel(R.afficher());
           musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/gestion_materiel1/Gestion_Materiel/Atelier_Connexion/sound/supp succe.mp3"));
                   musicAdd.play();
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();
                   notifyIcon->setIcon(QIcon("icone.png"));

                   notifyIcon->showMessage("GESTION COLLABORATION ","La suppression du reservation est effectuée",QSystemTrayIcon::Information,15000);

           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Suppression effectué.\n"
                                   "Click ok to exit."), QMessageBox::Cancel);
           int nb=ui->tableView->model()->rowCount();
                          ui->numres->clear();

                          for (int i=0;i<nb;i++)
                          {
                              QString cinf = ui->tableView->model()->index(i, 0).data().toString();
                             // ui->numres->addItem();
                          }
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                       QObject::tr("Suppression non effectue.\n"
                                   "Click OK to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_modif3_clicked()
{
    if (ui->modif3->isChecked())
        {
            ui->modif3->setText("Modifiable");

            QSqlTableModel *tableModel= new QSqlTableModel();
            tableModel->setTable("reservation");
            tableModel->select();
            ui->tableView->setModel(tableModel);
        }
        else
        {
            ui->modif3->setText("Modifier");
            musicAdd.setMedia(QUrl("C:/Users/ASUS I7/Desktop/Atelier_Connexion/modif succe.mp3"));
                    musicAdd.play();
            ui->tableView->setModel(R.afficher());

                    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                            notifyIcon->show();
                            notifyIcon->setIcon(QIcon("icone.png"));

                            notifyIcon->showMessage("GESTION COLLABORATEURS  RESERVATION ","reservation Modifié",QSystemTrayIcon::Information,15000);
            QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                        QObject::tr("Fonction modifié.\n"
                                    "Click OK to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_reset3_clicked()
{
    ui->numres->setText("");
    ui->nom_3->setText("");
    ui->prenom1->setText("");
    ui->dateres->setText("");
    ui->typeres->setCurrentText("");
    ui->nbtable->setText("");
    ui->nbchaise->setText("");
}
bool MainWindow::verifNOM()
{
    if (ui->nom->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->nom->text().isEmpty())
    {
        ui->nom->clear();
        ui->nom->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}
bool MainWindow::verifPRENOM()
{
    if (ui->prenom->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->prenom->text().isEmpty())
    {
        ui->prenom->clear();
        ui->prenom->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }

}
bool MainWindow::verifNOM1()
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
bool MainWindow::verifNOM2()
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
bool MainWindow::verifPRENOM1()
{
    if (ui->prenom1->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->prenom1->text().isEmpty())
    {
        ui->prenom1->clear();
        ui->prenom1->setPlaceholderText("contient que des caracteres") ;
        return false;
    }
    else
    {
        return true;
    }
}

