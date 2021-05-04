#include "client.h"
#include <QDebug>
#include "connexion.h"

client::client()
{


}
client::client(QString id,QString nom,QString prenom,QString adresse,QString tel,QString email)
{
  this->id=id;
  this->nom=nom;
  this->prenom=prenom;
  this->adresse=adresse;
  this->tel=tel;
  this->email=email;


}
QString client::get_id(){return  id;}
QString client::get_nom(){return nom;}
QString client::get_prenom(){return prenom;}
QString client::get_adresse(){return  adresse;}
QString client::get_tel(){return tel;}
QString client::get_email(){return email;}

void client::setid(QString id){ this->id=id;}
void client::setnom(QString nom){ this->nom=nom;}
void client::setprenom(QString prenom){ this->prenom=prenom;}
void client::setadresse(QString adresse){ this->prenom=adresse;}
void client::settel(QString tel){ this->tel=tel;}
void client::setemail(QString email){ this->email=email;}

bool client::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO client (ID, NOM, PRENOM, ADRESSE, TEL, EMAIL) "
                    "VALUES (:id, :nom, :prenom, :adresse, :tel, :email)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":adresse", adresse);
query.bindValue(":tel", tel);
query.bindValue(":email", email);

return    query.exec();
}


QSqlQueryModel * client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from client");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

    return model;
}


bool client::supprimer(QString id)
{
QSqlQuery query;

query.prepare("Delete from client where id = :id");
query.bindValue(":id", id);
return    query.exec();
}


bool client::modifier(QString id,QString nom ,QString prenom ,QString adresse ,QString tel ,QString email)
{
    QSqlQuery query;
    query.prepare("UPDATE client SET id:=id, nom:=nom, prenom:=prenom, adresse:=adresse, tel:=tel, email:=email");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":tel",tel);
    query.bindValue(":email",email);
    return query.exec();
    }

QSqlQueryModel *client::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from client where nom LIKE '"+rech+"%' or prenom LIKE '"+rech+"%'");
    return model;
}

QSqlQueryModel * client::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from client ORDER BY nom ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));


        return model;
}


