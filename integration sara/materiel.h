#ifndef MATERIEL_H
#define MATERIEL_H


#include<QString>
#include<QSqlQueryModel>

class Materiel
{
public:
    Materiel();
    Materiel(QString,QString,QString,QString,QString,QString);
    QString getid();
    QString getnom();
    QString gettype();
    QString getmarque();
    QString getprix();
    QString getcinf();

    void setid(QString);
    void setnom(QString);
    void settype(QString);
    void setmarque(QString);
    void setprix(QString);
    void setcinf(QString);
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString,QString);

         QSqlQueryModel * rechercher_nom(QString);
         QSqlQueryModel * rechercher_type(QString);
         QSqlQueryModel * rechercher_marque(QString);
         QSqlQueryModel * rechercher_nom_type(QString,QString);
         QSqlQueryModel * rechercher_nom_marque(QString,QString);
         QSqlQueryModel * rechercher_type_marque(QString,QString);
         QSqlQueryModel * rechercher_tous(QString,QString,QString);


private:

    QString id,nom,type,marque,prix,cinf;

};

#endif // MATERIEL_H
