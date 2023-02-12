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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_projectCfg
{
public:

    void setupUi(QWidget *projectCfg)
    {
        if (projectCfg->objectName().isEmpty())
            projectCfg->setObjectName(QString::fromUtf8("projectCfg"));
        projectCfg->resize(400, 300);

        retranslateUi(projectCfg);

        QMetaObject::connectSlotsByName(projectCfg);
    } // setupUi

    void retranslateUi(QWidget *projectCfg)
    {
        projectCfg->setWindowTitle(QCoreApplication::translate("projectCfg", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class projectCfg: public Ui_projectCfg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTCFG_H
