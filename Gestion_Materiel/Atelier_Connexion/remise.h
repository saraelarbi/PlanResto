#ifndef REMISE_H
#define REMISE_H
#include<qstring.h>
#include<QSqlQueryModel>
#include"calculatrice.h"
class Remise
{
public:
    Remise();
   Remise(QString,QString,QString,QString,QString);
    QString getidmateriel();
    QString getremise();
     QString getdates();
     QString getancienprix();
     QString getnouveauprix();
    void setidmateriel(QString);
    void setremise(QString);
    void setdates(QString);
    void setancienprix(QString);
     void setnouveauprix(QString);
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString);
    QSqlQueryModel* rechercher2(const QString &aux);

private:

    QString idmateriel,remise,dates,ancienprix,nouveauprix;

};


#endif // REMISE_H
