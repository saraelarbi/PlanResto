#ifndef BOISSON_H
#define BOISSON_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Boisson
{
public:
    Boisson();
    Boisson(int,int,QString,QString);
    int getId() ;
    int getprix();
    QString getnom();
    QString gettype();


    void setId(int);
    void setprix(int);
    void setnom(QString);
    void settype(QString);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
   QSqlQueryModel * recherche(QString nom);
   QSqlQueryModel * trier();
   QSqlQueryModel * trierN();
   QSqlQueryModel * trierI();


private:

int Id,prix;
QString nom,type;

};

#endif // BOISSON_H
