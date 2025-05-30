/********************************************************************************
** Form generated from reading UI file 'emplhr.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLHR_H
#define UI_EMPLHR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmplHR
{
public:
    QWidget *centralwidget;
    QPushButton *btnBack;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EmplHR)
    {
        if (EmplHR->objectName().isEmpty())
            EmplHR->setObjectName("EmplHR");
        EmplHR->resize(800, 600);
        centralwidget = new QWidget(EmplHR);
        centralwidget->setObjectName("centralwidget");
        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(0, 0, 81, 21));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(350, 230, 49, 16));
        EmplHR->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EmplHR);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        EmplHR->setMenuBar(menubar);
        statusbar = new QStatusBar(EmplHR);
        statusbar->setObjectName("statusbar");
        EmplHR->setStatusBar(statusbar);

        retranslateUi(EmplHR);

        QMetaObject::connectSlotsByName(EmplHR);
    } // setupUi

    void retranslateUi(QMainWindow *EmplHR)
    {
        EmplHR->setWindowTitle(QCoreApplication::translate("EmplHR", "MainWindow", nullptr));
        btnBack->setText(QCoreApplication::translate("EmplHR", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        label->setText(QCoreApplication::translate("EmplHR", "hr", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmplHR: public Ui_EmplHR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLHR_H
