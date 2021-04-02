#ifndef FONCTION_H
#define FONCTION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTime>
#include <QDate>


class fonction
{
private:


    QString typefonction,salaire,jourdetravail, heurededebut,heuredefin;

    QDate debutdeconge, findeconge;

public:

    fonction();
    fonction(QString,QString,QString,QString,QString,QDate,QDate);




    QString gettypefonction();
    QString getsalaire();
    QString getjourdetravail();
    QString getheurededebut();
    QString getheuredefin();
    QDate getdebutdeconge();
    QDate getfindeconge();


    void settypefonction(QString);
    void setsalaire(QString);
    void setjourdetravail(QString);
    void setheurededebut(QString);
    void setheuredefin(QString);
    void setdebutdeconge(QDate);
    void setfindeconge(QDate);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString,QDate,QDate);

     QSqlQueryModel * rechercher_salaire(QString);
     QSqlQueryModel * rechercher_jourdetravail(QString);
     QSqlQueryModel * rechercher_findeconge(QDate);
     QSqlQueryModel * rechercher_salaire_jourdetravail(QString,QString);
     QSqlQueryModel * rechercher_salaire_findeconge(QString,QDate);
     QSqlQueryModel * rechercher_jourdetravail_findeconge(QString,QDate);
     QSqlQueryModel * rechercher_tous(QString,QString,QDate);


};

#endif // FONCTION_H
