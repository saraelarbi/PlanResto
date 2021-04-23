#ifndef REMISE_H
#define REMISE_H
#include<qstring.h>
#include<QSqlQueryModel>
class Remise
{
public:
    Remise();
   Remise(QString,QString,QString);
    QString getidmateriel();
    QString getremise();
     QString getdates();
    void setidmateriel(QString);
    void setremise(QString);
    void setdates(QString);
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString);
    QSqlQueryModel* rechercher2(const QString &aux);

private:

    QString idmateriel,remise,dates;

};


#endif // REMISE_H
