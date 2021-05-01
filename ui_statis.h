/********************************************************************************
** Form generated from reading UI file 'statis.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIS_H
#define UI_STATIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_statis
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *statis)
    {
        if (statis->objectName().isEmpty())
            statis->setObjectName(QStringLiteral("statis"));
        statis->resize(400, 300);
        verticalLayoutWidget = new QWidget(statis);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, 0, 401, 301));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(statis);

        QMetaObject::connectSlotsByName(statis);
    } // setupUi

    void retranslateUi(QWidget *statis)
    {
        statis->setWindowTitle(QApplication::translate("statis", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class statis: public Ui_statis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIS_H
