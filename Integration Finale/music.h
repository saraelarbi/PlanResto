#ifndef MUSIC_H
#define MUSIC_H

#include <QDialog>

namespace Ui {
class music;
}
class QMediaPlayer;
class music : public QDialog
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = nullptr);
    ~music();

private slots:
    void on_ouvrir_clicked();

    void on_play_clicked();

    void on_pause_clicked();

    void on_stop_clicked();


    void on_mute_clicked();

    void on_volume_valueChanged(int value);


private:
    Ui::music *ui;
    QMediaPlayer *mMediaPlayer;
};

#endif // MUSIC_H
