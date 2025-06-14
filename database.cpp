#include "database.h"

// Настройки базы данных
const QString typeDB = "QPSQL";
const QString hostNameDB = "localhost";
const QString nameDB = "depository";
const QString userNameDB = "postgres";
const QString passwDB = "password";

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase(typeDB);

    if (!db.open()){
        db.setDatabaseName(nameDB);
        db.setHostName(hostNameDB);
        db.setUserName(userNameDB);
        db.setPassword(passwDB);
        db.setPort(5432);
    }
}

DataBase::~DataBase(){
    db.close();
}

//------------[MainWindow]--------------
int DataBase::SelectAISUser(QString login, QString password){
    QSqlQuery query;
    query.prepare("SELECT passw, user_type FROM AISUser WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        return 0; // фатальная ошибка
    }

    if (query.next()) {
        QString dbPassword = query.value(0).toString();
        QString userType = query.value(1).toString();
        if (dbPassword == password){
            if (userType == "center")
                return 1;
            else if (userType == "broker")
                return 2;
            else if (userType == "operator")
                return 3;
            else if (userType == "director")
                return 4;
        } else {
            return -2; // неправильный пароль
        }
    } else {
        return -1;
    }
    return 0;
}
//----------[Central depository]----------
void DataBase::loadStockDataToTable(QTableWidget *tableWidget, QString filter)
{
    if (tableSelectionConnection != nullptr)
        QObject::disconnect(tableSelectionConnection);

    if (!tableWidget) return;

    // Очистка и настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(5);

    // Установка заголовков
    QStringList headers = {"Тип ЦБ", "Тикер", "ISIN", "Цена", "Статус"};
    tableWidget->setHorizontalHeaderLabels(headers);

    // Настройка внешнего вида
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setVisible(false);

    // Настройка растягивания по ширине
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Растягиваем все колонки
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Interactive); // Для ISIN делаем Interactive

    // Выполнение запроса
    QSqlQuery query(db);
    if (filter == "new"){
        if (!query.exec("SELECT stock_type, ticker, ISIN, price, st_status "
                        "FROM Stock s "
                        "WHERE s.st_status = 'получена' OR s.st_status = 'отдана' ")) {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }
    } else {
        if (!query.exec("SELECT stock_type, ticker, ISIN, price, st_status "
                        "FROM Stock s ")) {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }
    }
    // Заполнение таблицы данными
    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("stock_type").toString()));   // Type
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("ticker").toString()));       // Ticker
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("ISIN").toString()));         // ISIN
        // Price (с форматированием)
        QTableWidgetItem *priceItem = new QTableWidgetItem();
        priceItem->setData(Qt::DisplayRole, query.value("price").toDouble());
        priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 3, priceItem);

        QTableWidgetItem *statusItem = new QTableWidgetItem();
        QString status = query.value("st_status").toString();
        statusItem->setText(status);
        statusItem->setForeground(status == "получена" ? QColor(0, 128, 0) : QColor(255, 0, 0));
        tableWidget->setItem(row, 4, statusItem);
    }

    // Автоподгон ширины колонки ISIN (после заполнения данных)
    tableWidget->resizeColumnToContents(2);

    // Подключение обработчика выбора строки
    tableSelectionConnection = QObject::connect(tableWidget, &QTableWidget::itemSelectionChanged, [tableWidget]() {
        auto selected = tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            int row = selected.first()->row();
            QString isin = tableWidget->item(row, 2)->text();
            qDebug() << "Выбрана ценная бумага ISIN:" << isin;
        }
    });
}

void DataBase::loadOperationsDataToTable(QTableWidget *tableWidget, QString user, QString filter)
{
    if (tableSelectionConnection != nullptr)
        QObject::disconnect(tableSelectionConnection);

    if (!tableWidget) return;

    QStringList headers;
    if (user == "center") {
        // Настройка таблицы
        tableWidget->clear();
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(6);

        // Установка заголовков
        headers = {
            "№депо продавца", "№депо покупателя", "Сумма",
            "Ценные бумаги", "Дата", "Статус"
        };
    } else {
        // Настройка таблицы
        tableWidget->clear();
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(7);

        // Установка заголовков
        headers = {
            "ID операции", "№депо продавца", "№депо покупателя",
            "Сумма", "Ценные бумаги", "Дата", "Статус"
        };
    }
    tableWidget->setHorizontalHeaderLabels(headers);

    // Настройка внешнего вида
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Выполнение запроса
    QSqlQuery query(db);
    QString queryText;
    int posDepSel = 0;
    int posDepBuy = 1;
    int posSum = 2;
    int posISINS = 3;
    int posDate = 4;
    int posStatus = 5;
    if (user == "center"){
        queryText = "SELECT depo_saler, depo_buyer, summary_cost, "
                        "stocks_ISINS, date, status "
                        "FROM Operations ";

    } else {
        queryText = "SELECT id_operation, depo_saler, depo_buyer, "
                    "summary_cost, stocks_ISINS, date, status "
                    "FROM Operations ";
        posDepSel++;
        posDepBuy++;
        posSum++;
        posISINS++;
        posDate++;
        posStatus++;
    }

    if (filter == "new")
        queryText += "WHERE status = 0 OR status = 2 ";

    query.prepare(queryText);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    // Заполнение таблицы данными
    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        if (user != "center"){
            tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        }

        // Seller Account
        QTableWidgetItem *sellerItem = new QTableWidgetItem();
        sellerItem->setData(Qt::DisplayRole,
                            query.value("depo_saler").isNull() ? 0 :
                                query.value("depo_saler").toInt());
        tableWidget->setItem(row, posDepSel, sellerItem);

        // Buyer Account
        QTableWidgetItem *buyerItem = new QTableWidgetItem();
        buyerItem->setData(Qt::DisplayRole, query.value("depo_buyer").toInt());
        tableWidget->setItem(row, posDepBuy, buyerItem);

        // Amount (с форматированием)
        QTableWidgetItem *amountItem = new QTableWidgetItem();
        amountItem->setData(Qt::DisplayRole, query.value("summary_cost").toDouble());
        amountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, posSum, amountItem);

        // Securities (ISIN коды)
        QString isins = query.value("stocks_ISINS").toString();
        isins = isins.mid(1, isins.length()-2).replace("\"", ""); // Форматирование массива
        tableWidget->setItem(row, posISINS, new QTableWidgetItem(isins));

        // Date
        QDateTime dt = query.value("date").toDateTime();
        tableWidget->setItem(row, posDate, new QTableWidgetItem(dt.toString("dd.MM.yyyy HH:mm")));

        // Status (с цветовым оформлением)
        QTableWidgetItem *statusItem = new QTableWidgetItem();
        int status = query.value("status").toInt();
        if (status == 0){
            statusItem->setText("Registered");
            statusItem->setForeground(QColor(255, 165, 0));
        } else if (status == 1){
            statusItem->setText("Completed");
            statusItem->setForeground(QColor(0, 128, 0));
        } else {
            statusItem->setText("Freezed");
            statusItem->setForeground(QColor(0, 0, 128));
        }
        statusItem->setFont(QFont("Arial", -1, QFont::Bold));
        tableWidget->setItem(row, posStatus, statusItem);
    }

    // Настройка столбцов
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setSectionResizeMode(posStatus, QHeaderView::Stretch); // Securities
}

