#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtSql>
#include <QTextEdit>
#include <QDebug>
#include <QLabel>
// Для импорта-экспорта данных
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
class DataBase
{
private:
    QSqlDatabase db;

public:
    DataBase();
    ~DataBase();
    QSqlDatabase getDB() const {return db;}
    //MainWindow
    int SelectAISUser(QString, QString);
    void loadStockDataToTextEdit(QTextEdit*);
    //Central depository
    void loadOperationsDataToTextEdit(QTextEdit*);
    bool exportReleasedStocksToCSV(const QString&);
    bool importReleasedStocksFromCSV(const QString&);
    bool importOperationsFromCSV(const QString&);
    //Broker
    void loadBrokersAccountDataToTextEdit(QString, QTextEdit*, QString = "");     // вывод связанных счетов
    void loadBrokersOperationsDataToTextEdit(QString,QTextEdit*, QString = "");   // вывод связанных операций
    void loadBrokersStocksDataToTextEdit(QString, QTextEdit*, QString = "");      // вывод связанных ценных бумаг
    void brokerFormInit(QString, QLabel*, QLabel*, QLabel*, QLabel*);   // основная инфа
    void brokerFormUpdate(QString, QLabel*, QLabel* );                  // обновление вспомогательных данных
    void deleteBrokerAccount(QString, QTextEdit*, QString);             // удаление счёта

    //Operator
    //HR
    //Director
};

#endif // DATABASE_H
