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

    QTableWidget* operationsTable = ui->tblOutput;
    QComboBox* operationsComboBox = ui->comboBox;
    connect(operationsTable, &QTableWidget::itemSelectionChanged, [=](){
        QList<QTableWidgetItem*> selected = operationsTable->selectedItems();
        if (!selected.isEmpty()) {
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


void EmplOperator::on_btnDealsAll_clicked()
{
    base->loadDealsRequests(ui->tblOutput);
}


void EmplOperator::on_btnDealsNew_clicked()
{
    base->loadDealsRequests(ui->tblOutput, 1);
}


void EmplOperator::on_btnDealsReport_clicked()
{

}


void EmplOperator::on_btnDealCheck_clicked()
{
    if (base->checkSufficientStocksForOperation(ui->comboBox->currentText().toInt())){
        QMessageBox::information(this, "Успех", "Операция может быть совершена");
    } else {
        QMessageBox::information(this, "Ошибка", "Операция не может быть совершена");
    }
}


void EmplOperator::on_btnDealReject_clicked()
{

}


void EmplOperator::on_btnDealAccept_clicked()
{

}

/*
void DataBase::loadStockDataToTable(QTableWidget* tableWidget, const QString& filter)
{
    if (!tableWidget) {
        qWarning() << "Invalid table widget pointer";
        return;
    }

    // Сохраняем текущую сортировку
    bool wasSortingEnabled = tableWidget->isSortingEnabled();
    tableWidget->setSortingEnabled(false);

    // Настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(6);  // Добавили колонку для статуса

    // Установка заголовков
    QStringList headers = {"Price", "Ticker", "ISIN", "Type", "Account", "Status"};
    tableWidget->setHorizontalHeaderLabels(headers);

    // Настройка внешнего вида
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Растягиваем ISIN

    // Подготовка запроса
    QSqlQuery query(db);
    QString sql = "SELECT price, ticker, ISIN, stock_type, id_account, st_status FROM Stock";

    if (!filter.isEmpty()) {
        sql += " WHERE " + filter;
    }

    if (!query.exec(sql)) {
        qCritical() << "Query failed:" << query.lastError().text();
        tableWidget->setSortingEnabled(wasSortingEnabled);
        return;
    }

    // Заполнение таблицы с прогрессом
    QProgressDialog progress("Loading data...", "Cancel", 0, 0, qobject_cast<QWidget*>(tableWidget->parent()));
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    int row = 0;
    while (query.next()) {
        if (progress.wasCanceled()) {
            break;
        }

        tableWidget->insertRow(row);

        // Price (форматирование с 4 знаками после запятой)
        QTableWidgetItem* priceItem = new QTableWidgetItem();
        priceItem->setData(Qt::DisplayRole, query.value("price").toDouble());
        priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 0, priceItem);

        // Ticker
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("ticker").toString()));

        // ISIN
        QTableWidgetItem* isinItem = new QTableWidgetItem(query.value("ISIN").toString());
        isinItem->setToolTip(query.value("ISIN").toString()); // Подсказка для полного ISIN
        tableWidget->setItem(row, 2, isinItem);

        // Type
        tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("stock_type").toString()));

        // Account
        QTableWidgetItem* accountItem = new QTableWidgetItem();
        accountItem->setData(Qt::DisplayRole, query.value("id_account").toInt());
        accountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 4, accountItem);

        // Status (с цветовым оформлением)
        QTableWidgetItem* statusItem = new QTableWidgetItem(query.value("st_status").toString());
        QString status = query.value("st_status").toString().toLower();
        if (status == "получена") {
            statusItem->setForeground(Qt::darkGreen);
        } else if (status == "отдана") {
            statusItem->setForeground(Qt::darkRed);
        } else {
            statusItem->setForeground(Qt::darkBlue);
        }
        tableWidget->setItem(row, 5, statusItem);

        row++;
    }

    progress.close();

    // Восстанавливаем сортировку
    tableWidget->setSortingEnabled(wasSortingEnabled);
    if (wasSortingEnabled) {
        tableWidget->sortByColumn(0, Qt::AscendingOrder);
    }

    // Подключение обработчика выбора строки
    QObject::connect(tableWidget, &QTableWidget::itemSelectionChanged, [tableWidget]() {
        auto selected = tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            int row = selected.first()->row();
            QString isin = tableWidget->item(row, 2)->text();
            QString status = tableWidget->item(row, 5)->text();
            qDebug() << "Selected stock:" << isin << "with status:" << status;
        }
    });

    // Обновляем статистику
    updateStockStatistics(tableWidget);
}
*/
