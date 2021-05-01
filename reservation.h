#ifndef RESERVATION_H
#define RESERVATION_H


#include<QString>
#include<QSqlQueryModel>
class  Reservation
{
public:
    Reservation();
    Reservation(QString,QString,QString,QString,QString,QString,QString);
    QString getnumres();
    QString getnom();
    QString getprenom();
    QString getdateres();
    QString gettyperes();
    QString getnbtable();
    QString getnbchaise();



    void setnumres(QString);
    void setnom(QString);
    void setprenom(QString);
    void setdateres(QString);
    void settyperes(QString);
    void setnbtable(QString);
    void setnbchaise(QString);



    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString,QString,QString);


private:

    QString numres,nom,prenom,dateres,typeres,nbtable,nbchaise;


};

#endif // RESERVATION_H
