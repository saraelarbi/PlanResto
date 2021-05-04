#ifndef REMISE_H
#define REMISE_H
#include<qstring.h>
#include<QSqlQueryModel>
#include"calculatrice.h"
#include<QDate>
class Remise
{
public:
    Remise();
   Remise(QString,QString,QDate,QString,QString);
    QString getidmateriel();
    QString getremise();
     QDate getdates();
     QString getancienprix();
     QString getnouveauprix();
    void setidmateriel(QString);
    void setremise(QString);
    void setdates(QDate);
    void setancienprix(QString);
     void setnouveauprix(QString);
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QDate,QString,QString);
    QSqlQueryModel* rechercher2(const QString &aux);

private:

    QString idmateriel,remise,ancienprix,nouveauprix;
    QDate dates;

};


#endif // REMISE_H
