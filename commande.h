#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>

#include <QSqlQuery>
#include <QSqlQueryModel>


class commande
{public:
    commande();
   commande(QString,QString,QString,QString,QString);
    QString get_id();
    QString get_nom();
    QString get_type();
    QString get_cinp();
    QString get_prix();

    void setid(QString);
    void setnom(QString);
    void settype(QString);
    void setcinp(QString);
    void setprix(QString);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString);
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * tri();
    QSqlQueryModel * afficherhis() ;
    bool ajoutehis();
    bool modifierhis() ;
private:
    QString id,nom,type,cinp,prix;

};

#endif // COMMANDE_H
