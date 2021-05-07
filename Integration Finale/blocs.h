#ifndef BLOCS_H
#define BLOCS_H


#include<QString>
#include<QSqlQueryModel>
class Blocs
{
public:
    Blocs();
    Blocs(QString,QString,QString);
    QString getIdblocs();
    QString getnumb();
    QString getetat();
    void setIdblocs(QString);
    void setnumb(QString);
    void setetat(QString);

    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString ,QString ,QString);
    QSqlQueryModel* rechercher(const QString &aux);

private:

    QString Idblocs,numb,etat;


};

#endif // BLOCS_H
