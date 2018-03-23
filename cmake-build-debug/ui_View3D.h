/********************************************************************************
** Form generated from reading UI file 'View3D.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW3D_H
#define UI_VIEW3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_View3D
{
public:
    QVBoxLayout *verticalLayout;
    QVTKWidget *view;

    void setupUi(QWidget *View3D)
    {
        if (View3D->objectName().isEmpty())
            View3D->setObjectName(QStringLiteral("View3D"));
        View3D->resize(400, 300);
        verticalLayout = new QVBoxLayout(View3D);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        view = new QVTKWidget(View3D);
        view->setObjectName(QStringLiteral("view"));

        verticalLayout->addWidget(view);


        retranslateUi(View3D);

        QMetaObject::connectSlotsByName(View3D);
    } // setupUi

    void retranslateUi(QWidget *View3D)
    {
        View3D->setWindowTitle(QApplication::translate("View3D", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class View3D: public Ui_View3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW3D_H
