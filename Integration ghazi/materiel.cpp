#include "materiel.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Materiel::Materiel()
{

}

Materiel::Materiel(QString id,QString nom,QString type,QString marque,QString prix,QString cinf)
{this->id=id; this->nom=nom; this->type=type; this->marque=marque; this->prix=prix; this->cinf=cinf;}
QString Materiel:: getid(){return id;}
QString Materiel:: getnom(){return nom;}
QString Materiel:: gettype(){return type;}
QString Materiel:: getmarque(){return marque;}
QString Materiel:: getprix(){return prix;}
QString Materiel:: getcinf(){return cinf;}
void Materiel:: setid(QString id){this->id=id;}
void Materiel::setnom(QString nom){this->nom=nom;}
void Materiel:: settype(QString type){this->type=type;}
void Materiel:: setmarque(QString marque){this->marque=marque;}
void Materiel:: setprix(QString prix){this->prix=prix;}
void Materiel:: setcinf(QString cinf){this->cinf=cinf;}
bool Materiel::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO MATERIEL (id, type, nom, marque, prix, cinf) "
                        "VALUES (:id,:type ,:nom ,:marque ,:prix ,:cinf)");
          query.bindValue(":id", id);
          query.bindValue(":type", type);
          query.bindValue(":nom", nom);
          query.bindValue(":marque", marque);
          query.bindValue(":prix", prix);
          query.bindValue(":cinf", cinf);




    return  query.exec();
}
bool Materiel::supprimer(QString id)
{
    QSqlQuery query;
    QString C=id;
            query.prepare("Delete from materiel where id=:id");
          query.bindValue(":id", C);
         return  query.exec();

}
QSqlQueryModel* Materiel::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM MATERIEL");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("marque"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("cinf"));




return model;
}

bool Materiel::modifier(QString id,QString nom,QString type,QString marque ,QString prix,QString cinf)
 {
     QSqlQuery query;

     query.prepare("UPDATE MATERIEL SET id:=id, nom:=nom, type:=type, marque:=marque, prix:=prix, cinf:=cinf");
     query.bindValue(":id",id);
     query.bindValue(":nom",nom);
     query.bindValue(":type",type);
     query.bindValue(":marque",marque);
     query.bindValue(":prix",prix);
     query.bindValue(":cinf",cinf);

     return query.exec();
}

QSqlQueryModel * Materiel::rechercher_nom(QString nom)
 {
     QSqlQuery qry;
     qry.prepare("select * from MATERIEL where nom=:nom");
     qry.bindValue(":nom",nom);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * Materiel::rechercher_type(QString type)
 {
     QSqlQuery qry;
     qry.prepare("select * from MATERIEL where type=:type");
     qry.bindValue(":type",type);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * Materiel::rechercher_marque(QString marque)
 {
     QSqlQuery qry;
     qry.prepare("select * from MATERIEL where marque=:marque");
     qry.bindValue(":marque",marque);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Materiel::rechercher_nom_type(QString nom,QString type)
 {
     QSqlQuery qry;
     qry.prepare("select * from MATERIEL where nom=:nom and type=:type ");
     qry.bindValue(":nom",nom);
     qry.bindValue(":type",type);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Materiel::rechercher_nom_marque(QString nom,QString marque)
 {
     QSqlQuery qry;
     qry.prepare("select * from MATERIEL where nom=:nom and marque=:marque ");
     qry.bindValue(":nom",nom);
     qry.bindValue(":marque",marque);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Materiel::rechercher_type_marque(QString type,QString marque)
 {
     QSqlQuery qry;
     qry.prepare("select * from MATERIEL where type=:type and marque=:marque ");
     qry.bindValue(":type",type);
     qry.bindValue(":marque",marque);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }





QSqlQueryModel * Materiel::rechercher_tous(QString nom,QString type,QString marque)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("select * from MATERIEL where nom=:nom and type=:type and marque=:marque");
    qry->bindValue(":nom",nom);
    qry->bindValue(":type",type);
    qry->bindValue(":marque",marque);
    qry->exec();

       QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery(*qry);
        return model;

}

