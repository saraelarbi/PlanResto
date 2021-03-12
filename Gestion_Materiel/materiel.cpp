#include "materiel.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Materiel::Materiel()
{

}

Materiel::Materiel(QString id,QString nom,QString type,QString marque,float prix)
{this->id=id; this->nom=nom; this->type=type; this->marque=marque; this->prix=prix;}
QString Materiel:: getid(){return id;}
QString Materiel:: getnom(){return nom;}
QString Materiel:: gettype(){return type;}
QString Materiel:: getmarque(){return marque;}
float Materiel:: getprix(){return prix;}
void Materiel:: setid(QString id){this->id=id;}
void Materiel::setnom(QString nom){this->nom=nom;}
void Materiel:: settype(QString type){this->type=type;}
void Materiel:: setmarque(QString marque){this->marque=marque;}
void Materiel:: setprix(float prix){this->prix=prix;}
bool Materiel::ajouter()
{

    QSqlQuery query;
    QString prix_string= QString::number(prix);
          query.prepare("INSERT INTO materiel (id, type, nom, marque, prix) "
                        "VALUES (:id,:type ,:nom ,:marque ,:prix)");
          query.bindValue(":id", id);
          query.bindValue(":type", type);
          query.bindValue(":nom", nom);
          query.bindValue(":marque", marque);
          query.bindValue(":prix", prix_string);



    return  query.exec();
}
bool Materiel::supprimer(QString id)
{
    QSqlQuery query;

          query.prepare("Delete from materiel where id=:id");
          query.bindValue(":id", id);
         return  query.exec();

}
QSqlQueryModel* Materiel::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM materiel");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("marque"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));




return model;
}





