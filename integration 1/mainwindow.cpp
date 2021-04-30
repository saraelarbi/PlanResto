#include "mainwindow.h"
#include "ui_mainwindow.h"

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
#include <QTextDocument>
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

    int nb=ui->affichage->model()->rowCount();
                   ui->TypeFonction_2->clear();

                   for (int i=0;i<nb;i++)
                   {
                       QString type_fonction = ui->affichage->model()->index(i, 0).data().toString();
                       ui->TypeFonction_2->addItem(type_fonction);
                   }


}

MainWindow::~MainWindow()
{
    delete ui;
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
