/********************************************************************************
** Form generated from reading UI file 'accountsmanager.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTSMANAGER_H
#define UI_ACCOUNTSMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccountsManager
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AccountsManager)
    {
        if (AccountsManager->objectName().isEmpty())
            AccountsManager->setObjectName("AccountsManager");
        AccountsManager->resize(554, 355);
        centralwidget = new QWidget(AccountsManager);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(90, 10, 181, 24));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(90, 60, 181, 24));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 49, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 70, 91, 16));
        AccountsManager->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AccountsManager);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 554, 21));
        AccountsManager->setMenuBar(menubar);
        statusbar = new QStatusBar(AccountsManager);
        statusbar->setObjectName("statusbar");
        AccountsManager->setStatusBar(statusbar);

        retranslateUi(AccountsManager);

        QMetaObject::connectSlotsByName(AccountsManager);
    } // setupUi

    void retranslateUi(QMainWindow *AccountsManager)
    {
        AccountsManager->setWindowTitle(QCoreApplication::translate("AccountsManager", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("AccountsManager", "\320\230\320\235\320\235:", nullptr));
        label_2->setText(QCoreApplication::translate("AccountsManager", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 \320\230\320\236:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccountsManager: public Ui_AccountsManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTSMANAGER_H