void DataBase::loadAccountsDataToTable(QTableWidget *tableWidget, QString filter){
    if (tableSelectionConnection != nullptr)
        QObject::disconnect(tableSelectionConnection);

    QSqlQuery query(db);
    QString queryText = "SELECT a.inn_invest, a.fio_inv, b.broker_name, a.acc_status, ad.depo_num "
                        "FROM Account a "
                        "JOIN Broker b ON a.id_broker = b.id_broker "
                        "LEFT JOIN AccDepo ad ON ad.id_account = a.id_account ";

    if (filter == "new")
        queryText += "WHERE a.acc_status = 'Зарегистрирован' OR a.acc_status = 'Отклонён'";

    queryText += "ORDER BY a.acc_status DESC ";
    query.prepare(queryText);
    query.exec();

    // Настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(5);

    // Установка заголовков
    QStringList headers = {
        "ИНН инвестора", "ФИО", "Обслуживающий брокер", "Состояние аккаунта", "№депозитарного счёта"
    };
    tableWidget->setHorizontalHeaderLabels(headers);

    while (query.next()){
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("inn_invest").toString()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("fio_inv").toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("broker_name").toString()));
        QString accStatus = query.value("acc_status").toString();
        QTableWidgetItem *statusItem = new QTableWidgetItem();
        statusItem->setText(accStatus);
        if (accStatus == "Зарегистрирован")
            statusItem->setForeground(QColor(255, 165, 0));
        else if (accStatus == "Активирован")
            statusItem->setForeground(QColor(0, 128, 0));
        else
            statusItem->setForeground(QColor(128, 0, 0));
        tableWidget->setItem(row, 3, statusItem);

        QString accDepo = query.value("depo_num").toString();
        QTableWidgetItem *accDepoItem = new QTableWidgetItem();
        if (accDepo == "")
            accDepo = "----";
        accDepoItem->setText(accDepo);
        tableWidget->setItem(row, 4, accDepoItem);
    }
    // Настройка столбцов
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // Подключение обработчика выбора
    tableSelectionConnection = QObject::connect(tableWidget, &QTableWidget::itemSelectionChanged, [tableWidget]() {
        auto selected = tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            int row = selected.first()->row();
            QString invINN = tableWidget->item(row, 0)->text();
            qDebug() << "Выбран пользователь с ИНН:" << invINN;
        }
    });
}

bool DataBase::exportReleasedStocksToCSV(const QString& filePath)
{
    //
    double price;
    QString ticker;
    QString ISIN;
    QString stock_type;

    // Запрос
    QSqlQuery query(db);
    QString sql = "SELECT price, ticker, ISIN, stock_type "
                  "FROM Stock WHERE st_status = 'отдана'";

    if (!query.exec(sql)) {
        QMessageBox::critical(nullptr, "Ошибка запроса",
                              "Ошибка выполнения SQL запроса: " + query.lastError().text());
        return false;
    }

    // Работа с файлом
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для записи");
        return false;
    }
    file.write("\xEF\xBB\xBF");
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);   // Устанавливаем кодировку UTF-8

    out << "price;ticker;ISIN;stock_type\n";

    int exportedCount = 0;
    while (query.next()) {
        price = query.value(0).toDouble();
        ticker = query.value(1).toString();
        ISIN = query.value(2).toString();
        stock_type = query.value(3).toString();
        exportedCount++;
        // Записываем данные с разделителем ";" (можно использовать ",")
        out << QString::number(price, 'f', 4) << ";"
            << ticker << ";"
            << ISIN << ";"
            << stock_type << "\n";
    }

    if (exportedCount == 0) {
        QMessageBox::information(nullptr, "Информация",
                                 "Нет акций со статусом 'отдана' для экспорта");
        return false;
    }


    file.close();
    QMessageBox::information(nullptr, "Успех",
                             QString("Успешно экспортировано %1 записей").arg(exportedCount));

    // Удаление данных из БД
    sql = "DELETE FROM Stock "
          "WHERE st_status = 'отдана';";

    if (!query.exec(sql)) {
        QMessageBox::critical(nullptr, "Ошибка запроса на удаление",
                              "Ошибка выполнения SQL запроса: " + query.lastError().text());
        file.close();
        return false;
    }

    return true;

}

