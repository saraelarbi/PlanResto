#include "fournisseur.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Fournisseur::Fournisseur()
{

}

Fournisseur::Fournisseur(QString cinf,QString nom,QString prenom,QString type,QString tel,QString email,QString adresse)
{this->cinf=cinf; this->tel=tel; this->nom=nom; this->prenom=prenom;this->type=type; this->email=email; this->adresse=adresse;}
QString Fournisseur:: getcinf(){return cinf;}
QString Fournisseur:: gettel(){return tel;}
QString Fournisseur:: getnom(){return nom;}
QString Fournisseur:: gettype(){return type;}
QString Fournisseur:: getprenom(){return prenom;}
QString Fournisseur:: getemail(){return email;}
void Fournisseur:: setcinf(QString cinf){this->cinf=cinf;}
void Fournisseur:: settel(QString tel){this->tel=tel;}
void Fournisseur::setnom(QString nom){this->nom=nom;}
void Fournisseur:: settype(QString type){this->type=type;}
void Fournisseur:: setprenom(QString prenom){this->prenom=prenom;}
void Fournisseur:: setadresse(QString adresse){this->adresse=adresse;}
void Fournisseur:: setemail(QString email){this->email=email;}

bool Fournisseur::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO FOURNISSEUR(cinf,nom,prenom,type,tel,adresse,email) "
                        "VALUES (:cinf ,:nom ,:prenom ,:type ,:tel,:email,:adresse)");
          query.bindValue(":cinf", cinf);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":type", type);
          query.bindValue(":tel", tel);
          query.bindValue(":email", email);
          query.bindValue(":adresse", adresse);



    return  query.exec();
}
bool Fournisseur::supprimer(QString cinf)
{

    QSqlQuery query;

          query.prepare("Delete from  FOURNISSEUR where cinf=:cinf");
          query.bindValue(":cinf", cinf);
         return  query.exec();

}
QSqlQueryModel* Fournisseur::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM FOURNISSEUR");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));





return model;
}

bool Fournisseur::modifier(QString,QString,QString,QString,QString,QString,QString)
 {
     QSqlQuery query;

     query.prepare("UPDATE FOURNISSEUR SET cinf:=cinf, nom:=nom, prenom:=prenom, type:=type, tel:=tel, email:=email,adresse:=adresse");
     query.bindValue(":cinf",cinf);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":type",type);
     query.bindValue(":tel",tel);
     query.bindValue(":email",email);
     query.bindValue(":adresse",adresse);

     return query.exec();
}






QSqlQueryModel* Fournisseur::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from FOURNISSEUR where ((cinf || nom || prenom || type || tel || email || adresse) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cinf"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));
    return model;
}






