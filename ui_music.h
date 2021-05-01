/********************************************************************************
** Form generated from reading UI file 'music.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSIC_H
#define UI_MUSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_music
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *ouvrir;
    QPushButton *play;
    QPushButton *pause;
    QPushButton *stop;
    QHBoxLayout *horizontalLayout_2;
    QSlider *volume;
    QPushButton *mute;

    void setupUi(QDialog *music)
    {
        if (music->objectName().isEmpty())
            music->setObjectName(QStringLiteral("music"));
        music->resize(400, 300);
        verticalLayout = new QVBoxLayout(music);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ouvrir = new QPushButton(music);
        ouvrir->setObjectName(QStringLiteral("ouvrir"));

        horizontalLayout->addWidget(ouvrir);

        play = new QPushButton(music);
        play->setObjectName(QStringLiteral("play"));

        horizontalLayout->addWidget(play);

        pause = new QPushButton(music);
        pause->setObjectName(QStringLiteral("pause"));

        horizontalLayout->addWidget(pause);

        stop = new QPushButton(music);
        stop->setObjectName(QStringLiteral("stop"));

        horizontalLayout->addWidget(stop);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        volume = new QSlider(music);
        volume->setObjectName(QStringLiteral("volume"));
        volume->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(volume);

        mute = new QPushButton(music);
        mute->setObjectName(QStringLiteral("mute"));

        horizontalLayout_2->addWidget(mute);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(music);

        QMetaObject::connectSlotsByName(music);
    } // setupUi

    void retranslateUi(QDialog *music)
    {
        music->setWindowTitle(QApplication::translate("music", "Dialog", Q_NULLPTR));
        ouvrir->setText(QApplication::translate("music", "open music", Q_NULLPTR));
        play->setText(QApplication::translate("music", "play", Q_NULLPTR));
        pause->setText(QApplication::translate("music", "pause", Q_NULLPTR));
        stop->setText(QApplication::translate("music", "stop", Q_NULLPTR));
        mute->setText(QApplication::translate("music", "mute", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class music: public Ui_music {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSIC_H
