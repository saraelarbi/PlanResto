#ifndef ABONNEMENT_H
#define ABONNEMENT_H
#include<QDate>
#include <QSqlQueryModel>


class Abonnement
{
public:
    Abonnement();
    Abonnement(int,QDate,QDate);
        int getid();
        QDate getdate_deb();
        QDate getdate_fin();

        void setid(int);
        void setdate_deb(QDate);
        void setdate_fin(QDate);

        bool ajouter();
      QSqlQueryModel* afficher();
      bool update(int , QDate ,QDate);
      bool supprimer(int);
    private:
        int id;
        QDate date_deb,date_fin;
};
#endif // ABONNEMENT_H
