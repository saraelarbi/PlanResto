#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmpPlat.afficher());//refresh
    ui->tableView_B->setModel(tmpBoisson.afficher());//refresh



}

MainWindow::~MainWindow()
{
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
    bool test=P.ajouter();
    ui->lineEdit_id->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_ing->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_prix->clear();
    if(test)
  {ui->tableView->setModel(tmpPlat.afficher());//refresh

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
