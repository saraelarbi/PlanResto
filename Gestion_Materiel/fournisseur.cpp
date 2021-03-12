#include "fournisseur.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Fournisseur::Fournisseur()
{

}

Fournisseur::Fournisseur(int cinf,QString nom,QString prenom,QString type,int tel,QString email,QString adresse)
{this->cinf=cinf; this->tel=tel; this->nom=nom; this->prenom=prenom;this->type=type; this->email=email; this->adresse=adresse;}
int Fournisseur:: getcinf(){return cinf;}
int Fournisseur:: gettel(){return tel;}
QString Fournisseur:: getnom(){return nom;}
QString Fournisseur:: gettype(){return type;}
QString Fournisseur:: getprenom(){return prenom;}
QString Fournisseur:: getemail(){return email;}
void Fournisseur:: setcinf(int cinf){this->cinf=cinf;}
void Fournisseur:: settel(int tel){this->tel=tel;}
void Fournisseur::setnom(QString nom){this->nom=nom;}
void Fournisseur:: settype(QString type){this->type=type;}
void Fournisseur:: setprenom(QString prenom){this->prenom=prenom;}
void Fournisseur:: setadresse(QString adresse){this->adresse=adresse;}
void Fournisseur:: setemail(QString email){this->email=email;}

bool Fournisseur::ajouter()
{

    QSqlQuery query;
    QString cinf_string= QString::number(cinf);
     QString tel_string= QString::number(tel);
          query.prepare("INSERT INTO fournisseur(cinf,  nom,prenom,type,tel,adresse, email) "
                        "VALUES (:cinf ,:nom ,:prenom ,:type ,:tel,:adresse ,:email)");
          query.bindValue(":cinf", cinf_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":type", type);
          query.bindValue(":tel", tel_string);
          query.bindValue(":email", email);
          query.bindValue(":adresse", adresse);



    return  query.exec();
}
bool Fournisseur::supprimer(int cinf)
{
    QSqlQuery query;

          query.prepare("Delete from fournisseur where id=:id");
          query.bindValue(":cinf", cinf);
         return  query.exec();

}
QSqlQueryModel* Fournisseur::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM fournisseur");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));





return model;
}
