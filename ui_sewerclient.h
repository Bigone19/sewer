/********************************************************************************
** Form generated from reading UI file 'sewerclient.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEWERCLIENT_H
#define UI_SEWERCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SewerClient
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SewerClient)
    {
        if (SewerClient->objectName().isEmpty())
            SewerClient->setObjectName("SewerClient");
        SewerClient->resize(800, 600);
        centralwidget = new QWidget(SewerClient);
        centralwidget->setObjectName("centralwidget");
        SewerClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SewerClient);
        menubar->setObjectName("menubar");
        SewerClient->setMenuBar(menubar);
        statusbar = new QStatusBar(SewerClient);
        statusbar->setObjectName("statusbar");
        SewerClient->setStatusBar(statusbar);

        retranslateUi(SewerClient);

        QMetaObject::connectSlotsByName(SewerClient);
    } // setupUi

    void retranslateUi(QMainWindow *SewerClient)
    {
        SewerClient->setWindowTitle(QCoreApplication::translate("SewerClient", "SewerClient", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SewerClient: public Ui_SewerClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEWERCLIENT_H
