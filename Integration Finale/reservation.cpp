

#include "reservation.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Reservation::Reservation()
{

}

Reservation::Reservation(QString numres,QString nom,QString prenom,QString dateres,QString typeres,QString nbtable,QString nbchaise)
{this->numres=numres; this->nom=nom; this->prenom=prenom;this->dateres=dateres;this->typeres=typeres;this->nbtable=nbtable;this->nbchaise=nbchaise;}
QString Reservation:: getnumres(){return numres;}
QString Reservation:: getnom(){return nom;}
QString Reservation:: getprenom(){return prenom;}
QString Reservation:: getdateres(){return dateres;}
QString Reservation:: gettyperes(){return typeres;}
QString Reservation:: getnbtable(){return nbtable;}
QString Reservation:: getnbchaise(){return nbchaise;}

void Reservation:: setnumres(QString numres){this->numres=numres;}
void Reservation::setnom(QString nom){this->nom=nom;}
void Reservation:: setprenom(QString prenom){this->prenom=prenom;}
void Reservation:: setdateres(QString dateres){this->dateres=dateres;}
void Reservation:: settyperes(QString typeres){this->typeres=typeres;}
void Reservation:: setnbtable(QString nbtable){this->nbtable=nbtable;}
void Reservation:: setnbchaise(QString nbchaise){this->nbchaise=nbchaise;}



bool Reservation::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO reservation(numres,nom,prenom,dateres,typeres,nbtable,nbchaise) "
                        "VALUES (:numres ,:nom ,:prenom ,:dateres,:typeres,:nbtable,:nbchaise)");

          query.bindValue(":typeres", typeres);
          query.bindValue(":prenom", prenom);
          query.bindValue(":numres", numres);
          query.bindValue(":nom", nom);
          query.bindValue(":nbtable", nbtable);
          query.bindValue(":nbchaise", nbchaise);
          query.bindValue(":dateres", dateres);


    return  query.exec();
}
bool Reservation::supprimer(QString numres)
{
    QSqlQuery query;
    QString R=numres;
          query.prepare("Delete from reservation where numres=:numres");
          query.bindValue(":numres", numres);
         return  query.exec();

}
bool Reservation::modifier(QString numres,QString nom,QString prenom,QString dateres,QString typeres,QString nbtable,QString nbchaise)
 {
     QSqlQuery query;
     query.prepare("UPDATE RESERVATION SET numres:=numres, nom:=nom, prenom:=prenom, dateres:=dateres, typeres:=typeres, nbtable:=nbtable, nbtable:=nbtable");
     query.bindValue(":numres", numres);
     query.bindValue(":nom", nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":dateres",dateres);
     query.bindValue(":typeres", typeres);
     query.bindValue(":nbtable", nbtable);
     query.bindValue(":nbchaise", nbchaise);

     return query.exec();
 }

QSqlQueryModel* Reservation::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM RESERVATION");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("numres"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("dateres"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("typeres"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbtable"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("nbchaise"));


return model;
}


