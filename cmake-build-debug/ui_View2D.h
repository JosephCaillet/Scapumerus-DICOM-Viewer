/********************************************************************************
** Form generated from reading UI file 'View2D.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW2D_H
#define UI_VIEW2D_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_View2D
{
public:
    QGridLayout *gridLayout;
    QVTKWidget *view;
    QLCDNumber *lcdNumber;
    QSlider *slider;
    QLCDNumber *objectCounterLcdNumber;

    void setupUi(QWidget *View2D)
    {
        if (View2D->objectName().isEmpty())
            View2D->setObjectName(QStringLiteral("View2D"));
        View2D->resize(405, 486);
        gridLayout = new QGridLayout(View2D);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        view = new QVTKWidget(View2D);
        view->setObjectName(QStringLiteral("view"));

        gridLayout->addWidget(view, 0, 0, 1, 2);

        lcdNumber = new QLCDNumber(View2D);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdNumber, 1, 1, 1, 1);

        slider = new QSlider(View2D);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider, 1, 0, 1, 1);

        objectCounterLcdNumber = new QLCDNumber(View2D);
        objectCounterLcdNumber->setObjectName(QStringLiteral("objectCounterLcdNumber"));
        objectCounterLcdNumber->setEnabled(false);
        objectCounterLcdNumber->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(objectCounterLcdNumber, 1, 2, 1, 1);

        gridLayout->setRowStretch(0, 1);

        retranslateUi(View2D);

        QMetaObject::connectSlotsByName(View2D);
    } // setupUi

    void retranslateUi(QWidget *View2D)
    {
        View2D->setWindowTitle(QApplication::translate("View2D", "Form", nullptr));
#ifndef QT_NO_TOOLTIP
        lcdNumber->setToolTip(QApplication::translate("View2D", "Current slice number", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        objectCounterLcdNumber->setToolTip(QApplication::translate("View2D", "Number of objects in current slice", nullptr));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class View2D: public Ui_View2D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW2D_H
