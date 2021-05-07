#include "produit.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Produit::Produit()
{

}

Produit::Produit(QString id,QString nom,QString type,QString marque,QString prix)
{this->id=id; this->nom=nom; this->type=type; this->marque=marque; this->prix=prix;}
QString Produit:: getid(){return id;}
QString Produit:: getnom(){return nom;}
QString Produit:: gettype(){return type;}
QString Produit:: getmarque(){return marque;}
QString Produit:: getprix(){return prix;}
void Produit:: setid(QString id){this->id=id;}
void Produit::setnom(QString nom){this->nom=nom;}
void Produit:: settype(QString type){this->type=type;}
void Produit:: setmarque(QString marque){this->marque=marque;}
void Produit:: setprix(QString prix){this->prix=prix;}
bool Produit::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO produit (id, type, nom, marque, prix) "
                        "VALUES (:id,:type ,:nom ,:marque ,:prix)");
          query.bindValue(":id", id);
          query.bindValue(":type", type);
          query.bindValue(":nom", nom);
          query.bindValue(":marque", marque);
          query.bindValue(":prix", prix);



    return  query.exec();
}
bool Produit::supprimer(QString id)
{
    QSqlQuery query;

          query.prepare("Delete from produit where id=:id");
          query.bindValue(":id", id);
         return  query.exec();

}
QSqlQueryModel* Produit::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM produit");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("marque"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));




return model;
}

bool Produit::modifier(QString id, QString  type, QString nom, QString marque , QString prix)
 {
     QSqlQuery query;

     query.prepare("UPDATE produit SET id:=id, nom:=nom,  type:=type, marque:=marque, prix:=prix");
     query.bindValue(":id", id);
     query.bindValue(":nom", nom);
     query.bindValue(":type", type);
     query.bindValue(":marque", marque);
     query.bindValue(":prix", prix);
     return query.exec();
 }
QSqlQueryModel * Produit::rechercher_nom(QString nom)
 {
     QSqlQuery qry;
     qry.prepare("select * from PRODUIT where nom=:nom");
     qry.bindValue(":nom",nom);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * Produit::rechercher_type(QString type)
 {
     QSqlQuery qry;
     qry.prepare("select * from PRODUIT where type=:type");
     qry.bindValue(":type",type);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * Produit::rechercher_marque(QString marque)
 {
     QSqlQuery qry;
     qry.prepare("select * from PRODUIT where marque=:marque");
     qry.bindValue(":marque",marque);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Produit::rechercher_nom_type(QString nom,QString type)
 {
     QSqlQuery qry;
     qry.prepare("select * from PRODUIT where nom=:nom and type=:type ");
     qry.bindValue(":nom",nom);
     qry.bindValue(":type",type);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Produit::rechercher_nom_marque(QString nom,QString marque)
 {
     QSqlQuery qry;
     qry.prepare("select * from PRODUIT where nom=:nom and marque=:marque ");
     qry.bindValue(":nom",nom);
     qry.bindValue(":marque",marque);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Produit::rechercher_type_marque(QString type,QString marque)
 {
     QSqlQuery qry;
     qry.prepare("select * from PRODUIT where type=:type and marque=:marque ");
     qry.bindValue(":type",type);
     qry.bindValue(":marque",marque);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }





QSqlQueryModel * Produit::rechercher_tous(QString nom,QString type,QString marque)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("select * from PRODUIT where nom=:nom and type=:type and marque=:marque");
    qry->bindValue(":nom",nom);
    qry->bindValue(":type",type);
    qry->bindValue(":marque",marque);
    qry->exec();

       QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery(*qry);
        return model;

}
projeth::projeth()
{
nom="";
datee="";
fn="";
}
projeth::projeth(QString nom,QString datee,QString fn)
{
    this->nom=nom;
    this->datee=datee;
    this->fn=fn ;
}
QString projeth::get_datee(){return  datee;}
QString projeth::get_fn(){return  fn;}
QString projeth::get_nom(){return  nom;}
bool projeth::ajoutehis()
{
    QSqlQuery query;
    query.prepare("INSERT INTO HISTAHER (NOM, DATEE, FN) "
                  "VALUES (:nom, :datee, :fn)");
    query.bindValue(":nom", nom);
    query.bindValue(":datee", datee);
    query.bindValue(":fn", fn);
    return    query.exec();
}
bool projeth::modifierhis()
{
    QSqlQuery query;
    query.prepare("UPDATE HISTAHER SET datee='"+datee+"',fn='"+fn+"' where nom='"+nom+"'  ;");
    query.bindValue(":nom",nom);
    query.bindValue(":datee", datee);
    query.bindValue(":fn", fn);
    return    query.exec();
}
QSqlQueryModel * projeth::afficherhis()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from HISTAHER");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FONCTION "));
        return model;

}
