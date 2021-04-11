#include "boisson.h"
#include <QSqlQuery>
#include "QDebug"

Boisson::Boisson()
{

}

Boisson::Boisson(int Id,int prix,QString nom,QString type)
{
    this->Id=Id;
    this->prix=prix;
    this->nom=nom;
    this->type=type;

}

int Boisson::getId(){return Id;}
int Boisson::getprix(){return prix;}
QString Boisson::getnom(){return nom;}
QString Boisson::gettype(){return type;}

void Boisson::setId(int Id){this->Id=Id;}
void Boisson::setprix(int prix){this->prix=prix;}
void Boisson::setnom(QString nom){this->nom=nom;}
void Boisson::settype(QString type){this->type=type;}

bool Boisson::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(Id);
    QString res1= QString::number(prix);
    query.prepare("INSERT INTO BOISSON (ID, PRIX, NOM, TYPE) "
                        "VALUES (:Id, :prix, :nom, :type)");
    query.bindValue(":Id", res);
    query.bindValue(":prix", res1);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    return    query.exec();

}

QSqlQueryModel * Boisson::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from BOISSON");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    return model;
}

bool Boisson::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from BOISSON where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Boisson::modifier(int id)
{
    QSqlQuery Q;
    QString res= QString::number(id);
    QString resP= QString::number(prix);
    Q.prepare("UPDATE  BOISSON SET PRIX=:prix,NOM=:nom,TYPE=:type where ID=:id");
    Q.bindValue(":id", res);
    Q.bindValue(":prix", resP);
    Q.bindValue(":nom", nom);
    Q.bindValue(":type",type);

    return    Q.exec();


}

QSqlQueryModel * Boisson::recherche(QString prix)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("SELECT * FROM BOISSON WHERE PRIX LIKE '%"+prix+"%'");
        model->query().bindValue(":prix",prix);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));


        return model;
}

QSqlQueryModel * Boisson::trier()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * FROM BOISSON ORDER BY PRIX asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    return model;
}

QSqlQueryModel * Boisson::trierN()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * FROM BOISSON ORDER BY NOM asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    return model;
}
