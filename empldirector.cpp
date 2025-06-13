#include "empldirector.h"
#include "ui_empldirector.h"

#include "mainwindow.h"

EmplDirector::EmplDirector(DataBase* temp, QString strLogin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmplDirector)
{
    ui->setupUi(this);
    login = strLogin;
    setDataBase(temp);
    ui->frmOutput->hide();
    ui->tabUserAppend->hide();
}

EmplDirector::~EmplDirector()
{
    delete ui;
    delete base;
}

void EmplDirector::on_btnBack_clicked()
{
    MainWindow *window = new MainWindow(getDataBase());
    window->show();
    this->close();
}


void EmplDirector::on_btnRepresentUsers_clicked()
{
    if (ui->tabUserAppend->isVisible())
        ui->tabUserAppend->hide();
    if (!ui->frmOutput->isVisible())
        ui->frmOutput->show();
}


void EmplDirector::on_btnAppendUser_clicked()
{
    if (ui->frmOutput->isVisible())
        ui->frmOutput->hide();
    if (!ui->tabUserAppend->isVisible()) {
        // чистка полей "брокера"
        ui->edtINN->clear();
        ui->edtName->clear();
        ui->edtLoginBroker->clear();
        ui->edtPasswordBroker->clear();
        // чистка полей "сотрудника"
        ui->edtFIO->setText("Иванов C.C.");
        ui->edtPhone->setText("70001112233");
        ui->edtPost->clear();
        ui->edtSalary->clear();
        ui->edtLogin->clear();
        ui->edtPassword->clear();
        // отображение
        ui->tabUserAppend->show();
        ui->frmAppendix->hide();
    }
}


void EmplDirector::on_btnDepsBrokers_clicked()
{
    base->loadDirectBrokersToTable(ui->tblOutput);
}


void EmplDirector::on_btnDepsOpers_clicked()
{
    base->loadDirectEmployeesToTable(ui->tblOutput);
}


void EmplDirector::on_btnAppendBroker_clicked()
{
    // обработка данных
    QString INN = ui->edtINN->text();
    QString name = ui->edtName->text();
    QString login = ui->edtLoginBroker->text();
    QString password = ui->edtPasswordBroker->text();
    // проверка данных
    if (INN == "" || name == "" || login == "" || password == "") {
        QMessageBox::warning(this, "Ошибка", "Есть незаполненные данные!");
        return;
    }
    // заполнение таблицы
    // Создаем диалог подтверждения
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение изнений",
                                  QString("Вы уверены в правильности внесённых данных?\nЭто действие нельзя отменить."),
                                  QMessageBox::Yes | QMessageBox::No);

    // Если пользователь подтвердил изменения
    if (reply == QMessageBox::Yes) {
        QString funcRes = base->appendDirectorsBroker(INN, name, login, password);
        if (funcRes != "Успех")
            QMessageBox::warning(this, "Ошибка", funcRes);
        else
            QMessageBox::information(this, "Успешно", "Брокер добавлен");
    }
}


void EmplDirector::on_btnAppendEmployee_clicked()
{
    // обработка данных
    QString FIO = ui->edtFIO->text();
    QString phone = ui->edtPhone->text();
    QString salary = ui->edtSalary->text();
    QString post;
    QString login = "";
    QString password = "";
    if (!ui->chkOperator->isChecked()) {
        post = ui->edtPost->text();
        if (FIO == "Иванов C.C." || phone == "70001112233" || post == "" || salary == "") {
            QMessageBox::warning(this, "Ошибка", "Укажите все данные! Не забудьте поменять телефонный номер!");
            return;
        }
    } else {
        post = "Операционист";
        login = ui->edtLogin->text();
        password = ui->edtPassword->text();

        if (FIO == "Иванов C.C." || phone == "70001112233" || post == "" || salary == "" || login == "" || password == "") {
            QMessageBox::warning(this, "Ошибка", "Укажите все данные! Не забудьте поменять телефонный номер!");
            return;
        }
    }
    // Создаем диалог подтверждения
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение изнений",
                                  QString("Вы уверены в правильности внесённых данных?\nЭто действие нельзя отменить."),
                                  QMessageBox::Yes | QMessageBox::No);

    // Если пользователь подтвердил изменения
    if (reply == QMessageBox::Yes) {
        QString funcRes = base->appendDirectorsEmployee(FIO, phone, salary, post, login, password);
        if (funcRes != "Успех")
            QMessageBox::warning(this, "Ошибка", funcRes);
        else
            QMessageBox::information(this, "Успешно", "Сотрудник добавлен");
    }
}

void EmplDirector::on_chkOperator_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1) {
        ui->frmAppendix->show();
        ui->edtPost->setDisabled(true);
    } else {
        ui->frmAppendix->hide();
        ui->edtPost->setDisabled(false);
    }
}
