#ifndef PRODUIT_H
#define PRODUIT_H


#include<QString>
#include<QSqlQueryModel>
class Produit
{
public:
    Produit();
    Produit(QString,QString,QString,QString,QString);
    QString getid();
    QString getnom();
    QString gettype();
    QString getmarque();
    QString getprix();

    void setid(QString);
    void setnom(QString);
    void settype(QString);
    void setmarque(QString);
    void setprix(QString);


    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString ,QString ,QString ,QString,QString);
             QSqlQueryModel * rechercher_nom(QString);
             QSqlQueryModel * rechercher_type(QString);
             QSqlQueryModel * rechercher_marque(QString);
             QSqlQueryModel * rechercher_nom_type(QString,QString);
             QSqlQueryModel * rechercher_nom_marque(QString,QString);
             QSqlQueryModel * rechercher_type_marque(QString,QString);
             QSqlQueryModel * rechercher_tous(QString,QString,QString);


private:

    QString id,nom,type,marque,prix;


};
class projeth
{
public:
       projeth() ;
       projeth(QString,QString,QString) ;
       QString get_nom();
       QString get_datee();
       QString get_fn();
       QSqlQueryModel * afficherhis() ;
       bool ajoutehis();
       bool modifierhis() ;
private:

    QString nom,datee,fn ;
};

#endif // PRODUIT_H
