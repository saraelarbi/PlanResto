#include "abonne.h"
#include<QSqlQuery>
#include<QtDebug>
#include <QObject>
Abonne::Abonne()
{
id_ab=0; nom=""; prenom="";payement=0;nbr_chats=0;sexe="";
}
Abonne::Abonne(int id_ab,QString nom,QString prenom,int payement,int nbr_chats,QString sexe)
{
    this->id_ab=id_ab; this->nom=nom; this->prenom=prenom; this->payement=payement; this->nbr_chats=nbr_chats;this->sexe=sexe;

}
int Abonne::getid_ab() {return id_ab;}
QString Abonne::getnom(){return nom;}
QString Abonne::getprenom(){return prenom;}
int Abonne::getpayemet() {return payement;}
int Abonne::getnbr_chats() {return nbr_chats;}
QString Abonne::getsexe() {return sexe;}
void Abonne::setid_ab(int id_ab){this->id_ab=id_ab;}
void Abonne::setnom(QString nom){this->nom=nom;}
void Abonne::setprenom(QString prenom){this->prenom=prenom;}
void Abonne::setpayement(int payement){this->payement=payement;}
void Abonne::setnbr_chats(int nbr_chats){this->nbr_chats=nbr_chats;}
void Abonne::setsexe(QString sexe){this->sexe=sexe;}
bool Abonne::ajouter()
{ bool test=false;
    QSqlQuery query;
    QString id_ab_string= QString::number(id_ab);
          query.prepare("INSERT INTO etudiant (id_ab, nom, prenom,payement,nbr_chats,sexe) "
                        "VALUES (:id_ab, :nom, :prenom, :payement, :nbr_chats, :sexe)");
          query.bindValue(0, id_ab_string);
          query.bindValue(1, nom);
          query.bindValue(2, prenom);
          query.bindValue(3, payement);
          query.bindValue(4, nbr_chats);
          query.bindValue(5, sexe);
        return query.exec();



    return test;

}
bool  Abonne::supprimer(int id_ab)
{  QSqlQuery query;
    query.prepare("delete from etudiant where id_ab=:id_ab");
  query.bindValue(0, id_ab);
return query.exec();


}
QSqlQueryModel* Abonne::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM etudiant");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Payement"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbr_chats"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
  return model;
}


bool Abonne::update(int id_ab, QString nom,QString prenom,int payement,int nbr_chats,QString sexe)
{
    QSqlQuery query;
    query.prepare("UPDATE etudiant SET id_ab= :id_ab,nom= :nom,prenom=:prenom,payement= :payement,nbr_chats=:nbr_chats,sexe=:sexe WHERE id_ab = :id_ab");
    query.bindValue(":id_ab", id_ab);
    query.bindValue(":nom",nom );
    query.bindValue(":prenom", prenom);
    query.bindValue(":payement", payement);
    query.bindValue(":nbr_chats", nbr_chats);
    query.bindValue(":sexe",sexe );
    return    query.exec();
}

QSqlQueryModel* Abonne::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from etudiant where ((id_ab || nom || prenom || payement || nbr_chats || sexe) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_ab"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("payement"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbr_chats"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));

    return model;
}

















