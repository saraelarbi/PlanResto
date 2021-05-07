

#include "contrat.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Contrat::Contrat()
{

}

Contrat:: Contrat(QString type,QString nom,QString duree,QString tarif,QString idcollaborateur)
{this->type=type; this->nom=nom; this->duree=duree;this->tarif=tarif;this->idcollaborateur=idcollaborateur;}
QString Contrat:: gettarif(){return tarif;}
QString Contrat:: getnom(){return nom;}
QString Contrat:: gettype(){return type;}
QString Contrat:: getduree(){return duree;}
QString Contrat:: getidcollaborateur(){return idcollaborateur;}
void Contrat:: settarif(QString tarif){this->tarif=tarif;}
void Contrat::setnom(QString nom){this->nom=nom;}
void Contrat:: settype(QString type){this->type=type;}
void Contrat:: setduree(QString duree){this->duree=duree;}
void Contrat:: setidcollaborateur(QString idcollaborateur){this->idcollaborateur=idcollaborateur;}


bool Contrat::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO contrat(type,nom,duree,tarif,idcollaborateur) "
                        "VALUES (:type ,:nom ,:duree ,:tarif,:idcollaborateur)");
          query.bindValue(":tarif", tarif);
          query.bindValue(":nom", nom);
          query.bindValue(":duree", duree);
          query.bindValue(":type", type);
          query.bindValue(":idcollaborateur", idcollaborateur);

    return  query.exec();
}
bool Contrat::supprimer(QString type)
{
    QSqlQuery query;
    QString C=type;
          query.prepare("Delete from contrat where type=:type");
          query.bindValue(":type", type);
         return  query.exec();

}
bool Contrat::modifier(QString type,QString nom,QString duree,QString tarif,QString idcollaborateur)
 {
     QSqlQuery query;
     query.prepare("UPDATE CONTRAT SET type:=type, nom:=nom, duree:=duree, tarif:=tarif, idcollaborateur:=idcollaborateur");
     query.bindValue(":type", type);
     query.bindValue(":nom", nom);
     query.bindValue(":duree",duree);
     query.bindValue(":tarif",tarif);
     query.bindValue(":idcollaborateur", idcollaborateur);
     return query.exec();
 }
QSqlQueryModel* Contrat::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM CONTRAT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("tarif"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("idcollaborateur"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));

return model;
}



QSqlQueryModel * Contrat::rechercher_nom(QString nom)
 {
     QSqlQuery qry;
     qry.prepare("select * from contrat where nom=:nom");
     qry.bindValue(":nom",nom);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * Contrat::rechercher_type(QString type)
 {
     QSqlQuery qry;
     qry.prepare("select * from contrat where type=:type");
     qry.bindValue(":type",type);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * Contrat::rechercher_tarif(QString tarif)
 {
     QSqlQuery qry;
     qry.prepare("select * from contrat where tarif=:tarif");
     qry.bindValue(":tarif",tarif);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Contrat::rechercher_nom_type(QString nom,QString type)
 {
     QSqlQuery qry;
     qry.prepare("select * from contrat where nom=:nom and type=:type ");
     qry.bindValue(":nom",nom);
     qry.bindValue(":type",type);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Contrat::rechercher_nom_tarif(QString nom,QString tarif)
 {
     QSqlQuery qry;
     qry.prepare("select * from contrat where nom=:nom and tarif=:tarif ");
     qry.bindValue(":nom",nom);
     qry.bindValue(":tarif",tarif);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Contrat::rechercher_type_tarif(QString type,QString tarif)
 {
     QSqlQuery qry;
     qry.prepare("select * from contrat where type=:type and tarif=:tarif ");
     qry.bindValue(":type",type);
     qry.bindValue(":tarif",tarif);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }


QSqlQueryModel * Contrat::rechercher_tous(QString nom,QString type,QString tarif)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("select * from contrat where nom=:nom and type=:type and tarif=:tarif");
    qry->bindValue(":nom",nom);
    qry->bindValue(":type",type);
    qry->bindValue(":tarif",tarif);
    qry->exec();

       QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery(*qry);
        return model;

}


