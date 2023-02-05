/********************************************************************************
** Form generated from reading UI file 'sewerclient.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEWERCLIENT_H
#define UI_SEWERCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SewerClient
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *filePostion;
    QPushButton *btnSelectFile;
    QPushButton *btnDetect;
    QLabel *labelImgDisplay;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SewerClient)
    {
        if (SewerClient->objectName().isEmpty())
            SewerClient->setObjectName(QString::fromUtf8("SewerClient"));
        SewerClient->resize(654, 712);
        centralwidget = new QWidget(SewerClient);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 642, 680));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        filePostion = new QLineEdit(widget);
        filePostion->setObjectName(QString::fromUtf8("filePostion"));

        horizontalLayout->addWidget(filePostion);

        btnSelectFile = new QPushButton(widget);
        btnSelectFile->setObjectName(QString::fromUtf8("btnSelectFile"));

        horizontalLayout->addWidget(btnSelectFile);

        btnDetect = new QPushButton(widget);
        btnDetect->setObjectName(QString::fromUtf8("btnDetect"));

        horizontalLayout->addWidget(btnDetect);


        verticalLayout->addLayout(horizontalLayout);

        labelImgDisplay = new QLabel(widget);
        labelImgDisplay->setObjectName(QString::fromUtf8("labelImgDisplay"));
        labelImgDisplay->setMinimumSize(QSize(640, 640));

        verticalLayout->addWidget(labelImgDisplay);

        SewerClient->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SewerClient);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SewerClient->setStatusBar(statusbar);

        retranslateUi(SewerClient);

        QMetaObject::connectSlotsByName(SewerClient);
    } // setupUi

    void retranslateUi(QMainWindow *SewerClient)
    {
        SewerClient->setWindowTitle(QCoreApplication::translate("SewerClient", "SewerClient", nullptr));
        btnSelectFile->setText(QCoreApplication::translate("SewerClient", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        btnDetect->setText(QCoreApplication::translate("SewerClient", "\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
        labelImgDisplay->setText(QCoreApplication::translate("SewerClient", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SewerClient: public Ui_SewerClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEWERCLIENT_H