bool DataBase::importReleasedStocksFromCSV(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для чтения");
        return false;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);  // Устанавливаем кодировку UTF-8

    db.transaction();

    // Пропускаем BOM и заголовок
    if (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("\xEF\xBB\xBF")) { // Проверка на BOM (Byte Order Mark)
            line = line.remove(0, 3); // Удаляем BOM
        }
        //Пропускаем заголовок
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(';');

        if (fields.size() < 4) continue;  // Пропускаем строки с недостаточным количеством полей

        QSqlQuery query(db);
        query.prepare("INSERT INTO Stock (price, ticker, ISIN, stock_type, st_status) "
                      "VALUES (:price, :ticker, :ISIN, :stock_type, :st_status)");

        bool ok;
        double price = fields[0].toDouble(&ok);
        if (!ok) {
            qDebug() << "Invalid price value: " << fields[0];
            continue; // Пропускаем строку, если значение цены неверное
        }
        query.bindValue(":price", price);
        query.bindValue(":ticker", fields[1]);
        query.bindValue(":ISIN", fields[2]);
        query.bindValue(":stock_type", fields[3]);
        query.bindValue(":st_status", "получена");

        if (!query.exec()) {
            db.rollback();
            qDebug() << "Insert error:" << query.lastError().text();
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка при добавлении записи: " + query.lastError().text());
            file.close();
            return false;
        }
    }

    db.commit();
    file.close();
    return true;
}

bool DataBase::importOperationsFromCSV(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для чтения");
        return false;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    db.transaction();

    // Пропускаем заголовок
    if (!in.atEnd()) in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(';');

        if (fields.size() < 5) continue;

        // Формируем правильный массив для PostgreSQL
        QString isins = fields[3].replace("\"", "");
        QString arraySql = "{" + isins.split(",").join(",") + "}"; // Формат: {RU0009024277} или {RU0009029541,RU0009029542}

        QSqlQuery query(db);
        query.prepare("INSERT INTO Operations (depo_buyer, depo_saler, summary_cost, stocks_ISINS, date, status) "
                      "VALUES (:depo_buyer, :depo_saler, :summary_cost, :stocks_ISINS, :date, :status)");

        query.bindValue(":depo_buyer", fields[0].isEmpty() ? QVariant() : fields[0]);
        query.bindValue(":depo_saler", fields[1].isEmpty() ? QVariant() : fields[1]);
        query.bindValue(":summary_cost", fields[2].toDouble());

        // Вариант 1: Используем строковое представление массива
        query.bindValue(":stocks_ISINS", arraySql);

        // Вариант 2: Альтернативный способ с использованием QVariantList
        // QVariantList isinList;
        // foreach (const QString &isin, isins.split(",")) {
        //     isinList << isin.trimmed();
        // }
        // query.bindValue(":stocks_ISINS", isinList);

        query.bindValue(":date", QDateTime::fromString(fields[4], "yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":status", fields.value(5, "0").toInt());

        qDebug() << "Executing query with values:"
                 << fields[0] << fields[1] << fields[2] << arraySql << fields[4];

        if (!query.exec()) {
            db.rollback();
            qDebug() << "Insert error:" << query.lastError().text();
            qDebug() << "Failed query:" << query.lastQuery();
            qDebug() << "Failed line:" << line;
            QMessageBox::critical(nullptr, "Ошибка",
                                  QString("Ошибка при добавлении записи:\n%1\n\nСтрока:\n%2")
                                      .arg(query.lastError().text())
                                      .arg(line));
            file.close();
            return false;
        }
    }

    db.commit();
    file.close();
    return true;
}

bool DataBase::rejectAccount(QString currInn){
    QSqlQuery query(db);
    query.prepare("UPDATE Account "
                  "SET acc_status = 'Отклонён' "
                  "WHERE inn_invest = :INN "
                  "AND acc_status = 'Зарегистрирован' ");
    query.bindValue(":INN", currInn);
    if (!query.exec())
        return false;
    query.next();
    return true;
}

QString DataBase::acceptAccount(QString currInn, QString newDepo){
    QSqlQuery query(db);
    // нужно найти id по инн
    query.prepare("SELECT a.id_account "
                  "FROM Account a "
                  "WHERE a.INN_invest = :INN ");
    query.bindValue(":INN", currInn);
    if (!query.exec())
        return "Пользователя не существует или \nего аккаунт уже активирован.";
    query.next();

    QString currId = query.value(0).toString();
    query.prepare("INSERT INTO AccDepo (depo_num, id_account) "
                  "values (:numer, :id_acc) ");
    query.bindValue(":numer", newDepo);
    query.bindValue(":id_acc", currId);
    if (!query.exec())
        return "Не удалось совершить операцию.";

    // нужно установить статус с зарег на активирован
    query.prepare("UPDATE Account "
                  "SET acc_status = 'Активирован' "
                  "WHERE id_account = :id_acc");
    query.bindValue(":id_acc", currId);
    if (!query.exec())
        return "Не удалось поменять статус.";

    return "Успех";
}

QString DataBase::getAccStatus(QString currInn) {
    QSqlQuery query(db);
    // нужно найти id по инн
    query.prepare("SELECT a.acc_status "
                  "FROM Account a "
                  "WHERE a.INN_invest = :INN ");
    query.bindValue(":INN", currInn);
    query.exec();
    query.next();
    return query.value(0).toString();
}
//----------[Broker]---------------
void DataBase::InnFillingCmb(QComboBox* cmbInnAccount, QString login){
    if (login != "") {
        QSqlQuery query(db);
        query.prepare("SELECT a.inn_invest "
                      "FROM Account a "
                      "JOIN Broker b ON b.id_broker = a.id_broker "
                      "JOIN AISUser u ON u.id_user = b.id_user "
                      "WHERE u.login = :login "
                      "ORDER BY a.id_account");

        query.bindValue(":login", login);
        if (query.exec()) {
            cmbInnAccount->clear();
            while (query.next()) {
                QString accountInn = query.value(0).toString();
                cmbInnAccount->addItem(QString(accountInn), accountInn);
            }
        } else {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            //stat_acc->setText("Ошибка запроса");
            return;
        }
    } else {
        QSqlQuery query(db);
        query.prepare("SELECT a.inn_invest "
                      "FROM Account a "
                      "ORDER BY a.inn_invest");

        if (query.exec()) {
            cmbInnAccount->clear();
            while (query.next()) {
                QString accountInn = query.value(0).toString();
                cmbInnAccount->addItem(QString(accountInn), accountInn);
            }
        } else {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            //stat_acc->setText("Ошибка запроса");
            return;
        }
    }
}

void DataBase::brokerFormInit(QString login, QLabel* name, QLabel* inn, QLabel* stat_acc, QLabel* stat_check) {
    QSqlQuery query(db);

    query.prepare("SELECT b.inn, b.broker_name "
                  "FROM Broker b "
                  "JOIN AISUser ais ON ais.id_user = b.id_user "
                  "WHERE ais.login = :log");

    query.bindValue(":log", login);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        name->setText("Ошибка запроса");
        inn->setText("Ошибка запроса");
        return;
    }

    if (query.next()) {
        // Устанавливаем значения из запроса
        name->setText(query.value("broker_name").toString());
        inn->setText(query.value("inn").toString());

        // Дополнительные проверки на NULL значения
        if (query.value("broker_name").isNull())
            name->setText("Не указано");
        if (query.value("inn").isNull())
            inn->setText("Не указано");
    } else {
        // Если запрос не вернул результатов
        name->setText("Брокер не найден");
        inn->setText("Не найден");
        qDebug() << "Брокер с логином" << login << "не найден";
    }

    brokerFormUpdate(login, stat_acc, stat_check);
}

