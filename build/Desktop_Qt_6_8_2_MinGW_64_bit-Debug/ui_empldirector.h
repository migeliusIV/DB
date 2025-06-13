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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmplDirector
{
public:
    QWidget *centralwidget;
    QPushButton *btnAppendUser;
    QPushButton *btnRepresentUsers;
    QPushButton *btnBack;
    QLabel *label;
    QFrame *frmOutput;
    QTableWidget *tblOutput;
    QPushButton *btnDepsBrokers;
    QPushButton *btnDepsOpers;
    QPushButton *pushButton;
    QTabWidget *tabUserAppend;
    QWidget *tbBroker;
    QPushButton *btnAppendBroker;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *edtINN;
    QLineEdit *edtName;
    QLabel *label_4;
    QLineEdit *edtLoginBroker;
    QLabel *label_5;
    QLineEdit *edtPasswordBroker;
    QWidget *tbEmployee;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *edtFIO;
    QLabel *label_8;
    QLineEdit *edtPost;
    QLineEdit *edtPhone;
    QLabel *label_9;
    QLineEdit *edtSalary;
    QPushButton *btnAppendEmployee;
    QCheckBox *chkOperator;
    QFrame *frmAppendix;
    QLabel *lblInfo;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *edtLogin;
    QLineEdit *edtPassword;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EmplDirector)
    {
        if (EmplDirector->objectName().isEmpty())
            EmplDirector->setObjectName("EmplDirector");
        EmplDirector->resize(800, 600);
        centralwidget = new QWidget(EmplDirector);
        centralwidget->setObjectName("centralwidget");
        btnAppendUser = new QPushButton(centralwidget);
        btnAppendUser->setObjectName("btnAppendUser");
        btnAppendUser->setGeometry(QRect(10, 163, 175, 24));
        btnRepresentUsers = new QPushButton(centralwidget);
        btnRepresentUsers->setObjectName("btnRepresentUsers");
        btnRepresentUsers->setGeometry(QRect(10, 141, 175, 24));
        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(0, 0, 81, 21));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 40, 141, 51));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        label->setFont(font);
        frmOutput = new QFrame(centralwidget);
        frmOutput->setObjectName("frmOutput");
        frmOutput->setGeometry(QRect(195, 30, 601, 521));
        frmOutput->setFrameShape(QFrame::Shape::StyledPanel);
        frmOutput->setFrameShadow(QFrame::Shadow::Raised);
        tblOutput = new QTableWidget(frmOutput);
        tblOutput->setObjectName("tblOutput");
        tblOutput->setGeometry(QRect(0, 40, 601, 481));
        btnDepsBrokers = new QPushButton(frmOutput);
        btnDepsBrokers->setObjectName("btnDepsBrokers");
        btnDepsBrokers->setGeometry(QRect(0, 17, 80, 24));
        btnDepsOpers = new QPushButton(frmOutput);
        btnDepsOpers->setObjectName("btnDepsOpers");
        btnDepsOpers->setGeometry(QRect(78, 17, 91, 24));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 240, 175, 24));
        tabUserAppend = new QTabWidget(centralwidget);
        tabUserAppend->setObjectName("tabUserAppend");
        tabUserAppend->setGeometry(QRect(195, 45, 521, 381));
        tbBroker = new QWidget();
        tbBroker->setObjectName("tbBroker");
        btnAppendBroker = new QPushButton(tbBroker);
        btnAppendBroker->setObjectName("btnAppendBroker");
        btnAppendBroker->setGeometry(QRect(70, 130, 80, 24));
        label_2 = new QLabel(tbBroker);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 49, 16));
        label_3 = new QLabel(tbBroker);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 40, 61, 16));
        edtINN = new QLineEdit(tbBroker);
        edtINN->setObjectName("edtINN");
        edtINN->setGeometry(QRect(70, 10, 131, 24));
        edtINN->setMaxLength(10);
        edtName = new QLineEdit(tbBroker);
        edtName->setObjectName("edtName");
        edtName->setGeometry(QRect(70, 40, 131, 24));
        label_4 = new QLabel(tbBroker);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 70, 49, 16));
        edtLoginBroker = new QLineEdit(tbBroker);
        edtLoginBroker->setObjectName("edtLoginBroker");
        edtLoginBroker->setGeometry(QRect(70, 70, 131, 24));
        label_5 = new QLabel(tbBroker);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 100, 49, 16));
        edtPasswordBroker = new QLineEdit(tbBroker);
        edtPasswordBroker->setObjectName("edtPasswordBroker");
        edtPasswordBroker->setGeometry(QRect(70, 100, 131, 24));
        tabUserAppend->addTab(tbBroker, QString());
        tbEmployee = new QWidget();
        tbEmployee->setObjectName("tbEmployee");
        label_6 = new QLabel(tbEmployee);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 100, 71, 16));
        label_7 = new QLabel(tbEmployee);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 10, 81, 16));
        edtFIO = new QLineEdit(tbEmployee);
        edtFIO->setObjectName("edtFIO");
        edtFIO->setGeometry(QRect(100, 10, 131, 24));
        label_8 = new QLabel(tbEmployee);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 40, 61, 16));
        edtPost = new QLineEdit(tbEmployee);
        edtPost->setObjectName("edtPost");
        edtPost->setGeometry(QRect(100, 100, 131, 24));
        edtPhone = new QLineEdit(tbEmployee);
        edtPhone->setObjectName("edtPhone");
        edtPhone->setGeometry(QRect(100, 40, 131, 24));
        edtPhone->setMaxLength(11);
        label_9 = new QLabel(tbEmployee);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 70, 61, 16));
        edtSalary = new QLineEdit(tbEmployee);
        edtSalary->setObjectName("edtSalary");
        edtSalary->setGeometry(QRect(100, 70, 131, 24));
        btnAppendEmployee = new QPushButton(tbEmployee);
        btnAppendEmployee->setObjectName("btnAppendEmployee");
        btnAppendEmployee->setGeometry(QRect(100, 130, 80, 24));
        chkOperator = new QCheckBox(tbEmployee);
        chkOperator->setObjectName("chkOperator");
        chkOperator->setGeometry(QRect(240, 100, 111, 22));
        frmAppendix = new QFrame(tbEmployee);
        frmAppendix->setObjectName("frmAppendix");
        frmAppendix->setGeometry(QRect(-1, 161, 521, 191));
        frmAppendix->setFrameShape(QFrame::Shape::StyledPanel);
        frmAppendix->setFrameShadow(QFrame::Shadow::Raised);
        lblInfo = new QLabel(frmAppendix);
        lblInfo->setObjectName("lblInfo");
        lblInfo->setGeometry(QRect(10, 10, 391, 16));
        label_10 = new QLabel(frmAppendix);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 36, 131, 16));
        label_11 = new QLabel(frmAppendix);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 90, 131, 16));
        edtLogin = new QLineEdit(frmAppendix);
        edtLogin->setObjectName("edtLogin");
        edtLogin->setGeometry(QRect(10, 56, 151, 24));
        edtPassword = new QLineEdit(frmAppendix);
        edtPassword->setObjectName("edtPassword");
        edtPassword->setGeometry(QRect(10, 110, 151, 24));
        tabUserAppend->addTab(tbEmployee, QString());
        EmplDirector->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EmplDirector);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        EmplDirector->setMenuBar(menubar);
        statusbar = new QStatusBar(EmplDirector);
        statusbar->setObjectName("statusbar");
        EmplDirector->setStatusBar(statusbar);

        retranslateUi(EmplDirector);

        tabUserAppend->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EmplDirector);
    } // setupUi

    void retranslateUi(QMainWindow *EmplDirector)
    {
        EmplDirector->setWindowTitle(QCoreApplication::translate("EmplDirector", "MainWindow", nullptr));
        btnAppendUser->setText(QCoreApplication::translate("EmplDirector", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217 \320\262 \320\220\320\230\320\241", nullptr));
        btnRepresentUsers->setText(QCoreApplication::translate("EmplDirector", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\265\320\271 \320\220\320\230\320\241", nullptr));
        btnBack->setText(QCoreApplication::translate("EmplDirector", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        label->setText(QCoreApplication::translate("EmplDirector", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200 \n"
"    \320\264\320\265\320\277\320\276\320\267\320\270\321\202\320\260\321\200\320\270\321\217", nullptr));
        btnDepsBrokers->setText(QCoreApplication::translate("EmplDirector", "\320\221\321\200\320\276\320\272\320\265\321\200\321\213", nullptr));
        btnDepsOpers->setText(QCoreApplication::translate("EmplDirector", "\320\241\320\276\321\202\321\200\321\203\320\264\320\275\320\270\320\272\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("EmplDirector", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217 \320\270\320\267 \320\220\320\230\320\241", nullptr));
        btnAppendBroker->setText(QCoreApplication::translate("EmplDirector", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("EmplDirector", "\320\230\320\235\320\235:", nullptr));
        label_3->setText(QCoreApplication::translate("EmplDirector", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", nullptr));
        label_4->setText(QCoreApplication::translate("EmplDirector", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
        label_5->setText(QCoreApplication::translate("EmplDirector", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        tabUserAppend->setTabText(tabUserAppend->indexOf(tbBroker), QCoreApplication::translate("EmplDirector", "\320\221\321\200\320\276\320\272\320\265\321\200", nullptr));
        label_6->setText(QCoreApplication::translate("EmplDirector", "\320\224\320\276\320\273\320\266\320\275\320\276\321\201\321\202\321\214:", nullptr));
        label_7->setText(QCoreApplication::translate("EmplDirector", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 \320\230.\320\236.:", nullptr));
        edtFIO->setText(QCoreApplication::translate("EmplDirector", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 C.C.", nullptr));
        label_8->setText(QCoreApplication::translate("EmplDirector", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275:", nullptr));
        edtPhone->setText(QCoreApplication::translate("EmplDirector", "70001112233", nullptr));
        label_9->setText(QCoreApplication::translate("EmplDirector", "\320\227\320\260\321\200\320\277\320\273\320\260\321\202\320\260:", nullptr));
        btnAppendEmployee->setText(QCoreApplication::translate("EmplDirector", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        chkOperator->setText(QCoreApplication::translate("EmplDirector", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\276\320\275\320\270\321\201\321\202", nullptr));
        lblInfo->setText(QCoreApplication::translate("EmplDirector", "\320\224\320\273\321\217 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\276\320\275\320\270\321\201\321\202\320\260 \320\275\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274\320\276 \321\202\320\260\320\272\320\266\320\265 \321\203\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\265 \321\201\320\262\320\265\320\264\320\265\320\275\320\270\321\217:", nullptr));
        label_10->setText(QCoreApplication::translate("EmplDirector", "\320\233\320\276\320\263\320\270\320\275 \321\203\321\207\321\221\321\202\320\275\320\276\320\271 \320\267\320\260\320\277\320\270\321\201\320\270:", nullptr));
        label_11->setText(QCoreApplication::translate("EmplDirector", "\320\237\320\260\321\200\320\276\320\273\321\214 \321\203\321\207\321\221\321\202\320\275\320\276\320\271 \320\267\320\260\320\277\320\270\321\201\320\270:", nullptr));
        tabUserAppend->setTabText(tabUserAppend->indexOf(tbEmployee), QCoreApplication::translate("EmplDirector", "\320\241\320\276\321\202\321\200\321\203\320\264\320\275\320\270\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmplDirector: public Ui_EmplDirector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLDIRECTOR_H
