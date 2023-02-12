/********************************************************************************
** Form generated from reading UI file 'projectcfg.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTCFG_H
#define UI_PROJECTCFG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_projectCfg
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *editProjectName;
    QPushButton *btnProjectName;

    void setupUi(QWidget *projectCfg)
    {
        if (projectCfg->objectName().isEmpty())
            projectCfg->setObjectName(QString::fromUtf8("projectCfg"));
        projectCfg->resize(298, 51);
        widget = new QWidget(projectCfg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 273, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        editProjectName = new QLineEdit(widget);
        editProjectName->setObjectName(QString::fromUtf8("editProjectName"));

        horizontalLayout->addWidget(editProjectName);

        btnProjectName = new QPushButton(widget);
        btnProjectName->setObjectName(QString::fromUtf8("btnProjectName"));

        horizontalLayout->addWidget(btnProjectName);


        retranslateUi(projectCfg);

        QMetaObject::connectSlotsByName(projectCfg);
    } // setupUi

    void retranslateUi(QWidget *projectCfg)
    {
        projectCfg->setWindowTitle(QCoreApplication::translate("projectCfg", "\351\241\271\347\233\256\344\277\241\346\201\257", nullptr));
        btnProjectName->setText(QCoreApplication::translate("projectCfg", "\346\267\273\345\212\240\351\241\271\347\233\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class projectCfg: public Ui_projectCfg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTCFG_H