void DataBase::brokerFormUpdate(QString login, QLabel* stat_acc, QLabel* stat_check){
    QSqlQuery query(db);

    query.prepare("SELECT COUNT(*) AS Kol "
                  "from Account a "
                  "JOIN Broker b on a.id_broker = b.id_broker "
                  "JOIN AISUser ais on ais.id_user = b.id_user "
                  "WHERE ais.login = :log");

    query.bindValue(":log", login);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        stat_acc->setText("Ошибка запроса");
        return;
    }

    if (query.next()) {
        // Устанавливаем значения из запроса
        stat_acc->setText(query.value("Kol").toString());
    } else {
        // Если запрос не вернул результатов
        stat_acc->setText("Брокер не найден");
        qDebug() << "Брокер с логином" << login << "не найден";
    }
}

void DataBase::loadBrokersOperationsDataToTable(QString login, QTableWidget* tableWidget, QString innAccountSearch) {
    if (!tableWidget) return;

    if (tableSelectionConnection) {
        QObject::disconnect(tableSelectionConnection);
    }

    // Очистка и настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(6);

    QStringList headers = {"Дата", "Статус", "ИНН продавца", "ИНН покупателя",
                           "Кол-во ЦБ", "Общая сумма"};
    tableWidget->setHorizontalHeaderLabels(headers);

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    // Формируем запрос с учетом реальной структуры таблиц
    QString queryText =
        "SELECT o.date, o.status, "
        "       acc_sale.INN_invest, acc_buy.INN_invest, "
        "       array_length(o.stocks_ISINS, 1) as stocks_count, "
        "       o.summary_cost "
        "FROM Operations o "
        "LEFT JOIN AccDepo adep_sale ON o.depo_saler = adep_sale.depo_num "
        "LEFT JOIN AccDepo adep_buy ON o.depo_buyer = adep_buy.depo_num "
        "LEFT JOIN Account acc_sale ON adep_sale.id_account = acc_sale.id_account "
        "LEFT JOIN Account acc_buy ON adep_buy.id_account = acc_buy.id_account "
        "LEFT JOIN Broker b_sale ON acc_sale.id_broker = b_sale.id_broker "
        "LEFT JOIN Broker b_buy ON acc_buy.id_broker = b_buy.id_broker "
        "LEFT JOIN AISUser u_sale ON b_sale.id_user = u_sale.id_user "
        "LEFT JOIN AISUser u_buy ON b_buy.id_user = u_buy.id_user "
        "WHERE (u_sale.login = ? OR u_buy.login = ? OR "
        "      (o.depo_saler IS NULL AND o.depo_buyer IS NULL AND "
        "       EXISTS (SELECT 1 FROM Broker b JOIN AISUser u ON b.id_user = u.id_user "
        "              WHERE u.login = ?))) ";

    if (!innAccountSearch.isEmpty()) {
        queryText += "AND (acc_sale.INN_invest = ? OR acc_buy.INN_invest = ?) ";
    }

    queryText += "ORDER BY o.date DESC";

    QSqlQuery query(db);
    query.prepare(queryText);

    // Добавляем параметры
    query.addBindValue(login);
    query.addBindValue(login);
    query.addBindValue(login);

    if (!innAccountSearch.isEmpty()) {
        query.addBindValue(innAccountSearch);
        query.addBindValue(innAccountSearch);
    }

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        qDebug() << "Выполняемый запрос:" << query.executedQuery();
        return;
    }

    // Заполнение таблицы данными
    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        // Дата
        QDateTime dt = query.value(0).toDateTime();
        tableWidget->setItem(row, 0, new QTableWidgetItem(dt.toString("dd.MM.yyyy HH:mm:ss")));

        // Статус
        QString status;
        switch(query.value(1).toInt()) {
        case 0: status = "Зарегистрирована"; break;
        case 1: status = "Совершена"; break;
        case 2: status = "Заморожена"; break;
        default: status = "Неизвестно";
        }
        tableWidget->setItem(row, 1, new QTableWidgetItem(status));

        // ИНН продавца
        QTableWidgetItem* saleItem = new QTableWidgetItem(query.value(2).isNull() ? "NULL" : query.value(2).toString());
        saleItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 2, saleItem);

        // ИНН покупателя
        QTableWidgetItem* buyItem = new QTableWidgetItem(query.value(3).isNull() ? "NULL" : query.value(3).toString());
        buyItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 3, buyItem);

        // Количество ЦБ
        QTableWidgetItem* countItem = new QTableWidgetItem();
        countItem->setData(Qt::DisplayRole, query.value(4).toInt());
        countItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 4, countItem);

        // Общая сумма
        QTableWidgetItem* priceItem = new QTableWidgetItem();
        priceItem->setData(Qt::DisplayRole, QString::number(query.value(5).toDouble(), 'f', 4));
        priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 5, priceItem);
    }

    // Настройка столбцов
    tableWidget->resizeColumnToContents(0);
    tableWidget->resizeColumnToContents(1);
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    tableWidget->resizeColumnToContents(4);
    tableWidget->resizeColumnToContents(5);
}

