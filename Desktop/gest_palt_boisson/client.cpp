#include "client.h"


client::client(int CIN,QString nom,QString prenom,int age)
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
    this->age=age;
}
bool client::ajouter()
{
QSqlQuery query;
QString res= QString::number(CIN);
QString res1= QString::number(age);
query.prepare("INSERT INTO CLIENT (CIN, PRENOM, AGE, NOM) "
                    "VALUES (:CIN, :prenom, :age, :nom)");
query.bindValue(":CIN", res);
query.bindValue(":prenom", prenom);
query.bindValue(":age", res1);
query.bindValue(":nom", nom);
return    query.exec();
}


QSqlQueryModel * client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CLIENT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
    return model;
}
