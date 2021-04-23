#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include "smtp.h"
#include "arduino.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    ui->tableView->setModel(tmpPlat.afficher());//refresh
    ui->tableView_B->setModel(tmpBoisson.afficher());//refresh

    delete ui;

}


/*void MainWindow::on_pushButton_2_clicked()
{
    ui->tableView->setModel(tmpclient.afficher());//refresh

}

void MainWindow::on_pushButton_5_clicked()
{
    int Id=ui->lineEdit_2->text().toInt();
    int prix=ui->lineEdit->text().toInt();
    Qstirng nom=ui->lineEdit_4->text();
    Qstirng type=ui->lineEdit_5->text();
    Qstirng ingredients=ui->lineEdit_3->text();
    Plat P(Id,prix,nom,type,ingredients);
}*/

void MainWindow::on_pushButton_4_clicked()
{
    int Id=ui->lineEdit_id->text().toInt();
    int prix=ui->lineEdit_prix->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString type=ui->lineEdit_type->text();
    QString ingredients=ui->lineEdit_ing->text();
    Plat P(Id,prix,nom,type,ingredients);

     if(verifID()&&verifNOM()&&verifTYPE()&&verifPRIX())
     {
         bool test=P.ajouter();
         ui->lineEdit_id->clear();
         ui->lineEdit_type->clear();
         ui->lineEdit_ing->clear();
         ui->lineEdit_nom->clear();
         ui->lineEdit_prix->clear();
    if(test)
  {ui->tableView->setModel(tmpPlat.afficher());//refresh


            Smtp* smtp = new Smtp("omarnouri9999@gmail.com","selimanouri14","smtp.gmail.com",465);
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtp->sendMail("omarnouri9999@gmail.com","abdelmoomen.medhioub@esprit.tn","add plat"," plat ajouté avec succès");


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


void MainWindow::on_pushButton_3_clicked()
{
    ui->tableView->setModel(tmpPlat.afficher());//refresh
    ui->lineEdit_id->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_ing->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prix->clear();
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from PLAT where ID='"+val+"' or NOM='"+val+"' or TYPE='"+val+"' or PRIX='"+val+"' or INGREDIENTS='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_id->setText(qry.value(0).toString());
            ui->lineEdit_prix->setText(qry.value(1).toString());
            ui->lineEdit_nom->setText(qry.value(2).toString());
            ui->lineEdit_type->setText(qry.value(3).toString());
            ui->lineEdit_ing->setText(qry.value(4).toString());
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    bool test=tmpPlat.supprimer(id);
    ui->lineEdit_id->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_ing->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prix->clear();
    if(test)
    {ui->tableView->setModel(tmpPlat.afficher());//refresh

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

void MainWindow::on_pushButton_2_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    int prix = ui->lineEdit_prix->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString type = ui->lineEdit_type->text();
    QString ingredients = ui->lineEdit_ing->text();
    Plat P(id,prix,nom,type,ingredients);
    bool test=P.modifier(id);
    ui->lineEdit_id->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_ing->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prix->clear();
    if(test)
    {
        ui->tableView->setModel(tmpPlat.afficher());


        QMessageBox::information(nullptr, QObject::tr("modifier un Plat"),

                    QObject::tr("Plat modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else

    {
        QMessageBox::critical(nullptr, QObject::tr("modifier un Plat"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int Id=ui->lineEdit_idB->text().toInt();
    int prix=ui->lineEdit_prixB->text().toInt();
    QString nom=ui->lineEdit_nomB->text();
    QString type=ui->lineEdit_typeB->text();
    Boisson B(Id,prix,nom,type);

    if(verifIDb()&&verifNOMb()&&verifTYPEb()&&verifPRIXb())
    {
    bool test=B.ajouter();
    ui->lineEdit_idB->clear();
    ui->lineEdit_typeB->clear();
    ui->lineEdit_nomB->clear();
    ui->lineEdit_prixB->clear();
    if(test)
  {

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

void MainWindow::on_pushButton_7_clicked()
{
    int id = ui->lineEdit_idB->text().toInt();
    int prix = ui->lineEdit_prixB->text().toInt();
    QString nom = ui->lineEdit_nomB->text();
    QString type = ui->lineEdit_typeB->text();

    Boisson B(id,prix,nom,type);
    bool test=B.modifier(id);
    ui->lineEdit_idB->clear();
    ui->lineEdit_typeB->clear();

    ui->lineEdit_nomB->clear();
    ui->lineEdit_prixB->clear();
    if(test)
    {
        ui->tableView_B->setModel(tmpBoisson.afficher());//refresh


        QMessageBox::information(nullptr, QObject::tr("modifier boisson"),

                    QObject::tr("boisson modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else

    {
        QMessageBox::critical(nullptr, QObject::tr("modifier un boisson"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_8_clicked()
{
    int id = ui->lineEdit_idB->text().toInt();
    bool test=tmpBoisson.supprimer(id);
    ui->lineEdit_idB->clear();
    ui->lineEdit_typeB->clear();
    ui->lineEdit_nomB->clear();
    ui->lineEdit_prixB->clear();
    if(test){
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

void MainWindow::on_pushButton_6_clicked()
{
    ui->tableView_B->setModel(tmpBoisson.afficher());//refresh
    ui->lineEdit_idB->clear();
    ui->lineEdit_typeB->clear();

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
            ui->lineEdit_idB->setText(qry.value(0).toString());
            ui->lineEdit_prixB->setText(qry.value(1).toString());
            ui->lineEdit_nomB->setText(qry.value(2).toString());
            ui->lineEdit_typeB->setText(qry.value(3).toString());
        }
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->tableView->setModel(tmpPlat.trier());//refresh
}

void MainWindow::on_pushButton_10_clicked()
{
      ui->tableView->setModel(tmpPlat.trierN());//refresh
}

void MainWindow::on_pushButton_11_clicked()
{
    QString valeur=ui->lineEdit->text();
    Plat *e=new Plat();
    ui->tableView->setModel(e->recherche(valeur));

}

void MainWindow::on_pushButton_12_clicked()
{

        QPdfWriter pdf("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/PDF.pdf");
        QPainter painter(&pdf);
        int i = 4000;
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(1100,1200,"Liste Des Plats ");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 50));
        painter.drawRect(100,100,7300,2600);

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
            QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/PDF.pdf"));
            painter.end();
        }
        if (reponse == QMessageBox::No)
        {
            painter.end();
        }

}

void MainWindow::on_pushButton_13_clicked()
{
    QString valeur=ui->lineEdit_2->text();
    Boisson *e=new Boisson();
    ui->tableView_B->setModel(e->recherche(valeur));

}

void MainWindow::on_pushButton_16_clicked()
{
     ui->tableView_B->setModel(tmpBoisson.trier());//refresh
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->tableView_B->setModel(tmpBoisson.trierN());//refresh
}

void MainWindow::on_pushButton_14_clicked()
{
    QPdfWriter pdf("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/PDF.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(1100,1200,"Liste Des Boissons ");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(100,100,7300,2600);

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
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/PDF.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }

}

void MainWindow::on_pushButton_17_clicked()
{

    ui->tableView->setModel(tmpPlat.trierI());//refresh
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableView->setModel(tmpPlat.recherche(ui->lineEdit->text()));
}

void MainWindow::on_pushButton_18_clicked()
{

    ui->tableView_B->setModel(tmpBoisson.trierI());//refresh
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
   ui->tableView_B->setModel(tmpBoisson.recherche(ui->lineEdit_2->text()));
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

}