void DataBase::loadBrokersAccountDataToTable(QString login, QTableWidget* tableWidget, QString innAccountSearch)
{
    //if (!tableWidget) return;
    if (tableSelectionConnection != nullptr)
        QObject::disconnect(tableSelectionConnection);

    // Очистка и настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(4);

    // Установка заголовков
    QStringList headers = {"ИНН инвестора", "Фамилия И.О.", "Статус аккаунта", "Бюджет"};
    tableWidget->setHorizontalHeaderLabels(headers);

    // Настройка внешнего вида
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Подготовка запроса
    QSqlQuery query(db);
    QString queryText = "SELECT a.inn_invest, a.fio_inv, a.acc_status, a.budget "
                        "FROM Account a "
                        "JOIN Broker b ON a.id_broker = b.id_broker "
                        "JOIN AISUser ais ON ais.id_user = b.id_user "
                        "WHERE ais.login = :login";

    if (!innAccountSearch.isEmpty()) {
        queryText += " AND a.inn_invest = :inn_invest";
    }

    query.prepare(queryText);
    query.bindValue(":login", login);

    if (!innAccountSearch.isEmpty()) {
        query.bindValue(":inn_invest", innAccountSearch);
    }

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    // Заполнение таблицы данными
    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        // Номер счёта
        QTableWidgetItem* accountItem = new QTableWidgetItem();
        accountItem->setData(Qt::DisplayRole, query.value("inn_invest").toString());
        tableWidget->setItem(row, 0, accountItem);
        // ИНН инвестора
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("fio_inv").toString()));
        // Статус
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("acc_status").toString()));
        // Бюджет (форматирование с 4 знаками после запятой)
        QTableWidgetItem* budgetItem = new QTableWidgetItem();
        double budgetValue = query.value("budget").toDouble();
        budgetItem->setData(Qt::DisplayRole, QString::number(budgetValue, 'f', 4)); // 'f' - fixed-point notation, 4 - decimal places
        //budgetItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 3, budgetItem);
    }

    // Настройка столбцов
    tableWidget->resizeColumnToContents(0); // Автоподгон для номера счёта
    //tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Растягиваем ИНН

    // Подключение обработчика выбора строки
    tableSelectionConnection = QObject::connect(tableWidget, &QTableWidget::itemSelectionChanged, [tableWidget]() {
        auto selected = tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            int row = selected.first()->row();
            QString inn = tableWidget->item(row, 0)->text();
            QString fio = tableWidget->item(row, 1)->text();
            qDebug() << "ИНН инвестора:" << inn << "ФИО:" << fio;
        }
    });
}

void DataBase::loadBrokersStocksDataToTable(QString login, QTableWidget* tableWidget, QString innAccountSearch)
{
    if (!tableWidget) return;
    QObject::disconnect(tableSelectionConnection);
    // Очистка и настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(5);

    // Установка заголовков
    QStringList headers = {"ИНН владельца", "Тип ЦБ", "Тикер", "ISIN", "Цена"};
    tableWidget->setHorizontalHeaderLabels(headers);

    // Настройка внешнего вида
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    // Подготовка запроса
    QSqlQuery query(db);
    QString queryText = "SELECT a.inn_invest, s.stock_type, s.ticker, s.ISIN, s.price "
                        "FROM Stock s "
                        "JOIN Account a ON a.id_account = s.id_account "
                        "JOIN Broker b on a.id_broker = b.id_broker "
                        "JOIN AISUser ais on ais.id_user = b.id_user "
                        "WHERE ais.login = :login";

    if (!innAccountSearch.isEmpty()) {
        queryText += " AND a.inn_invest = :inn_invest";
    }

    query.prepare(queryText);
    query.bindValue(":login", login);

    if (!innAccountSearch.isEmpty()) {
        query.bindValue(":inn_invest", innAccountSearch);
    }

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    // Заполнение таблицы данными
    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        // Номер счёта
        QTableWidgetItem* accountItem = new QTableWidgetItem();
        accountItem->setData(Qt::DisplayRole, query.value(0).toString());
        accountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 0, accountItem);
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Тип ЦБ
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Тикер
        tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // ISIN

        // Цена (форматирование с 4 знаками после запятой)
        QTableWidgetItem* priceItem = new QTableWidgetItem();
        priceItem->setData(Qt::DisplayRole, QString::number(query.value(4).toDouble(), 'f', 4));
        priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 4, priceItem);
    }

    // Настройка столбцов
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QString DataBase::deleteBrokerAccount(QString login, QString innAccountToDelete) {
    QSqlQuery query(db);
    bool success = false;

    // Сначала проверяем, принадлежит ли счет указанному брокеру
    query.prepare("SELECT a.id_account, a.budget, count(s.id_stock) "
                  "FROM Account a "
                  "LEFT JOIN Stock s ON s.id_account = a.id_account "
                  "JOIN Broker b ON a.id_broker = b.id_broker "
                  "JOIN AISUser ais ON ais.id_user = b.id_user "
                  "WHERE ais.login = :log AND a.inn_invest = :innAccount "
                  "GROUP BY a.id_account");

    query.bindValue(":log", login);
    query.bindValue(":innAccount", innAccountToDelete);

    if (!query.exec()) {
        return "Ошибочный запрос!";
    }

    if (!query.next()) {
        return "Счет не найден или не принадлежит данному брокеру!";
    }

    if (query.value(1).toFloat() > 0) // < 0 проверять не буду - запрещу такую возможность
        return "Счёт не может быть удалён, так как на нём остались средства!";
    else if (query.value(2).toInt() > 0)
        return "Счёт не может быть удалён. У владельца остались не проданные ценные бумаги!";
    else {
        // Если проверка прошла, удаляем счет
        query.prepare("DELETE FROM Account WHERE inn_invest = :innAccount");
        query.bindValue(":innAccount", innAccountToDelete);

        if (query.exec()) {
            if (query.numRowsAffected() > 0) {
                success = true;
            }
        } else {
            qDebug() << "Ошибка удаления счета:" << query.lastError().text();
        }

        if (success) {
            return "Успешно";
        }
    }
    return "Неопознанная ошибка.";
}

