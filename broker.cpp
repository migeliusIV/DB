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
    base->brokerFillingCmb(login, ui->comboBox);
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
    // форма для регистрации счёта
    base->brokerFormUpdate(login, ui->lblAccountTxt, ui->lblCheckTxt);
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
            QString funcRes = base->deleteBrokerAccount(login, ui->tblOutput, depoNum);
            // Удаление выбранного счета
            if (funcRes == "Успешно") {
                // Appendix
                base->loadBrokersAccountDataToTable(login, ui->tblOutput);
                base->brokerFormUpdate(login, ui->lblAccountTxt, ui->lblCheckTxt);
                base->brokerFillingCmb(login, ui->comboBox);
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

