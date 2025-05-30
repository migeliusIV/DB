/********************************************************************************
** Form generated from reading UI file 'emploperator.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOPERATOR_H
#define UI_EMPLOPERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmplOperator
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QWidget *tab_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *btnBack;
    QFrame *frmInfo;
    QLabel *lblCompanyName;
    QLabel *lnlINN;
    QLabel *lblINNTxt;
    QLabel *lblCompanyNameTxt;
    QPushButton *btnUserChanges;
    QLabel *lblUserInfo;
    QLabel *lblAppendix;
    QLabel *lblAccounts;
    QLabel *lblAccountTxt;
    QLabel *lblCheckTxt;
    QLabel *lblCkecks;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EmplOperator)
    {
        if (EmplOperator->objectName().isEmpty())
            EmplOperator->setObjectName("EmplOperator");
        EmplOperator->resize(800, 600);
        centralwidget = new QWidget(EmplOperator);
        centralwidget->setObjectName("centralwidget");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 200, 761, 341));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 130, 761, 71));
        tab = new QWidget();
        tab->setObjectName("tab");
        pushButton_4 = new QPushButton(tab);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(0, 0, 80, 24));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(0, 20, 80, 24));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(0, 0, 61, 24));
        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(0, 20, 61, 24));
        tabWidget->addTab(tab_2, QString());
        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(0, 0, 81, 21));
        frmInfo = new QFrame(centralwidget);
        frmInfo->setObjectName("frmInfo");
        frmInfo->setGeometry(QRect(140, 10, 421, 111));
        frmInfo->setFrameShape(QFrame::Shape::StyledPanel);
        frmInfo->setFrameShadow(QFrame::Shadow::Raised);
        lblCompanyName = new QLabel(frmInfo);
        lblCompanyName->setObjectName("lblCompanyName");
        lblCompanyName->setGeometry(QRect(0, 32, 61, 16));
        lnlINN = new QLabel(frmInfo);
        lnlINN->setObjectName("lnlINN");
        lnlINN->setGeometry(QRect(0, 52, 111, 16));
        lblINNTxt = new QLabel(frmInfo);
        lblINNTxt->setObjectName("lblINNTxt");
        lblINNTxt->setGeometry(QRect(110, 50, 81, 20));
        lblCompanyNameTxt = new QLabel(frmInfo);
        lblCompanyNameTxt->setObjectName("lblCompanyNameTxt");
        lblCompanyNameTxt->setGeometry(QRect(32, 30, 151, 20));
        btnUserChanges = new QPushButton(frmInfo);
        btnUserChanges->setObjectName("btnUserChanges");
        btnUserChanges->setGeometry(QRect(0, 72, 111, 24));
        lblUserInfo = new QLabel(frmInfo);
        lblUserInfo->setObjectName("lblUserInfo");
        lblUserInfo->setGeometry(QRect(0, 10, 171, 16));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        lblUserInfo->setFont(font);
        lblAppendix = new QLabel(frmInfo);
        lblAppendix->setObjectName("lblAppendix");
        lblAppendix->setGeometry(QRect(240, 9, 121, 16));
        lblAppendix->setFont(font);
        lblAccounts = new QLabel(frmInfo);
        lblAccounts->setObjectName("lblAccounts");
        lblAccounts->setGeometry(QRect(240, 30, 101, 20));
        lblAccountTxt = new QLabel(frmInfo);
        lblAccountTxt->setObjectName("lblAccountTxt");
        lblAccountTxt->setGeometry(QRect(320, 32, 49, 16));
        lblAccountTxt->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lblCheckTxt = new QLabel(frmInfo);
        lblCheckTxt->setObjectName("lblCheckTxt");
        lblCheckTxt->setGeometry(QRect(320, 50, 49, 16));
        lblCheckTxt->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lblCkecks = new QLabel(frmInfo);
        lblCkecks->setObjectName("lblCkecks");
        lblCkecks->setGeometry(QRect(240, 48, 101, 20));
        EmplOperator->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EmplOperator);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        EmplOperator->setMenuBar(menubar);
        statusbar = new QStatusBar(EmplOperator);
        statusbar->setObjectName("statusbar");
        EmplOperator->setStatusBar(statusbar);

        retranslateUi(EmplOperator);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EmplOperator);
    } // setupUi

    void retranslateUi(QMainWindow *EmplOperator)
    {
        EmplOperator->setWindowTitle(QCoreApplication::translate("EmplOperator", "MainWindow", nullptr));
        pushButton_4->setText(QCoreApplication::translate("EmplOperator", "\320\222\321\201\320\265", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EmplOperator", "\320\235\320\276\320\262\321\213\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EmplOperator", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        pushButton_3->setText(QCoreApplication::translate("EmplOperator", "\320\222\321\201\320\265", nullptr));
        pushButton_5->setText(QCoreApplication::translate("EmplOperator", "\320\235\320\276\320\262\321\213\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EmplOperator", "\320\241\321\207\320\265\321\202\320\260", nullptr));
        btnBack->setText(QCoreApplication::translate("EmplOperator", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        lblCompanyName->setText(QCoreApplication::translate("EmplOperator", "\320\244\320\230\320\236:", nullptr));
        lnlINN->setText(QCoreApplication::translate("EmplOperator", "\320\242\320\260\320\261\320\265\320\273\321\214\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200:", nullptr));
        lblINNTxt->setText(QCoreApplication::translate("EmplOperator", "TextLabel", nullptr));
        lblCompanyNameTxt->setText(QCoreApplication::translate("EmplOperator", "TextLabel", nullptr));
        btnUserChanges->setText(QCoreApplication::translate("EmplOperator", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        lblUserInfo->setText(QCoreApplication::translate("EmplOperator", "\320\224\320\260\320\275\320\275\321\213\320\265 \320\276 \321\201\320\276\321\202\321\200\321\203\320\264\320\275\320\270\320\272\320\265:", nullptr));
        lblAppendix->setText(QCoreApplication::translate("EmplOperator", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\320\276:", nullptr));
        lblAccounts->setText(QCoreApplication::translate("EmplOperator", "\320\236\321\202\320\272\321\200\321\213\321\202\321\213\321\205 \321\201\321\207\320\265\321\202\320\276\320\262:", nullptr));
        lblAccountTxt->setText(QCoreApplication::translate("EmplOperator", "0", nullptr));
        lblCheckTxt->setText(QCoreApplication::translate("EmplOperator", "0", nullptr));
        lblCkecks->setText(QCoreApplication::translate("EmplOperator", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\321\213\321\205 \321\207\320\265\320\272\320\276\320\262:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmplOperator: public Ui_EmplOperator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOPERATOR_H
