#include "abonnement.h"
#include<QSqlQuery>
#include<QtDebug>
#include <QObject>
Abonnement::Abonnement()
{
    id=0;
    date_deb=date_deb.currentDate();
    date_fin=date_fin.currentDate();
}
Abonnement::Abonnement(int id,QDate date_deb,QDate date_fin)
{
    this->id=id; this->date_deb=date_deb; this->date_fin=date_fin;
}
int Abonnement::getid() {return id;}
QDate Abonnement::getdate_deb(){return date_deb;}
QDate Abonnement::getdate_fin(){return date_fin;}
void Abonnement::setid(int id){this->id=id;}
void Abonnement::setdate_deb(QDate date_deb){this->date_deb=date_deb;}
void Abonnement::setdate_fin(QDate date_fin){this->date_fin=date_fin;}

bool Abonnement::ajouter()
{ bool test=false;
    QSqlQuery query;
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO abonnement (id, date_deb, date_fin) "
                        "VALUES (:id, :date_deb, :date_fin)");
          query.bindValue(0, id_string);
          query.bindValue(1, date_deb);
          query.bindValue(2, date_fin);

        return query.exec();



    return test;

}
bool  Abonnement::supprimer(int id)
{  QSqlQuery query;
    query.prepare("delete from abonnement where id=:id");
  query.bindValue(0, id);
return query.exec();


}
QSqlQueryModel* Abonnement::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM abonnement");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date_deb"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_fin"));

  return model;
}


bool Abonnement::update(int id, QDate date_deb,QDate date_fin)
{
    QSqlQuery query;
    query.prepare("UPDATE abonnement SET id= :id,date_deb= :date_deb,date_fin=:date_fin WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":date_deb",date_deb );
    query.bindValue(":date_fin", date_fin);


    return    query.exec();
}
