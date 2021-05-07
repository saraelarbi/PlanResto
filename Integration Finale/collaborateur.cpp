#include "collaborateur.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Collaborateur::Collaborateur()
{

}

Collaborateur::Collaborateur(QString idcollaborateur,QString nom,QString prenom,QString telephone,QString adresse,QString email)
{this->idcollaborateur=idcollaborateur; this->nom=nom; this->prenom=prenom; this->telephone=telephone; this->adresse=adresse; this->email=email;}
QString Collaborateur:: getid(){return idcollaborateur;}
QString Collaborateur:: getnom(){return nom;}
QString Collaborateur:: getprenom(){return prenom;}
QString Collaborateur:: gettelephone(){return telephone;}
QString Collaborateur:: getadresse(){return adresse;}
QString Collaborateur:: getemail(){return email;}
void Collaborateur:: setid(QString idcollaborateur){this->idcollaborateur=idcollaborateur;}
void Collaborateur::setnom(QString nom){this->nom=nom;}
void Collaborateur:: setprenom(QString prenom){this->prenom=prenom;}
void Collaborateur:: settelephone(QString telephone){this->telephone=telephone;}
void Collaborateur:: setadresse(QString adresse){this->adresse=adresse;}
void Collaborateur:: setemail(QString email){this->email=email;}

bool Collaborateur::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO collaborateur (idcollaborateur, nom, prenom, telephone, adresse, email) "
                        "VALUES (:idcollaborateur ,:nom ,:prenom ,:telephone ,:adresse ,:email)");
          query.bindValue(":idcollaborateur", idcollaborateur);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":telephone", telephone);
          query.bindValue(":adresse", adresse);
          query.bindValue(":email", email);




    return  query.exec();
}

QSqlQueryModel* Collaborateur::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM COLLABORATEUR");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("telephone"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));

return model;
}


bool Collaborateur::supprimer(QString idcollaborateur)
{
    QSqlQuery query;

          query.prepare("Delete from collaborateur where idcollaborateur=:idcollaborateur");
          query.bindValue(":idcollaborateur", idcollaborateur);
          return  query.exec();

}

bool Collaborateur::modifier(QString idcollaborateur,QString nom,QString prenom,QString telephone,QString adresse,QString email)
 {
     QSqlQuery query;
     query.prepare("UPDATE collaborateur SET idcollaborateur:=idcollaborateur, nom:=nom, prenom:=prenom, telephone:=telephone, adresse:=adresse, email:=email");
     query.bindValue(":idcollaborateur", idcollaborateur);
     query.bindValue(":nom", nom);
     query.bindValue(":prenom", prenom);
     query.bindValue(":telephone", telephone);
     query.bindValue(":adresse", adresse);
     query.bindValue(":email", email);
     return query.exec();
 }
histoS::histoS()
{
nom="";
datee="";
fn="";
}
histoS::histoS(QString nom,QString datee,QString fn)
{
    this->nom=nom;
    this->datee=datee;
    this->fn=fn ;
}
QString histoS::get_datee(){return  datee;}
QString histoS::get_fn(){return  fn;}
QString histoS::get_nom(){return  nom;}
bool histoS::ajoutehis()
{
    QSqlQuery query;
    query.prepare("INSERT INTO histsalma (NOM, DATEE, FN) "
                  "VALUES (:nom, :datee, :fn)");
    query.bindValue(":nom", nom);
    query.bindValue(":datee", datee);
    query.bindValue(":fn", fn);
    return    query.exec();
}
bool histoS::modifierhis()
{
    QSqlQuery query;
    query.prepare("UPDATE histsalma SET datee='"+datee+"',fn='"+fn+"' where nom='"+nom+"'  ;");
    query.bindValue(":nom",nom);
    query.bindValue(":datee", datee);
    query.bindValue(":fn", fn);
    return    query.exec();
}
QSqlQueryModel * histoS::afficherhis()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from histsalma");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("fonction "));
        return model;

}


