#include "notifications.h"
#include <QSystemTrayIcon>
#include<QString>

notifications::notifications()
{

}

void notifications::notifications_ajouterPlat()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/Integration Finale/valider.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Plats","Nouveau Plat ajouté ",QSystemTrayIcon::Information,15000);

}

void notifications::notifications_supprimerPlat(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/Integration Finale/supprimer.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Plats ","Plat Supprimé",QSystemTrayIcon::Information,15000);
}

void notifications::notifications_modifierPlat(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/Integration Finale/modifier.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Plats ","Plat est modifié",QSystemTrayIcon::Information,15000);

}





void notifications::notifications_ajouterBoisson()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/Integration Finale/valider.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Boisson","Nouveau Boisson ajouté ",QSystemTrayIcon::Information,15000);
}


void notifications::notifications_supprimerBoisson(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/Integration Finale/supprimer.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Boisson ","Boisson Supprimé",QSystemTrayIcon::Information,15000);
}

void notifications::notifications_modifierBoisson(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/Integration Finale/modifier.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Boisson ","Boisson est modifié",QSystemTrayIcon::Information,15000);

}
