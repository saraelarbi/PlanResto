#include "remise.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Remise::Remise()
{

}

Remise::Remise(QString idmateriel,QString remise,QDate dates,QString ancienprix,QString nouveauprix)
{this->idmateriel=idmateriel; this->remise=remise; this->dates=dates; this->ancienprix=ancienprix; this->nouveauprix=nouveauprix;}
QString Remise:: getidmateriel(){return idmateriel;}
QString Remise:: getremise(){return remise;}
QDate Remise:: getdates(){return dates;}
QString Remise:: getancienprix(){return ancienprix;}
QString Remise:: getnouveauprix(){return nouveauprix;}


void Remise:: setidmateriel(QString idmateriel) {this->idmateriel=idmateriel;}
void Remise:: setremise(QString remise){this->remise=remise;}
void Remise:: setdates(QDate dates){this->dates=dates;}
void Remise:: setancienprix(QString ancienprix) {this->ancienprix=ancienprix;}
void Remise:: setnouveauprix(QString nouveauprix) {this->nouveauprix=nouveauprix;}


bool Remise::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO REMISE(idmateriel,remise,dates,ancienprix,nouveauprix) "
                        "VALUES (:idmateriel ,:remise,:dates,:ancienprix,:nouveauprix)");
          query.bindValue(":idmateriel", idmateriel);
          query.bindValue(":remise", remise);
            query.bindValue(":dates", dates);
            query.bindValue(":ancienprix", ancienprix);
            query.bindValue(":nouveauprix", nouveauprix);


    return  query.exec();
}
bool Remise::supprimer(QString idmateriel)
{

    QSqlQuery query;

          query.prepare("Delete from  REMISE where idmateriel=:idmateriel");
          query.bindValue(":idmateriel", idmateriel);
         return  query.exec();

}
QSqlQueryModel* Remise::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM REMISE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Materiel"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Remise"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Dates"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Ancien Prix"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nouveau Prix"));



return model;
}

bool Remise::modifier(QString,QString,QDate,QString,QString)
 {
     QSqlQuery query;

     query.prepare("UPDATE REMISE SET idmateriel:=idmateriel, remise:=remise, dates:=dates, ancienprix:=ancienprix,nouveauprix:=nouveauprix");
     query.bindValue(":idmateriel",idmateriel);
     query.bindValue(":remise",remise);
       query.bindValue(":dates",dates);
       query.bindValue(":ancienprix",ancienprix);
       query.bindValue(":nouveauprix",nouveauprix);


     return query.exec();
}







QSqlQueryModel* Remise::rechercher2 (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from REMISE where ((idmateriel || remise || dates || ancienprix || nouveauprix ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idmateriel"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("remise"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dates"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ancienprix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nouveauprix"));


    return model;
}
