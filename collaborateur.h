#ifndef COLLABORATEUR_H
#define COLLABORATEUR_H


#include<QString>
#include<QSqlQueryModel>
class Collaborateur
{
public:
   Collaborateur();
    Collaborateur(QString,QString,QString,QString,QString,QString);
    QString getid();
    QString getnom();
    QString getprenom();
    QString gettelephone();
    QString getadresse();
    QString getemail();


    void setid(QString);
    void setnom(QString);
    void setprenom(QString);
    void settelephone(QString);
    void setadresse(QString);
    void setemail(QString);


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(QString);
        bool modifier(QString,QString,QString,QString,QString,QString);
        QSqlQueryModel * tri();


private:

    QString idcollaborateur,nom,prenom,adresse,email,telephone;


};

#endif // COLLABORATEUR_H
