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

//-------MainWindow------------
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
            else if (userType == "hr")
                return 4;
            else if (userType == "director")
                return 5;
        } else {
            return -2; // неправильный пароль
        }
    } else {
        return -1;
    }
}
//-------Central depository----------
void DataBase::loadStockDataToTextEdit(QTextEdit *textEdit) {
    QSqlQuery query(db);
    if (!query.exec("SELECT price, ticker, ISIN, stock_type, id_account FROM Stock")) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    // Начинаем HTML-таблицу с адаптивным дизайном
    QString html = "<html><head><style>"
                   "table { width: 100%; border-collapse: collapse; }"
                   "th { background-color: #f2f2f2; text-align: left; padding: 8px; }"
                   "td { padding: 6px; border-bottom: 1px solid #ddd; }"
                   "tr:hover { background-color: #f5f5f5; }"
                   "</style></head><body>"
                   "<table>"
                   "<tr>"
                   "<th>Price</th>"
                   "<th>Ticker</th>"
                   "<th>ISIN</th>"
                   "<th>Type</th>"
                   "<th>Account</th>"
                   "</tr>";

    while (query.next()) {
        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "</tr>")
                    .arg(query.value(0).toDouble(), 0, 'f', 4)
                    .arg(query.value(1).toString())
                    .arg(query.value(2).toString())
                    .arg(query.value(3).toString())
                    .arg(query.value(4).toInt());
    }

    html += "</table></body></html>";

    textEdit->setHtml(html);
}

void DataBase::loadOperationsDataToTextEdit(QTextEdit *textEdit) {
    QSqlQuery query(db);
    if (!query.exec("SELECT id_account_sale, id_account_buy, summary_cost, stocks_ISINS, date, status, id_depository FROM Operations")) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    // HTML-шаблон с CSS стилями
    QString html = R"(
    <html>
    <head>
    <style>
        table {
            width: 100%;
            border-collapse: collapse;
            font-family: Arial, sans-serif;
        }
        th {
            background-color: #4CAF50;
            color: white;
            text-align: left;
            padding: 10px;
        }
        td {
            padding: 8px;
            border-bottom: 1px solid #ddd;
        }
        tr:nth-child(even) {
            background-color: #f2f2f2;
        }
        tr:hover {
            background-color: #e6f7ff;
        }
        .status-0 { color: orange; font-weight: bold; }
        .status-1 { color: green; font-weight: bold; }
    </style>
    </head>
    <body>
    <table>
        <tr>
            <th>Seller Acc</th>
            <th>Buyer Acc</th>
            <th>Amount</th>
            <th>Securities</th>
            <th>Date</th>
            <th>Status</th>
            <th>Depository</th>
        </tr>
    )";

    while (query.next()) {
        int sellerAcc = query.value(0).isNull() ? 0 : query.value(0).toInt();
        int buyerAcc = query.value(1).toInt();
        double amount = query.value(2).toDouble();
        QStringList securities = query.value(3).toStringList();
        QDateTime date = query.value(4).toDateTime();
        int status = query.value(5).toInt();
        int depository = query.value(6).toInt();

        QString statusText;
        QString statusClass;
        if (status == 0) {
            statusText = "Registered";
            statusClass = "status-0";
        } else {
            statusText = "Completed";
            statusClass = "status-1";
        }

        html += QString(R"(
        <tr>
            <td>%1</td>
            <td>%2</td>
            <td>%3 ₽</td>
            <td>%4</td>
            <td>%5</td>
            <td class="%6">%7</td>
            <td>%8</td>
        </tr>
        )")
                    .arg(sellerAcc)
                    .arg(buyerAcc)
                    .arg(amount, 0, 'f', 2)
                    .arg(securities.join(", "))
                    .arg(date.toString("dd.MM.yyyy HH:mm"))
                    .arg(statusClass)
                    .arg(statusText)
                    .arg(depository);
    }

    html += "</table></body></html>";
    textEdit->setHtml(html);
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
        query.bindValue(":st_status", "передана");

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

