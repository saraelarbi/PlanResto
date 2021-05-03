#include "emplyer.h"
#include "fonction.h"


Employes::Employes()
{

}

Employes::Employes(QString CIN,QString nom,QString prenom,QString TypeFonction ,QString Telephone ,QString email,QString Adress)
{
     this->CIN=CIN;
     this->nom=nom;
     this->prenom=prenom;
     this->TypeFonction=TypeFonction;
     this->Telephone=Telephone;
     this->email=email;
     this->Adress=Adress;
}

QString Employes::getCIN(){ return CIN;}
QString Employes::getnom(){ return nom;}
QString Employes::getprenom(){ return prenom;}
QString Employes::getTypeFonction(){ return TypeFonction;}
QString Employes::getTelephone(){ return Telephone;}
QString Employes::getemail(){ return email;}
QString Employes::getAdress(){ return Adress;}


void Employes::setCIN(QString CIN){ this->CIN=CIN;}
void Employes::setnom(QString nom){ this->nom=nom;}
void Employes::setprenom(QString prenom){ this->prenom=prenom;}
void Employes::setTypeFonction(QString TypeFonction){ this->TypeFonction=TypeFonction;}
void Employes::setTelephone(QString Telephone){ this->prenom=Telephone;}
void Employes::setemail(QString email){ this->email=email;}
void Employes::setAdress(QString Adress){ this->Adress=Adress;}


bool Employes::ajouter()
{
    QSqlQuery query;

          query.prepare("INSERT INTO EM (CIN, nom, prenom,TypeFonction, Telephone, email, Adress) "
                        "VALUES (:CIN, :nom, :prenom,:TypeFonction, :Telephone, :email, :Adress)");
          query.bindValue(":CIN",CIN);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":TypeFonction", TypeFonction);
          query.bindValue(":Telephone", Telephone);
          query.bindValue(":email", email);
          query.bindValue(":Adress", Adress);



    return query.exec();
}

bool Employes::supprimer(QString CIN)
{
    QSqlQuery query;
    QString C = CIN;
    query.prepare("Delete from EM where CIN=:CIN");
    query.bindValue(":CIN",C);
    return query.exec();
}

 QSqlQueryModel * Employes::afficher()
 {
     QSqlQueryModel * Model= new QSqlQueryModel;
     Model -> setQuery("select * from EM");
     Model -> setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
     Model -> setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
     Model -> setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
     Model -> setHeaderData(3,Qt::Horizontal,QObject::tr("TypeFonction"));
     Model -> setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));
     Model -> setHeaderData(5,Qt::Horizontal,QObject::tr("email"));
     Model -> setHeaderData(6,Qt::Horizontal,QObject::tr("Adress"));
     return Model;

 }

 bool Employes::modifier(QString CIN,QString nom,QString prenom,QString TypeFonction ,QString Telephone ,QString email,QString Adress)
 {
     QSqlQuery query;
     query.prepare("UPDATE EM SET CIN:=CIN, nom:=nom, prenom:=prenom, TypeFonction:=TypeFonction, Telephone:=Telephone, email:=email, Adress:=Adress");
     query.bindValue(":CIN",CIN);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":TypeFonction",TypeFonction);
     query.bindValue(":Telephone",Telephone);
     query.bindValue(":email",email);
     query.bindValue(":Adress",Adress);
     return query.exec();
 }

 void Employes::exporter(QTableView *table)
 {

     QString filters("CSV files (*.csv);;All files (*.*)");
     QString defaultFilter("CSV files (*.csv)");
     QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                                     filters, &defaultFilter);
     QFile file(fileName);
     QAbstractItemModel *model =  table->model();
     if (file.open(QFile::WriteOnly | QFile::Truncate))
     {
         QTextStream data(&file);
         QStringList strList;
         for (int i = 0; i < model->columnCount(); i++)
         {
             if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                 strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
             else
                 strList.append("");
         }
         data << strList.join(";") << "\n";
         for (int i = 0; i < model->rowCount(); i++)
         {
             strList.clear();
             for (int j = 0; j < model->columnCount(); j++)
             {

                 if (model->data(model->index(i, j)).toString().length() > 0)
                     strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                 else
                     strList.append("");
             }
             data << strList.join(";") + "\n";
         }
         file.close();
     }
 }
