#ifndef STAT_H
#define STAT_H
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

#include <QWidget>

namespace Ui {
class stat;
}

class statis : public QWidget
{
    Q_OBJECT

public:
    explicit stat(QWidget *parent = nullptr);
     void make();
    stat();

private:
    Ui::stat *ui;
};

#endif // STAT_H
