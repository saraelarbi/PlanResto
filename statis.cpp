#include "statis.h"
#include "ui_statis.h"
#include<qsqlquery.h>

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
        int une_annee;
        int plus;
        int total;
        QString Une_annee;
        QString Plus;

        QSqlQuery q;

        q.prepare("SELECT COUNT(type) FROM contrat where etat ='Une_annee' ");
        q.exec();
        q.first() ;
        Une_annee=(q.value(0).toInt());

        q.prepare("SELECT COUNT(type) FROM contrat where etat ='Plus' ");
        q.exec();
        q.first() ;
        Plus=(q.value(0).toInt());
        q.prepare("SELECT COUNT(type) FROM contrat ");
        q.exec();
        q.first() ;
        total=(q.value(0).toInt());

        plus=((double)plus/(double)total)*100;
        une_annee=100-plus;

        Une_annee= QString::number(une_annee);
        Plus=QString::number(plus);
        QPieSeries *series;
         series= new  QPieSeries();
         series->append("UNEANNEE"+Une_annee+"%",une_annee);
         series->append("PLUS"+Plus+"%",plus);
         QPieSlice *slice0 = series->slices().at(0);
          slice0->setLabelVisible();

          QPieSlice *slice1 = series->slices().at(1);
             slice1->setExploded();
             slice1->setLabelVisible();
             slice1->setPen(QPen(Qt::darkRed, 2));
             slice1->setBrush(Qt::black);

              QChart *chart = new QChart();
              chart->addSeries(series);
              chart->setTitle("Statistiques sur les durees de collaborations ");
              chart->legend()->show();
              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);
              ui->verticalLayout->addWidget(chartView);

}
