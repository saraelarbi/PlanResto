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
#include<QTextDocument>
#include<QDesktopServices>
#include<QtPrintSupport/QPrintDialog>
#include<QPainter>
#include<QPdfWriter>
#include<QFileDialog>
#include<QMediaPlayer>
#include<QComboBox>
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
#include <QRadioButton>




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

void MainWindow::on_pb_excel_clicked()
{QTableView *table;
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

void MainWindow::on_pushButton_3_clicked()
{
    mMediaPlayer->play();
}

void MainWindow::on_pushButton_5_clicked()
{
    mMediaPlayer->pause();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->avance->setValue(value);
}

void MainWindow::on_pushButton_2_clicked()
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

void MainWindow::on_pushButton_clicked()
{
    ui->tabhis->setModel(tmph.afficherhis()) ;
    ui->tabhis->setModel(tmph.afficherhis());//refresh
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
