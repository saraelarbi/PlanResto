#include "statis.h"
#include "ui_statis.h"
#include <QString>
#include"contrat.h"
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
        int male;
        int femelle;
        int total;
        QString Male;
        QString Femelle;

        QSqlQuery q;

        q.prepare("SELECT COUNT(type) FROM contrat where duree ='-1an' ");
        q.exec();
        q.first() ;
        -1an=(q.value(0).toInt());

        q.prepare("SELECT COUNT(type) FROM contrat where etat ='+1an' ");
        q.exec();
        q.first() ;
        Femelle=(q.value(0).toInt());
        q.prepare("SELECT COUNT(type) FROM etudiant ");
        q.exec();
        q.first() ;
        total=(q.value(0).toInt());

        +1an=((double)+1an/(double)total)*100;
        -1an=100-+1an;

        -1an= QString::number(-1an);
        +1an=QString::number(+1an);
        QPieSeries *series;
         series= new  QPieSeries();
         series->append("MALE"+Male+"%",male);
         series->append("+1an"+Femelle+"%",femelle);
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
