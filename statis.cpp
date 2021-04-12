/*#include "statis.h"
#include "ui_mainwindow.h"
#include <QString>
#include"contrat.h"
#include<qsqlquery.h>

#include<QtCharts/chartsnamespace.h>


statis::statis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statis)
{
    ui->setupUi(this);
}

statis::~statis()
{
    delete ui;
}
void statis::make()
{
        int une_anneé;
        int plus;
        int total;


        QSqlQuery q;

        q.prepare("SELECT COUNT(type) FROM contrat where duree =' une_anneé' ");
        q.exec();
        q.first() ;
         une_anneé=(q.value(0).toInt());

        q.prepare("SELECT COUNT(type) FROM contrat where etat ='plus' ");
        q.exec();
        q.first() ;
        plus=(q.value(0).toInt());
        q.prepare("SELECT COUNT(type) FROM contrat ");
        q.exec();
        q.first() ;
        total=(q.value(0).toInt());

        plus=((double)+plus/(double)total)*100;
         une_anneé=100-plus;

         une_anneé= int::number(une_anneé);
        plus=QString::number(plus);
        QPieSeries *series;
         series= new  QPieSeries();
         series->append("une_anneé"+une_anneé+"%",une_anneé);
         series->append("plus+plus+"%",plus);
         QPieSlice *slice0 = series->slices().at(0);
          slice0->setLabelVisible();

          QPieSlice *slice1 = series->slices().at(1);
             slice1->setExploded();
             slice1->setLabelVisible();
             slice1->setPen(QPen(Qt::darkRed, 2));
             slice1->setBrush(Qt::black);

              QChart *chart = new QChart();
              chart->addSeries(series);
              chart->setTitle("Statistiques sur la duree des collaboration ");
              chart->legend()->show();
              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);
              ui->verticalLayout->addWidget(chartView);

}
*/
