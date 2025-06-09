/********************************************************************************
** Form generated from reading UI file 'centrdepwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CENTRDEPWINDOW_H
#define UI_CENTRDEPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_centrdepwindow
{
public:
    QWidget *centralwidget;
    QLabel *lblUserType;
    QFrame *frame;
    QPushButton *btnStocks;
    QPushButton *btnOperations;
    QFrame *frame_2;
    QPushButton *btnStockAppend;
    QPushButton *btnStockDelete;
    QPushButton *btnOperationAppend;
    QPushButton *btnReport;
    QPushButton *btnBack;
    QLabel *label;
    QTableWidget *tblOutput;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *centrdepwindow)
    {
        if (centrdepwindow->objectName().isEmpty())
            centrdepwindow->setObjectName("centrdepwindow");
        centrdepwindow->resize(800, 600);
        centralwidget = new QWidget(centrdepwindow);
        centralwidget->setObjectName("centralwidget");
        lblUserType = new QLabel(centralwidget);
        lblUserType->setObjectName("lblUserType");
        lblUserType->setGeometry(QRect(20, 60, 121, 51));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        lblUserType->setFont(font);
        lblUserType->setAcceptDrops(false);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(190, 60, 171, 31));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        btnStocks = new QPushButton(frame);
        btnStocks->setObjectName("btnStocks");
        btnStocks->setGeometry(QRect(0, 10, 81, 21));
        btnOperations = new QPushButton(frame);
        btnOperations->setObjectName("btnOperations");
        btnOperations->setGeometry(QRect(80, 10, 91, 21));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 180, 171, 121));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        btnStockAppend = new QPushButton(frame_2);
        btnStockAppend->setObjectName("btnStockAppend");
        btnStockAppend->setGeometry(QRect(0, 0, 171, 24));
        QFont font1;
        font1.setPointSize(9);
        btnStockAppend->setFont(font1);
        btnStockAppend->setAutoRepeatDelay(333);
        btnStockDelete = new QPushButton(frame_2);
        btnStockDelete->setObjectName("btnStockDelete");
        btnStockDelete->setGeometry(QRect(0, 23, 171, 24));
        btnOperationAppend = new QPushButton(frame_2);
        btnOperationAppend->setObjectName("btnOperationAppend");
        btnOperationAppend->setGeometry(QRect(0, 46, 171, 24));
        btnReport = new QPushButton(frame_2);
        btnReport->setObjectName("btnReport");
        btnReport->setGeometry(QRect(0, 69, 171, 24));
        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");
        btnBack->setGeometry(QRect(0, 0, 81, 21));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 100, 111, 20));
        label->setFont(font);
        tblOutput = new QTableWidget(centralwidget);
        tblOutput->setObjectName("tblOutput");
        tblOutput->setGeometry(QRect(190, 90, 601, 451));
        centrdepwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(centrdepwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        centrdepwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(centrdepwindow);
        statusbar->setObjectName("statusbar");
        centrdepwindow->setStatusBar(statusbar);

        retranslateUi(centrdepwindow);

        QMetaObject::connectSlotsByName(centrdepwindow);
    } // setupUi

    void retranslateUi(QMainWindow *centrdepwindow)
    {
        centrdepwindow->setWindowTitle(QCoreApplication::translate("centrdepwindow", "MainWindow", nullptr));
        lblUserType->setText(QCoreApplication::translate("centrdepwindow", "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\321\213\320\271", nullptr));
        btnStocks->setText(QCoreApplication::translate("centrdepwindow", "\320\220\320\272\321\206\320\270\320\270", nullptr));
        btnOperations->setText(QCoreApplication::translate("centrdepwindow", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        btnStockAppend->setText(QCoreApplication::translate("centrdepwindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\246\320\221", nullptr));
        btnStockDelete->setText(QCoreApplication::translate("centrdepwindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270 \320\246\320\221", nullptr));
        btnOperationAppend->setText(QCoreApplication::translate("centrdepwindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\321\216", nullptr));
        btnReport->setText(QCoreApplication::translate("centrdepwindow", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200 \320\276\321\202\321\207\321\221\321\202\320\276\320\262", nullptr));
        btnBack->setText(QCoreApplication::translate("centrdepwindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        label->setText(QCoreApplication::translate("centrdepwindow", " \320\264\320\265\320\277\320\276\320\267\320\270\321\202\320\260\321\200\320\270\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class centrdepwindow: public Ui_centrdepwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CENTRDEPWINDOW_H
