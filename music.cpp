#include "music.h"
#include "ui_music.h"
#include<QMediaPlayer>
#include<QFileDialog>
music::music(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::music)
{
    ui->setupUi(this);
    mMediaPlayer = new QMediaPlayer(this);

    connect(mMediaPlayer, &QMediaPlayer::positionChanged,[&](qint64 pos){
        ui->avancement->setValue(pos);
    });
}

music::~music()
{
    delete ui;
}

void music::on_ouvrir_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"ouvrir");
    if (filename.isEmpty())
    {return;}
    mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    mMediaPlayer->setVolume(ui->volume->value());
    on_play_clicked();
}

void music::on_play_clicked()
{
    mMediaPlayer->play();
}

void music::on_pause_clicked()
{
    mMediaPlayer->pause();
}

void music::on_stop_clicked()
{
    mMediaPlayer->stop();
}



void music::on_mute_clicked()
{
    if(ui->mute->text()=="mute"){
    mMediaPlayer->setMuted(true);
    ui->mute->setText("unmute");
    }else {mMediaPlayer->setMuted(false);
        ui->mute->setText("mute");
    }
}

void music::on_volume_valueChanged(int value)
{
    mMediaPlayer->setVolume(value);
}
