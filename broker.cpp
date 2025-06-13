#include "broker.h"
#include "./ui_broker.h"

// Необходимость
#include "mainwindow.h"
#include "passwchange.h"

Broker::Broker(DataBase* temp, QString strLogin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Broker)
{
    ui->setupUi(this);
    login = strLogin;
    setDataBase(temp);
    // visual
    ui->frmAccAppend->hide();
    base->InnFillingCmb(ui->comboBox, login);
    base->brokerFormInit(login, ui->lblCompanyNameTxt, ui->lblINNTxt, ui->lblAccountTxt, ui->lblCheckTxt);  // statistics
    QTableWidget* operationsTable = ui->tblOutput;                                                          // Box field relative
    QComboBox* operationsComboBox = ui->comboBox;
    connect(operationsTable, &QTableWidget::itemSelectionChanged, [=](){
        QList<QTableWidgetItem*> selected = operationsTable->selectedItems();
        if (!selected.isEmpty() && outputMode == 2) {
            // Получаем id_operation из первого столбца выбранной строки
            QString operationId = operationsTable->item(selected.first()->row(), 0)->text();

            // Устанавливаем значение в комбобокс
            operationsComboBox->setCurrentText(operationId);

            // ИЛИ если нужно найти по значению:
            int index = operationsComboBox->findText(operationId);
            if (index != -1) {
                operationsComboBox->setCurrentIndex(index);
            }
        }
    });
}

Broker::~Broker()
{
    base->~DataBase();
    delete base;
    delete ui;
}

void Broker::on_btnUserChanges_clicked()
{
    PasswChange *window = new PasswChange(getDataBase(), login, this);
    window->show();
    //this->close();
}


void Broker::on_btnAccountAppend_clicked()
{
    if (!ui->frmAccAppend->isVisible()) {
        ui->frmAccAppend->show();
    } else
        ui->frmAccAppend->hide();// форма для регистрации счёта    
}

void Broker::on_btnAccept_clicked()
{
    QString FIO = ui->edtFIO->text();
    QString INN = ui->edtINNInv->text();
    if (INN.length() != 12){
        ui->edtFIO->setStyleSheet("QLineEdit { color: black; }");
        ui->edtINNInv->setStyleSheet("QLineEdit { color: red; }");
        QMessageBox::warning(this, "Ошибка", "Введён неверный ИНН!");
        return;
    } else if (INN == "000111222333") {
        ui->edtFIO->setStyleSheet("QLineEdit { color: black; }");
        ui->edtINNInv->setStyleSheet("QLineEdit { color: red; }");
        QMessageBox::warning(this, "Ошибка", "Укажите действительный ИНН!");
        return;
    } else if (FIO == "Иванов C.C."){
        ui->edtFIO->setStyleSheet("QLineEdit { color: red; }");
        ui->edtINNInv->setStyleSheet("QLineEdit { color: black; }");
        QMessageBox::warning(this, "Ошибка", "Укажите действительные ФИО инвестора!");
        return;
    } else {
        // Визуальные эффекты
        ui->edtFIO->setStyleSheet("QLineEdit { color: black; }");
        ui->edtINNInv->setStyleSheet("QLineEdit { color: black; }");
        // Обновление данных
        QString funcRes = base->appendBrokerAccount(login, INN, FIO);
        if (funcRes == "Успешно"){
            base->loadBrokersAccountDataToTable(login, ui->tblOutput);
            base->brokerFormUpdate(login, ui->lblAccountTxt, ui->lblCheckTxt);
            base->InnFillingCmb(ui->comboBox, login);
        } else {
            QMessageBox::warning(this, "Ошибка", funcRes);
        }
    }
    return;
}


void Broker::on_btnAccountDel_clicked()
{
    // Получаем номер депо для удаления
    QString depoNum = ui->comboBox->currentText();

    if (depoNum == "")
        QMessageBox::warning(this, "Ошибка", "Укажите ИНН!");
    else if (depoNum.length() != 12)
        QMessageBox::warning(this, "Ошибка", "Неправильный ИНН (нарушена длина)!");
    else {
        // Создаем диалог подтверждения
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение удаления",
                                      QString("Вы действительно хотите удалить счет №%1?\nЭто действие нельзя отменить.").arg(depoNum),
                                      QMessageBox::Yes | QMessageBox::No);

        // Если пользователь подтвердил удаление
        if (reply == QMessageBox::Yes) {
            QString funcRes = base->deleteBrokerAccount(login, depoNum);
            // Удаление выбранного счета
            if (funcRes == "Успешно") {
                // Appendix
                base->loadBrokersAccountDataToTable(login, ui->tblOutput);
                base->brokerFormUpdate(login, ui->lblAccountTxt, ui->lblCheckTxt);
                base->InnFillingCmb(ui->comboBox, login);
                // Опционально: показать сообщение об успешном удалении
                //QMessageBox::information(this, "Успешно", "Счет был удален.");
            } else {
                QMessageBox::warning(this, "Ошибка", funcRes);
            }
        } else {
            // Пользователь отменил удаление
            qDebug() << "Удаление отменено пользователем";
        }
    }
}


void Broker::on_btnOperations_clicked()
{
    base->loadBrokersOperationsDataToTable(login, ui->tblOutput);
    outputMode = 1;
}


void Broker::on_btnAccounts_clicked()
{
    base->loadBrokersAccountDataToTable(login, ui->tblOutput);
    outputMode = 2;
}


void Broker::on_btnStocks_clicked()
{
    base->loadBrokersStocksDataToTable(login, ui->tblOutput);
    outputMode = 3;
}


void Broker::on_btnSearch_clicked()
{
    switch (outputMode){
        case 1: {  // (operations)
            base->loadBrokersOperationsDataToTable(login, ui->tblOutput, ui->comboBox->currentText());
            break;
        }
        case 2: { // (accounts)
            base->loadBrokersAccountDataToTable(login, ui->tblOutput, ui->comboBox->currentText());
            break;
        }
        case 3: { // (stocks)
            base->loadBrokersStocksDataToTable(login, ui->tblOutput, ui->comboBox->currentText());
            break;
        }
    }
}

void Broker::on_btnBack_clicked()
{
    MainWindow *window = new MainWindow(getDataBase());
    window->show();
    this->close();
}

void Broker::on_btnReports_clicked()
{
    QString dirPath = "C:/AIS_FS/brokers/" + login;

    // Проверяем существование директории
    QDir dir(dirPath);
    if (!dir.exists()) {
        QMessageBox::warning(this, "Ошибка", "Директория с отчетами не найдена!");
        return;
    }

    // Открываем диалог выбора файла
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Выберите отчет для просмотра",
        dirPath,
        "Все файлы (*.*);;PDF (*.pdf);;Excel (*.xlsx *.xls);;Текстовые (*.txt)"
        );

    // Если файл выбран
    if (!filePath.isEmpty()) {
        // Открываем файл в ассоциированном приложении
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }
}

