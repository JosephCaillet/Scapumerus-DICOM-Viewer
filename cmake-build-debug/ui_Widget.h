/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "View2D.h"
#include "View3D.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QWidget *top;
    QHBoxLayout *horizontalLayout;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *segmentButton;
    QPushButton *countButton;
    QSpacerItem *horizontalSpacer_2;
    QProgressBar *progressBar;
    QSpacerItem *horizontalSpacer;
    QPushButton *invertBgColorButton;
    QPushButton *colorsButton;
    QHBoxLayout *horizontalLayout_3;
    View2D *view2D;
    View3D *view3D;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(975, 453);
        QIcon icon;
        icon.addFile(QStringLiteral("img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        top = new QWidget(Widget);
        top->setObjectName(QStringLiteral("top"));
        horizontalLayout = new QHBoxLayout(top);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        loadButton = new QPushButton(top);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("img/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadButton->setIcon(icon1);
        loadButton->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(loadButton);

        saveButton = new QPushButton(top);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral("img/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton->setIcon(icon2);

        horizontalLayout->addWidget(saveButton);

        segmentButton = new QPushButton(top);
        segmentButton->setObjectName(QStringLiteral("segmentButton"));
        segmentButton->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral("img/segment.png"), QSize(), QIcon::Normal, QIcon::Off);
        segmentButton->setIcon(icon3);

        horizontalLayout->addWidget(segmentButton);

        countButton = new QPushButton(top);
        countButton->setObjectName(QStringLiteral("countButton"));
        countButton->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QStringLiteral("img/count.png"), QSize(), QIcon::Normal, QIcon::Off);
        countButton->setIcon(icon4);

        horizontalLayout->addWidget(countButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        progressBar = new QProgressBar(top);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setValue(24);
        progressBar->setInvertedAppearance(false);

        horizontalLayout->addWidget(progressBar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        invertBgColorButton = new QPushButton(top);
        invertBgColorButton->setObjectName(QStringLiteral("invertBgColorButton"));
        invertBgColorButton->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QStringLiteral("img/invert.png"), QSize(), QIcon::Normal, QIcon::Off);
        invertBgColorButton->setIcon(icon5);
        invertBgColorButton->setCheckable(true);

        horizontalLayout->addWidget(invertBgColorButton);

        colorsButton = new QPushButton(top);
        colorsButton->setObjectName(QStringLiteral("colorsButton"));
        colorsButton->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral("img/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        colorsButton->setIcon(icon6);
        colorsButton->setCheckable(true);

        horizontalLayout->addWidget(colorsButton);


        verticalLayout->addWidget(top);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        view2D = new View2D(Widget);
        view2D->setObjectName(QStringLiteral("view2D"));

        horizontalLayout_3->addWidget(view2D);

        view3D = new View3D(Widget);
        view3D->setObjectName(QStringLiteral("view3D"));

        horizontalLayout_3->addWidget(view3D);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Scapumerus DICOM Viewer", nullptr));
#ifndef QT_NO_TOOLTIP
        loadButton->setToolTip(QApplication::translate("Widget", "Open DICOM image folder", nullptr));
#endif // QT_NO_TOOLTIP
        loadButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        saveButton->setToolTip(QApplication::translate("Widget", "Save STL Models", nullptr));
#endif // QT_NO_TOOLTIP
        saveButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        segmentButton->setToolTip(QApplication::translate("Widget", "Segment datas", nullptr));
#endif // QT_NO_TOOLTIP
        segmentButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        countButton->setToolTip(QApplication::translate("Widget", "Count object by slice", nullptr));
#endif // QT_NO_TOOLTIP
        countButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        invertBgColorButton->setToolTip(QApplication::translate("Widget", "Invert background", nullptr));
#endif // QT_NO_TOOLTIP
        invertBgColorButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        colorsButton->setToolTip(QApplication::translate("Widget", "Colorized bones", nullptr));
#endif // QT_NO_TOOLTIP
        colorsButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
