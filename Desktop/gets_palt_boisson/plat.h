#ifndef PLAT_H
#define PLAT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Plat
{
public:
    Plat();
    Plat(int,int,QString,QString,QString);
    int getId() ;
    int getprix();
    QString getnom();
    QString gettype();
    QString getingredients();

    void setId(int);
    void setprix(int);
    void setnom(QString);
    void settype(QString);
    void setingredients(QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);





private:

int Id,prix;
QString nom,type,ingredients;

};

#endif // PLAT_H