QString DataBase::appendBrokerAccount(QString login, QString newINN, QString newFIO){
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(a.id_account) AS kol "
                  "FROM Account a "
                  "WHERE a.INN_invest = :INN ");
    query.bindValue(":INN", newINN);
    query.exec();
    query.next();
    if (query.value(0).toInt() != 0)
        return "Пользователь уже зарегистрирован!";

    query.prepare("SELECT b.id_broker "
                  "FROM Broker b "
                  "JOIN AISUser ais on ais.id_user = b.id_user "
                  "WHERE ais.login = :log ");
    query.bindValue(":log", login);
    query.exec();
    query.next();
    QString idBroker = query.value(0).toString();

    query.prepare("INSERT INTO Account (INN_invest, id_broker, FIO_inv) "
                  "VALUES (:INN, :broker, :FIO) ");
    query.bindValue(":broker", idBroker);
    query.bindValue(":INN", newINN);
    query.bindValue(":FIO", newFIO);
    query.exec();
    query.next();
    return "Успешно";
}

//----------[Operator]---------
void DataBase::loadDealsRequests(QTableWidget* tableWidget, int mode){
    // Настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(8);

    // Установка заголовков
    QStringList headers = {
        "ID операции", "Счёт продавца", "Счёт покупателя",
        "Сумма", "ISIN коды", "Дата", "Статус", "Депозитарий"
    };
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);

    // Настройка внешнего вида
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    //tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // Выполнение запроса
    QSqlQuery query(db);
    QString sql;
    if (mode == 0) {
        sql = "SELECT "
                      "id_operation, id_account_sale, id_account_buy, "
                      "summary_cost, stocks_ISINS, date, status, id_depository "
                      "FROM Operations "
                      "ORDER BY date DESC";
    } else {
        sql = "SELECT "
                      "id_operation, id_account_sale, id_account_buy, "
                      "summary_cost, stocks_ISINS, date, status, id_depository "
                      "FROM Operations "
                      "WHERE status = 0 "
                      "ORDER BY date DESC";
    }

    if (!query.exec(sql)) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    // Заполнение таблицы данными
    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        // ID операции
        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("id_operation").toString()));

        // Счета
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("id_account_sale").toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("id_account_buy").toString()));

        // Сумма (форматируем с 4 знаками после запятой)
        QTableWidgetItem* costItem = new QTableWidgetItem();
        costItem->setData(Qt::DisplayRole, query.value("summary_cost").toDouble());
        costItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        tableWidget->setItem(row, 3, costItem);

        // ISIN коды (массив преобразуем в строку)
        QString isins = query.value("stocks_ISINS").toString();
        isins = isins.mid(1, isins.length() - 2).replace("\"", ""); // Удаляем {} и кавычки
        tableWidget->setItem(row, 4, new QTableWidgetItem(isins));

        // Дата (форматируем)
        QDateTime dt = query.value("date").toDateTime();
        tableWidget->setItem(row, 5, new QTableWidgetItem(dt.toString("dd.MM.yyyy hh:mm")));

        // Статус (текстовое представление)
        QString status;
        switch(query.value("status").toInt()) {
        case 0: status = "Зарегистрирована"; break;
        case 1: status = "Совершена"; break;
        default: status = "Неизвестно";
        }
        tableWidget->setItem(row, 6, new QTableWidgetItem(status));

        // Депозитарий
        tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("id_depository").toString()));
    }

    // Автоподгон ширины столбцов
    tableWidget->resizeColumnsToContents();

    // Подключение обработчика выбора строки
    QObject::connect(tableWidget, &QTableWidget::itemSelectionChanged, [tableWidget]() {
        auto selected = tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            int row = selected.first()->row();
            QString operationId = tableWidget->item(row, 0)->text();
            qDebug() << "Выбрана операция ID:" << operationId;
        }
    });
}

//--------[Password window]--------
void DataBase::setPassword(QString login, QString newPassword){
    QSqlQuery query(db);

    // Первый запрос - проверка статуса операции и счетов
    query.prepare(
        "UPDATE AISUser SET passw = :newPass WHERE login = :currLog "
        );

    query.bindValue(":currLog", login);
    query.bindValue(":newPass", newPassword);
    query.exec();
}
//---------[Director]----------
void DataBase::loadDirectEmployeesToTable(QTableWidget* tableWidget){
    QSqlQuery query(db);
    // Настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(6);

    // Установка заголовков
    QStringList headers = {
        "ФИО сотрудника", "Телефон", "Зарплата", "Должность", "Логин пользователя", "Пароль"
    };
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    query.prepare("SELECT e.FIO_empl, e.phone, e.salary, e.post, ais.login, ais.passw "
                  "From Employee e "
                  "LEFT JOIN AISUser ais ON ais.id_user = e.id_user"
                  );
    if (!query.exec()) {
        qDebug() << "Ошибка:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("FIO_empl").toString()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("phone").toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("salary").toString()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("post").toString()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("login").toString()));
        tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("passw").toString()));
    }
    // Автоподгон ширины столбцов
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

