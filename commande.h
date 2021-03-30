#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>

#include <QSqlQuery>
#include <QSqlQueryModel>


class commande
{public:
    commande();
   commande(QString,QString,QString,QString,float);
    QString get_id();
    QString get_nom();
    QString get_type();
    QString get_cinp();
    float get_prix();



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString);
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * tri();
private:
    QString id,nom,type,cinp;
    float prix;

};

#endif // COMMANDE_H
