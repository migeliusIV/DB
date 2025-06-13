#include "empldirector.h"
#include "ui_empldirector.h"

#include "mainwindow.h"

EmplDirector::EmplDirector(DataBase* temp, QString strLogin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmplDirector)
{
    ui->setupUi(this);
    login = strLogin;
    outputMode = 0;
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
    if (ui->frmOutput->isVisible()){
        ui->frmOutput->hide();
        outputMode = 0;
    }
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
    outputMode = 1;
    base->loadDirectBrokersToTable(ui->tblOutput);
}


void EmplDirector::on_btnDepsOpers_clicked()
{
    outputMode = 2;
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

void EmplDirector::on_btnDeleteUser_clicked()
{
    // Получаем таблицу из интерфейса
    QTableWidget* table = ui->tblOutput;

    // Проверяем, есть ли выбранные строки
    if (table->selectedItems().isEmpty() || outputMode == 0) {
        QMessageBox::warning(this, "Ошибка", "Не выбрана ни одна строка!");
        return;
    }

    // Создаем диалог подтверждения
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение изнений",
                                  QString("Вы уверены, что хотите удалить пользователя?\nЭто действие нельзя отменить."),
                                  QMessageBox::Yes | QMessageBox::No);

    // Если пользователь подтвердил изменения
    if (reply == QMessageBox::Yes) {
        // Получаем первую выбранную строку
        int selectedRow = table->currentRow();
        if (outputMode == 1) {
            // Получаем значение из первого столбца выбранной строки
            QTableWidgetItem* inn = table->item(selectedRow, 0);
            QTableWidgetItem* login = table->item(selectedRow, 2);
            if (!inn || !login) {
                QMessageBox::warning(this, "Ошибка", "Не удалось получить данные из таблицы!");
                return;
            }
            // Сохраняем значение
            QString strInn = inn->text();
            QString strLogin = login->text();
            qDebug() << "Выбранное значение1:" << strInn; // debug
            qDebug() << "Выбранное значение2:" << strLogin; // debug
            // Удаление записи
            base->deleteDirectorsBroker(strInn, strLogin);
            base->loadDirectBrokersToTable(ui->tblOutput);
        } else {
            // Получаем значение из первого столбца выбранной строки
            QTableWidgetItem* phone = table->item(selectedRow, 1);
            QTableWidgetItem* login = table->item(selectedRow, 4);
            if (!phone || !login) {
                QMessageBox::warning(this, "Ошибка", "Не удалось получить данные из таблицы!");
                return;
            }
            // Сохраняем значение
            QString strPhone = phone->text();
            QString strLogin = login->text();
            qDebug() << "Выбранное значение1:" << strPhone; // debug
            qDebug() << "Выбранное значение2:" << strLogin; // debug
            // Удаление записи
            base->deleteDirectorsEmployee(strPhone, strLogin);
            base->loadDirectEmployeesToTable(ui->tblOutput);
        }
    } else
        return;
}

