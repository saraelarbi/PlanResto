#ifndef MATERIEL_H
#define MATERIEL_H
#include<QString>
#include<QSqlQueryModel>
class Materiel
{
public:
    Materiel();
    Materiel(QString,QString,QString,QString,float);
    QString getid();
    QString getnom();
    QString gettype();
    QString getmarque();
    float getprix();

    void setid(QString);
    void setnom(QString);
    void settype(QString);
    void setmarque(QString);
    void setprix(float);

    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);

private:

    QString id,nom,type,marque;
    float prix;

};

#endif // MATERIEL_H
