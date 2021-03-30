#include "commande.h"
#include <QDebug>
#include "connection.h"

commande::commande()
{
id=" ";
nom=" ";
type=" ";
cinp=" ";
prix=0;

}
commande::commande(QString id,QString nom,QString type,QString cinp,float prix)
{
  this->id=id;
  this->nom=nom;
  this->type=type;
  this->cinp=cinp;
  this->prix=prix;



}
QString commande::get_id(){return  id;}
QString commande::get_nom(){return nom;}
QString commande::get_type(){return type;}
QString commande::get_cinp(){return  cinp;}
float commande::get_prix(){return  prix;}


bool commande::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO commande (ID, NOM, TYPE, CINP, PRIX) "
                    "VALUES (:id, :nom, :type, :cinp, :prix)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":type", type);
query.bindValue(":cinp", cinp);
query.bindValue(":prix", prix);


return    query.exec();
}

QSqlQueryModel * commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from commande");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("CINP"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}

bool commande::supprimer(QString id)
{
QSqlQuery query;

query.prepare("Delete from commande where id = :id ");
query.bindValue(":id", id);
return    query.exec();
}
bool commande::modifier(QString id)
{
    QSqlQuery query;

  query.prepare("UPDATE commande set nom='"+nom+"',type='"+type+"', cinp='"+cinp+"', prix='"+prix+"' WHERE id LIKE '"+id+"' ");
   return query.exec();
    }
QSqlQueryModel *commande::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from commande where nom LIKE '"+rech+"%' or type LIKE '"+rech+"%'");
    return model;
}
QSqlQueryModel *commande::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from client ORDER BY nom ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cinp"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));


        return model;
}

