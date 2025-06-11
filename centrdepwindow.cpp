#include "centrdepwindow.h"
#include "./ui_centrdepwindow.h"

// my
#include "mainwindow.h"

centrdepwindow::centrdepwindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::centrdepwindow)
{
    ui->setupUi(this);
    ui->frmDepoInit->hide();
    outputMode = 0;
    //base->InnFillingCmb(ui->comboBox);

    QTableWidget* operationsTable = ui->tblOutput;                                                          // Box field relative
    QComboBox* operationsComboBox = ui->comboBox;
    connect(operationsTable, &QTableWidget::itemSelectionChanged, [=](){
        QList<QTableWidgetItem*> selected = operationsTable->selectedItems();
        if (!selected.isEmpty() && outputMode == 3) {
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

centrdepwindow::~centrdepwindow()
{
    base->~DataBase();
    delete base;
    delete ui;
}

void centrdepwindow::on_btnStocks_clicked()
{
    if (ui->frmDepoInit->isVisible())
        ui->frmDepoInit->hide();
    base->loadStockDataToTable(ui->tblOutput);
    outputMode = 1;
}


void centrdepwindow::on_btnOperations_clicked()
{
    if (ui->frmDepoInit->isVisible())
        ui->frmDepoInit->hide();
    base->loadOperationsDataToTable(ui->tblOutput);
    outputMode = 2;
}

void centrdepwindow::on_btnStockAppend_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Сохранить CSV файл",
                                                    QDir::homePath(),
                                                    "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        base->importReleasedStocksFromCSV(filePath);
    }
}


void centrdepwindow::on_btnOperationAppend_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Открыть CSV файл",
                                                    QDir::homePath(),
                                                    "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        base->importOperationsFromCSV(filePath);
    }
}


void centrdepwindow::on_btnStockDelete_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Открыть CSV файл",
                                                    QDir::homePath(),
                                                    "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        base->exportReleasedStocksToCSV(filePath);
    }
}


void centrdepwindow::on_btnReport_clicked()
{
    QString dirPath = "C:/AIS_FS/center";

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


void centrdepwindow::on_btnBack_clicked()
{
    MainWindow *window = new MainWindow(getDataBase());
    window->show();
    this->close();
}


void centrdepwindow::on_btnDepoInit_clicked()
{
    if (ui->edtDepoNum->text().length() != 4){
        QMessageBox::warning(this, "Ошибка", "Неверный номер депозитарного счёта!");
    } else if (ui->comboBox->currentText().length() != 12){
        QMessageBox::warning(this, "Ошибка", "Неверный ИНН!");
    } else {
        // Создаем диалог подтверждения
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение изнений",
                                      QString("Вы действительно хотите присвоить инвестору счет депо №%1?\nЭто действие нельзя отменить.").arg(ui->edtDepoNum->text()),
                                      QMessageBox::Yes | QMessageBox::No);

        // Если пользователь подтвердил удаление
        if (reply == QMessageBox::Yes) {
            // функция добавления
        }
    }
}


void centrdepwindow::on_btnAccounts_clicked()
{
    if (!ui->frmDepoInit->isVisible())
        ui->frmDepoInit->show();
    base->loadAccountsDataToTable(ui->tblOutput);
    outputMode = 3;
}

