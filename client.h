#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class client
{public:
    client();
    client(QString,QString,QString,QString,QString,QString);
    QString get_id();
    QString get_nom();
    QString get_prenom();
    QString get_adresse();
    QString get_tel();
    QString get_email();

    void setid(QString);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void settel(QString);
    void setemail(QString);



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString,QString);
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * tri();
private:
    QString id,nom,prenom,adresse,email,tel;

};

#endif // CLIENT_H
