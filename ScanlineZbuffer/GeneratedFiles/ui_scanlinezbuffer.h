/********************************************************************************
** Form generated from reading UI file 'scanlinezbuffer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANLINEZBUFFER_H
#define UI_SCANLINEZBUFFER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "scanlinezbufferview.h"

QT_BEGIN_NAMESPACE

class Ui_ScanlineZbufferClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    ScanlineZbufferView *graphicsView;
    QOpenGLWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ScanlineZbufferClass)
    {
        if (ScanlineZbufferClass->objectName().isEmpty())
            ScanlineZbufferClass->setObjectName(QStringLiteral("ScanlineZbufferClass"));
        ScanlineZbufferClass->resize(982, 688);
        actionOpen = new QAction(ScanlineZbufferClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(ScanlineZbufferClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new ScanlineZbufferView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 90, 431, 401));
        openGLWidget = new QOpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(490, 90, 461, 401));
        ScanlineZbufferClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ScanlineZbufferClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 982, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        ScanlineZbufferClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ScanlineZbufferClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ScanlineZbufferClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ScanlineZbufferClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ScanlineZbufferClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionOpen);

        retranslateUi(ScanlineZbufferClass);

        QMetaObject::connectSlotsByName(ScanlineZbufferClass);
    } // setupUi

    void retranslateUi(QMainWindow *ScanlineZbufferClass)
    {
        ScanlineZbufferClass->setWindowTitle(QApplication::translate("ScanlineZbufferClass", "ScanlineZbuffer", 0));
        actionOpen->setText(QApplication::translate("ScanlineZbufferClass", "open...", 0));
        menu->setTitle(QApplication::translate("ScanlineZbufferClass", "file", 0));
    } // retranslateUi

};

namespace Ui {
    class ScanlineZbufferClass: public Ui_ScanlineZbufferClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANLINEZBUFFER_H
