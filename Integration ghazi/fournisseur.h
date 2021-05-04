#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include<QString>
#include<QSqlQueryModel>
class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(QString,QString,QString,QString,QString,QString,QString);
    QString getcinf();
    QString getnom();
    QString gettype();
    QString getprenom();
    QString gettel();
    QString getadresse();
    QString getemail();

    void setcinf(QString);
    void setnom(QString);
    void settype(QString);
    void setprenom(QString);
    void settel(QString);
    void setadresse(QString);
      void setemail(QString);

    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString,QString,QString);
    QSqlQueryModel* rechercher(const QString &aux);
private:

    QString cinf,tel,nom,type,prenom,email,adresse;


};
#endif // FOURNISSEUR_H
