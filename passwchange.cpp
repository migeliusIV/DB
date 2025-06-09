#include "passwchange.h"
#include "ui_passwchange.h"

PasswChange::PasswChange(DataBase* db, QString userLogin, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswChange)
{
    base = db;
    login = userLogin;
    ui->setupUi(this);
    ui->lblLogin->setText(login);
    ui->edtNewPassw->setEchoMode(QLineEdit::Password);
}

PasswChange::~PasswChange()
{
    delete base;
    delete ui;
}

void PasswChange::on_buttonBox_2_accepted()
{
    QString newPassword = ui->edtNewPassw->text();
    QString newPasswordConfirm = ui->edtNewPasswConfirm->text();

    if (newPasswordConfirm == newPassword && newPassword != "") {
        base->setPassword(login, newPassword);
        this->close();
    } else {
        QMessageBox::information(this, "Ошибка", "Пароли не совпадают!");
    }
}


void PasswChange::on_buttonBox_2_rejected()
{
    this->close();
}

