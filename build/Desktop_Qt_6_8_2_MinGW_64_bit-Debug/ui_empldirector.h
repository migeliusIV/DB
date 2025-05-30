/********************************************************************************
** Form generated from reading UI file 'empldirector.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLDIRECTOR_H
#define UI_EMPLDIRECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmplDirector
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *btnBack;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EmplDirector)
    {
        if (EmplDirector->objectName().isEmpty())
            EmplDirector->setObjectName("EmplDirector");
        EmplDirector->resize(800, 600);
        centralwidget = new QWidget(EmplDirector);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(150, 130, 201, 24));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(150, 170, 201, 24));
        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(0, 0, 81, 21));
        EmplDirector->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EmplDirector);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        EmplDirector->setMenuBar(menubar);
        statusbar = new QStatusBar(EmplDirector);
        statusbar->setObjectName("statusbar");
        EmplDirector->setStatusBar(statusbar);

        retranslateUi(EmplDirector);

        QMetaObject::connectSlotsByName(EmplDirector);
    } // setupUi

    void retranslateUi(QMainWindow *EmplDirector)
    {
        EmplDirector->setWindowTitle(QCoreApplication::translate("EmplDirector", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("EmplDirector", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217 \320\262 \320\220\320\230\320\241", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EmplDirector", "\320\235\321\203 \320\272\320\275\320\276\320\277\320\272\320\260 \320\270 \320\272\320\275\320\276\320\277\320\272\320\260...", nullptr));
        btnBack->setText(QCoreApplication::translate("EmplDirector", "\320\235\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmplDirector: public Ui_EmplDirector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLDIRECTOR_H
