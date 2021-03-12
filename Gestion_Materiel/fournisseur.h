#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include<QString>
#include<QSqlQueryModel>
class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(int,QString,QString,QString,int,QString,QString);
    int getcinf();
    QString getnom();
    QString gettype();
    QString getprenom();
     int gettel();
    QString getadresse();
    QString getemail();

    void setcinf(int);
    void setnom(QString);
    void settype(QString);
    void setprenom(QString);
    void settel(int);
    void setadresse(QString);
      void setemail(QString);

    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);

private:
    int cinf,tel;
    QString nom,type,prenom,email,adresse;


};
#endif // FOURNISSEUR_H
