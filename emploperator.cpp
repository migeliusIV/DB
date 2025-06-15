#include "emploperator.h"
#include "ui_emploperator.h"

#include "passwchange.h"
#include "mainwindow.h"

EmplOperator::EmplOperator(DataBase* temp, QString strLogin, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmplOperator)
{
    ui->setupUi(this);
    login = strLogin;
    setDataBase(temp);
    base->windowInit(login, ui->lblFIO, ui->lblPhone);
    base->InnFillingCmb(ui->comboBox_2);
    outputMode = ui->tabWidget->currentIndex();
    filterMode = "all";
    // Account's comboBox filling
    QTableWidget* accountsTable = ui->tblOutput;
    QComboBox* accountsComboBox = ui->comboBox_2;
    connect(accountsTable, &QTableWidget::itemSelectionChanged, [=](){
        QList<QTableWidgetItem*> selected = accountsTable->selectedItems();
        if (!selected.isEmpty()) {
            // Получаем id_operation из первого столбца выбранной строки
            QString accoundInn = accountsTable->item(selected.first()->row(), 0)->text();

            // Устанавливаем значение в комбобокс
            accountsComboBox->setCurrentText(accoundInn);

            // ИЛИ если нужно найти по значению:
            int index = accountsComboBox->findText(accoundInn);
            if (index != -1) {
                accountsComboBox->setCurrentIndex(index);
            }
        }
    });

    // Opetation's comboBox filling
    QTableWidget* operationsTable = ui->tblOutput;
    QComboBox* operationsComboBox = ui->comboBox;
    base->idFillingCmb(operationsComboBox);
    connect(operationsTable, &QTableWidget::itemSelectionChanged, [=](){
        QList<QTableWidgetItem*> selected = operationsTable->selectedItems();
        if (!selected.isEmpty() && outputMode == 0) {
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

EmplOperator::~EmplOperator()
{
    delete base;
    delete ui;
}
//--------[Representation]----------
//------Operations--------
void EmplOperator::on_btnDealsAll_clicked()
{
    base->loadOperationsDataToTable(ui->tblOutput, "Oper", "all");
    base->idFillingCmb(ui->comboBox);
    filterMode = "all";
}

void EmplOperator::on_btnDealsNew_clicked()
{
    base->loadOperationsDataToTable(ui->tblOutput, "Oper", "new");
    base->idFillingCmb(ui->comboBox);
    filterMode = "new";
}
//------Accounts--------
void EmplOperator::on_btnAccntsAll_clicked()
{
    base->loadAccountsDataToTable(ui->tblOutput, "all");
}

void EmplOperator::on_btnAccntsNew_clicked()
{
    base->loadAccountsDataToTable(ui->tblOutput, "new");
}
//------Stocks--------
void EmplOperator::on_btnStocksAll_clicked()
{
    base->loadStockDataToTable(ui->tblOutput, "all");
}

void EmplOperator::on_btnStocksNew_clicked()
{
    base->loadStockDataToTable(ui->tblOutput, "new");
}
//------Views--------
void EmplOperator::on_tabWidget_tabBarClicked(int index)
{
    if (outputMode != index) {
        ui->tblOutput->clear();
        outputMode = index;
        if (outputMode == 0)
            base->loadOperationsDataToTable(ui->tblOutput, "all");
        else if (outputMode == 1)
            base->loadAccountsDataToTable(ui->tblOutput, "all");
        else
            base->loadStockDataToTable(ui->tblOutput, "all");
    }
}

//----------[Instruments]---------
void EmplOperator::on_btnUserChanges_clicked()
{
    PasswChange *window = new PasswChange(getDataBase(), login, this);
    window->show();
}

void EmplOperator::on_btnBack_2_clicked()
{
    MainWindow *window = new MainWindow(getDataBase());
    window->show();
    this->close();
}

void EmplOperator::on_btnDealsReport_clicked()
{
    // в самую последнюю очередь
}

void EmplOperator::on_btnDealReject_clicked()
{
    QString funcRes = base->setFreezeOperation(ui->comboBox->currentText());
    if (funcRes != "Успех")
        QMessageBox::warning(this, "Ошибка", funcRes);
    base->loadOperationsDataToTable(ui->tblOutput, "Oper", filterMode);
}

void EmplOperator::on_btnDealAccept_clicked()
{
    QString funcRes = base->setAcceptOperation(ui->comboBox->currentText());
    if (funcRes != "Успех")
        QMessageBox::warning(this, "Ошибка", funcRes);
    base->loadOperationsDataToTable(ui->tblOutput, "Oper", filterMode);
}

void EmplOperator::on_btnRejectAccount_clicked()
{
    QString inn = ui->comboBox_2->currentText();
    if (base->getAccStatus(inn) == "Зарегистрирован"){
        // Создаем диалог подтверждения
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение изнений",
                                      QString("Вы действительно хотите отклонить запрос на регистрацию счёта инвестору с ИНН: №%1?\nЭто действие нельзя отменить.").arg(ui->comboBox->currentText()),
                                      QMessageBox::Yes | QMessageBox::No);

        // Если пользователь подтвердил удаление
        if (reply == QMessageBox::Yes) {
            if (!base->rejectAccount(inn))
                QMessageBox::warning(this, "Ошибка", "Операция не может быть совершена");
            base->loadAccountsDataToTable(ui->tblOutput);
        }
    } else
        QMessageBox::warning(this, "Ошибка", "Операция не может быть совершена");

}
