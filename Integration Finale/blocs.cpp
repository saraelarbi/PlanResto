#include "blocs.h"

#include "blocs.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Blocs::Blocs()
{

}

Blocs::Blocs(QString Idblocs,QString numb,QString etat)
{this->Idblocs=Idblocs; this->numb=numb; this->etat=etat;}
QString Blocs:: getIdblocs(){return Idblocs;}
QString Blocs:: getnumb(){return numb;}
QString Blocs:: getetat(){return etat;}
void Blocs:: setIdblocs(QString Idblocs){this->Idblocs=Idblocs;}
void Blocs:: setnumb(QString numb){this->numb=numb;}
void Blocs::setetat(QString etat){this->etat=etat;}
bool Blocs::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO BLOCS(Idblocs,numb,etat) "
                        "VALUES (:Idblocs ,:numb ,:etat )");
          query.bindValue(":Idblocs", Idblocs);
          query.bindValue(":numb", numb);
          query.bindValue(":etat", etat);

    return  query.exec();
}
bool Blocs::supprimer(QString Idblocs)
{
    QSqlQuery query;

          query.prepare("Delete from BLOCS where Idblocs=:Idblocs");
          query.bindValue(":Idblocs", Idblocs);
         return  query.exec();

}
QSqlQueryModel* Blocs::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM BLOCS");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("numb"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));

return model;
}

bool Blocs::modifier(QString Idblocs,QString numb,QString etat)
 {
     QSqlQuery query;
     query.prepare("UPDATE BLOCS SET Idblocs:=Idblocs, numb:=numb, etat:=etat");
     query.bindValue(":Idblocs", Idblocs);
     query.bindValue(":numb", numb);
     query.bindValue(":etat", etat);
     return query.exec();
 }
QSqlQueryModel* Blocs::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from blocs where ((idblocs || numb || etat ) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idblocs"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("numb"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));

    return model;
}
