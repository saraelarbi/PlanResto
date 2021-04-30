#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "produit.h"
#include "blocs.h"
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QTableWidget>
#include<QPdfWriter>
#include<QPainter>
#include<QSqlQuery>
#include<QDesktopServices>
#include<QUrl>
#include<statis.h>
#include<QMediaPlayer>
#include<QSound>
#include<QPropertyAnimation>
#include <QMessageBox>
#include <QIntValidator>
#include<QPrinter>
#include<QPrintDialog>
#include"music.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   /* QPixmap pix("C:/Users/ASUS CELERON/Desktop/interface/image/PRR");
       ui->label_13->setPixmap(pix);
       animation = new QPropertyAnimation(ui->img,"geometry");
       animation->setDuration(10000);
       animation->setStartValue(ui->img->geometry());
       animation->setEndValue(QRect(610,0,100,100));
       animation->start();*/
    ui->tab_bloc->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_bloc->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_produit->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_produit->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_produit->setModel(P.afficher());
    ui->tab_bloc->setModel(B.afficher());

     ui->prix->setValidator(new QIntValidator(0, 999999999, this));
      ui->numb->setValidator(new QIntValidator(0, 999999999, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::verifCHAMPVIDE()

{



    if(ui->nom->text().isEmpty() && ui->id->text().isEmpty() && ui->type->text().isEmpty() && ui->marque->text().isEmpty() &&  ui->prix->text().isEmpty())

    {

         ui->nom->clear();

         ui->id->clear();

         ui->type->clear();

         ui->marque->clear();


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


bool MainWindow::verifCHAMPVIDEbloc()

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


bool MainWindow::verifNUMB()

{

    if (ui->numb->text().contains(QRegExp("[^a-zA-Z ]") ) || ui->numb->text().isEmpty())

    {

        ui->numb->clear();

        ui->numb->setPlaceholderText("contient que des caracteres") ;

        return false;

    }

    else

    {

        return true;

    }

}


bool MainWindow::verifETAT()

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





void MainWindow::on_pb_ajouter1_clicked()
{
   QString idblocs=ui->idblocs->text();
   QString numb=ui->numb->text();
    QString etat=ui->etat->text();

   Blocs B(idblocs,numb,etat);


    bool test2=B.ajouter();
   /* if((idblocs=="")&&(numb=="")&&(etat==""))
        {
         QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                               QObject::tr("Tous les champs sont vides"),QMessageBox::Ok);
     }
    else if((idblocs==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ idblocs est vide"),QMessageBox::Ok);
   }
    else if((numb==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ numb est vide"),QMessageBox::Ok);
   }
    else if((etat==""))
   {
    QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Le champ etat est vide"),QMessageBox::Ok);
   }
*/
    if(test2 && verifCHAMPVIDEbloc() && verifNUMB() && verifETAT())
    {
        ui->tab_bloc->setModel(B.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION BLOCS  BLOCS ","bloc Ajouté",QSystemTrayIcon::Information,15000);
        musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/interface/sound/ajout succe.mp3"));
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



void MainWindow::on_pb_ajouter_clicked()
{
       QString id=ui->id->text();
       QString nom=ui->nom->text();
       QString type=ui->type->text();
       QString marque=ui->marque->text();
       QString prix=ui->prix->text();
           srand (time(NULL));
           QDate d = QDate::currentDate() ;
            QString datee =d.toString("dd / MM / yyyy ") ;
            QString fn="ajouter" ;
           QString nom1 = ui->nom->text();
         projeth pp(nom1,datee,fn) ;
         bool test1=pp.ajoutehis() ;


       Produit P(id,type,nom,marque,prix);


       bool test2=P.ajouter();

       if(test2 && verifCHAMPVIDE() && verifNOM() && verifTYPE() && verifMARQUE() )
       {
           ui->tab_produit->setModel(P.afficher());
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();
                   notifyIcon->setIcon(QIcon("icone.png"));

                   notifyIcon->showMessage("GESTION PRODUIT  PRODUIT ","produit Ajouté",QSystemTrayIcon::Information,15000);
           musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/interface/sound/ajout succe.mp3"));
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
           musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/interface/sound/supp succe.mp3"));
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
           musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/interface/sound/supp succe.mp3"));
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
        musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/interface/sound/modif succe.mp3"));
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
        musicAdd.setMedia(QUrl("C:/Users/ASUS CELERON/Desktop/interface/sound/modif succe.mp3"));
                        musicAdd.play();
        QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                    QObject::tr("Fonction modifié.\n"
                                "Click OK to exit."), QMessageBox::Cancel);
        srand (time(NULL));
                                  QDate d = QDate::currentDate() ;
                                   QString datee =d.toString("dd / MM / yyyy ") ;
                                   QString fn="modifier" ;
                                  QString nom1 = ui->nom->text();
                                projeth pp(nom1,datee,fn) ;
                                bool test1=pp.modifierhis() ;

    }
}

void MainWindow::on_rechercher_produit_clicked()
{
    if (ui->checkBox_nom->isChecked())
              { QString nom=ui->rech_nom->text();
                  QSqlQueryModel *verif=P.rechercher_nom(nom);
                  if (verif!=nullptr)
                  {
                      ui->tab_produit->setModel(verif);

                  }
               }

            if (ui->checkBox_type->isChecked())
              { QString type=ui->rech_type->text();
                  QSqlQueryModel *verif=P.rechercher_type(type);
                  if (verif!=nullptr)
                  {

                      ui->tab_produit->setModel(verif);

                  }
               }
             if (ui->checkBox_marque->isChecked())
              { QString marque=ui->rech_marque->text();
                  QSqlQueryModel *verif=P.rechercher_marque(marque);
                  if (verif!=nullptr)
                  {

                      ui->tab_produit->setModel(verif);

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
             if ((ui->checkBox_nom->isChecked())&&(ui->checkBox_marque->isChecked()))
              {
                  QString nom=ui->rech_nom->text();
                 QString marque=ui->rech_marque->text();

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
              if ((ui->checkBox_type->isChecked())&&(ui->checkBox_marque->isChecked()))
              {
                 QString type=ui->rech_type->text();
                 QString marque=ui->rech_marque->text();

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


           if ((ui->checkBox_nom->isChecked())&&(ui->checkBox_marque->isChecked())&&(ui->checkBox_type->isChecked()))
           {

               QString marque=ui->rech_marque->text();
               QString nom=ui->rech_nom->text();
               QString type=ui->rech_type->text();

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
    ui->id->setText("");
        ui->type->setText("");
        ui->nom->setText("");
        ui->marque->setText("");
        ui->prix->setText("");
}

void MainWindow::on_pushButton_2_clicked()
{

                       QPdfWriter pdf("C:/Produit/taher/Pdf.pdf");
                       QPainter painter(&pdf);
                      int i = 4000;
                           painter.setPen(Qt::red);
                           painter.setFont(QFont("Comic Sans MS", 30));
                           painter.drawText(1100,1100,"Liste Des Produits ");
                           painter.setPen(Qt::blue);
                           painter.setFont(QFont("Comic Sans MS", 50));
                           painter.drawRect(100,100,7300,1900);
                           painter.setPen(Qt::blue);

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
                                   QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Produit/taher/Pdf.pdf"));
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

void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    Blocs B;
            if(ui->recherche->text() == "")
                {
                    ui->tab_bloc->setModel(B.afficher());
                }
                else
                {
                     ui->tab_bloc->setModel(B.rechercher(ui->recherche->text()));
                }
    }



void MainWindow::on_radioButton_clicked()
{

    ui->tab_bloc->setModel(B.afficher());
}

void MainWindow::on_pushButton_7_clicked()
{

    ui->tabhis->setModel(tmph.afficherhis()) ;
    ui->tabhis->setModel(tmph.afficherhis());//refresh
}

void MainWindow::on_pushButton_3_clicked()
{
    QPrinter printer;
         printer.setPrinterName("imprimer");
         QPrintDialog dialog(&printer, this);
         if (dialog.exec() == QDialog::Rejected) return;
         ui->tab_bloc->render(&printer);
}

void MainWindow::on_pushButton_4_clicked()
{
    music music;
        music.setModal(true);
        music.exec();
}

void MainWindow::on_music_bloc_clicked()
{
    music music;
        music.setModal(true);
        music.exec();
}

void MainWindow::on_music_his_clicked()
{
    music music;
        music.setModal(true);
        music.exec();
}