bool DataBase::importOperationsFromCSV(const QString& filePath)
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

        if (fields.size() < 5) continue;  // Пропускаем строки с недостаточным количеством полей

        // Разбираем массив ISIN
        QStringList isins = fields[3].replace("\"", "").split(",");
        QString arraySql = "ARRAY['" + isins.join("','") + "']";

        QSqlQuery query(db);
        query.prepare("INSERT INTO Operations (id_account_buy, id_account_sale, summary_cost, stocks_ISINS, date, status)"
                      "VALUES(:id_account_buy, :id_account_sale, :summary_cost, :stocks_ISINS, :date, :status)");

        query.bindValue(":id_account_buy", fields[0]);
        query.bindValue(":id_account_sale", fields[1]);
        query.bindValue(":summary_cost", fields[2]);
        query.bindValue(":stocks_ISINS", arraySql);
        query.bindValue(":date", fields[4]);
        query.bindValue(":status", "0");

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

//-------Broker------------
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
void DataBase::loadBrokersAccountDataToTextEdit(QString login, QTextEdit* textEdit, QString idAccountSearch) {
    QSqlQuery query(db);
    if (idAccountSearch == "") {
        query.prepare("SELECT id_account, inn_invest, budget "
                        "FROM Account a "
                        "JOIN Broker b on a.id_broker = b.id_broker "
                        "JOIN AISUser ais on ais.id_user = b.id_user "
                        "WHERE ais.login = :log");

        query.bindValue(":log", login);
        if (!query.exec()) {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }
    } else {
        query.prepare("SELECT id_account, inn_invest, budget "
                      "FROM Account a "
                      "JOIN Broker b on a.id_broker = b.id_broker "
                      "JOIN AISUser ais on ais.id_user = b.id_user "
                      "WHERE ais.login = :log AND a.id_account = :idAccountSearch");

        query.bindValue(":log", login);
        query.bindValue(":idAccountSearch", idAccountSearch);

        if (!query.exec()){
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }
    }

    // Начинаем HTML-таблицу с адаптивным дизайном
    QString html = "<html><head><style>"
                   "table { width: 100%; border-collapse: collapse; }"
                   "th { background-color: #f2f2f2; text-align: left; padding: 8px; }"
                   "td { padding: 6px; border-bottom: 1px solid #ddd; }"
                   "tr:hover { background-color: #f5f5f5; }"
                   "</style></head><body>"
                   "<table>"
                   "<tr>"
                   "<th>№депозитарного счёта</th>"
                   "<th>ИНН инвестора</th>"
                   "<th>Бюджет</th>"
                   "</tr>";

    while (query.next()) {
        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "</tr>")
                    .arg(query.value(0).toInt())
                    .arg(query.value(1).toString())
                    .arg(query.value(2).toDouble(), 0, 'f', 4);
    }

    html += "</table></body></html>";

    textEdit->setHtml(html);
}

void DataBase::loadBrokersStocksDataToTextEdit(QString login, QTextEdit* textEdit, QString idAccountSearch){
    QSqlQuery query(db);
    if (idAccountSearch == "") {
        query.prepare("SELECT a.id_account, s.stock_type, s.ticker, s.ISIN, s.price "
                      "FROM Stock s "
                      "JOIN Account a ON a.id_account = s.id_account "
                      "JOIN Broker b on a.id_broker = b.id_broker "
                      "JOIN AISUser ais on ais.id_user = b.id_user "
                      "WHERE ais.login = :log");

        query.bindValue(":log", login);
        if (!query.exec()) {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }
    } else {
        query.prepare("SELECT a.id_account, s.stock_type, s.ticker, s.ISIN, s.price "
                      "FROM Stock s "
                      "JOIN Account a ON a.id_account = s.id_account "
                      "JOIN Broker b on a.id_broker = b.id_broker "
                      "JOIN AISUser ais on ais.id_user = b.id_user "
                      "WHERE ais.login = :log AND a.id_account = :idAccountSearch");

        query.bindValue(":log", login);
        query.bindValue(":idAccountSearch", idAccountSearch);

        if (!query.exec()){
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }
    }

    // Начинаем HTML-таблицу с адаптивным дизайном
    QString html = "<html><head><style>"
                   "table { width: 100%; border-collapse: collapse; }"
                   "th { background-color: #f2f2f2; text-align: left; padding: 8px; }"
                   "td { padding: 6px; border-bottom: 1px solid #ddd; }"
                   "tr:hover { background-color: #f5f5f5; }"
                   "</style></head><body>"
                   "<table>"
                   "<tr>"
                   "<th>№счёта владельца</th>"
                   "<th>Тип ЦБ</th>"
                   "<th>Тикер</th>"
                   "<th>ISIN</th>"
                   "<th>Цена</th>"
                   "</tr>";

    while (query.next()) {
        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "</tr>")
                    .arg(query.value(0).toInt())
                    .arg(query.value(1).toString())
                    .arg(query.value(2).toString())
                    .arg(query.value(3).toString())
                    .arg(query.value(4).toDouble(), 0, 'f', 4);
    }

    html += "</table></body></html>";

    textEdit->setHtml(html);
}

