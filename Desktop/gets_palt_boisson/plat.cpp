#include "plat.h"
#include <QSqlQuery>
#include "QDebug"


Plat::Plat()
{

}


Plat::Plat(int Id,int prix,QString nom,QString type,QString ingredients)
{
    this->Id=Id;
    this->prix=prix;
    this->nom=nom;
    this->type=type;
    this->ingredients=ingredients;
}
int Plat::getId(){return Id;}
int Plat::getprix(){return prix;}
QString Plat::getnom(){return nom;}
QString Plat::gettype(){return type;}
QString Plat::getingredients(){return ingredients;}

void Plat::setId(int Id){this->Id=Id;}
void Plat::setprix(int prix){this->prix=prix;}
void Plat::setnom(QString nom){this->nom=nom;}
void Plat::settype(QString type){this->type=type;}
void Plat::setingredients(QString ingredients){this->ingredients=ingredients;}

bool Plat::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(Id);
    QString res1= QString::number(prix);
    query.prepare("INSERT INTO PLAT (ID, PRIX, NOM, TYPE, INGREDIENTS) "
                        "VALUES (:Id, :prix, :nom, :type, :ingredients)");
    query.bindValue(":Id", res);
    query.bindValue(":prix", res1);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":ingredients", ingredients);
    return    query.exec();

}
QSqlQueryModel * Plat::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PLAT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ingredients"));
    return model;
}

bool Plat::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from PLAT where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Plat::modifier(int id)
{
    QSqlQuery Q;
    QString res= QString::number(id);
    QString resP= QString::number(prix);
    Q.prepare("UPDATE  PLAT SET PRIX=:prix,NOM=:nom,TYPE=:type , INGREDIENTS=:ingredients where ID=:id");
    Q.bindValue(":id", res);
    Q.bindValue(":prix", resP);
    Q.bindValue(":nom", nom);
    Q.bindValue(":type",type);
    Q.bindValue(":ingredients",ingredients);


    return    Q.exec();


}
QSqlQueryModel * Plat::recherche(QString prix)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("SELECT * FROM PLAT WHERE PRIX LIKE '%"+prix+"%'");
        model->query().bindValue(":prix",prix);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("ingredients"));

        return model;
}

QSqlQueryModel * Plat::trier()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * FROM PLAT ORDER BY PRIX asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ingredients"));
    return model;
}
QSqlQueryModel * Plat::trierN()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * FROM PLAT ORDER BY NOM asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ingredients"));
    return model;
}

