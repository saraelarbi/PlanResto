#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include "smtp.h"
#include "arduino.h"
#include<QSystemTrayIcon>
#include <QSound>
/*#include <QtCharts/QChartView>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    son=new QSound("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/Ajout.wav");
    son1=new QSound("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/Modifier.wav");
    son2=new QSound("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/supprimer.wav");
    son3=new QSound("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/Ajout.wav");
    son4=new QSound("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/Modifier.wav");
    son5=new QSound("C:/Users/abdelmomen medhioub/Desktop/gets_palt_boisson/supprimer.wav");

    timerr=new QTimer(this) ;
        connect(timerr , SIGNAL(timeout()),this,SLOT(myfunctionn())) ;
        timerr->start(1000) ;

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

void MainWindow::on_pushButton_ajouter_Plat_clicked()
{
    int Id=ui->lineEdit_id->text().toInt();
    int prix=ui->lineEdit_prix->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString type  ;
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


     if(verifID()&&verifNOM()&&verifPRIX()&&verifingredients())
     {

         bool test=P.ajouter();


    if(test)
  {ui->tableView->setModel(tmpPlat.afficher());//refresh
        ui->lineEdit_id->clear();
        ui->comboBox_type->setCurrentIndex(0);
        ui->lineEdit_ing->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_prix->clear();
        N.notifications_ajouterPlat();
 son->play();
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


void MainWindow::on_pushButton_afficher_Plat_clicked()
{
    ui->tableView->setModel(tmpPlat.afficher());//refresh
    ui->lineEdit_id->clear();
    ui->comboBox_type->setCurrentIndex(0);
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
    {ui->tableView->setModel(tmpPlat.afficher());//refresh
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
        ui->tableView->setModel(tmpPlat.afficher());


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
    ui->tableView->setModel(tmpPlat.trier());//refresh
}

void MainWindow::on_tri_nom_Plat_clicked()
{
      ui->tableView->setModel(tmpPlat.trierN());//refresh
}

void MainWindow::on_fermer_porte_clicked()
{
    a.write_to_arduino("0");

}

void MainWindow::on_imprimer_pdf_Plat_clicked()
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

void MainWindow::on_tri_id_Plat_clicked()
{

    ui->tableView->setModel(tmpPlat.trierI());//refresh
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
