#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H
#include <QSystemTrayIcon>
#include<QString>


class notifications
{
public:
    notifications();
    void notifications_ajouterPlat();
    void notifications_ajouterBoisson();
    void notifications_supprimerPlat();
    void notifications_supprimerBoisson();
    void notifications_modifierPlat();
    void notifications_modifierBoisson();
};

#endif // NOTIFICATIONS_H
