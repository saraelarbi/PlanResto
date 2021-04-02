#ifndef EMPLYER_H
#define EMPLYER_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QFileDialog>
#include <QCoreApplication>
#include <QTextStream>



class Employes
{
private:


    int id;
    QString CIN,nom,prenom,TypeFonction,Telephone,email,Adress;

public:

    Employes();
    Employes(QString,QString,QString,QString,QString,QString,QString);




    QString getCIN();
    QString getnom();
    QString getprenom();
    QString getTypeFonction();
    QString getTelephone();
    QString getemail();
    QString getAdress();


    void setCIN(QString);
    void setnom(QString);
    void setprenom(QString);
    void setTypeFonction(QString);
    void setTelephone(QString);
    void setemail(QString);
    void setAdress(QString);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString,QString,QString,QString);
    void exporter(QTableView *table);



};

#endif // EMPLYER_H
