#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QWidget>

namespace Ui {
class calculatrice;
}

class calculatrice : public QWidget
{
    Q_OBJECT

public:
    explicit calculatrice(QWidget *parent = nullptr);
    ~calculatrice();
    void make();
     void setcalc(calculatrice c);
private:
    Ui::calculatrice *ui;
private slots :

    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
};

#endif // CALCULATRICE_H
