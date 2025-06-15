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
#include <QtWidgets/QComboBox>
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
    QTableWidget *tblOutput;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *btnDealsAll;
    QPushButton *btnDealsNew;
    QComboBox *comboBox;
    QLabel *label_3;
    QPushButton *btnDealReject;
    QPushButton *btnDealAccept;
    QWidget *tab_2;
    QPushButton *btnAccntsAll;
    QPushButton *btnAccntsNew;
    QComboBox *comboBox_2;
    QPushButton *btnRejectAccount;
    QWidget *tab_3;
    QPushButton *btnDealsNew_3;
    QPushButton *btnStocksAll;
    QPushButton *btnStocksNew;
    QFrame *frmInfo;
    QLabel *lblCompanyName;
    QLabel *lnlINN;
    QLabel *lblPhone;
    QLabel *lblFIO;
    QPushButton *btnUserChanges;
    QLabel *lblUserInfo;
    QPushButton *btnBack_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EmplOperator)
    {
        if (EmplOperator->objectName().isEmpty())
            EmplOperator->setObjectName("EmplOperator");
        EmplOperator->resize(800, 600);
        centralwidget = new QWidget(EmplOperator);
        centralwidget->setObjectName("centralwidget");
        tblOutput = new QTableWidget(centralwidget);
        tblOutput->setObjectName("tblOutput");
        tblOutput->setGeometry(QRect(20, 208, 771, 341));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 128, 771, 81));
        tab = new QWidget();
        tab->setObjectName("tab");
        btnDealsAll = new QPushButton(tab);
        btnDealsAll->setObjectName("btnDealsAll");
        btnDealsAll->setGeometry(QRect(0, 4, 80, 24));
        btnDealsNew = new QPushButton(tab);
        btnDealsNew->setObjectName("btnDealsNew");
        btnDealsNew->setGeometry(QRect(0, 26, 80, 24));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(370, 25, 81, 24));
        comboBox->setEditable(true);
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(111, 28, 261, 16));
        btnDealReject = new QPushButton(tab);
        btnDealReject->setObjectName("btnDealReject");
        btnDealReject->setGeometry(QRect(450, 25, 71, 24));
        btnDealAccept = new QPushButton(tab);
        btnDealAccept->setObjectName("btnDealAccept");
        btnDealAccept->setGeometry(QRect(520, 25, 71, 24));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        btnAccntsAll = new QPushButton(tab_2);
        btnAccntsAll->setObjectName("btnAccntsAll");
        btnAccntsAll->setGeometry(QRect(0, 4, 80, 24));
        btnAccntsNew = new QPushButton(tab_2);
        btnAccntsNew->setObjectName("btnAccntsNew");
        btnAccntsNew->setGeometry(QRect(0, 26, 80, 24));
        comboBox_2 = new QComboBox(tab_2);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(111, 25, 121, 24));
        comboBox_2->setEditable(true);
        btnRejectAccount = new QPushButton(tab_2);
        btnRejectAccount->setObjectName("btnRejectAccount");
        btnRejectAccount->setGeometry(QRect(232, 22, 80, 28));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        btnDealsNew_3 = new QPushButton(tab_3);
        btnDealsNew_3->setObjectName("btnDealsNew_3");
        btnDealsNew_3->setGeometry(QRect(0, 4, 80, 24));
        btnStocksAll = new QPushButton(tab_3);
        btnStocksAll->setObjectName("btnStocksAll");
        btnStocksAll->setGeometry(QRect(0, 4, 80, 24));
        btnStocksNew = new QPushButton(tab_3);
        btnStocksNew->setObjectName("btnStocksNew");
        btnStocksNew->setGeometry(QRect(0, 26, 80, 24));
        tabWidget->addTab(tab_3, QString());
        frmInfo = new QFrame(centralwidget);
        frmInfo->setObjectName("frmInfo");
        frmInfo->setGeometry(QRect(290, 10, 211, 111));
        frmInfo->setFrameShape(QFrame::Shape::StyledPanel);
        frmInfo->setFrameShadow(QFrame::Shadow::Raised);
        lblCompanyName = new QLabel(frmInfo);
        lblCompanyName->setObjectName("lblCompanyName");
        lblCompanyName->setGeometry(QRect(0, 32, 61, 16));
        lnlINN = new QLabel(frmInfo);
        lnlINN->setObjectName("lnlINN");
        lnlINN->setGeometry(QRect(0, 52, 121, 16));
        lblPhone = new QLabel(frmInfo);
        lblPhone->setObjectName("lblPhone");
        lblPhone->setGeometry(QRect(120, 50, 81, 20));
        lblFIO = new QLabel(frmInfo);
        lblFIO->setObjectName("lblFIO");
        lblFIO->setGeometry(QRect(32, 30, 141, 20));
        lblFIO->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        btnUserChanges = new QPushButton(frmInfo);
        btnUserChanges->setObjectName("btnUserChanges");
        btnUserChanges->setGeometry(QRect(50, 70, 111, 24));
        lblUserInfo = new QLabel(frmInfo);
        lblUserInfo->setObjectName("lblUserInfo");
        lblUserInfo->setGeometry(QRect(0, 10, 211, 16));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        lblUserInfo->setFont(font);
        btnBack_2 = new QPushButton(centralwidget);
        btnBack_2->setObjectName("btnBack_2");
        btnBack_2->setGeometry(QRect(0, 0, 81, 21));
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
        btnDealsAll->setText(QCoreApplication::translate("EmplOperator", "\320\222\321\201\320\265", nullptr));
        btnDealsNew->setText(QCoreApplication::translate("EmplOperator", "\320\235\320\276\320\262\321\213\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("EmplOperator", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\265\321\211\321\221 \320\275\320\265 \321\200\320\260\321\201\321\201\320\274\320\276\321\202\321\200\320\265\320\275\320\275\321\203\321\216 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\321\216:", nullptr));
        btnDealReject->setText(QCoreApplication::translate("EmplOperator", "\320\236\321\202\320\273\320\276\320\266\320\270\321\202\321\214", nullptr));
        btnDealAccept->setText(QCoreApplication::translate("EmplOperator", "\320\236\320\264\320\276\320\261\321\200\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("EmplOperator", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        btnAccntsAll->setText(QCoreApplication::translate("EmplOperator", "\320\222\321\201\320\265", nullptr));
        btnAccntsNew->setText(QCoreApplication::translate("EmplOperator", "\320\235\320\276\320\262\321\213\320\265", nullptr));
        btnRejectAccount->setText(QCoreApplication::translate("EmplOperator", "\320\236\321\202\320\272\320\273\320\276\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("EmplOperator", "\320\241\321\207\320\265\321\202\320\260", nullptr));
        btnDealsNew_3->setText(QCoreApplication::translate("EmplOperator", "\320\235\320\276\320\262\321\213\320\265", nullptr));
        btnStocksAll->setText(QCoreApplication::translate("EmplOperator", "\320\222\321\201\320\265", nullptr));
        btnStocksNew->setText(QCoreApplication::translate("EmplOperator", "\320\235\320\276\320\262\321\213\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("EmplOperator", "\320\246\320\265\320\275\320\275\321\213\320\265 \320\261\321\203\320\274\320\260\320\263\320\270", nullptr));
        lblCompanyName->setText(QCoreApplication::translate("EmplOperator", "\320\244\320\230\320\236:", nullptr));
        lnlINN->setText(QCoreApplication::translate("EmplOperator", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200:", nullptr));
        lblPhone->setText(QCoreApplication::translate("EmplOperator", "TextLabel", nullptr));
        lblFIO->setText(QCoreApplication::translate("EmplOperator", "TextLabel", nullptr));
        btnUserChanges->setText(QCoreApplication::translate("EmplOperator", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        lblUserInfo->setText(QCoreApplication::translate("EmplOperator", "\320\224\320\260\320\275\320\275\321\213\320\265 \320\276\320\261 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\276\320\275\320\270\321\201\321\202\320\265:", nullptr));
        btnBack_2->setText(QCoreApplication::translate("EmplOperator", "\320\235\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmplOperator: public Ui_EmplOperator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOPERATOR_H
