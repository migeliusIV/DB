/********************************************************************************
** Form generated from reading UI file 'broker.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROKER_H
#define UI_BROKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Broker
{
public:
    QWidget *centralwidget;
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
    QLabel *label_3;
    QPushButton *btnAccountDel;
    QPushButton *btnAccountAppend;
    QPushButton *btnReports;
    QFrame *frmOutput;
    QTextEdit *teOutput;
    QPushButton *btnOperations;
    QPushButton *btnAccounts;
    QPushButton *btnStocks;
    QFrame *frmSearch;
    QLabel *lblSearch;
    QLineEdit *edtSearhing;
    QPushButton *btnSearch;
    QPushButton *btnBack;
    QFontComboBox *fontComboBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Broker)
    {
        if (Broker->objectName().isEmpty())
            Broker->setObjectName("Broker");
        Broker->resize(800, 600);
        centralwidget = new QWidget(Broker);
        centralwidget->setObjectName("centralwidget");
        frmInfo = new QFrame(centralwidget);
        frmInfo->setObjectName("frmInfo");
        frmInfo->setGeometry(QRect(20, 50, 231, 331));
        frmInfo->setFrameShape(QFrame::Shape::StyledPanel);
        frmInfo->setFrameShadow(QFrame::Shadow::Raised);
        lblCompanyName = new QLabel(frmInfo);
        lblCompanyName->setObjectName("lblCompanyName");
        lblCompanyName->setGeometry(QRect(0, 32, 61, 16));
        lnlINN = new QLabel(frmInfo);
        lnlINN->setObjectName("lnlINN");
        lnlINN->setGeometry(QRect(0, 52, 49, 16));
        lblINNTxt = new QLabel(frmInfo);
        lblINNTxt->setObjectName("lblINNTxt");
        lblINNTxt->setGeometry(QRect(60, 52, 131, 16));
        lblCompanyNameTxt = new QLabel(frmInfo);
        lblCompanyNameTxt->setObjectName("lblCompanyNameTxt");
        lblCompanyNameTxt->setGeometry(QRect(60, 32, 131, 16));
        btnUserChanges = new QPushButton(frmInfo);
        btnUserChanges->setObjectName("btnUserChanges");
        btnUserChanges->setGeometry(QRect(0, 72, 111, 24));
        lblUserInfo = new QLabel(frmInfo);
        lblUserInfo->setObjectName("lblUserInfo");
        lblUserInfo->setGeometry(QRect(0, 10, 141, 16));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        lblUserInfo->setFont(font);
        lblAppendix = new QLabel(frmInfo);
        lblAppendix->setObjectName("lblAppendix");
        lblAppendix->setGeometry(QRect(0, 118, 121, 16));
        lblAppendix->setFont(font);
        lblAccounts = new QLabel(frmInfo);
        lblAccounts->setObjectName("lblAccounts");
        lblAccounts->setGeometry(QRect(0, 138, 101, 20));
        lblAccountTxt = new QLabel(frmInfo);
        lblAccountTxt->setObjectName("lblAccountTxt");
        lblAccountTxt->setGeometry(QRect(80, 140, 49, 16));
        lblAccountTxt->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lblCheckTxt = new QLabel(frmInfo);
        lblCheckTxt->setObjectName("lblCheckTxt");
        lblCheckTxt->setGeometry(QRect(80, 158, 49, 16));
        lblCheckTxt->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lblCkecks = new QLabel(frmInfo);
        lblCkecks->setObjectName("lblCkecks");
        lblCkecks->setGeometry(QRect(0, 156, 101, 20));
        label_3 = new QLabel(frmInfo);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 207, 51, 21));
        label_3->setFont(font);
        btnAccountDel = new QPushButton(frmInfo);
        btnAccountDel->setObjectName("btnAccountDel");
        btnAccountDel->setGeometry(QRect(0, 260, 171, 24));
        btnAccountAppend = new QPushButton(frmInfo);
        btnAccountAppend->setObjectName("btnAccountAppend");
        btnAccountAppend->setGeometry(QRect(0, 237, 171, 24));
        btnReports = new QPushButton(frmInfo);
        btnReports->setObjectName("btnReports");
        btnReports->setGeometry(QRect(0, 283, 171, 24));
        frmOutput = new QFrame(centralwidget);
        frmOutput->setObjectName("frmOutput");
        frmOutput->setGeometry(QRect(320, 20, 471, 501));
        frmOutput->setFrameShape(QFrame::Shape::StyledPanel);
        frmOutput->setFrameShadow(QFrame::Shadow::Raised);
        teOutput = new QTextEdit(frmOutput);
        teOutput->setObjectName("teOutput");
        teOutput->setGeometry(QRect(0, 23, 471, 481));
        btnOperations = new QPushButton(frmOutput);
        btnOperations->setObjectName("btnOperations");
        btnOperations->setGeometry(QRect(0, 0, 80, 24));
        btnAccounts = new QPushButton(frmOutput);
        btnAccounts->setObjectName("btnAccounts");
        btnAccounts->setGeometry(QRect(79, 0, 80, 24));
        btnStocks = new QPushButton(frmOutput);
        btnStocks->setObjectName("btnStocks");
        btnStocks->setGeometry(QRect(158, 0, 101, 24));
        frmSearch = new QFrame(centralwidget);
        frmSearch->setObjectName("frmSearch");
        frmSearch->setGeometry(QRect(320, 521, 381, 31));
        frmSearch->setFrameShape(QFrame::Shape::StyledPanel);
        frmSearch->setFrameShadow(QFrame::Shadow::Raised);
        lblSearch = new QLabel(frmSearch);
        lblSearch->setObjectName("lblSearch");
        lblSearch->setGeometry(QRect(0, 0, 111, 24));
        edtSearhing = new QLineEdit(frmSearch);
        edtSearhing->setObjectName("edtSearhing");
        edtSearhing->setGeometry(QRect(104, 0, 191, 24));
        btnSearch = new QPushButton(frmSearch);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setGeometry(QRect(294, -1, 80, 26));
        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(0, 0, 81, 21));
        fontComboBox = new QFontComboBox(centralwidget);
        fontComboBox->setObjectName("fontComboBox");
        fontComboBox->setGeometry(QRect(710, 530, 81, 21));
        Broker->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Broker);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Broker->setMenuBar(menubar);
        statusbar = new QStatusBar(Broker);
        statusbar->setObjectName("statusbar");
        Broker->setStatusBar(statusbar);

        retranslateUi(Broker);

        QMetaObject::connectSlotsByName(Broker);
    } // setupUi

    void retranslateUi(QMainWindow *Broker)
    {
        Broker->setWindowTitle(QCoreApplication::translate("Broker", "MainWindow", nullptr));
        lblCompanyName->setText(QCoreApplication::translate("Broker", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", nullptr));
        lnlINN->setText(QCoreApplication::translate("Broker", "\320\230\320\235\320\235:", nullptr));
        lblINNTxt->setText(QCoreApplication::translate("Broker", "TextLabel", nullptr));
        lblCompanyNameTxt->setText(QCoreApplication::translate("Broker", "TextLabel", nullptr));
        btnUserChanges->setText(QCoreApplication::translate("Broker", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        lblUserInfo->setText(QCoreApplication::translate("Broker", "\320\224\320\260\320\275\320\275\321\213\320\265 \320\276 \320\261\321\200\320\276\320\272\320\265\321\200\320\265:", nullptr));
        lblAppendix->setText(QCoreApplication::translate("Broker", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\320\276:", nullptr));
        lblAccounts->setText(QCoreApplication::translate("Broker", "\320\236\321\202\320\272\321\200\321\213\321\202\321\213\321\205 \321\201\321\207\320\265\321\202\320\276\320\262:", nullptr));
        lblAccountTxt->setText(QCoreApplication::translate("Broker", "0", nullptr));
        lblCheckTxt->setText(QCoreApplication::translate("Broker", "0", nullptr));
        lblCkecks->setText(QCoreApplication::translate("Broker", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\321\213\321\205 \321\207\320\265\320\272\320\276\320\262:", nullptr));
        label_3->setText(QCoreApplication::translate("Broker", "\320\234\320\265\320\275\321\216", nullptr));
        btnAccountDel->setText(QCoreApplication::translate("Broker", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \321\201\321\207\321\221\321\202", nullptr));
        btnAccountAppend->setText(QCoreApplication::translate("Broker", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\201\321\207\321\221\321\202", nullptr));
        btnReports->setText(QCoreApplication::translate("Broker", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\207\320\265\320\272\320\270 (\320\276\321\202\321\207\321\221\321\202\321\213)", nullptr));
        btnOperations->setText(QCoreApplication::translate("Broker", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        btnAccounts->setText(QCoreApplication::translate("Broker", "\320\241\321\207\320\265\321\202\320\260", nullptr));
        btnStocks->setText(QCoreApplication::translate("Broker", "\320\246\320\265\320\275\320\275\321\213\320\265 \320\261\321\203\320\274\320\260\320\263\320\270", nullptr));
        lblSearch->setText(QCoreApplication::translate("Broker", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \342\204\226\321\201\321\207\321\221\321\202\320\260:", nullptr));
        btnSearch->setText(QCoreApplication::translate("Broker", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        btnBack->setText(QCoreApplication::translate("Broker", "\320\235\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Broker: public Ui_Broker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROKER_H
