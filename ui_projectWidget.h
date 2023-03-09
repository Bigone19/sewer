/********************************************************************************
** Form generated from reading UI file 'projectWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTWIDGET_H
#define UI_PROJECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_projectDlg
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *editProjectName;
    QPushButton *btnProjectName;

    void setupUi(QWidget *projectDlg)
    {
        if (projectDlg->objectName().isEmpty())
            projectDlg->setObjectName(QString::fromUtf8("projectDlg"));
        projectDlg->resize(298, 51);
        layoutWidget = new QWidget(projectDlg);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 273, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        editProjectName = new QLineEdit(layoutWidget);
        editProjectName->setObjectName(QString::fromUtf8("editProjectName"));

        horizontalLayout->addWidget(editProjectName);

        btnProjectName = new QPushButton(layoutWidget);
        btnProjectName->setObjectName(QString::fromUtf8("btnProjectName"));

        horizontalLayout->addWidget(btnProjectName);


        retranslateUi(projectDlg);

        QMetaObject::connectSlotsByName(projectDlg);
    } // setupUi

    void retranslateUi(QWidget *projectDlg)
    {
        projectDlg->setWindowTitle(QCoreApplication::translate("projectDlg", "\351\241\271\347\233\256\344\277\241\346\201\257", nullptr));
        btnProjectName->setText(QCoreApplication::translate("projectDlg", "\346\267\273\345\212\240\351\241\271\347\233\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class projectDlg: public Ui_projectDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTWIDGET_H
