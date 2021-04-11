#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "commande.h"
#include <QMessageBox>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include<QSystemTrayIcon>
#include <QSound>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
son=new QSound("C:/Users/ASUS/Desktop/qt/SmartResto/ss.wav");


ui->tabclient_2->setModel(tmpclient.afficher());
ui->tabcommande_2->setModel(tmpcommande.afficher());

ui->tabclient_2->setSelectionBehavior(QAbstractItemView::SelectRows);
ui->tabclient_2->setSelectionMode(QAbstractItemView::SingleSelection);
ui->tabcommande_2->setSelectionBehavior(QAbstractItemView::SelectRows);
ui->tabcommande_2->setSelectionMode(QAbstractItemView::SingleSelection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    son->play();


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
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un client"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


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
void MainWindow::on_pb_ajouter2_clicked()
{
     son->play();

    QString id= ui->lineEdit_id2->text();
    QString nom= ui->lineEdit_nom2->text();
    QString type= ui->lineEdit_type->text();
    QString prix= ui->lineEdit_prix->text();
    QString cinp= ui->lineEdit_cinp->text();



  commande co(id,nom,type,cinp,prix);
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
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un commande"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

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

void MainWindow::on_resetClient_clicked()
{
    ui->lineEdit_id->setText("");
    ui->lineEdit_nom->setText("");
    ui->lineEdit_prenom->setText("");
    ui->lineEdit_tel->setText("");
    ui->lineEdit_adresse->setText("");
    ui->lineEdit_email->setText("");
}

void MainWindow::on_resetCommande_clicked()
{
    ui->lineEdit_id2->setText("");
    ui->lineEdit_nom2->setText("");
    ui->lineEdit_type->setText("");
    ui->lineEdit_cinp->setText("");
    ui->lineEdit_prix->setText("");
}

void MainWindow::on_reaficherClient_clicked()
{
     ui->lineEditrech->setText("");
     ui->tabclient_2->setModel(tmpclient.afficher());

}

void MainWindow::on_reaficherCommande_clicked()
{
    ui->lineEditrech2->setText("");
    ui->tabcommande_2->setModel(tmpcommande.afficher());


}

/*void MainWindow::on_stat_Commande_clicked()
{
    QSqlQueryModel * model = new  QSqlQueryModel ();
    float salairee = prix.toFloat();
   model-> setQuery ( " select * from COMMANDE where PRIX <5 " );
       float salairee = model-> rowCount();
   model-> setQuery ( " select * from COMMANDE où PRIX entre 5 et 10 " );
       float salairee = model-> rowCount ();
   model-> setQuery ( " sélectionnez * dans TICKET où PRIX> 10 " );
       float salaireee = model-> rowCount ();
       total flottant = salaire + salaire + salaire;
       QString a = QString ( " moins de 5 Dinars " + QString :: number ((salaire * 100 ) / total, ' f ' , 2 ) + " % " );
       QString b = QString ( " entre 5 et 10 Dinars " + QString :: number ((salairee * 100 ) / total, ' f ' , 2 ) + " % " );
       QString c = QString ( " +10 Dinars " + QString :: number ((salaireee * 100 ) / total, ' f ' , 2 ) + " % " );
       QPieSeries * series = new  QPieSeries ();
       series-> append (a, salaire);
       series-> append (b, salairee);
       series-> append (c, salaireee);
       si (salaire!= 0 )
       {QPieSlice * slice = series-> slices (). en ( 0 );
           slice-> setLabelVisible ();
           slice-> setPen ( QPen ());}
       si (salairee! = 0 )
       {
           // Ajouter une étiquette, exploser et définir le pinceau pour la 2ème tranche
           QPieSlice * slice1 = series-> slices (). en ( 1 );
           // tranche1-> setExploded ();
           slice1-> setLabelVisible ();
       }
       si (salaireee! = 0 )
       {
           // Ajout d'étiquettes au reste des tranches
           QPieSlice * slice2 = series-> slices (). en ( 2 );
           // tranche1-> setExploded ();
           slice2-> setLabelVisible ();
       }
       // Créer le widget de graphique
       QChart * chart = nouveau  QChart ();
       // Ajouter des données au graphique avec un titre et masquer la légende
   graphique-> addSeries (série);
   chart-> setTitle ( " Pourcentage Par Prix: Nombre Des Tickets " + QString :: number (total));
       graphique-> légende () -> cacher ();
       // Utilisé pour afficher le graphique
       QChartView * chartView = nouveau  QChartView (graphique);
       chartView-> setRenderHint (QPainter :: Antialiasing);
       chartView-> redimensionner ( 1000 , 500 );
       chartView-> show ();
}*/
