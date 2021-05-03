#include "connexion.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
/*db.setDatabaseName("SmartResto");//inserer le nom de la source de données ODBC
db.setUserName("aymen");//inserer nom de l'utilisateur
db.setPassword("esprit21");//inserer mot de passe de cet utilisateur
*/
db.setDatabaseName("test bd");//inserer le nom de la source de données ODBC
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("191JFT2284");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