void DataBase::loadBrokersOperationsDataToTextEdit(QString login, QTextEdit* textEdit, QString idAccountSearch){
    QSqlQuery query(db);
    if (idAccountSearch == "") {
        query.prepare("SELECT a.id_account, s.stock_type, s.ticker, s.ISIN, s.price "
                      "FROM Stock s "
                      "JOIN Account a ON a.id_account = s.id_account "
                      "JOIN Broker b on a.id_broker = b.id_broker "
                      "JOIN AISUser ais on ais.id_user = b.id_user "
                      "WHERE ais.login = :log");

        query.bindValue(":log", login);
        if (!query.exec()) {
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }
    } else {
        query.prepare("SELECT a.id_account, s.stock_type, s.ticker, s.ISIN, s.price "
                      "FROM Stock s "
                      "JOIN Account a ON a.id_account = s.id_account "
                      "JOIN Broker b on a.id_broker = b.id_broker "
                      "JOIN AISUser ais on ais.id_user = b.id_user "
                      "WHERE ais.login = :log AND a.id_account = :idAccountSearch");

        query.bindValue(":log", login);
        query.bindValue(":idAccountSearch", idAccountSearch);

        if (!query.exec()){
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
            return;
        }
    }

    // Начинаем HTML-таблицу с адаптивным дизайном
    QString html = "<html><head><style>"
                   "table { width: 100%; border-collapse: collapse; }"
                   "th { background-color: #f2f2f2; text-align: left; padding: 8px; }"
                   "td { padding: 6px; border-bottom: 1px solid #ddd; }"
                   "tr:hover { background-color: #f5f5f5; }"
                   "</style></head><body>"
                   "<table>"
                   "<tr>"
                   "<th>№счёта владельца</th>"
                   "<th>Тип ЦБ</th>"
                   "<th>Тикер</th>"
                   "<th>ISIN</th>"
                   "<th>Цена</th>"
                   "</tr>";

    while (query.next()) {
        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "</tr>")
                    .arg(query.value(0).toInt())
                    .arg(query.value(1).toString())
                    .arg(query.value(2).toString())
                    .arg(query.value(3).toString())
                    .arg(query.value(4).toDouble(), 0, 'f', 4);
    }

    html += "</table></body></html>";

    textEdit->setHtml(html);
}

void DataBase::deleteBrokerAccount(QString login, QTextEdit* textEdit, QString idAccountToDelete) {
    QSqlQuery query(db);
    bool success = false;

    // Сначала проверяем, принадлежит ли счет указанному брокеру
    query.prepare("SELECT a.id_account FROM Account a "
                  "JOIN Broker b ON a.id_broker = b.id_broker "
                  "JOIN AISUser ais ON ais.id_user = b.id_user "
                  "WHERE ais.login = :log AND a.id_account = :idAccount");

    query.bindValue(":log", login);
    query.bindValue(":idAccount", idAccountToDelete);

    if (!query.exec()) {
        qDebug() << "Ошибка проверки счета:" << query.lastError().text();
        textEdit->setText("Ошибка при проверке счета");
        return;
    }

    if (!query.next()) {
        textEdit->setText("Счет не найден или не принадлежит данному брокеру");
        return;
    }

    // Если проверка прошла, удаляем счет
    query.prepare("DELETE FROM Account WHERE id_account = :idAccount");
    query.bindValue(":idAccount", idAccountToDelete);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            textEdit->setText(QString("Счет №%1 успешно удален").arg(idAccountToDelete));
            success = true;
        } else {
            textEdit->setText("Счет не был удален (возможно, его не существует)");
        }
    } else {
        qDebug() << "Ошибка удаления счета:" << query.lastError().text();
        textEdit->setText("Ошибка при удалении счета");
    }

    // Обновляем список счетов после удаления
    if (success) {
        loadBrokersAccountDataToTextEdit(login, textEdit);
    }
}

//------debug-----
