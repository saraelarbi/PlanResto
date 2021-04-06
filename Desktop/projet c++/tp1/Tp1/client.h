#ifndef CLIENT_H
#define CLIENT_H
#include <QString>

class client
{

private:
    int CIN;
    QString prenom,nom;


public:
    client();
    void setCIN(int cn) {CIN=cn;}
    void setPrenom(QString pr) {prenom=pr;}
    void setNom(QString nm) {nom=nm;}
int getCIN(){return CIN;}
    QString getPrenom(){return prenom;}
    QString getNom(){return nom;}

};

#endif // CLIENT_H
