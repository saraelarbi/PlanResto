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
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("adresse"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("email"));

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
QSqlQueryModel * Collaborateur::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from collaborateur ORDER BY nom ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));


        return model;
}
/*QSqlQueryModel * Collaborateur::rechercher_nom(QString nom)
 {
     QSqlQuery qry;
     qry.prepare("select * from COLLABORATEUR where nom=:nom");
     qry.bindValue(":nom",nom);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * Collaborateur::rechercher_prenom(QString type)
 {
     QSqlQuery qry;
     qry.prepare("select * from COLLABORATEUR where type=:type");
     qry.bindValue(":prenom",prenom);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * Collaborateur::rechercher_telephone(QString telephone)
 {
     QSqlQuery qry;
     qry.prepare("select * from COLLABORATEUR where telephone=:telephone");
     qry.bindValue(":telephone",telephone);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Collaborateur::rechercher_nom_prenom(QString nom,QString prenom)
 {
     QSqlQuery qry;
     qry.prepare("select * from COLLABORATEUR where nom=:nom and prenom=:prenom ");
     qry.bindValue(":nom",nom);
     qry.bindValue(":prenom",prenom);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Collaborateur::rechercher_nom_telephone(QString nom,QString telephone)
 {
     QSqlQuery qry;
     qry.prepare("select * from COLLABORATEUR where nom=:nom and telephone=:telephone ");
     qry.bindValue(":nom",nom);
     qry.bindValue(":telephone",telephone);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * Collaborateur::rechercher_prenom_telephone(QString prenom,QString telephone)
 {
     QSqlQuery qry;
     qry.prepare("select * from COLLABORATEUR where prenom=:prenom and telephone=:telephone ");
     qry.bindValue(":prenom",prenom);
     qry.bindValue(":telephone",telephone);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }





QSqlQueryModel * Collaborateur::rechercher_tous(QString nom,QString prenom,QString telephone)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("select * from COLLABORATEUR where nom=:nom and prenom=:prenom and telephone=:telephone");
    qry->bindValue(":nom",nom);
    qry->bindValue(":prenom",prenom);
    qry->bindValue(":telephone",telephone);
    qry->exec();

       QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery(*qry);
        return model;

}

*/