void DataBase::loadDirectBrokersToTable(QTableWidget* tableWidget){
    QSqlQuery query(db);
    // Настройка таблицы
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(4);

    // Установка заголовков
    QStringList headers = {
        "ИНН брокера", "Название брокера", "Логин пользователя", "Пароль"
    };
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    query.prepare("SELECT b.INN, b.broker_name, ais.login, ais.passw "
                  "From Broker b "
                  "JOIN AISUser ais ON ais.id_user = b.id_user"
                  );
    if (!query.exec()) {
        qDebug() << "Ошибка:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("INN").toString()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("broker_name").toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("login").toString()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("passw").toString()));
    }
    // Автоподгон ширины столбцов
    tableWidget->resizeColumnsToContents();
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QString DataBase::appendDirectorsBroker(QString INN, QString name, QString login, QString password){
    QSqlQuery query(db);
    // Проверка существования пользователя в АИС
    query.prepare("SELECT ais.login "
                  "FROM AISUser ais "
                  "WHERE ais.login = :log ");
    query.bindValue(":log", login);
    query.exec();
    query.next();
    if (query.value(0).toString() == login)
        return "Пользователь с указанным логином уже существует.";

    query.prepare("SELECT b.inn "
                  "FROM Broker b "
                  "WHERE b.INN = :inn ");
    query.bindValue(":inn", INN);
    query.exec();
    query.next();
    if (query.value(0).toString() == INN)
        return "Пользователь с указанным ИНН уже существует.";

    // Добавление в АИС пользователя
    query.prepare("INSERT INTO AISUser (login, passw, user_type) "
                  "VALUES (:log, :pass, 'broker') ");
    query.bindValue(":log", login);
    query.bindValue(":pass", password);
    query.exec();

    // Получение айдишника пользователя в АИС
    query.prepare("SELECT id_user "
                  "FROM AISUser "
                  "WHERE login = :log");
    query.bindValue(":log", login);
    query.exec();
    query.next();
    QString idUser = query.value(0).toString();

    query.prepare("INSERT INTO Broker (INN, broker_name, id_user) "
                  "VALUES (:inn, :name, :id_user) ");
    query.bindValue(":inn", INN);
    query.bindValue(":name", name);
    query.bindValue(":id_user", idUser);
    if (!query.exec())
        return "Не удалось добавить сотрудника!";

    return "Успех";
}

QString DataBase::appendDirectorsEmployee(QString FIO, QString phone, QString salary, QString post, QString login, QString password){
    QSqlQuery mainQuery(db);
    mainQuery.prepare("INSERT INTO Employee (FIO_empl, phone, salary, post, id_user)"
                      "VALUES (:FIO, :phone, :salary, :post, :id_user) ");

    if (login != "" && password != "") {
        QSqlQuery query(db);
        query.prepare("SELECT ais.login "
                      "FROM AISUser ais "
                      "WHERE ais.login = :log ");
        query.bindValue(":log", login);
        query.exec();
        query.next();
        if (query.value(0).toString() == login)
            return "Пользователь с указанным логином уже существует.";

        query.prepare("SELECT e.phone "
                      "FROM Employee e "
                      "WHERE e.phone = :phone ");
        query.bindValue(":phone", phone);
        query.exec();
        query.next();
        if (query.value(0).toString() == phone)
            return "Пользователь с указанным номером телефона уже существует.";

        query.prepare("INSERT INTO AISUser (login, passw, user_type) "
                       "VALUES (:log, :pass, 'operator') ");
        query.bindValue(":log", login);
        query.bindValue(":pass", password);
        query.exec();

        query.prepare("SELECT id_user "
                      "FROM AISUser "
                      "WHERE login = :log");
        query.bindValue(":log", login);
        query.exec();
        query.next();
        QString idUser = query.value(0).toString();

        mainQuery.bindValue(":id_user", idUser);
    } else
        mainQuery.bindValue(":id_user", QVariant());

    mainQuery.bindValue(":FIO", FIO);
    mainQuery.bindValue(":phone", phone);
    mainQuery.bindValue(":salary", salary);
    mainQuery.bindValue(":post", post);
    if (!mainQuery.exec())
        return "Не удалось добавить сотрудника!";

    return "Успех";
}

void DataBase::deleteDirectorsEmployee(QString phone, QString login){
    QSqlQuery query(db);
    query.prepare("DELETE FROM Employee e "
                  "WHERE e.phone = :phone ");
    query.bindValue(":phone", phone);
    query.exec();

    if (login != ""){
        query.prepare("DELETE FROM AISUser ais "
                      "WHERE ais.login = :login ");
        query.bindValue(":login", login);
        query.exec();
    }
}

void DataBase::deleteDirectorsBroker(QString inn, QString login){
    QSqlQuery query(db);
    query.prepare("DELETE FROM Broker b "
                  "WHERE b.inn = :inn ");
    query.bindValue(":inn", inn);
    query.exec();

    query.prepare("DELETE FROM AISUser ais "
                  "WHERE ais.login = :login ");
    query.bindValue(":login", login);
    query.exec();
}

//-------------Operator part2 (test)-------
void DataBase::windowInit(QString login, QLabel* lblFio, QLabel* lblPhone){
    QSqlQuery query(db);
    query.prepare("SELECT e.fio_empl, e.phone "
                  "FROM Employee e "
                  "JOIN AISUser ais ON ais.id_user = e.id_user "
                  "WHERE ais.login = :log");

    query.bindValue(":log", login);
    query.exec();
    query.next();

    lblFio->setText(query.value(0).toString());
    lblPhone->setText(query.value(1).toString());
}

void DataBase::idFillingCmb(QComboBox* cmbIdOperation){
    QSqlQuery query(db);
    query.prepare("SELECT id_operation "
                  "FROM Operations ");
    if (query.exec()) {
        cmbIdOperation->clear();
        while (query.next()) {
            QString operationId= query.value(0).toString();
            cmbIdOperation->addItem(QString(operationId), operationId);
        }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        //stat_acc->setText("Ошибка запроса");
        return;
    }
}

QString DataBase::setFreezeOperation(QString operationId){
    QSqlQuery query(db);
    query.prepare("SELECT status FROM Operations WHERE id_operation = ?");
    query.addBindValue(operationId.toInt());

    query.exec();
    query.next();
    qDebug() << query.value(0).toInt();
    if (query.value(0).toInt() == 1)
        return "Операция уже совершена. Невозможно её отложить.";

    query.prepare("UPDATE Operations "
                  "SET status = 2 "
                  "WHERE id_operation = :operId");
    query.bindValue(":operId", operationId);
    query.exec();
    return "Успех";
}

QString DataBase::setAcceptOperation(QString operationId){
    QSqlQuery query(db);
    db.transaction(); // Начинаем транзакцию

    try {
        // 1. Получаем данные операции
        query.prepare("SELECT depo_buyer, depo_saler, summary_cost, stocks_ISINS "
                      "FROM Operations WHERE id_operation = ? AND status <> 1");
        query.addBindValue(operationId.toInt());

        if (!query.exec() || !query.next()) {
            db.rollback();
            return "Ошибка: операция не найдена или уже обработана";
        }

        QString buyerDepo = query.value("depo_buyer").toString();
        QString sellerDepo = query.value("depo_saler").toString();
        double cost = query.value("summary_cost").toDouble();
        QStringList isins = query.value("stocks_ISINS").toString()
                                .mid(1, query.value("stocks_ISINS").toString().length()-2)
                                .replace("\"", "").split(",");

        // 2. Проверка бюджета покупателя (если указан депозитарий)
        if (!buyerDepo.isEmpty()) {
            query.prepare("SELECT a.budget FROM Account a "
                          "JOIN AccDepo ad ON a.id_account = ad.id_account "
                          "WHERE ad.depo_num = ?");
            query.addBindValue(buyerDepo);

            if (!query.exec() || !query.next()) {
                db.rollback();
                return "Ошибка: не найден счет покупателя";
            }

            double buyerBudget = query.value(0).toDouble();
            if (buyerBudget < cost) {
                db.rollback();
                return "Ошибка: недостаточно средств у покупателя";
            }
        }

        // 3. Проверка и списание ценных бумаг у продавца (если указан)
        if (!sellerDepo.isEmpty()) {
            // Получаем account_id продавца
            query.prepare("SELECT id_account FROM AccDepo WHERE depo_num = ?");
            query.addBindValue(sellerDepo);

            if (!query.exec() || !query.next()) {
                db.rollback();
                return "Ошибка: не найден счет продавца";
            }

            int sellerAccountId = query.value(0).toInt();

            // Проверяем наличие всех ценных бумаг
            for (const QString& isin : isins) {
                query.prepare("SELECT 1 FROM Stock WHERE ISIN = ? AND id_account = ?");
                query.addBindValue(isin.trimmed());
                query.addBindValue(sellerAccountId);

                if (!query.exec() || !query.next()) {
                    db.rollback();
                    return "Ошибка: ценная бумага " + isin + " не найдена у продавца";
                }
            }

            // Списание ценных бумаг у продавца
            for (const QString& isin : isins) {
                if (!buyerDepo.isEmpty()){
                    query.prepare("UPDATE Stock SET id_account = NULL, st_status = 'получена' "
                                  "WHERE ISIN = ? AND id_account = ?");
                } else {
                    query.prepare("UPDATE Stock SET id_account = NULL, st_status = 'отдана' "
                                  "WHERE ISIN = ? AND id_account = ?");
                }
                query.addBindValue(isin.trimmed());
                query.addBindValue(sellerAccountId);

                if (!query.exec()) {
                    db.rollback();
                    return "Ошибка при списании ценных бумаг у продавца";
                }
            }
        }

        // 4. Проверка бесхозных ценных бумаг (если продавец не указан)
        if (sellerDepo.isEmpty()) {
            for (const QString& isin : isins) {
                query.prepare("SELECT 1 FROM Stock WHERE ISIN = ? AND id_account IS NULL");
                query.addBindValue(isin.trimmed());

                if (!query.exec() || !query.next()) {
                    db.rollback();
                    return "Ошибка: ценная бумага " + isin + " не найдена среди бесхозных";
                }
            }
        }

        // 5. Переприсвоение ценных бумаг покупателю (если указан)
        if (!buyerDepo.isEmpty()) {
            // Получаем account_id покупателя
            query.prepare("SELECT id_account FROM AccDepo WHERE depo_num = ?");
            query.addBindValue(buyerDepo);

            if (!query.exec() || !query.next()) {
                db.rollback();
                return "Ошибка: не найден счет покупателя";
            }

            int buyerAccountId = query.value(0).toInt();

            // Присвоение ценных бумаг покупателю
            for (const QString& isin : isins) {
                query.prepare("UPDATE Stock SET id_account = ?, st_status = 'присвоена' "
                              "WHERE ISIN = ? AND (id_account IS NULL OR id_account = ?)");
                query.addBindValue(buyerAccountId);
                query.addBindValue(isin.trimmed());
                query.addBindValue(buyerAccountId);

                if (!query.exec()) {
                    db.rollback();
                    return "Ошибка при присвоении ценных бумаг покупателю";
                }
            }

            // Обновление бюджета покупателя
            query.prepare("UPDATE Account SET budget = budget - ? "
                          "WHERE id_account = ?");
            query.addBindValue(cost);
            query.addBindValue(buyerAccountId);

            if (!query.exec()) {
                db.rollback();
                return "Ошибка при списании средств у покупателя";
            }
        }

        // 6. Обновление бюджета продавца (если указан)
        if (!sellerDepo.isEmpty()) {
            // Получаем account_id продавца
            query.prepare("SELECT id_account FROM AccDepo WHERE depo_num = ?");
            query.addBindValue(sellerDepo);
            query.exec();
            query.next();
            int sellerAccountId = query.value(0).toInt();

            query.prepare("UPDATE Account SET budget = budget + ? "
                          "WHERE id_account = ?");
            query.addBindValue(cost);
            query.addBindValue(sellerAccountId);

            if (!query.exec()) {
                db.rollback();
                return "Ошибка при зачислении средств продавцу";
            }
        }

        // 7. Обновление статуса операции
        query.prepare("UPDATE Operations SET status = 1 WHERE id_operation = ?");
        query.addBindValue(operationId);

        if (!query.exec()) {
            db.rollback();
            return "Ошибка при обновлении статуса операции";
        }

        db.commit(); // Фиксируем транзакцию
        return "Успех";

    } catch (...) {
        db.rollback();
        return "Неизвестная ошибка при выполнении операции";
    }
}
//-------------[Universe]----------
void DataBase::createReport(QString path, QString header, QString text){

}
