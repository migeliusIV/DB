/********************************************************************************
** Form generated from reading UI file 'passwchange.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWCHANGE_H
#define UI_PASSWCHANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_PasswChange
{
public:
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_4;
    QDialogButtonBox *buttonBox_2;
    QLabel *label;

    void setupUi(QDialog *PasswChange)
    {
        if (PasswChange->objectName().isEmpty())
            PasswChange->setObjectName("PasswChange");
        PasswChange->resize(400, 253);
        label_2 = new QLabel(PasswChange);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 30, 181, 21));
        QFont font;
        font.setPointSize(11);
        label_2->setFont(font);
        lineEdit = new QLineEdit(PasswChange);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(100, 90, 191, 24));
        lineEdit_2 = new QLineEdit(PasswChange);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(100, 160, 191, 24));
        label_3 = new QLabel(PasswChange);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(100, 70, 131, 16));
        QFont font1;
        font1.setPointSize(8);
        label_3->setFont(font1);
        label_4 = new QLabel(PasswChange);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(100, 140, 151, 16));
        label_4->setFont(font1);
        buttonBox_2 = new QDialogButtonBox(PasswChange);
        buttonBox_2->setObjectName("buttonBox_2");
        buttonBox_2->setGeometry(QRect(110, 200, 171, 32));
        buttonBox_2->setOrientation(Qt::Orientation::Horizontal);
        buttonBox_2->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(PasswChange);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 30, 51, 21));
        label->setFont(font);

        retranslateUi(PasswChange);

        QMetaObject::connectSlotsByName(PasswChange);
    } // setupUi

    void retranslateUi(QDialog *PasswChange)
    {
        PasswChange->setWindowTitle(QCoreApplication::translate("PasswChange", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("PasswChange", "text", nullptr));
        label_3->setText(QCoreApplication::translate("PasswChange", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("PasswChange", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\275\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        label->setText(QCoreApplication::translate("PasswChange", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswChange: public Ui_PasswChange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWCHANGE_H
