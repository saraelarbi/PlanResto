#include "remise.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Remise::Remise()
{

}

Remise::Remise(QString idmateriel,QString remise)
{this->idmateriel=idmateriel; this->remise=remise;}
QString Remise:: getidmateriel(){return idmateriel;}
QString Remise:: getremise(){return remise;}

void Remise:: setidmateriel(QString idmateriel) {this->idmateriel=idmateriel;}
void Remise:: setremise(QString remise){this->remise=remise;}

bool Remise::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO REMISE(idmateriel,remise) "
                        "VALUES (:idmateriel ,:remise)");
          query.bindValue(":idmateriel", idmateriel);
          query.bindValue(":remise", remise);

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




return model;
}

bool Remise::modifier(QString,QString)
 {
     QSqlQuery query;

     query.prepare("UPDATE REMISE SET idmateriel:=idmateriel, remise:=remise");
     query.bindValue(":idmateriel",idmateriel);
     query.bindValue(":remise",remise);

     return query.exec();
}






QSqlQueryModel* Remise::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from REMISE where ((idmateriel || remise ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID materiel"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("remise"));
    return model;
}

