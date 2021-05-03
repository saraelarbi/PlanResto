#include "fonction.h"


fonction::fonction()
{

}
fonction::fonction(QString typefonction,QString salaire,QString jourdetravail,QString heurededebut,QString heuredefin,QDate debutdeconge,QDate findeconge)
{
    this->typefonction=typefonction;
    this->salaire=salaire;
    this->jourdetravail=jourdetravail;
    this->heurededebut=heurededebut;
    this->heuredefin=heuredefin;
    this->debutdeconge=debutdeconge;
    this->findeconge=findeconge;
}

QString fonction::gettypefonction(){ return typefonction;}
QString fonction::getsalaire(){ return salaire;}
QString fonction::getjourdetravail(){ return jourdetravail;}
QString fonction::getheurededebut(){ return heurededebut;}
QString fonction::getheuredefin(){ return heuredefin;}
QDate fonction::getdebutdeconge(){ return debutdeconge;}
QDate fonction::getfindeconge(){ return findeconge;}


void fonction::settypefonction(QString typefonction){ this->typefonction=typefonction;}
void fonction::setsalaire(QString salaire){ this->salaire=salaire;}
void fonction::setjourdetravail(QString jourdetravail){ this->jourdetravail=jourdetravail;}
void fonction::setheurededebut(QString heurededebut){ this->heurededebut=heurededebut;}
void fonction::setheuredefin(QString heuredefin){ this->heuredefin=heuredefin;}
void fonction::setdebutdeconge(QDate debutdeconge){ this->debutdeconge=debutdeconge;}
void fonction::setfindeconge(QDate findeconge){ this->findeconge=findeconge;}


bool fonction::ajouter()
{

    QSqlQuery query;

          query.prepare("INSERT INTO FC (typefonction, salaire, jourdetravail, heurededebut, heuredefin, debutdeconge, findeconge) "
                        "VALUES (:typefonction, :salaire, :jourdetravail, :heurededebut, :heuredefin, :debutdeconge, :findeconge)");
          query.bindValue(":typefonction",typefonction);
          query.bindValue(":salaire", salaire);
          query.bindValue(":jourdetravail", jourdetravail);
          query.bindValue(":heurededebut", heurededebut);
          query.bindValue(":heuredefin", heuredefin);
          query.bindValue(":debutdeconge", debutdeconge);
          query.bindValue(":findeconge", findeconge);



    return query.exec();
}


bool fonction::supprimer(QString typefonction)
{
    QSqlQuery query;
    QString res = typefonction;
    query.prepare("Delete from FC where typefonction= :typefonction");
    query.bindValue(":typefonction",res);
    return query.exec();
}

 QSqlQueryModel * fonction::afficher()
 {
     QSqlQueryModel * Model= new QSqlQueryModel;
     Model -> setQuery("select * from FC");
     Model -> setHeaderData(0,Qt::Horizontal,QObject::tr("typefonction"));
     Model -> setHeaderData(1,Qt::Horizontal,QObject::tr("salaire"));
     Model -> setHeaderData(2,Qt::Horizontal,QObject::tr("jourdetravail"));
     Model -> setHeaderData(3,Qt::Horizontal,QObject::tr("heurededebut"));
     Model -> setHeaderData(4,Qt::Horizontal,QObject::tr("heuredefin"));
     Model -> setHeaderData(5,Qt::Horizontal,QObject::tr("debutdeconge"));
     Model -> setHeaderData(6,Qt::Horizontal,QObject::tr("findeconge"));
     return Model;

 }

 bool fonction::modifier(QString typefonction,QString salaire,QString jourdetravail,QString heurededebut,QString heuredefin,QDate debutdeconge,QDate findeconge)
 {
     QSqlQuery query;
     query.prepare("UPDATE FC SET typefonction:=typefonction, salaire:=salaire, jourdetravail:=jourdetravail, heurededebut:=heurededebut, heuredefin:=heuredefin, debutdeconge:=debutdeconge, findeconge:=findeconge");
     query.bindValue(":typefonction",typefonction);
     query.bindValue(":salaire",salaire);
     query.bindValue(":jourdetravail",jourdetravail);
     query.bindValue(":heurededebut",heurededebut);
     query.bindValue(":heuredefin",heuredefin);
     query.bindValue(":debutdeconge",debutdeconge);
     query.bindValue(":findeconge",findeconge);
     return query.exec();
 }


 QSqlQueryModel * fonction::rechercher_salaire(QString salaire)
 {
     QSqlQuery qry;
     qry.prepare("select * from FC where salaire=:salaire");
     qry.bindValue(":salaire",salaire);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * fonction::rechercher_jourdetravail(QString jourdetravail)
 {
     QSqlQuery qry;
     qry.prepare("select * from FC where jourdetravail=:jourdetravail");
     qry.bindValue(":jourdetravail",jourdetravail);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }

 QSqlQueryModel * fonction::rechercher_findeconge(QDate findeconge)
 {
     QSqlQuery qry;
     qry.prepare("select * from FC where findeconge=:findeconge");
     qry.bindValue(":findeconge",findeconge);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * fonction::rechercher_salaire_jourdetravail(QString salaire,QString jourdetravail)
 {
     QSqlQuery qry;
     qry.prepare("select * from FC where salaire=:salaire and jourdetravail=:jourdetravail ");
     qry.bindValue(":salaire",salaire);
     qry.bindValue(":jourdetravail",jourdetravail);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * fonction::rechercher_salaire_findeconge(QString salaire,QDate findeconge)
 {
     QSqlQuery qry;
     qry.prepare("select * from FC where salaire=:salaire and findeconge=:findeconge ");
     qry.bindValue(":salaire",salaire);
     qry.bindValue(":findeconge",findeconge);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }
 QSqlQueryModel * fonction::rechercher_jourdetravail_findeconge(QString jourdetravail,QDate findeconge)
 {
     QSqlQuery qry;
     qry.prepare("select * from FC where jourdetravail=:jourdetravail and findeconge=:findeconge ");
     qry.bindValue(":jourdetravail",jourdetravail);
     qry.bindValue(":findeconge",findeconge);
     qry.exec();

     QSqlQueryModel *model= new QSqlQueryModel;
     model->setQuery(qry);


    return model;


 }





QSqlQueryModel * fonction::rechercher_tous(QString salaire,QString jourdetravail,QDate findeconge)
{
    QSqlQuery *qry= new QSqlQuery();
    qry->prepare("select * from FC where salaire=:salaire and jourdetravail=:jourdetravail and findeconge=:findeconge");
    qry->bindValue(":salaire",salaire);
    qry->bindValue(":jourdetravail",jourdetravail);
    qry->bindValue(":findeconge",findeconge);
    qry->exec();

       QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery(*qry);
        return model;

}

