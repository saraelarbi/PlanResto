#ifndef GESEMPCONG_H
#define GESEMPCONG_H

#include"materiel.h"
#include <QDialog>




namespace Ui {
class gesmat;
}

class gesmat : public QDialog
{
    Q_OBJECT

public:
    explicit gesmat(QWidget *parent = nullptr);
    ~gesmat();

private slots:
 void on_ajoutemp_clicked();
 void on_tabWidget_employes_currentChanged(int index);
 void on_suppemp_clicked();
 void on_modifemp_clicked();


 void on_pushButton_rechercheemp_clicked();
 void on_triemp_clicked();

private:
    Ui::gesmat *ui;
    Materiel insmateriel;



};


#endif // GESEMPCONG_H
