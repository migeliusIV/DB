/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(400, 262);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(120, 210, 171, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 51, 21));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 30, 181, 21));
        label_2->setFont(font);
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(20, 90, 191, 24));
        lineEdit_2 = new QLineEdit(Dialog);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(20, 160, 191, 24));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 70, 131, 16));
        QFont font1;
        font1.setPointSize(8);
        label_3->setFont(font1);
        label_4 = new QLabel(Dialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 140, 151, 16));
        label_4->setFont(font1);

        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "text", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\275\320\276\320\262\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
