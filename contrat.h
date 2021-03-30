#ifndef CONTRAT_H
#define CONTRAT_H


#include<QString>
#include<QSqlQueryModel>
class  Contrat
{
public:
    Contrat();
    Contrat(QString,QString,QString,QString,QString);
    QString gettype();
    QString getnom();
    QString getduree();
    QString gettarif();
    QString getidcollaborateur();


    void settype(QString);
    void setnom(QString);
    void setduree(QString);
    void settarif(QString);
    void setidcollaborateur(QString);


    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString);
             QSqlQueryModel *rechercher_nom(QString);
             QSqlQueryModel *rechercher_type(QString);
             QSqlQueryModel *rechercher_tarif(QString);
             QSqlQueryModel *rechercher_nom_type(QString,QString);
             QSqlQueryModel *rechercher_nom_tarif(QString,QString);
             QSqlQueryModel *rechercher_type_tarif(QString,QString);
             QSqlQueryModel *rechercher_tous(QString,QString,QString);

private:

    QString type,nom,duree,tarif,idcollaborateur;


};

#endif // CONTRAT_H
